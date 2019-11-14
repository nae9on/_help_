program histogram_openmp
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
  integer(c_int) :: seed = 123
  integer :: i, k, me, hist(16), id(10000)
  double precision :: wcstart, wcend, ct

  hist = 0
  call timing(wcstart, ct)
!$omp parallel private(seed,i,k,me)
  me = omp_get_thread_num()
  seed = 123 + 159*me
! cannot exactly reproduce serial results
! but with fixed thread number results should always be the same
! between runs
  do k = 1, 100000
!$omp do
     do i = 1, 10000
        id(i) = iand(rand_r(seed),z'f') + 1
     end do
!$omp end do
!$omp master
     do i = 1, 10000
        hist(id(i)) = hist(id(i)) + 1
     end do
!$omp end master
!$omp barrier
! barrier prevents ir from being modified before hist update is done
  end do
!$omp end parallel

 call timing(wcend, ct)
  do i=1, 16
     write(*,fmt='(''hist('',i0,'')='',i0)') i, hist(i)
  end do
  write(*,fmt='(''Time: '',F12.5)') wcend - wcstart
end program histogram_openmp
