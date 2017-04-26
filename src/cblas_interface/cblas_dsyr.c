/* $Id: flexiblas.h 3741 2013-10-01 12:54:54Z komart $ */
/* 
 Copyright (C) 2013  Martin Köhler, koehlerm@mpi-magdeburg.mpg.de

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "cblas.h"
#include "cblas_f77.h"
#include "../flexiblas.h"

void cblas_dsyr(const CBLAS_LAYOUT layout, const CBLAS_UPLO Uplo,
                const int N, const double  alpha, const double  *X,
                const int incX, double  *A, const int lda)
{
   char UL;
   #define F77_UL &UL

#ifdef F77_INT
   F77_INT F77_N=N, F77_incX=incX, F77_lda=lda;
#else
   #define F77_N N
   #define F77_incX incX
   #define F77_lda  lda
#endif
   current_backend->blas.dsyr.calls[POS_CBLAS] ++;

   if ( current_backend->post_init != 0 ) {
   	__flexiblas_backend_init(current_backend);
   	current_backend->post_init = 0;
   }
   if ( current_backend->blas.dsyr.call_cblas != NULL ) {
	   double te = 0, ts = 0;
	   if ( __flexiblas_profile ) {
		   ts = flexiblas_wtime(); 
	   }
	   void (*fn)
		  (const CBLAS_LAYOUT layout, const CBLAS_UPLO Uplo,
                const int N, const double  alpha, const double  *X,
                const int incX, double  *A, const int lda)
		   = current_backend->blas.dsyr.call_cblas;
	fn(layout,Uplo,N,alpha,X,incX,A,lda);
	if ( __flexiblas_profile ){
	   te = flexiblas_wtime(); 
	   current_backend->blas.dsyr.timings[POS_CBLAS] += (te - ts); 
	}
   } else {

	   extern int CBLAS_CallFromC;
	   extern int RowMajorStrg;
	   RowMajorStrg = 0;
	   CBLAS_CallFromC = 1;
	   if (layout == CblasColMajor)
	   {
	      if (Uplo == CblasLower) UL = 'L';
	      else if (Uplo == CblasUpper) UL = 'U';
	      else 
	      {
		 cblas_xerbla(2, "cblas_dsyr","Illegal Uplo setting, %d\n",Uplo );
		 CBLAS_CallFromC = 0;
		 RowMajorStrg = 0;
		 return;
	      }
	      #ifdef F77_CHAR
		 F77_UL = C2F_CHAR(&UL);
	      #endif

	      FC_GLOBAL(dsyr,DSYR)(F77_UL, &F77_N, &alpha, X, &F77_incX, A, &F77_lda);

	   }  else if (layout == CblasRowMajor) 
	   {
	      RowMajorStrg = 1;
	      if (Uplo == CblasLower) UL = 'U';
	      else if (Uplo == CblasUpper) UL = 'L';
	      else 
	      {
		 cblas_xerbla(2, "cblas_dsyr","Illegal Uplo setting, %d\n",Uplo );
		 CBLAS_CallFromC = 0;
		 RowMajorStrg = 0;
		 return;
	      }
	      #ifdef F77_CHAR
		 F77_UL = C2F_CHAR(&UL);
	      #endif  
	      FC_GLOBAL(dsyr,DSYR)(F77_UL, &F77_N, &alpha, X, &F77_incX, A, &F77_lda); 
	   } else cblas_xerbla(1, "cblas_dsyr", "Illegal layout setting, %d\n", layout);
	   CBLAS_CallFromC = 0;
	   RowMajorStrg = 0;
   }
   return;
} 
