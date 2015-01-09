
      program testcode
*
      implicit none
*
      integer member,ntot,f,iq,ix
      character*100 gridname
      character*100 xpdf(-6:7)
      double precision sum
      double precision Q2(5)
      double precision xlha(11)
      double precision pdf(-6:7),pdf2(-6:7) 
      logical has_photon
      external has_photon
      
      data xpdf / "x*tbar","x*bbar","x*cbar","x*sbar","x*ubar","x*dbar",
     1	   "x*g","x*d","x*u","x*s","x*c","x*b","x*t","x*photon" /
      data Q2 / 2d0, 1d1, 1d2, 1d3, 1d4 /
      data xlha / 1d-7, 1d-6, 1d-5, 1d-4, 1d-3, 1d-2,
     1     1d-1, 3d-1, 5d-1, 7d-1, 9d-1 /
      
      gridname = "NNPDF23_nlo_as_0119.LHgrid"
      member = 0

      call NNPDFDriver(gridname)      
      call NNinitPDF(member)
            
      call InitPDFSetByName(gridname)
      call initPDF(member)

      sum = 0d0
      ntot = 6
      if (has_photon().eqv..true.) ntot = ntot+1

      do f=-6,ntot
         do iq=1,5
            write(6,*) "Q2 = ", Q2(iq)
            write(6,*) xpdf(f)
            write(6,*) "   x      Fortran    LHAPDF"
            
            do ix=1,11
               if (has_photon().eqv..false.) then                  
                  call evolvePDF(xlha(ix),Q2(iq)**0.5,pdf)                  
               else
                  call evolvePDFphoton(xlha(ix),Q2(iq)**0.5,pdf,pdf(7))
               endif
               call NNevolvePDF(xlha(ix),Q2(iq)**0.5,pdf2)
               write(6,*) xlha(ix),pdf2(f),pdf(f)
               
               sum = pdf(f)-pdf2(f)
            enddo
            write(6,*) ""
         enddo
      enddo
      
      if (sum.ne.0d0) then
         write(6,*) "Problems in the interpolation...",sum
      endif

      stop
      end
