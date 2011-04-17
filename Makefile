# Makefile for UnArk

SHELL := /bin/sh

INSTALL := install
INSTALL_PROGRAM := $(INSTALL)
INSTALL_DATA := $(INSTALL) -m 644

target := unark
lib := libark32.so

prefix := /usr/local

.SUFFIXES :
.SUFFIXES : .cpp

.PHONY : all
all : $(target)

$(target) : -ldl

.PHONY : install
install : $(lib) $(target)
	$(INSTALL_DATA) $(lib) $(prefix)/lib/$(lib)
	$(INSTALL_PROGRAM) $(target) $(prefix)/bin/$(target)

.PHONY : uninstall
uninstall :
	-rm -f $(prefix)/lib/$(lib)
	-rm -f $(prefix)/bin/$(target)

.PHONY : clean
clean :
	-rm -f $(target) 테스트.txt

.PHONY : distclean
distclean : clean
