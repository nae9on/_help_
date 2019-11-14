! Serial Fortran version 
! Numerical Solution of heat conduction equation in 
! two dimensions
module mod_heat
  implicit none
  integer, parameter :: rk = selected_real_kind(12,100)
! first line for testing, second for measurements
!  integer, parameter :: imax=20,kmax=11,itmax=20000
  integer, parameter :: imax=200,kmax=200,itmax=100000
  real(kind=rk), parameter :: eps = 1.0e-8_rk
!
  real(kind=rk), dimension(0:imax,0:kmax)     :: phi
  real(kind=rk), dimension(1:imax-1,1:kmax-1) :: phin
contains
  subroutine print_field()
    implicit none
    integer :: i, k, kk, kl, kkk
    kl=6
    kkk=kl-1
    do k=0,kmax,kl
       if(k+kkk.gt.kmax) kkk=kmax-k
       write (*,'(/,a,i5,a,i5)') 'columns',k,' to',k+kkk
       do i=0,imax
          write (*,'(i5,6(1pg12.4))') i,(phi(i,k+kk),kk=0,kkk)
       enddo
    enddo
  end subroutine print_field
end module mod_heat
module timer
! Timer implementation based on system_clock intrinsic
  implicit none
  private
  public :: dwalltime
  integer, parameter :: ik = selected_int_kind(6)
  logical, save :: first = .true.
  integer(ik), save ::  count_rate, count_max
  double precision, save :: conversion = 0.0d0
contains
  double precision function dwalltime()
    integer(ik) :: count
    if (first) then
       first = .false.
       call system_clock(count, count_rate, count_max)
       conversion = 1.0d0 / dble(count_rate)
    else
       call system_clock(count)
    end if
    dwalltime = count * conversion
  end function dwalltime
end module timer
program heatf
  use mod_heat
  use timer
  implicit none
  real(kind=rk) :: dx,dy,dx2,dy2,dx2i,dy2i,dt,dphi,dphimax
  real(kind=rk) :: t0, t1, mflops
  integer ::       i,it,k
!
  dx=1.0_rk/kmax
  dy=1.0_rk/imax
  dx2=dx*dx
  dy2=dy*dy
  dx2i=1.0_rk/dx2
  dy2i=1.0_rk/dy2
  dt=min(dx2,dy2)/4.0_rk

! start values 0.d0
  do k=0,kmax-1
     do i=1,imax-1
        phi(i,k)=0.0_rk
     enddo
  enddo
  
! boundary values 1.d0
  do i=0,imax
     phi(i,kmax)=1.0_rk
  enddo

! boundary values dx
  phi(0,0)=0.0_rk
  phi(imax,0)=0.0_rk
  do k=1,kmax-1
     phi(0,k)=phi(0,k-1)+dx
     phi(imax,k)=phi(imax,k-1)+dx
  enddo

! print
  write (*,'(/,a)') 'Heat Conduction 2D:'
  write (*,'(/,4(a,1pg12.4))') 'dx =',dx,', dy =',dy,', dt =',dt,', eps =',eps
  if (imax .le. 20 .and. kmax .le. 20) then
     write (*,'(/,a)') 'start values'
     call print_field()
  endif

  t0=dwalltime()

! iteration
  do it=1,itmax
     dphimax=0.
     do k=1,kmax-1
        do i=1,imax-1
           dphi=(phi(i+1,k)+phi(i-1,k)-2.0_rk*phi(i,k))*dy2i  &
                +(phi(i,k+1)+phi(i,k-1)-2.0_rk*phi(i,k))*dx2i
           dphi=dphi*dt
           dphimax=max(dphimax,dphi)
           phin(i,k)=phi(i,k)+dphi
        enddo
     enddo
     
! save values
     do k=1,kmax-1
        do i=1,imax-1
           phi(i,k)=phin(i,k)
        enddo
     enddo
     
!     if (mod(it, 250) == 0) write(*, *) ' delta = ',dphimax

! precision reached?
     if(dphimax.lt.eps) goto 10
  enddo

10 continue

  t1=dwalltime()

! print
  write (*,'(/,a,i8,a)')         'iterations:        ',it
  if (imax .le. 20 .and. kmax .le. 20) then
     call print_field()
  endif
  write (*,'(/,a,1pg12.4,/)') 'wall time:   ', t1 - t0
  mflops = 11.0_rk * dble(kmax-1)*dble(imax-1)*dble(it) / 1.e6_rk
  write (*,'(/,a,1pg12.4,/)') 'MFlop/s:   ', mflops/(t1 - t0)
end program heatf

