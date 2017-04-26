/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) Martin Koehler, 2015-2017
 */
 /* This file it automatically generated. Please do not edit. */
 /* Generated: Tue Mar 28 16:07:34 2017 */ 
        
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <complex.h>

#include "fortran_mangle.h"

#include "flexiblas.h"


#ifdef INTEGER8
#define blasint int64_t
#else 
#define blasint int 
#endif



#ifdef FLEXIBLAS_ABI_INTEL 
void FC_GLOBAL(dlasq6,DLASQ6)(blasint* i0, blasint* n0, double* z, blasint* pp, double* dmin, double* dmin1, double* dmin2, double* dn, double* dnm1, double* dnm2)
#else
void FC_GLOBAL(dlasq6,DLASQ6)(blasint* i0, blasint* n0, double* z, blasint* pp, double* dmin, double* dmin1, double* dmin2, double* dn, double* dnm1, double* dnm2)
#endif 
{
    double ts;
	void (*fn) (void* i0, void* n0, void* z, void* pp, void* dmin, void* dmin1, void* dmin2, void* dn, void* dnm1, void* dnm2);
	if ( current_backend->post_init != 0 ) {
		__flexiblas_backend_init(current_backend); 
		current_backend->post_init = 0; 
	}
	fn = current_backend->lapack.dlasq6.call_fblas; 
	if ( __flexiblas_profile ) {
		ts = flexiblas_wtime(); 
		fn((void*) i0, (void*) n0, (void*) z, (void*) pp, (void*) dmin, (void*) dmin1, (void*) dmin2, (void*) dn, (void*) dnm1, (void*) dnm2); 
		current_backend->lapack.dlasq6.timings[0] += (flexiblas_wtime() -ts);
		current_backend->lapack.dlasq6.calls[0]++;
	} else { 
		fn((void*) i0, (void*) n0, (void*) z, (void*) pp, (void*) dmin, (void*) dmin1, (void*) dmin2, (void*) dn, (void*) dnm1, (void*) dnm2); 
	} 
	return;
}
#ifdef FLEXIBLAS_ABI_IBM
void dlasq6_(blasint* i0, blasint* n0, double* z, blasint* pp, double* dmin, double* dmin1, double* dmin2, double* dn, double* dnm1, double* dnm2) __attribute__((alias(MTS(FC_GLOBAL(dlasq6,DLASQ6)))));
#else
void dlasq6(blasint* i0, blasint* n0, double* z, blasint* pp, double* dmin, double* dmin1, double* dmin2, double* dn, double* dnm1, double* dnm2) __attribute__((alias(MTS(FC_GLOBAL(dlasq6,DLASQ6)))));
#endif



