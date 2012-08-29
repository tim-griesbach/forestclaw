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

#ifndef FORESTCLAW2D_H
#define FORESTCLAW2D_H

#include <p4est_wrap.h>

#ifdef __cplusplus
extern "C"
{
#if 0
}                               /* need this because indent is dumb */
#endif
#endif

typedef struct fclaw2d_domain fclaw2d_domain_t;
typedef struct fclaw2d_block fclaw2d_block_t;
typedef struct fclaw2d_patch fclaw2d_patch_t;

typedef void (*fclaw2d_mapc2m_t) (const double xyc[2], double xyzp[3],
                                  fclaw2d_domain_t * domain, void *user);

/*
 * The domain structure gives a processor local view of the grid hierarchy.
 * Unless explicitly noted otherwise, all variables are processor local,
 * i.e., they are generally different on each processor.
 * Variables that are synchronized and shared between processors
 * are denoted *global*.
 */

struct fclaw2d_patch
{
    int level;                  /* 0 is root, increases if refined */
    double xlower, xupper;
    double ylower, yupper;
    fclaw2d_patch_t *next;      /* next patch same level same block */
    void *user;
};

struct fclaw2d_block
{
    double xlower, xupper;
    double ylower, yupper;
    fclaw2d_mapc2m_t mapc2m;
    void *mapc2m_user;
    int mthbc[4];               /* >0 for physical bc types */
    int num_patches;            /* local patches in this block */
    int num_patches_before;     /* in all previous blocks */
    int minlevel, maxlevel;     /* local over this block */
    fclaw2d_patch_t *patches;   /* allocated storage */
    fclaw2d_patch_t *patchbylevel[P4EST_MAXLEVEL + 1];  /* pointers */
    void *user;
};

struct fclaw2d_domain
{
    MPI_Comm mpicomm;           /* MPI communicator */
    int mpisize, mpirank;       /* MPI variables */
    int num_patches_all;        /* sum over all blocks */
    int minlevel_all, maxlevel_all;     /* proc local */
    int global_minlevel, global_maxlevel;       /* global */
    int possible_maxlevel;      /* theoretical maximum */
    int num_blocks;
    fclaw2d_block_t *blocks;    /* allocated storage */
    int *patch_to_block;        /* allocated storage */
    p4est_wrap_t *pp;
    void *user;
};

int fclaw2d_domain_dimension (fclaw2d_domain_t * domain);
int fclaw2d_domain_num_faces (fclaw2d_domain_t * domain);
int fclaw2d_domain_num_corners (fclaw2d_domain_t * domain);
int fclaw2d_domain_num_face_corners (fclaw2d_domain_t * domain);
int fclaw2d_domain_num_orientations (fclaw2d_domain_t * domain);
void fclaw2d_domain_corner_faces (fclaw2d_domain_t * domain,
                                  int icorner, int faces[2]);

/** Callback prototype for the patch iterators.
 * \param [in] domain	General domain structure.
 * \param [in] patch	The patch currently processed by the iterator.
 * \param [in] blockno  Block number of processed patch.
 * \param [in] patchno  Patch number within block of processed patch.
 * \param [in,out] user	Data that was passed into the iterator functions.
 */
typedef void (*fclaw2d_patch_callback_t)
    (fclaw2d_domain_t * domain, fclaw2d_patch_t * patch,
     int blockno, int patchno, void *user);

/** Iterate over all patches on a given level.
 * \param [in] domain	General domain structure.
 * \param [in] level	Level to iterate.  Ignore patches of other levels.
 * \param [in] pcb	Function called for each patch of matching level.
 * \param [in,out] user	Data is passed to the pcb callback.
 */
void fclaw2d_domain_iterate_level (fclaw2d_domain_t * domain, int level,
                                   fclaw2d_patch_callback_t pcb, void *user);

/** Iterate over all patches of all levels.
 * \param [in] domain	General domain structure.
 * \param [in] pcb	Function called for each patch in the domain.
 * \param [in,out] user	Data is passed to the pcb callback.
 */
void fclaw2d_domain_iterate_patches (fclaw2d_domain_t * domain,
                                     fclaw2d_patch_callback_t pcb,
                                     void *user);

/** Determine boundary type >0 from fclaw2d_block_t, or 0 for neighbor patches.
 * \param [in] domain	Valid domain structure.
 * \param [in] blockno	Number of the block within the domain.
 * \param [in] patchno	Number of the patch within the block.
 * \param [in,out] boundaries	Domain boundaries as present in block->mthbc.
 *			The order is left, right, bottom, top.
 * \return		True if at least one patch face is on a boundary.
 */
