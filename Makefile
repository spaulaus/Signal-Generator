#!/bin/make
SHELL=/bin/bash

vpath %.cpp src/
vpath %.hpp include/
vpath %.o obj/

#Set some paths to install the shared objects to
SO_INSTALL_PATH = /home/vincent/programs/libFiles
HEADER_INSTALL_PATH = /home/vincent/programs/headerFiles

#Set some of the compile options
CXX = g++
CXXFLAGS = -fPIC -g -Wall $(CINCLUDEDIRS)
LDLIBS = -ldl -lpthread
CINCLUDEDIRS = -Iinclude
c++SrcSuf = cpp

#Set hte name of the program to be complied
PROGRAM = example
VERSION = $(shell git describe --abbrev=0 --tags)

#Define Objects
EXAMPLEO = sig.o
SIGGENO = SignalGenerator.o

#DefineSharedObject
SO_NAME = $(subst .o,.so,lib$(SIGGENO))
SO_NAME_W_DIR = $(addprefix $(OBJDIR)/,$(SO_NAME))
SO_NAME_FULL=$(addsuffix .$(VERSION), $(SO_NAME_W_DIR))

#Define the name of the header for the SO
HEADER_NAME = $(subst .o,.hpp,$(SIGGENO))

#Make the object list and prefix the object directory
OBJS = $(EXAMPLEO) $(SIGGENO)
OBJDIR = obj
OBJS_W_DIR = $(addprefix $(OBJDIR)/,$(OBJS))

.SUFFIXES: .$(c++SrcSuf)

all: $(OBJS_W_DIR) $(PROGRAM)

$(OBJS_W_DIR): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PROGRAM): $(OBJS_W_DIR)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@

.PHONY: clean so
clean: 
	@echo "Cleaning..."
	@rm -f $(OBJDIR)/* $(PROGRAM) *~ src/*~ include/*~

so: $(HEADER_NAME)
	g++ -shared $(OBJDIR)/$(SIGGENO)  -o $(SO_NAME_FULL)
	cp $(SO_NAME_FULL) $(SO_INSTALL_PATH)
	ln -sf $(SO_INSTALL_PATH)/$(SO_NAME_FULL) $(SO_INSTALL_PATH)/$(SO_NAME)
	cp $^ $(HEADER_INSTALL_PATH)
