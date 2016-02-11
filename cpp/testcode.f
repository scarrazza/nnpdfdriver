***************************************
*     Example of fortran code
***************************************
      program main
      implicit none
      double precision nnxfx
      
      call initnnset("NNPDF30_nlo_as_0118")
      call initpdf(0)
      write(6,*) nnxfx(0.1d0,10d0,0)
      
      end
