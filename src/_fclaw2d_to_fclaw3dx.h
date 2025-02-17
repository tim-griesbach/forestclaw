/*
Copyright (c) 2012-2021 Carsten Burstedde, Donna Calhoun, Scott Aiton
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

//fclaw2d_clawpatch_conservation.h
#define fclaw2d_clawpatch_registers_t fclaw3dx_clawpatch_registers_t
#define fclaw2d_clawpatch_registers fclaw3dx_clawpatch_registers
#define fclaw2d_clawpatch_packmode fclaw3dx_clawpatch_packmode
#define fclaw2d_clawpatch_packmode_t fclaw3dx_clawpatch_packmode_t
#define fclaw2d_clawpatch_fort_time_sync_f2c_t fclaw3dx_clawpatch_fort_time_sync_f2c_t
#define fclaw2d_clawpatch_fort_time_sync_samesize_t fclaw3dx_clawpatch_fort_time_sync_samesize_t
#define fclaw2d_clawpatch_time_sync_new fclaw3dx_clawpatch_time_sync_new
#define fclaw2d_clawpatch_time_sync_delete fclaw3dx_clawpatch_time_sync_delete
#define fclaw2d_clawpatch_time_sync_setup fclaw3dx_clawpatch_time_sync_setup
#define fclaw2d_clawpatch_time_sync_f2c fclaw3dx_clawpatch_time_sync_f2c
#define fclaw2d_clawpatch_time_sync_samesize fclaw3dx_clawpatch_time_sync_samesize
#define fclaw2d_clawpatch_time_sync_reset fclaw3dx_clawpatch_time_sync_reset
#define fclaw2d_clawpatch_time_sync_pack_registers fclaw3dx_clawpatch_time_sync_pack_registers

//fclaw2d_clawpatch_diagnostics.h
#define error_info_t fclaw3dx_clawpatch_error_info_t
#define fclaw2d_clawpatch_diagnostics_initialize fclaw3dx_clawpatch_diagnostics_initialize
#define fclaw2d_clawpatch_diagnostics_compute fclaw3dx_clawpatch_diagnostics_compute
#define fclaw2d_clawpatch_diagnostics_gather fclaw3dx_clawpatch_diagnostics_gather
#define fclaw2d_clawpatch_diagnostics_reset fclaw3dx_clawpatch_diagnostics_reset
#define fclaw2d_clawpatch_diagnostics_finalize fclaw3dx_clawpatch_diagnostics_finalize
#define fclaw2d_clawpatch_diagnostics_vtable_initialize fclaw3dx_clawpatch_diagnostics_vtable_initialize
#define fclaw2d_clawpatch_diagnostics_cons_default fclaw3dx_clawpatch_diagnostics_cons_default
#define fclaw2d_clawpatch_diagnostics_error_default fclaw3dx_clawpatch_diagnostics_error_default

//fclaw2d_clawpatch_fort.h
#define clawpatch_fort_copy_face_t fclaw3dx_clawpatch_fort_copy_face_t
#define clawpatch_fort_average_face_t fclaw3dx_clawpatch_fort_average_face_t
#define clawpatch_fort_interpolate_face_t fclaw3dx_clawpatch_fort_interpolate_face_t
#define clawpatch_fort_copy_corner_t fclaw3dx_clawpatch_fort_copy_corner_t
#define clawpatch_fort_average_corner_t fclaw3dx_clawpatch_fort_average_corner_t
#define clawpatch_fort_interpolate_corner_t fclaw3dx_clawpatch_fort_interpolate_corner_t
#define clawpatch_fort_tag4refinement_t fclaw3dx_clawpatch_fort_tag4refinement_t
#define clawpatch_fort_tag4coarsening_t fclaw3dx_clawpatch_fort_tag4coarsening_t
#define clawpatch_fort_exceeds_threshold_t fclaw3dx_clawpatch_fort_exceeds_threshold_t
#define clawpatch_fort_interpolate2fine_t fclaw3dx_clawpatch_fort_interpolate2fine_t
#define clawpatch_fort_average2coarse_t fclaw3dx_clawpatch_fort_average2coarse_t
#define clawpatch_fort_timeinterp_t fclaw3dx_clawpatch_fort_timeinterp_t
#define clawpatch_fort_local_ghost_pack_t fclaw3dx_clawpatch_fort_local_ghost_pack_t
#define clawpatch_fort_header_ascii_t fclaw3dx_clawpatch_fort_header_ascii_t
#define clawpatch_fort_output_ascii_t fclaw3dx_clawpatch_fort_output_ascii_t
#define clawpatch_fort_error_t fclaw3dx_clawpatch_fort_error_t
#define clawpatch_fort_conscheck_t fclaw3dx_clawpatch_fort_conscheck_t
#define clawpatch_fort_area_t fclaw3dx_clawpatch_fort_area_t
#define clawpatch_fort_norm_t fclaw3dx_clawpatch_fort_norm_t
#define FCLAW2D_CLAWPATCH_GET_REFINEMENT_CRITERIA FCLAW3DX_CLAWPATCH_GET_REFINEMENT_CRITERIA
#define FCLAW2D_CLAWPATCH_EXCEEDS_THRESHOLD FCLAW3DX_CLAWPATCH_EXCEEDS_THRESHOLD

//fclaw2d_clawpatch_options.h
#define fclaw2d_clawpatch_options_t fclaw3dx_clawpatch_options_t
#define fclaw2d_clawpatch_options fclaw3dx_clawpatch_options
#define fclaw2d_clawpatch_options_register fclaw3dx_clawpatch_options_register
#define fclaw2d_clawpatch_options_store  fclaw3dx_clawpatch_options_store 
#define fclaw2d_clawpatch_get_options fclaw3dx_clawpatch_get_options
#define fclaw2d_clawpatch_set_refinement_criteria fclaw3dx_clawpatch_set_refinement_criteria
#define fclaw2d_clawpatch_get_refinement_criteria fclaw3dx_clawpatch_get_refinement_criteria

//fclaw2d_clawpatch_output_ascii.h
#define cb_clawpatch_output_ascii fclaw3dx_clawpatch_output_ascii_cb
#define fclaw2d_clawpatch_output_ascii fclaw3dx_clawpatch_output_ascii
#define fclaw2d_clawpatch_time_header_ascii fclaw3dx_clawpatch_time_header_ascii

//fclaw2d_clawpatch_output_vtk.h
#define fclaw2d_vtk_patch_data_t fclaw3dx_vtk_patch_data_t
#define fclaw2d_vtk_write_file fclaw3dx_vtk_write_file
#define fclaw2d_clawpatch_output_vtk fclaw3dx_clawpatch_output_vtk

//fclaw2d_clawpatch_pillow.h
#define fclaw2d_clawpatch_pillow_vtable_t fclaw3dx_clawpatch_pillow_vtable_t
#define pillow_fort_copy_block_corner_t fclaw3dx_clawpatch_pillow_fort_copy_block_corner_t
#define pillow_fort_average_block_corner_t fclaw3dx_clawpatch_pillow_fort_average_block_corner_t
#define pillow_fort_interpolate_block_corner_t fclaw3dx_clawpatch_pillow_fort_interpolate_block_corner_t
#define fclaw2d_clawpatch_use_pillowsphere fclaw3dx_clawpatch_use_pillowsphere
#define fclaw2d_clawpatch_pillow_vtable_initialize fclaw3dx_clawpatch_pillow_vtable_initialize
#define fclaw2d_clawpatch_pillow_vtable fclaw3dx_clawpatch_pillow_vtable
#define fclaw2d_clawpatch_pillow_vt fclaw3dx_clawpatch_pillow_vt

//fclaw2d_clawpatch_transform.h
#define fclaw2d_clawpatch_transform_init_data fclaw3dx_clawpatch_transform_init_data
#define fclaw2d_clawpatch_face_transformation fclaw3dx_clawpatch_face_transformation
#define fclaw2d_clawpatch_face_transformation_intra fclaw3dx_clawpatch_face_transformation_intra 
#define FCLAW2D_CLAWPATCH_TRANSFORM_FACE FCLAW3DX_CLAWPATCH_TRANSFORM_FACE
#define FCLAW2D_CLAWPATCH_TRANSFORM_FACE_HALF FCLAW3DX_CLAWPATCH_TRANSFORM_FACE_HALF
#define FCLAW2D_CLAWPATCH_TRANSFORM_CORNER FCLAW3DX_CLAWPATCH_TRANSFORM_CORNER
#define FCLAW2D_CLAWPATCH_TRANSFORM_CORNER_HALF FCLAW3DX_CLAWPATCH_TRANSFORM_CORNER_HALF

//fclaw2d_clawpatch.h
#define fclaw2d_clawpatch_vtable_t fclaw3dx_clawpatch_vtable_t
#define fclaw2d_clawpatch_set_user_data_t fclaw3dx_clawpatch_set_user_data_t
#define fclaw2d_clawpatch_time_sync_pack_registers_t fclaw3dx_clawpatch_time_sync_pack_registers_t
#define fclaw2d_clawpatch_local_ghost_pack_aux_t fclaw3dx_clawpatch_local_ghost_pack_aux_t
#define fclaw2d_clawpatch_fort_local_ghost_pack_registers_t fclaw3dx_clawpatch_fort_local_ghost_pack_registers_t
#define fclaw2d_clawpatch_time_header_t fclaw3dx_clawpatch_time_header_t
#define fclaw2d_clawpatch_diagnostics_cons_t fclaw3dx_clawpatch_diagnostics_cons_t
#define fclaw2d_clawpatch_diagnostics_error_t fclaw3dx_clawpatch_diagnostics_error_t
#define fclaw2d_clawpatch_vtable_initialize fclaw3dx_clawpatch_vtable_initialize
#define fclaw2d_clawpatch_vt fclaw3dx_clawpatch_vt
#define fclaw2d_clawpatch_vtable fclaw3dx_clawpatch_vtable
#define fclaw2d_clawpatch_save_current_step fclaw3dx_clawpatch_save_current_step
#define fclaw2d_clawpatch_grid_data fclaw3dx_clawpatch_grid_data
#define fclaw2d_clawpatch_metric_scalar fclaw3dx_clawpatch_metric_scalar
#define fclaw2d_clawpatch_metric_vector fclaw3dx_clawpatch_metric_vector
#define fclaw2d_clawpatch_metric_data fclaw3dx_clawpatch_metric_data
#define fclaw2d_clawpatch_metric_data2 fclaw3dx_clawpatch_metric_data2
#define fclaw2d_clawpatch_get_area fclaw3dx_clawpatch_get_area
#define fclaw2d_clawpatch_soln_data fclaw3dx_clawpatch_soln_data
#define fclaw2d_clawpatch_aux_data fclaw3dx_clawpatch_aux_data
#define fclaw2d_clawpatch_rhs_data fclaw3dx_clawpatch_rhs_data
#define fclaw2d_clawpatch_elliptic_error_data fclaw3dx_clawpatch_elliptic_error_data
#define fclaw2d_clawpatch_elliptic_soln_data fclaw3dx_clawpatch_elliptic_soln_data
#define fclaw2d_clawpatch_get_q fclaw3dx_clawpatch_get_q
#define fclaw2d_clawpatch_get_error fclaw3dx_clawpatch_get_error
#define fclaw2d_clawpatch_get_exactsoln fclaw3dx_clawpatch_get_exactsoln
#define fclaw2d_clawpatch_size fclaw3dx_clawpatch_size
#define fclaw2d_clawpatch_get_user_data fclaw3dx_clawpatch_get_user_data
#define fclaw2d_clawpatch_set_user_data fclaw3dx_clawpatch_set_user_data
#define fclaw2d_clawpatch_get_solver_data fclaw3dx_clawpatch_get_solver_data
#define fclaw2d_clawpatch_set_solver_data fclaw3dx_clawpatch_set_solver_data
#define fclaw2d_clawpatch_timesync_data fclaw3dx_clawpatch_timesync_data
#define fclaw2d_clawpatch_get_q_timesync fclaw3dx_clawpatch_get_q_timesync
#define fclaw2d_clawpatch_get_registers fclaw3dx_clawpatch_get_registers

//fclaw2d_clawpatch.hpp
#define fclaw2d_clawpatch_t fclaw3dx_clawpatch_t
#define fclaw2d_clawpatch_get_clawpatch fclaw3dx_clawpatch_get_clawpatch
#define fclaw2d_clawpatch_get_metric_patch fclaw3dx_clawpatch_get_metric_patch