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
 /* Generated: Tue Mar 28 16:07:37 2017 */ 
        
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
void FC_GLOBAL(stfsm,STFSM)(char* transr, char* side, char* uplo, char* trans, char* diag, blasint* m, blasint* n, float* alpha, float* a, float* b, blasint* ldb)
#else
void FC_GLOBAL(stfsm,STFSM)(char* transr, char* side, char* uplo, char* trans, char* diag, blasint* m, blasint* n, float* alpha, float* a, float* b, blasint* ldb)
#endif 
{
    double ts;
	void (*fn) (void* transr, void* side, void* uplo, void* trans, void* diag, void* m, void* n, void* alpha, void* a, void* b, void* ldb);
	if ( current_backend->post_init != 0 ) {
		__flexiblas_backend_init(current_backend); 
		current_backend->post_init = 0; 
	}
	fn = current_backend->lapack.stfsm.call_fblas; 
	if ( __flexiblas_profile ) {
		ts = flexiblas_wtime(); 
		fn((void*) transr, (void*) side, (void*) uplo, (void*) trans, (void*) diag, (void*) m, (void*) n, (void*) alpha, (void*) a, (void*) b, (void*) ldb); 
		current_backend->lapack.stfsm.timings[0] += (flexiblas_wtime() -ts);
		current_backend->lapack.stfsm.calls[0]++;
	} else { 
		fn((void*) transr, (void*) side, (void*) uplo, (void*) trans, (void*) diag, (void*) m, (void*) n, (void*) alpha, (void*) a, (void*) b, (void*) ldb); 
	} 
	return;
}
#ifdef FLEXIBLAS_ABI_IBM
void stfsm_(char* transr, char* side, char* uplo, char* trans, char* diag, blasint* m, blasint* n, float* alpha, float* a, float* b, blasint* ldb) __attribute__((alias(MTS(FC_GLOBAL(stfsm,STFSM)))));
#else
void stfsm(char* transr, char* side, char* uplo, char* trans, char* diag, blasint* m, blasint* n, float* alpha, float* a, float* b, blasint* ldb) __attribute__((alias(MTS(FC_GLOBAL(stfsm,STFSM)))));
#endif



