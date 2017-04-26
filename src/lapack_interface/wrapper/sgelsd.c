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
 /* Generated: Tue Mar 28 16:07:35 2017 */ 
        
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
void FC_GLOBAL(sgelsd,SGELSD)(blasint* m, blasint* n, blasint* nrhs, float* a, blasint* lda, float* b, blasint* ldb, float* s, float* rcond, blasint* rank_bn, float* work, blasint* lwork, blasint* iwork, blasint* info)
#else
void FC_GLOBAL(sgelsd,SGELSD)(blasint* m, blasint* n, blasint* nrhs, float* a, blasint* lda, float* b, blasint* ldb, float* s, float* rcond, blasint* rank_bn, float* work, blasint* lwork, blasint* iwork, blasint* info)
#endif 
{
    double ts;
	void (*fn) (void* m, void* n, void* nrhs, void* a, void* lda, void* b, void* ldb, void* s, void* rcond, void* rank_bn, void* work, void* lwork, void* iwork, void* info);
	if ( current_backend->post_init != 0 ) {
		__flexiblas_backend_init(current_backend); 
		current_backend->post_init = 0; 
	}
	fn = current_backend->lapack.sgelsd.call_fblas; 
	if ( __flexiblas_profile ) {
		ts = flexiblas_wtime(); 
		fn((void*) m, (void*) n, (void*) nrhs, (void*) a, (void*) lda, (void*) b, (void*) ldb, (void*) s, (void*) rcond, (void*) rank_bn, (void*) work, (void*) lwork, (void*) iwork, (void*) info); 
		current_backend->lapack.sgelsd.timings[0] += (flexiblas_wtime() -ts);
		current_backend->lapack.sgelsd.calls[0]++;
	} else { 
		fn((void*) m, (void*) n, (void*) nrhs, (void*) a, (void*) lda, (void*) b, (void*) ldb, (void*) s, (void*) rcond, (void*) rank_bn, (void*) work, (void*) lwork, (void*) iwork, (void*) info); 
	} 
	return;
}
#ifdef FLEXIBLAS_ABI_IBM
void sgelsd_(blasint* m, blasint* n, blasint* nrhs, float* a, blasint* lda, float* b, blasint* ldb, float* s, float* rcond, blasint* rank_bn, float* work, blasint* lwork, blasint* iwork, blasint* info) __attribute__((alias(MTS(FC_GLOBAL(sgelsd,SGELSD)))));
#else
void sgelsd(blasint* m, blasint* n, blasint* nrhs, float* a, blasint* lda, float* b, blasint* ldb, float* s, float* rcond, blasint* rank_bn, float* work, blasint* lwork, blasint* iwork, blasint* info) __attribute__((alias(MTS(FC_GLOBAL(sgelsd,SGELSD)))));
#endif



