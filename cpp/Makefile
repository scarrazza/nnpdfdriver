
all: testcode.cc NNPDFDriver.cc
	g++ -O3 -c NNPDFDriver.cc
	g++ -O3 -c testcode.cc -I $(shell lhapdf-config --incdir)
	g++ -O3 testcode.o NNPDFDriver.o -o testcode -I $(shell lhapdf-config --incdir) -L $(shell lhapdf-config --libdir) -lLHAPDF

clean:
	rm -rf *.o testcode *~
