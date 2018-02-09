CC = gcc
CXX = g++
CFLAGS = -O2 -Wall
CXXFLAGS = -O2 -Wall -std=c++11
LDLIBS = -liconv

CSRCS = $(wildcard *.c)
CPPSRCS = $(wildcard *.cpp)

OBJS := $(CSRCS:.c=.o)
OBJS += $(CPPSRCS:.cpp=.o)

BIN = $(OBJS:.o=)
SYMS = $(OBJS:.o=.dSYM)

all: $(BIN)

.PHONY: clean
clean:
	rm -rf $(OBJS) $(BIN) $(SYMS)
