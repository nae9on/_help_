module mod_raytracef
  implicit none
  private
  public :: is, intersect, shade, calc_tile
  integer, parameter :: is = selected_int_kind(2)
  double precision, parameter :: objs(4, 11) = reshape( (/ &
         0.d0 ,0.d0, -100.5d0, 10000.d0 , &
         0.d0, 0.d0, 0.d0, 0.25d0 , &
         0.272166d0, 0.272166d0, 0.544331d0, .027777d0  , &
         0.643951d0, 0.172546d0, 0.d0, .027777d0 , &
         0.172546d0, 0.643951d0, 0.d0, .027777d0 , &
        -0.371785d0, 0.099620d0, 0.544331d0, .027777d0 , &
        -0.471405d0, 0.471405d0, 0.d0, .027777d0 , &
        -0.643951d0,-0.172546d0, 0.d0, .027777d0 , &
         0.099620d0,-0.371785d0, 0.544331d0, .027777d0 , &
        -0.172546d0,-0.643951d0, 0.d0, .027777d0 , &
         0.471405d0,-0.471405d0, 0.d0, .027777d0  /), (/ 4, 11 /) )
  double precision, parameter :: objs_shade(3, 3) = reshape( (/ &
         4.d0, 3.d0, 2.d0 , &
         1.d0,-4.d0, 4.d0 , &
        -3.d0, 1.d0, 5.d0  /), (/3, 3/) )
  double precision :: small = 1.0d-6
contains
  integer function intersect(x, y, z, dx, dy, dz, pmax)
    double precision, intent(in) :: x, y, z, dx, dy, dz
    double precision, intent(inout) :: pmax
!
    integer :: i
    double precision :: xx, yy, zz, b(11), t(11), pmaxloc
!
    intersect = 0
    pmaxloc = pmax
!$omp simd private(xx, yy, zz) 
    do i=1, 11
       xx = objs(1,i) - x ; yy = objs(2,i) - y; zz = objs(3,i) - z
       b(i) = xx * dx + yy * dy + zz * dz
       t(i) = b(i) * b(i) - xx * xx - yy * yy - zz * zz + objs(4,i)
    end do
!$omp end simd
! following part split off because not vectorizable:
    do i=1, 11
       if (t(i) >= 0) then
          t(i) = b(i) - sqrt(t(i))
          if (t(i) >= small .and. t(i) <= pmaxloc) then
             intersect = i
             pmaxloc = t(i)
          end if
       end if
    end do
    pmax = pmaxloc
  end function intersect
  recursive function shade(x, y, z, dx, dy, dz, id) &
                             result (res)
   double precision :: res
    double precision, value :: x, y, z
    double precision, intent(in) :: dx, dy, dz
    integer, intent(in) :: id
!
    double precision :: pmax, c, r(3), k
    double precision :: nx, ny, nz, ldx(3), ldy(3), ldz(3), rdx, rdy, rdz, xl
    integer :: is(3), i, ij
!
    pmax = 1.0d6
    i = intersect(x, y, z, dx, dy, dz, pmax)
    c = 0.0d0
    if (i == 0) then
       res = 0.0d0
    else
       x = x + pmax * dx; y = y + pmax * dy; z = z + pmax * dz
       nx = x - objs(1,i); ny = y - objs(2,i); nz = z - objs(3,i)
       r = sqrt(nx * nx + ny * ny + nz * nz)
       nx = nx/r(1); ny = ny/r(1); nz = nz/r(1)
       k = nx * dx + ny * dy + nz * dz
       rdx = dx - 2 * k * nx; rdy = dy - 2 * k * ny; rdz = dz - 2 * k * nz
!$omp simd private(xl)
       do i = 1, 3
          ldx(i) = objs_shade(1,i) - x
          ldy(i) = objs_shade(2,i) - y
          ldz(i) = objs_shade(3,i) - z
          r(i) = sqrt(ldx(i) * ldx(i) + ldy(i) * ldy(i) + ldz(i) * ldz(i));
          xl = 1/r(i)
          ldx(i) = ldx(i)*xl; ldy(i) = ldy(i)*xl; ldz(i) = ldz(i)*xl;
       end do
!$omp end simd

       do i=1, 3
          if (intersect(x, y, z, ldx(i), ldy(i), ldz(i), r(i)) /= 0) cycle
          r(i) = ldx(i) * nx + ldy(i) * ny + ldz(i) * nz
          if (r(i) < 0.0d0) cycle
          c = c + r(i)
          r(i) = rdx * ldx(i) + rdy * ldy(i) + rdz * ldz(i)
          if (r(i) > 0.0d0) then
             c = c + 2.0d0 * r(i)**15
          end if
       end do


       if (id < 10) c = c + 0.5d0 * shade(x, y, z, rdx, rdy, rdz, id + 1)
       res = c
    end if
  end function shade
  subroutine calc_tile(size, ixstart, iystart, tilesize, tile)
    integer, intent(in) :: size, ixstart, iystart, tilesize
    integer(kind=is), intent(inout) :: tile(:,:)
!
    double precision :: dx, dy, dz, c, r, xx, yy
    integer :: ix, iy

    do iy=1, tilesize
       yy = 1.0d0 - (iystart + iy - 1) / dble(size - 1)
       dz = -2.72303d0                   + yy * 2.04606d0;
       do ix=1, tilesize
          xx = (ixstart + ix - 1) / dble(size - 1)
          dx = -0.847569d0 - xx * 1.30741d0 - yy * 1.19745d0
          dy = -1.98535d0  + xx * 2.11197d0 - yy * 0.741279d0
          r = sqrt(dx * dx + dy * dy + dz * dz)
          c = 100.d0 * shade(2.1d0, 1.3d0, 1.7d0, dx/r, dy/r, dz/r, 0);
!          write(*,*) 'ix, iy, c:',ix,iy,c
          c = max(c, 0.0d0)
          c = min(c, 255.1d0)
          tile(ix, iy) = int(c, 1_is)
       end do
   end do
  end subroutine calc_tile
end module mod_raytracef
program raytracef
  use mod_raytracef
  implicit none
  integer, parameter :: size = 2000, tilesize = 200
  integer :: xtiles, ytiles, xc, yc, tilebase, ix, iy
  integer(kind=is), allocatable :: picture(:,:), tile(:,:)
  character(len=1) :: cc
  double precision :: wcstart,wcend,cpustart,cpuend

  allocate(picture(size, size))  

  call timing(wcstart,cpustart)
  xtiles = size / tilesize
  ytiles = size / tilesize

  allocate(tile(tilesize, tilesize))
  do yc = 0, xtiles - 1
     do xc = 0, xtiles - 1
        call calc_tile(size, xc*tilesize, yc*tilesize, tilesize, tile)
        picture(xc*tilesize+1:(xc+1)*tilesize, yc*tilesize+1:(yc+1)*tilesize) = tile
     end do
  end do
  deallocate(tile)
  call timing(wcend,cpuend)
  write(*,*) 'Walltime: ',wcend-wcstart
  write(*, *) 'Ready for I/O ...'
  open(unit=20, file='result.pnm', access='STREAM', form='UNFORMATTED', status='REPLACE')
  write(20)'P5'//new_line('')//int2str(size)//' '//int2str(size)//new_line('')//int2str(255)//new_line('')
  write(20) picture
  close(20)
  write(*, *) '... done.'
  deallocate(picture)
contains

  function int2str(number)result(string)
    integer :: number
    character(16):: dum
    character(:),allocatable :: string
    write(dum,*)number
    string=trim(adjustl(dum))
  end function int2str
end program raytracef
