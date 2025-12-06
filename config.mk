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
		   -D_GNU_SOURCE

CFLAGS = $(CPPFLAGS) \
		 -march=native \
		 -pipe \
		 -std=gnu17 \
		 -Og \
		 -g \
		 -Wall \
		 -Wextra \
		 -Wno-unused \
		 -pedantic

CXXFLAGS = $(CPPFLAGS) \
		   -I$(GLOBAL_PREFIX)/include/docopt \
		   -D_GLIBCXX_ASSERTIONS \
		   -std=c++17 \
		   -march=native \
		   -pipe \
		   -Og \
		   -g \
		   -Wall \
		   -Wextra \
		   -Wno-unused \
		   -pedantic

LDFLAGS = -L$(GLOBAL_PREFIX)/lib/jeff \
		  -Llib \
		  -ljeff

LDXXFLAGS = -L$(GLOBAL_PREFIX)/lib/jeff \
			-Llib \
			-ldocopt

PKG_CONFIG_BIN := pkgconf

JEFF_INCDIR = $(INCDIR)/jeff
JEFF_H = $(JEFF_INCDIR)/jeff.h \
		 $(JEFF_INCDIR)/jinput.h \
		 $(JEFF_INCDIR)/jlog.h \
		 $(JEFF_INCDIR)/jlua.h \
		 $(JEFF_INCDIR)/jmemory.h \
		 $(JEFF_INCDIR)/jrandom.h \
		 $(JEFF_INCDIR)/jsignal.h \
		 $(JEFF_INCDIR)/jstring.h \
		 $(JEFF_INCDIR)/jtypes.h

JEFF_OBJECTS = $(OBJDIR)/jstring.o \
			   $(OBJDIR)/jmemory.o \
			   $(OBJDIR)/jdie.o \
			   $(OBJDIR)/jerr.o \
			   $(OBJDIR)/jlog.o \
			   $(OBJDIR)/jrandom.o \
			   $(OBJDIR)/jsignal.o \
			   $(OBJDIR)/jinput.o \

JEFF_LIBS = $(LIBDIR)/libjeff.so \
			$(LIBDIR)/libjlua.so

JEFF_CFLAGS = $(CFLAGS) \
			  -fPIC

JEFF_LDFLAGS = -lc

JEFF_ACTIONS = cointoss \
			   yn

JEFF_LUA_H = $(JEFF_INCDIR)/jlua.h
JEFF_LUA_CFLAGS = $(JEFF_CFLAGS) \
				  -I$(GLOBAL_PREFIX)/include/luajit-2.1

JEFF_LUA_LDFLAGS = $(JEFF_LDFLAGS) \
				   -L$(GLOBAL_PREFIX)/lib/jeff \
				   -Llib \
				   -L. \
				   -ljeff \
				   -llua \
				   -lluajit-5.1

LUA_H = $(JEFF_INCDIR)/jlua.h

LUA_CFLAGS = -I$(GLOBAL_PREFIX)/include/luajit-2.1 \
			 -I$(GLOBAL_PREFIX)/include/jeff

LUA_LDFLAGS = -L$(GLOBAL_PREFIX)/lib/jeff \
			  -Llib \
			  -L. \
			  -ljeff \
			  -ljlua \
			  -llua \
			  -lluajit-5.1

ACTIONS = $(JEFF_ACTIONS)
