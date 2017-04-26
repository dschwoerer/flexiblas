SUBROUTINE FZAXPBY(N,ZA,ZX,INCX,ZB,ZY,INCY)
    !     .. Scalar Arguments ..
    DOUBLE COMPLEX ZA,ZB
    INTEGER*4 INCX,INCY,N
    !     ..
    !     .. Array Arguments ..
    DOUBLE COMPLEX ZX(*),ZY(*)
    !     ..
    !
    !  Purpose
    !  =======
    !
    !     ZAXPY constant times a vector plus constant times a vector.
    !
    !  Further Details
    !  ===============
    !
    !     jack dongarra, linpack, 3/11/78.
    !     Martin Koehler, FlexiBLAS 9/5/2014
    !     modified 12/3/93, array(1) declarations changed to array(*)
    !     modified 09/05/2014, axpy -> axpby 
    !
    !  =====================================================================
    !
    !     .. Local Scalars ..
    INTEGER*4 I,IX,IY
    !     ..
    !     .. External Functions ..
    DOUBLE PRECISION FDCABS1
    EXTERNAL FDCABS1
    !     ..
    IF (N.LE.0) RETURN
    IF (FDCABS1(ZA).EQ.0.0d0 .AND. FDCABS1(ZB).EQ.0.0d0) RETURN
    IF (INCX.EQ.1 .AND. INCY.EQ.1) THEN
        !
        !        code for both increments equal to 1
        !
        DO I = 1,N
            ZY(I) = ZB * ZY(I) + ZA*ZX(I)
        END DO
    ELSE
        !
        !        code for unequal increments or equal increments
        !          not equal to 1
        !
        IX = 1
        IY = 1
        IF (INCX.LT.0) IX = (-N+1)*INCX + 1
        IF (INCY.LT.0) IY = (-N+1)*INCY + 1
        DO I = 1,N
            ZY(IY) = ZB * ZY(IY) + ZA*ZX(IX)
            IX = IX + INCX
            IY = IY + INCY
        END DO
    END IF
    !
    RETURN
END SUBROUTINE


