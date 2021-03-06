MODULE mod_sq_mvm
  USE omp_lib
  IMPLICIT none
  INTEGER, PARAMETER :: rk=kind(1.0d0)
  INTERFACE
     SUBROUTINE dummy(x)
       IMPORT :: rk
       REAL(rk) :: x(:)
     END SUBROUTINE dummy
  END INTERFACE
CONTAINS
  SUBROUTINE mvm1(a, x, r, ialg, stat)
    REAL(KIND=rk), INTENT(IN) :: a(:,:), x(:)
    REAL(KIND=rk), INTENT(INOUT) :: r(:)
    INTEGER, INTENT(IN) :: ialg
    INTEGER, INTENT(OUT) :: stat

    INTEGER :: j, k, n

    stat = 0
    IF ( size(a,2) < size(x,1) .or. size(a, 1) < size(r,1) .or. &
         size(r, 1) > size(x, 1) ) THEN
       stat = 1
       RETURN
    END IF
    n = size(a, 1)

!$OMP parallel do
    DO j = 1, n
       r(j) = 0.0_rk
       DO k = 1, n
          r(j) = r(j) + a(j, k) * x(k)
       END DO
    END DO
!$OMP end parallel do

  END SUBROUTINE mvm1
  SUBROUTINE mvm2(a, x, r, ialg, stat)
    REAL(KIND=rk), INTENT(IN) :: a(:,:), x(:)
    REAL(KIND=rk), INTENT(INOUT), CONTIGUOUS :: r(:)
    INTEGER, INTENT(IN) :: ialg
    INTEGER, INTENT(OUT) :: stat

    INTEGER :: j, k, n

    stat = 0
    IF ( size(a,2) < size(x,1) .or. size(a, 1) < size(r,1) .or. &
         size(r, 1) > size(x, 1) ) THEN
       stat = 1
       RETURN
    END IF
    n = size(a, 1)
!$OMP parallel
!$OMP do
    DO j = 1, n
      r(j) = 0.0_rk
    END DO
!$OMP end do
!$OMP do reduction(+:r)
    DO k = 1, n
       DO j = 1, n
          r(j) = r(j) + a(j, k) * x(k)
       END DO
    END DO
!$OMP end do
!$OMP end parallel
  END SUBROUTINE mvm2
END MODULE mod_sq_mvm
PROGRAM sq_mvm
  USE mod_sq_mvm
  IMPLICIT none
  INTEGER, PARAMETER :: dim = 4
  INTEGER, PARAMETER :: variant = 2
  INTEGER :: isz(dim) = [ 1000, 2000, 4000, 8000 ]
  REAL(KIND=rk), ALLOCATABLE :: a(:,:), x(:), r(:)
  REAL(KIND=rk) :: ti, ops
  INTEGER :: in, is, it, istat, j, k, kb, n, nt, nit
  CHARACTER(len=3) :: cs

  WRITE(*,'(''Size  Threads  Time(s)   Perf(Mflop/s)   Checksum'')')
  nt = 1
!$OMP parallel
!$OMP master
!$ nt = omp_get_num_threads()
!$OMP end master
!$OMP end parallel
  DO in=1, dim
     n = isz(in)

     ALLOCATE(a(n,n), x(n), r(n))


     DO k = 1, n
        x(k) = 2.0e-2_rk
        DO j = 1, n
           a(j, k) = 1.0_rk
        END DO
     END DO

     nit = max(1,(20000/n)**2)

     ops = 2 * real(n,rk) * real(n,rk)
     ti = omp_get_wtime()
     SELECT CASE (variant)
     CASE(1)
       DO it=1, nit
          CALL mvm2(a, x, r, is, istat)
       END DO
     CASE(2)
       DO it=1, nit
          CALL mvm2(a, x, r, is, istat)
       END DO
     END SELECT
     ti = omp_get_wtime() - ti

     IF (istat /= 0) THEN
        WRITE(*,'(''failed mvm execution - aborting.'')')
        STOP
     ELSE
        WRITE(*,'(I4,3X,I3,X,1P,E12.3,4X,0P,F7.1,4X,E15.8)') n, nt, ti, &
             nit*ops/(1.0e6_rk * ti), sum(r(1:n))
     END IF
     DEALLOCATE(a, x, r)
  END DO
END PROGRAM sq_mvm
