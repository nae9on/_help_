program recursion_f
  implicit none
  integer, parameter :: len = 1000000
  double precision, parameter :: up = 1.00001d0
  double precision :: Sn
  double precision, dimension(0:len) :: opt
  integer :: n

  Sn = 1.0d0
  do n = 0,len
     opt( n ) = Sn
     Sn = Sn * up 
  enddo

  write(*,*) 'Result is ',Sn
end program recursion_f
