
all: testcode.cc NNPDFDriver.cc testcode.f
	g++ -O3 -c NNPDFDriver.cc
	g++ -O3 -c testcode.cc -I $(shell lhapdf-config --incdir)
	g++ -O3 testcode.o NNPDFDriver.o -o testcode -I $(shell lhapdf-config --incdir) -L $(shell lhapdf-config --libdir) -lLHAPDF
	gfortran -O3 -c testcode.f -o testcode.fo
	gfortran -O3 testcode.fo NNPDFDriver.o -o testcode_fortran -lstdc++
clean:
	rm -rf *.o *.fo testcode testcode_fortran *~
