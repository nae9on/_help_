program histogram_serial
  use, intrinsic :: iso_c_binding
  use omp_lib
  implicit none
  interface
     integer(c_int) function rand_r(seed) bind(c)
       import :: c_int
       integer :: seed
     end function rand_r
     subroutine timing(wc, ct) bind(c)
       import :: c_double
       real(c_double) :: wc, ct
     end subroutine timing
  end interface
  integer(c_int) :: seed 
  integer :: i, id, me, hist(16)
  double precision :: wcstart, wcend, ct

  hist = 0
  call timing(wcstart, ct)
!$omp parallel private(seed, id)
  me = omp_get_thread_num()
  seed = 123 + 159*me
!$omp do reduction(+:hist)
  do i = 1, 1000000000
     id = iand(rand_r(seed),z'f') + 1
     hist(id) = hist(id) + 1
  end do
!$omp end do nowait
!$omp end parallel
  call timing(wcend, ct)
  do i=1, 16
     write(*,fmt='(''hist('',i0,'')='',i0)') i, hist(i)
  end do
  write(*,fmt='(''Time: '',F12.5)') wcend - wcstart
end program histogram_serial
