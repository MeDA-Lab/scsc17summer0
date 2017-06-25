CXX      = g++
CXXFLAGS = -O2 -std=c++11

INCS = -I include

TGT  = main
TGTS = $(TGT)

HDRS =

.PHONY: all clean

all: $(TGTS)

main:

test: test.o read_args.o read_object.o construct_laplacian.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(INCS)

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

read_args.o: read_args.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

read_object.o: read_object.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

construct_laplacian.o: construct_laplacian.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	rm -r $(TGTS) *.o
