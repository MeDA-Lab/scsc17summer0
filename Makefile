CXX      = g++
CXXFLAGS = -O2 -std=c++11

INCS = -I include

TGT  = main test
TGTS = $(TGT)

HDRS =

.PHONY: all clean

all: $(TGTS)

main:

test: test.o read_args.o read_object.o construct_laplacian.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test.o: src/test.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(INCS)

read_args.o: src/core/read_args.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(INCS)

read_object.o: src/core/read_object.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(INCS)

construct_laplacian.o: src/core/construct_laplacian.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(INCS)

clean:
	rm -r $(TGTS) *.o
