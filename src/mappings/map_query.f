      logical function ispillowsphere()
      implicit none

      integer id, fclaw2d_map_is_pillowsphere
      integer*8 cont, get_context

      cont = get_context()

      id = fclaw2d_map_is_pillowsphere(cont)
      ispillowsphere = id .ne. 0

      end

      logical function iscubedsphere()
      implicit none

      integer id, fclaw2d_map_is_cubedsphere
      integer*8 cont, get_context

      cont = get_context()

      id = fclaw2d_map_is_cubedsphere(cont)
      iscubedsphere = id .ne. 0

      end


      logical function isflat()
      implicit none

      integer id, fclaw2d_map_is_flat
      integer*8 cont, get_context

      cont = get_context()

      id = fclaw2d_map_is_flat(cont)
      isflat = id .ne. 0

      end

      logical function issphere()
      implicit none

      integer id, fclaw2d_map_is_sphere
      integer*8 cont, get_context

      cont = get_context()

      id = fclaw2d_map_is_sphere(cont)
      issphere = id .ne. 0

      end

      logical function iscart()
      implicit none

      integer id, fclaw2d_map_is_cart
      integer*8 cont, get_context

      cont = get_context()

      id = fclaw2d_map_is_cart(cont)
      iscart = id .ne. 0

      end

      logical function isdisk()
      implicit none

      integer id, fclaw2d_map_is_disk
      integer*8 cont, get_context

      cont = get_context()

      id = fclaw2d_map_is_disk(cont)
      isdisk = id .ne. 0

      end
