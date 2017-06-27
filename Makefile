CXX      = g++
CXXFLAGS = -O2 -std=c++11 -fopenmp

TGT        = main
MKLTGT     = main_mkl
MAGMATGT   = main_magma
MKLSPTGT   = main_mkl_sp
MAGMASPTGT = main_magma_sp
TGTS       = $(TGT) $(MKLTGT) $(MAGMATGT) $(MKLSPTGT) $(MAGMASPTGT)

HDRS = include/harmonic.hpp include/timer.hpp

INCS = -I include

MKLINCS = -m64 -I${MKLROOT}/include
MKLLNKS = -L${MKLROOT}/lib/intel64 -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl

MAGMAINCS =
MAGMALNKS = -lcublas -lcusparse -lcudart -lcusolver -lmagma_sparse -lmagma

OBJ = \
	read_args.o \
	read_object.o \
	verify_boundary.o \
	reorder_vertex.o \
	construct_laplacian.o \
	map_boundary.o \
	solve_harmonic.o \
	write_object.o

MKLOBJ = \
	read_args.o \
	read_object.o \
	verify_boundary.o \
	reorder_vertex.o \
	construct_laplacian_mkl.o \
	map_boundary_mkl.o \
	solve_harmonic_mkl.o \
	write_object.o

MAGMAOBJ = \
	read_args.o \
	read_object.o \
	verify_boundary.o \
	reorder_vertex.o \
	construct_laplacian.o \
	map_boundary.o \
	solve_harmonic_magma.o \
	write_object.o

.PHONY: all clean

all: $(TGTS)

%.o: src/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< $(INCS)

%.o: src/core/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< $(INCS)

%.o: src/mkl/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< $(INCS) $(MKLINCS)

%.o: src/magma/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< $(INCS) $(MKLINCS) $(MAGMAINCS)

%.o: src/sparse/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< $(INCS)

main: main.o $(OBJ)
	$(CXX) $(CXXFLAGS) $< $(OBJ) -o $@

main_mkl: main.o $(MKLOBJ)
	$(CXX) $(CXXFLAGS) $< $(MKLOBJ) -o $@ $(MKLLNKS)

main_magma: main.o $(MAGMAOBJ)
	$(CXX) $(CXXFLAGS) $< $(MAGMAOBJ) -o $@ $(MKLLNKS) $(MAGMALNKS)

test: test.o read_args.o read_object.o construct_laplacian.o
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -r $(TGTS) test *.o
