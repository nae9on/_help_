program recursion_f
  implicit none
  integer, parameter :: len = 1000000
  double precision, parameter :: up = 1.00001d0
  double precision :: Sn, origSn
  double precision, dimension(0:len) :: opt
  integer :: n, lastn

  origSn = 1.d0
  lastn = -2

  !$OMP PARALLEL DO FIRSTPRIVATE(lastn) LASTPRIVATE(Sn)
  do n = 0,len

     if (lastn .eq. n-1) then ! still in same chunk?

        Sn = Sn * up        ! yes: fast version

     else

        Sn = origSn * up**n ! no: slow version

     endif
     opt( n ) = Sn
     lastn = n ! storing index
  enddo
  !$OMP END PARALLEL DO
  Sn = Sn * up

  write(*,*) 'Result is ',Sn
end program recursion_f
