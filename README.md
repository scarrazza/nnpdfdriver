# nnpdfdriver 
NNPDF stand-alone drivers for C++ and Fortran77 which
can be easily included in any program. The drivers use as input the
official LHAPDF5 and LHAPDF6 (c++) grids at [lhapdf.hepforge.org/](lhapdf.hepforge.org/).

## Download

Checkout the latest release at https://github.com/scarrazza/nnpdfdriver/releases

## Compile

```Shell
cd nnpdfdriver/cpp or nnpdfdriver/fortran
make
```

## Run

```Shell
# run example
./testcode
```

## Code example

```C++
/**
 * NNPDF tutorial: Loading and using a NNPDF grid with the NNPDF Driver.
 *
 * Compile with:
 * g++ -O3 tutorial.cc NNPDFDriver.cc -o prog
 *
 * Author: The NNPDF Collaboration - 2014
 */
 
#include "iostream"
#include "cmath"
#include "NNPDFDriver.h"
using namespace std;
 
int main()
{
  NNPDFDriver *nnpdf = new NNPDFDriver("NNPDF23_nlo_as_0119.LHgrid");
  nnpdf->initPDF(0); // initialize PDF member
 
  // fast option
  // NNPDFDriver *nnpdf = new NNPDFDriver("NNPDF23_nlo_as_0119.LHgrid", 0);
 
  double x = 0.1, Q = sqrt(2);
  int f = 0;
  cout << nnpdf->xfx(x,Q,f) << endl; // prints the gluon x*PDF
 
  delete *nnpdf;                 
   
  return 0;
}
```