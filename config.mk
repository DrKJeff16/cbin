CC := gcc
CXX := g++

GLOBAL_PREFIX := /usr
LOCAL_PREFIX := $(HOME)/.local
INSTALL_BIN_DIR = $(GLOBAL_PREFIX)/bin

BINDIR = bin
INCDIR = include
LIBDIR = lib
OBJDIR = obj
SRCDIR = src

ALL_DIRS = $(BINDIR) \
		   $(INCDIR) \
		   $(LIBDIR) \
		   $(OBJDIR) \
		   $(SRCDIR)

CPPFLAGS = -Iinclude \
		   -I. \
		   -I$(GLOBAL_PREFIX)/include/jeff \
		   -D_GNU_SOURCE \
		   -D_FORTIFY_SOURCE=2

CFLAGS = $(CPPFLAGS) \
		 -march=native \
		 -pipe \
		 -std=gnu17 \
		 -O2 \
		 -g \
		 -Wall \
		 -Wextra \
		 -Wformat-security \
		 -Wno-unused \
		 -Wno-implicit-fallthrough \
		 -pedantic \
		 -pthread \
		 -fstack-protector

CXXFLAGS = $(CPPFLAGS) \
		   -D_GLIBCXX_ASSERTIONS \
		   -std=c++17 \
		   -march=native \
		   -pipe \
		   -O2 \
		   -g \
		   -Wall \
		   -Wextra \
		   -Wno-unused \
		   -Wno-implicit-fallthrough \
		   -pedantic \
		   -pthread

LDFLAGS = -L$(GLOBAL_PREFIX)/lib/jeff \
		  -Llib \
		  -ljeff \
		  -luv

LDXXFLAGS = -L$(GLOBAL_PREFIX)/lib/jeff \
			-Llib \
			-ldocopt \
			-luv

PKG_CONFIG_BIN := pkgconf

JEFF_INCDIR = $(INCDIR)/jeff
JEFF_H = $(JEFF_INCDIR)/jeff.h \
		 $(JEFF_INCDIR)/jasync.h \
		 $(JEFF_INCDIR)/jhash.h \
		 $(JEFF_INCDIR)/jfile.h \
		 $(JEFF_INCDIR)/jinput.h \
		 $(JEFF_INCDIR)/jlog.h \
		 $(JEFF_INCDIR)/jmemory.h \
		 $(JEFF_INCDIR)/jrandom.h \
		 $(JEFF_INCDIR)/jsignal.h \
		 $(JEFF_INCDIR)/jstring.h \
		 $(JEFF_INCDIR)/jtypes.h

JEFF_OBJECTS = \
			   $(OBJDIR)/jdie.o \
			   $(OBJDIR)/jerr.o \
			   $(OBJDIR)/jhash.o \
			   $(OBJDIR)/jinput.o \
			   $(OBJDIR)/jfile.o \
			   $(OBJDIR)/jlog.o \
			   $(OBJDIR)/jluajit.o \
			   $(OBJDIR)/jmemory.o \
			   $(OBJDIR)/jrandom.o \
			   $(OBJDIR)/jsignal.o \
			   $(OBJDIR)/jstring.o

JEFF_LIBS = $(LIBDIR)/libjeff.so

JEFF_CFLAGS = $(CFLAGS) \
			  -I/usr/include/luajit-2.1 \
			  -fPIC

JEFF_LDFLAGS = -lc \
			   -llua \
			   -lluajit-5.1 \
			   -lm \
			   -luv

JEFF_ACTIONS = cointoss \
			   countdown \
			   nwl_trim \
			   yn

ACTIONS = $(JEFF_ACTIONS)

# vim: set ts=4 sts=4 sw=0 noet ai si sta:
