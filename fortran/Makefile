
all: testcode.f NNPDFDriver.f
	gfortran -O3 -c NNPDFDriver.f
	gfortran -O3 -c testcode.f -I $(shell lhapdf-config --incdir)
	gfortran -O3 testcode.o NNPDFDriver.o -o testcode -I $(shell lhapdf-config --incdir) -L $(shell lhapdf-config --libdir) -lLHAPDF

clean:
	rm -rf *.o testcode *~
