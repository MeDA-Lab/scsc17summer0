CXX      = g++
CXXFLAGS = -O2

TGT  = main
TGTS = $(TGT)

HDRS =

.PHONY: all clean

all: $(TGTS)

main:

clean:
	rm -r $(TGTS) *.o
