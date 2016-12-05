/*
  Copyright (c) 2012 Carsten Burstedde, Donna Calhoun
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "sphere_user.h"

#include <fclaw2d_forestclaw.h>
#include <fc2d_clawpack46.h>

#include <fclaw2d_map.h>
#include <fclaw2d_map_query.h>
#include <p4est_connectivity.h>

static void *
    options_register_user (fclaw_app_t * app, void *package, sc_options_t * opt)
{
    user_options_t* user = (user_options_t*) package;

    sc_options_add_int (opt, 0, "example", &user->example, 0,
                        "[user] 0 for cubed sphere, "    \
                        "2 for pillow sphere ");

    sc_options_add_int (opt, 0, "claw-version", &user->claw_version, 5,
                        "[user] Clawpack version (4 or 5) [5]");

    sc_options_add_double (opt, 0, "revs-per-second", &user->revs_per_second, 2,
                        "[user] Revolutions per second [2]");

    user->is_registered = 1;
    return NULL;
}

static fclaw_exit_type_t
    options_check_user (fclaw_app_t * app, void *package, void *registered)
{
    user_options_t* user = (user_options_t*) package;
    if (user->example < 0 || user->example > 2) {
        fclaw_global_essentialf ("Option --user:example must be 0 or 1\n");
        return FCLAW_EXIT_ERROR;
    }
    return FCLAW_NOEXIT;
}

#if 0
static void
    options_destroy_user(fclaw_app_t* app, void* package, void *registered)
{
    user_options_t* user = (user_options_t*) package;
    FCLAW_ASSERT(user != NULL);
    FCLAW_FREE(user);
};
#endif

static const fclaw_app_options_vtable_t options_vtable_user = {
    options_register_user,
    NULL,      /* options_postprocess_user */
    options_check_user,
    NULL
};


static
void register_user_options (fclaw_app_t * app,
                            const char *configfile,
                            user_options_t* user)
{
    FCLAW_ASSERT (app != NULL);

    /* sneaking the version string into the package pointer */
    /* when there are more parameters to pass, create a structure to pass */
    fclaw_app_options_register (app,"user", configfile, &options_vtable_user,
                                user);
}


const user_options_t* sphere_user_get_options(fclaw2d_domain_t* domain)
{
    fclaw_app_t* app;
    app = fclaw2d_domain_get_app(domain);

    const user_options_t* user = (user_options_t*) fclaw_app_get_user(app);

    return (user_options_t*) user;
}


static
    void run_program(fclaw_app_t* app)
    {
        sc_MPI_Comm            mpicomm;

        /* Mapped, multi-block domain */
        p4est_connectivity_t     *conn = NULL;
        fclaw2d_domain_t	 *domain;
        fclaw2d_map_context_t    *cont = NULL;

        amr_options_t   *gparms;
        user_options_t  *user;

        /* Used locally */
        double pi = M_PI;
        double rotate[2];

        mpicomm = fclaw_app_get_mpi_size_rank (app, NULL, NULL);

        gparms = fclaw_forestclaw_get_options(app);
        user = (user_options_t*) fclaw_app_get_user(app);

        rotate[0] = pi*gparms->theta/180.0;
        rotate[1] = pi*gparms->phi/180.0;

        switch (user->example) {
        case 0:
            conn = p4est_connectivity_new_cubed();
            cont = fclaw2d_map_new_cubedsphere(gparms->scale,gparms->shift,rotate);
            break;
        case 1:
            conn = p4est_connectivity_new_pillow();
            cont = fclaw2d_map_new_pillowsphere(gparms->scale,gparms->shift,rotate);
            break;
        default:
            SC_ABORT_NOT_REACHED (); /* must be checked in torus_checkparms */
        }

        domain = fclaw2d_domain_new_conn_map (mpicomm, gparms->minlevel, conn, cont);

        fclaw2d_domain_list_levels(domain, FCLAW_VERBOSITY_ESSENTIAL);
        fclaw2d_domain_list_neighbors(domain, FCLAW_VERBOSITY_DEBUG);

        /* ---------------------------------------------------------------
           Set domain data.
           --------------------------------------------------------------- */
        fclaw2d_domain_data_new(domain);
        fclaw2d_domain_set_app(domain,app);

        sphere_link_solvers(domain);

        /* --------------------------------------------------
           Initialize and run the simulation
           -------------------------------------------------- */

        fclaw2d_initialize(&domain);
        fclaw2d_run(&domain);
        fclaw2d_finalize(&domain);

        /* --------------------------------------------------
           Clean up the mapping context.
           -------------------------------------------------- */
        fclaw2d_map_destroy (cont);
    }


int main (int argc, char **argv)
{
    int first_arg;
    fclaw_app_t *app;
    fclaw_exit_type_t vexit;

    /* options */
    sc_options_t    *options;
    user_options_t    suser_options, *user = &suser_options;

    int retval;

    /* Initialize application */
    app = fclaw_app_new (&argc, &argv, user);
    fclaw2d_clawpatch_link_app (app);

    /* Register packages */
    fclaw_forestclaw_register(app,"fclaw_options.ini");
    fc2d_clawpack46_register(app,"fclaw_options.ini");
    fc2d_clawpack5_register(app,"fclaw_options.ini");

    /* User options */
    register_user_options (app, "fclaw_options.ini",user);

    /* Read configuration file(s) and command line, and process options */
    options = fclaw_app_get_options (app);
    retval = fclaw_options_read_from_file(options);
    vexit =  fclaw_app_options_parse (app, &first_arg,"fclaw_options.ini.used");

    /* Run program */
    if (!retval & !vexit)
    {
        run_program(app);
    }

    fclaw_forestclaw_destroy(app);
    fclaw_app_destroy (app);

    return 0;
}
