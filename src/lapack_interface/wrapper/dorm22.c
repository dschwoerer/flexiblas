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
void FC_GLOBAL(dorm22,DORM22)(char* side, char* trans, blasint* m, blasint* n, blasint* n1, blasint* n2, double* q, blasint* ldq, double* c, blasint* ldc, double* work, blasint* lwork, blasint* info)
#else
void FC_GLOBAL(dorm22,DORM22)(char* side, char* trans, blasint* m, blasint* n, blasint* n1, blasint* n2, double* q, blasint* ldq, double* c, blasint* ldc, double* work, blasint* lwork, blasint* info)
#endif 
{
    double ts;
	void (*fn) (void* side, void* trans, void* m, void* n, void* n1, void* n2, void* q, void* ldq, void* c, void* ldc, void* work, void* lwork, void* info);
	if ( current_backend->post_init != 0 ) {
		__flexiblas_backend_init(current_backend); 
		current_backend->post_init = 0; 
	}
	fn = current_backend->lapack.dorm22.call_fblas; 
	if ( __flexiblas_profile ) {
		ts = flexiblas_wtime(); 
		fn((void*) side, (void*) trans, (void*) m, (void*) n, (void*) n1, (void*) n2, (void*) q, (void*) ldq, (void*) c, (void*) ldc, (void*) work, (void*) lwork, (void*) info); 
		current_backend->lapack.dorm22.timings[0] += (flexiblas_wtime() -ts);
		current_backend->lapack.dorm22.calls[0]++;
	} else { 
		fn((void*) side, (void*) trans, (void*) m, (void*) n, (void*) n1, (void*) n2, (void*) q, (void*) ldq, (void*) c, (void*) ldc, (void*) work, (void*) lwork, (void*) info); 
	} 
	return;
}
#ifdef FLEXIBLAS_ABI_IBM
void dorm22_(char* side, char* trans, blasint* m, blasint* n, blasint* n1, blasint* n2, double* q, blasint* ldq, double* c, blasint* ldc, double* work, blasint* lwork, blasint* info) __attribute__((alias(MTS(FC_GLOBAL(dorm22,DORM22)))));
#else
void dorm22(char* side, char* trans, blasint* m, blasint* n, blasint* n1, blasint* n2, double* q, blasint* ldq, double* c, blasint* ldc, double* work, blasint* lwork, blasint* info) __attribute__((alias(MTS(FC_GLOBAL(dorm22,DORM22)))));
#endif



