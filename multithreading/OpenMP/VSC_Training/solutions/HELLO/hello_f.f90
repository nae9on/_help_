module m
  use omp_lib, ONLY : omp_get_thread_num, omp_get_wtime
  implicit none
  interface
     integer(c_int) function sleep(seconds) BIND(C)
       use, intrinsic :: iso_c_binding
       integer(c_int), value :: seconds
     end function sleep
  end interface
contains
  subroutine f()
    integer :: me, iret
    me = 0
!$  me = omp_get_thread_num()
    print *, 'Hello from thread ',me
    iret = sleep(me)
  end subroutine
end module
program hello
  use m
  implicit none
  double precision :: ti
  ti = omp_get_wtime()
!$omp parallel  
  call f()
  !$omp end parallel
  ti = omp_get_wtime() - ti
  print '(''f took '',F8.3,'' seconds.'')', ti
end program


