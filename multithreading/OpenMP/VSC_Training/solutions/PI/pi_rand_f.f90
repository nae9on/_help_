program pi_serial_rand_f
  use, intrinsic :: iso_c_binding
  use omp_lib
  implicit none
  integer, parameter :: rk = kind(1.0d0)
  integer, parameter :: n = 100000000
  real(rk), parameter :: pi_ref = 3.1415926535897932384626433
  real(rk), parameter :: RAND_MAX = 2147483647._rk 
  ! NOTE: check RAND_MAX value in C library call rand_r
  interface
    subroutine timing(t, ct) bind(c)
      import :: c_double
      real(c_double), intent(inout) :: t, ct
    end subroutine
    integer(c_int) function rand_r(iseed) bind(c)
      import :: c_int
      integer(c_int) :: iseed
    end function
  end interface 

  integer :: i, i_inside, i_tot
  integer :: iseed = 5
  real(rk) :: rd1, rd2, pi_approx
  real(rk) :: t1, t2, ct1, ct2

  call timing(t1, ct1)

! calculate pi from random numbers on a quarter circle 
  i_tot = 0;
!$omp parallel private(iseed, i_inside, rd1, rd2)
!  unsuitable choices may give bad results here. Please test with 
!  different values for OMP_NUM_THREADS 
  iseed = 1713*omp_get_thread_num() + 5
  i_inside = 0;
!$omp do 
  do i=1, n
    rd1 = real(rand_r(iseed),rk) / RAND_MAX
    rd2 = real(rand_r(iseed),rk) / RAND_MAX
    if ((rd1*rd1 + rd2*rd2) <= 1.0_rk) i_inside = i_inside + 1
  end do
!$omp end do
!$omp critical
  i_tot = i_tot + i_inside
!$omp end critical
!$omp end parallel
  pi_approx = 4.0_rk * real(i_tot,rk) / real(n,rk)

  call timing(t2, ct2)

  write(*, fmt='(''computed  pi     = '',f19.16)') pi_approx
  write(*, fmt='(''reference pi_ref = '',f19.16)') pi_ref
  write(*, fmt='(''error= pi-pi_ref = '',f19.16)') pi_approx - pi_ref
  write(*, fmt='(''CPU time         = '',f12.6)') ct2 - ct1
  write(*, fmt='(''wall clock time  = '',f12.6)') t2 - t1

end program