int fclaw2d_patch_boundary_type (fclaw2d_domain_t * domain,
                                 int blockno, int patchno, int boundaries[4]);



typedef enum fclaw2d_face_neighbor
{
    FCLAW2D_FACE_NEIGHBOR_BOUNDARY,
    FCLAW2D_FACE_NEIGHBOR_HALFSIZE,
    FCLAW2D_FACE_NEIGHBOR_SAMESIZE,
    FCLAW2D_FACE_NEIGHBOR_DOUBLESIZE
}
fclaw2d_face_neighbor_t;

/** Determine neighbor patch(es) and orientation across a given face.
 * \param [in] domain	Valid domain structure.
 * \param [in] blockno	Number of the block within the domain.
 * \param [in] patchno	Number of the patch within the block.
 * \param [in] faceno	Number of the patch face: left, right, bottom, top.
 * \param [in,out] rproc	Processor number of neighbor patches.
 * \param [in,out] rblockno	Neighbor block number.
 * \param [in,out] rpatchno	Neighbor patch numbers for up to 2 neighbors.
 * \param [in,out] rfaceno	Neighbor face number and orientation.
 * \return			The Type of face neighbor connection.
 */
fclaw2d_face_neighbor_t fclaw2d_patch_face_neighbors (fclaw2d_domain_t *
                                                      domain, int blockno,
                                                      int patchno,
                                                      int faceno,
                                                      int rproc[2],
                                                      int *rblockno,
                                                      int rpatchno[2],
                                                      int *rfaceno);

/** Determine neighbor patch(es) and orientation across a given corner.
 * The current version only looks for same-proc same-tree same-size neighbors.
 * \param [in] domain	Valid domain structure.
 * \param [in] blockno	Number of the block within the domain.
 * \param [in] patchno	Number of the patch within the block.
 * \param [in] cornerno	Number of the patch corner: bl, br, tl, tr.
 * \return			The patch number in blockno or -1 if not found.
 */
int fclaw2d_patch_corner_neighbors (fclaw2d_domain_t * domain,
                                    int blockno, int patchno, int cornerno);

/** Mark a patch for refinement.
 */
void fclaw2d_patch_mark_refine (fclaw2d_domain_t * domain,
                                int blockno, int patchno);

/** Mark a patch for coarsening.
 * Coarsening will only happen if all sibling patches are marked as well.
 */
void fclaw2d_patch_mark_coarsen (fclaw2d_domain_t * domain,
                                 int blockno, int patchno);



/* We don't need very much, since we only copy the user data from old patch to the new patch */
typedef void (*fclaw2d_match_unchanged_callback_t)
    (fclaw2d_domain_t * old_domain, fclaw2d_domain_t * new_domain,
     fclaw2d_patch_t * old_patch, fclaw2d_patch_t *new_patch, void *user);

/* Iterate over patches at level 'level' that didn't change upon regridding */
/* 'level' here refers to the level of the old patch */
void
fclaw2d_domain_iterate_unchanged(fclaw2d_domain_t *old_domain, fclaw2d_domain_t *new_domain, int level,
                               fclaw2d_match_unchanged_callback_t cb_user, void *user);


/* Four new patches are passed in, which must be initialized by interpolation from old patch. */
typedef void (*fclaw2d_match_refined_callback_t)
    (fclaw2d_domain_t * old_domain, fclaw2d_domain_t * new_domain,
     fclaw2d_patch_t * old_patch, fclaw2d_patch_t **new_patch, void *user);

/* Iterate over patches which have been refined */
void
fclaw2d_domain_iterate_refined(fclaw2d_domain_t *old_domain, fclaw2d_domain_t *new_domain, int level,
                               fclaw2d_match_refined_callback_t cb_user, void *user);


/* Four new patches are passed in, which must be initialized by interpolation from old patch. */
/* For this, it would be easiest if all four siblings were passed in at the same time */
typedef void (*fclaw2d_match_coarsened_callback_t)
    (fclaw2d_domain_t * old_domain, fclaw2d_domain_t * new_domain,
     fclaw2d_patch_t **old_patch, fclaw2d_patch_t *new_patch, void *user);

/* Iterate over patches which have been coarsened */
void
fclaw2d_domain_iterate_coarsened(fclaw2d_domain_t *old_domain, fclaw2d_domain_t *new_domain, int level,
                                 fclaw2d_match_coarsened_callback_t cb_user, void *user);

#ifdef __cplusplus
#if 0
{                               /* need this because indent is dumb */
#endif
}
#endif

#endif
