module m
  implicit none
  interface
     integer(c_int) function sleep(seconds) BIND(C)
       use, intrinsic :: iso_c_binding
       integer(c_int), value :: seconds
     end function sleep
  end interface
contains
  subroutine f()
    print *, 'Hello'
  end subroutine
end module
program hello
  use m
  implicit none
  
  call f()

end program


