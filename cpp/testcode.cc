#include "NNPDFDriver.h"
#include "LHAPDF/LHAPDF.h"
#include <cmath>
#include <stdlib.h>
#include <iomanip>
using namespace std;

int main(int argc, char** argv)
{
  string gridname = "";
  int member = 0;
  if (argc > 2)
    {
      gridname = argv[1];
      member = atoi(argv[2]);
    }
  else
    {
      cout << "\nusage: ./testcode <gridname> <member>\n" << endl;
      exit(-1);
    }

  string xpdf[] = {"x*tbar","x*bbar","x*cbar","x*sbar","x*ubar","x*dbar",
		   "x*g","x*d","x*u","x*s","x*c","x*b","x*t","x*photon"};
  double xlha[] = {1e-7, 1e-6, 1e-5, 1e-4, 1e-3, 1e-2,
		   1e-1, 3e-1, 5e-1, 7e-1, 9e-1};  
  double Q2[] = { 1.0, 2.0, 10.0, 100.0, 1000.0, 10000.0 };
  
  // fast option load single grid file
  NNPDFDriver *nnpdf = new NNPDFDriver(gridname, member);

  // or slow option
  // NNPDFDriver *nnpdf = new NNPDFDriver(gridname);
  // nnpdf->initPDF(member);
  
#if LHAPDF_MAJOR_VERSION > 5
  const LHAPDF::PDF*pdf = LHAPDF::mkPDF(gridname, member);
#define XFS(X,Q,F) pdf->xfxQ(F,X,Q)
#define XFSPHT(X,Q,F) pdf->xfxQ(F,X,Q)
#else
  LHAPDF::initPDFSet(gridname);
  LHAPDF::initPDF(member);
#define XFS(X,Q,F) LHAPDF::xfx(X,Q,F)
#define XFSPHT(X,Q,F) LHAPDF::xfxphoton(X,Q,F)
#endif

  double sum = 0;
  int ntot = 6;
  if (nnpdf->hasPhoton()) ntot++;

  for (int f = -6; f <= ntot; f++)
    {
      for (int iq = 0; iq < 6; iq++)
	{	
	  cout << "  " << xpdf[f+6] << ", Q2 = " << Q2[iq] << endl;
	  cout << "   x \t     C++ \tLHAPDF  \tDiff" << endl;
	  for (int ix = 0; ix < 11; ix++)
	    {
	      double a = nnpdf->xfx(xlha[ix],sqrt(Q2[iq]), f);
	      double b = 0;
	      if (nnpdf->hasPhoton())
		b = XFSPHT(xlha[ix],sqrt(Q2[iq]),f);
	      else
		b = XFS(xlha[ix],sqrt(Q2[iq]),f);
	      cout << scientific << setprecision(1) << xlha[ix] << "  ";
	      cout << scientific << setprecision(5) << a << "  " << b << "  " << a-b << endl;
	      sum += a-b;
	    } 
	  cout << endl;
	}
    }

  cout << "Sum of differences... " << sum << endl;    
  
  delete nnpdf;

  return 0;
}
