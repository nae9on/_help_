program race
  use omp_lib
  implicit none
  real :: x, y, z
  integer :: i

  z = 0.0
  x = 0.0
!$omp parallel private(y) shared(x) reduction(+:z)
  y = omp_get_thread_num()
!$omp critical
  x = x + y
!$omp end critical
  z = z + f(x, z)
!$omp end parallel 
  write(*,'(''Result is '',E12.3)') z
contains
  pure real function f(a, b)
    real, intent(in) :: a, b
    f = a
  end function
end program
