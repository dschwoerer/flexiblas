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

void cblas_cgerc(const CBLAS_LAYOUT layout, const int M, const int N,
        const void *alpha, const void *X, const int incX,
        const void *Y, const int incY, void *A, const int lda)
{
#ifdef F77_INT
    F77_INT F77_M=M, F77_N=N, F77_lda=lda, F77_incX=incX, F77_incY=incY;
#else
#define F77_M M
#define F77_N N
#define F77_incX incX
#define F77_incY incy
#define F77_lda lda   
#endif

    current_backend->blas.cgerc.calls[POS_CBLAS] ++;

    if ( current_backend->post_init != 0 ) {
        __flexiblas_backend_init(current_backend);
        current_backend->post_init = 0;
    }
    if ( current_backend->blas.cgerc.call_cblas != NULL ) {
        double te = 0, ts = 0;
        if (__flexiblas_profile ){ 
            ts = flexiblas_wtime(); 
        }
        void (*fn)
            (const CBLAS_LAYOUT layout, const int M, const int N,
             const void *alpha, const void *X, const int incX,
             const void *Y, const int incY, void *A, const int lda)
            = current_backend->blas.cgerc.call_cblas;
        fn(layout,M,N,alpha,X,incX,Y,incY,A,lda);
        if (__flexiblas_profile ){
            te = flexiblas_wtime(); 
            current_backend->blas.cgerc.timings[POS_CBLAS] += (te - ts); 
        }
    } else {
        int n, i, tincy, incy=incY;
        float *y, *yy, *ty, *st;

        extern int CBLAS_CallFromC;
        extern int RowMajorStrg;
        RowMajorStrg = 0;

        COPY_CONST_PTR(y,Y);
        COPY_CONST_PTR(yy,Y);

        CBLAS_CallFromC = 1;
        if (layout == CblasColMajor)
        {
            FC_GLOBAL(cgerc,CGERC)( &F77_M, &F77_N, alpha, X, &F77_incX, Y, &F77_incY, A,
                    &F77_lda);
        }  else if (layout == CblasRowMajor)
        {
            RowMajorStrg = 1;
            if (N > 0)
            {
                n = N << 1;
                y = malloc(n*sizeof(float));

                ty = y;
                if( incY > 0 ) {
                    i = incY << 1;
                    tincy = 2;
                    st= y+n;
                } else {
                    i = incY *(-2);
                    tincy = -2;
                    st = y-2;
                    y +=(n-2);
                }
                do
                {
                    *y = *yy;
                    y[1] = -yy[1];
                    y += tincy ;
                    yy += i;
                }
                while (y != st);
                y = ty;

#ifdef F77_INT
                F77_incY = 1;
#else
                incy = 1;
#endif
            }
            else {
                COPY_CONST_PTR(y,Y);
            }

            FC_GLOBAL(cgeru,CGERU)( &F77_N, &F77_M, alpha, y, &F77_incY, X, &F77_incX, A,
                    &F77_lda);
            if(Y!=y)
                free(y);

        } else cblas_xerbla(1, "cblas_cgerc", "Illegal layout setting, %d\n", layout);
        CBLAS_CallFromC = 0;
        RowMajorStrg = 0;

    }
    return;
}
