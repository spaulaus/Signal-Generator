#!/bin/make
SHELL=/bin/bash

vpath %.cpp src/
vpath %.h include/

CINCLUDEDIRS = -Iinclude

CXX = g++
CXXFLAGS += -Wall $(CINCLUDEDIRS)
LDLIBS += -ldl -lpthread
c++SrcSuf = cpp

#Define Objects
SIGNALGENERATORO = SignalGenerator.o
MAINO = sig.o

#List Objects
OBJS = $(MAINO) $(SIGNALGENERATORO) 

PROGRAM = sig

.SUFFIXES: .$(c++SrcSuf)

.phony: all clean
all: $(PROGRAM)

clean: 
	@echo "Cleaning..."
	@rm -f $(OBJS) $(PROGRAM) *~ src/*~ include/*~

$(PROGRAM): $(OBJS) 
	$(CXX) $(LDLIBS) $^ -o $@