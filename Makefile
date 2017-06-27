CXX      = g++
CXXFLAGS = -O2 -std=c++11

TGT        = main
MKLTGT     = main_mkl
MAGMATGT   = main_magma
MKLSPTGT   = main_mkl_sp
MAGMASPTGT = main_magma_sp
TGTS       = $(TGT) $(MKLTGT) $(MAGMATGT) $(MKLSPTGT) $(MAGMASPTGT)

HDRS = include/harmonic.hpp include/timer.hpp

INCS = -I include

OBJ = \
	read_args.o \
	read_object.o \
	verify_boundary.o \
	reorder_vertex.o \
	construct_laplacian.o \
	map_boundary.o \
	solve_harmonic.o \
	write_object.o \

.PHONY: all clean

all: $(TGTS)

%.o: src/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< $(INCS)

%.o: src/core/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< $(INCS)

main: main.o $(OBJ)
	$(CXX) $(CXXFLAGS) $< $(OBJ) -o $@

main_mkl:

main_magma:

main_mkl_sp:

main_magma_sp:

test: test.o read_args.o read_object.o construct_laplacian.o
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -r $(TGTS) *.o
