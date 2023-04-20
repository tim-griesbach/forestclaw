double precision function psi(xp,yp,zp,t)
   implicit none

   double precision xp,yp,zp,t

   double precision pi, pi2
   common /compi/ pi, pi2

   double precision maxelev, revs_per_second
   common /com_sphere/ maxelev, revs_per_second

   double precision rp

   rp = sqrt(xp**2 + yp**2 + zp**2)
   psi = pi2*revs_per_second*yp*rp

   psi = -psi

end function psi