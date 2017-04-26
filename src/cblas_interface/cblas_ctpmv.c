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


void cblas_ctpmv(const CBLAS_LAYOUT layout, const CBLAS_UPLO Uplo,
        const CBLAS_TRANSPOSE TransA, const CBLAS_DIAG Diag,
        const int N, const void  *Ap, void  *X, const int incX)
{
    char TA;
    char UL;
    char DI;
#define F77_TA &TA
#define F77_UL &UL
#define F77_DI &DI   
#ifdef F77_INT
    F77_INT F77_N=N, F77_incX=incX;
#else
#define F77_N N
#define F77_incX incX
#endif
    current_backend->blas.ctpmv.calls[POS_CBLAS] ++;

    if ( current_backend->post_init != 0 ) {
        __flexiblas_backend_init(current_backend);
        current_backend->post_init = 0;
    }
    if ( current_backend->blas.ctpmv.call_cblas != NULL ) {
        double te = 0, ts = 0;
        if ( __flexiblas_profile ) {
            ts = flexiblas_wtime(); 
        }
        void (*fn)
            (const CBLAS_LAYOUT layout, const CBLAS_UPLO Uplo,
             const CBLAS_TRANSPOSE TransA, const CBLAS_DIAG Diag,
             const int N, const void  *Ap, void  *X, const int incX)
            = current_backend->blas.ctpmv.call_cblas;
        fn(layout,Uplo,TransA,Diag,N,Ap,X,incX);
        if ( __flexiblas_profile ){
            te = flexiblas_wtime(); 
            current_backend->blas.ctpmv.timings[POS_CBLAS] += (te - ts);
        }
    } else {
        int n, i=0, tincX;
        float *st=0,*x=(float *)X;
        extern int CBLAS_CallFromC;
        extern int RowMajorStrg;
        RowMajorStrg = 0;

        CBLAS_CallFromC = 1;
        if (layout == CblasColMajor)
        {
            if (Uplo == CblasUpper) UL = 'U';
            else if (Uplo == CblasLower) UL = 'L';
            else
            {
                cblas_xerbla(2, "cblas_ctpmv","Illegal Uplo setting, %d\n", Uplo);
                CBLAS_CallFromC = 0;
                RowMajorStrg = 0;
                return;
            }
            if (TransA == CblasNoTrans) TA = 'N';
            else if (TransA == CblasTrans) TA = 'T';
            else if (TransA == CblasConjTrans) TA = 'C';
            else
            {
                cblas_xerbla(3, "cblas_ctpmv","Illegal TransA setting, %d\n", TransA);
                CBLAS_CallFromC = 0;
                RowMajorStrg = 0;
                return;
            }
            if (Diag == CblasUnit) DI = 'U';
            else if (Diag == CblasNonUnit) DI = 'N';
            else
            {
                cblas_xerbla(4, "cblas_ctpmv","Illegal Diag setting, %d\n", Diag);
                CBLAS_CallFromC = 0;
                RowMajorStrg = 0;
                return;
            }
#ifdef F77_CHAR
            F77_UL = C2F_CHAR(&UL);
            F77_TA = C2F_CHAR(&TA);
            F77_DI = C2F_CHAR(&DI);
#endif
            FC_GLOBAL(ctpmv,CTPMV)( F77_UL, F77_TA, F77_DI, &F77_N, Ap, X, &F77_incX);
        }
        else if (layout == CblasRowMajor)
        {
            RowMajorStrg = 1;
            if (Uplo == CblasUpper) UL = 'L';
            else if (Uplo == CblasLower) UL = 'U';
            else
            {
                cblas_xerbla(2, "cblas_ctpmv","Illegal Uplo setting, %d\n", Uplo);
                CBLAS_CallFromC = 0;
                RowMajorStrg = 0;
                return;
            }

            if (TransA == CblasNoTrans) TA = 'T';
            else if (TransA == CblasTrans) TA = 'N';
            else if (TransA == CblasConjTrans)
            {
                TA = 'N';
                if ( N > 0)
                {
                    if(incX > 0)
                        tincX = incX;
                    else
                        tincX = -incX;
                    i = tincX << 1;
                    n = i * N;
                    x++;
                    st = x + n;
                    do
                    {
                        *x = -(*x);
                        x += i;
                    }
                    while (x != st);
                    x -= n;
                }
            }
            else
            {
                cblas_xerbla(3, "cblas_ctpmv","Illegal TransA setting, %d\n", TransA);
                CBLAS_CallFromC = 0;
                RowMajorStrg = 0;
                return;
            }

            if (Diag == CblasUnit) DI = 'U';
            else if (Diag == CblasNonUnit) DI = 'N';
            else
            {
                cblas_xerbla(4, "cblas_ctpmv","Illegal Diag setting, %d\n", Diag);
                CBLAS_CallFromC = 0;
                RowMajorStrg = 0;
                return;
            }
#ifdef F77_CHAR
            F77_UL = C2F_CHAR(&UL);
            F77_TA = C2F_CHAR(&TA);
            F77_DI = C2F_CHAR(&DI);
#endif

            FC_GLOBAL(ctpmv,CTPMV)( F77_UL, F77_TA, F77_DI, &F77_N, Ap, X,&F77_incX);
            if (TransA == CblasConjTrans)
            {
                if (N > 0)
                {
                    do
                    {
                        *x = -(*x);
                        x += i;
                    }
                    while (x != st);
                }
            }
        }
        else cblas_xerbla(1, "cblas_ctpmv", "Illegal layout setting, %d\n", layout);
        CBLAS_CallFromC = 0;
        RowMajorStrg = 0;

    }
    return;
}
