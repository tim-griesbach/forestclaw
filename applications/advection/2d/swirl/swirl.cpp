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

// This needs to go away.  The p4est namespace should not be used directly.
#include <p4est.h>

#include "amr_forestclaw.H"
#include "amr_utils.H"
#include "amr_waveprop.H"
#include "amr_options.h"

#include "swirl_user.H"


int
main (int argc, char **argv)
{
  int		        lp;
  MPI_Comm              mpicomm;
  sc_options_t          *options;
  fclaw2d_domain_t	*domain;
  amr_options_t         *gparms;
  amr_waveprop_parms_t  *waveprop_parms;


  lp = SC_LP_PRODUCTION;
  mpicomm = MPI_COMM_WORLD;
  fclaw_mpi_init (&argc, &argv, mpicomm, lp);

  /* ---------------------------------------------------------------
     Read parameters from .ini file.
     -------------------------------------------------------------- */
  options = sc_options_new(argv[0]);

  /* Register default parameters and any solver parameters */
  gparms = amr_options_new(options);
  waveprop_parms = amr_waveprop_parms_new(options);

  /* Parse any command line arguments.  Argument gparms is no longer needed
     as an input since the array conversion is now done in 'postprocess' */
#if 0
  amr_options_parse(options, gparms, argc, argv, lp);
#endif
  amr_options_parse(options,argc,argv,lp);

  /* Any arrays are converted here */
  amr_postprocess_parms(gparms);
  amr_waveprop_postprocess_parms(waveprop_parms);

  /* Check final state of parameters */
  amr_checkparms(gparms);
  amr_waveprop_checkparms(waveprop_parms,gparms);

  /* ---------------------------------------------------------------
     Domain geometry
     -------------------------------------------------------------- */
  domain = fclaw2d_domain_new_unitsquare (mpicomm, gparms->minlevel);

  fclaw2d_domain_list_levels(domain, lp);
  fclaw2d_domain_list_neighbors(domain, lp);

  /* ---------------------------------------------------------------
     Set domain data.
     --------------------------------------------------------------- */
  init_domain_data(domain);

  set_domain_parms(domain,gparms);
  set_waveprop_parms(domain,waveprop_parms);

  /* ---------------------------------------------------------------
     Set domain data.
     --------------------------------------------------------------- */

  /* Using user defined functions */
  link_problem_setup(domain,swirl_problem_setup);
  swirl_link_solvers(domain);

  /* Plain vanilla waveprop algorithm */
  /* link_problem_setup(domain,amr_waveprop_setprob); */
  /* amr_waveprop_link_solvers(domain); */

  /* ---------------------------------------------------------------
     Run
     --------------------------------------------------------------- */
  amrinit(&domain);
  amrrun(&domain);
  amrreset(&domain);

  sc_options_destroy (options);         /* this could be moved up */
  amr_options_destroy (gparms);
  amr_waveprop_parms_delete(waveprop_parms);

  fclaw_mpi_finalize ();

  return 0;
}
