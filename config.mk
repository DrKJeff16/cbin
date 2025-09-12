CC := gcc
CXX := g++

LOCAL_PREFIX := $(HOME)/.local
GLOBAL_PREFIX := /usr
INSTALL_BIN_DIR := $(GLOBAL_PREFIX)/bin

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
		   -I/usr/include/jeff \
		   -DNDEBUG \
		   -D_REENTRANT \
		   -D_GNU_SOURCE

CFLAGS = $(CPPFLAGS) \
		 -march=native \
		 -pipe \
		 -std=gnu99 \
		 -O2 \
		 -g \
		 -ggdb \
		 -Wall \
		 -Wextra \
		 -Wno-unused \
		 -pedantic \
		 -pthread

CXXFLAGS = $(CPPFLAGS) \
		   -D_GLIBCXX_ASSERTIONS \
		   -I/usr/include/docopt \
		   -std=c++17 \
		   -march=native \
		   -pipe \
		   -O2 \
		   -g \
		   -ggdb \
		   -Wall \
		   -Wextra \
		   -Wno-unused \
		   -pedantic \
		   -pthread

LDFLAGS = -L/usr/lib/jeff \
		  -Llib \
		  -ljeff \
		  -lc \
		  -lm \
		  -lpthread

LDXXFLAGS = -L/usr/lib/jeff \
			-Llib \
			-ldocopt

PKG_CONFIG_BIN := pkgconf

JEFF_INCDIR = $(INCDIR)/jeff

JEFF_H = $(JEFF_INCDIR)/jeff.h \
		 $(JEFF_INCDIR)/jautomata.h \
		 $(JEFF_INCDIR)/jinput.h \
		 $(JEFF_INCDIR)/jlog.h \
		 $(JEFF_INCDIR)/jlua.h \
		 $(JEFF_INCDIR)/jmemory.h \
		 $(JEFF_INCDIR)/jrandom.h \
		 $(JEFF_INCDIR)/jsignal.h \
		 $(JEFF_INCDIR)/jstring.h \
		 $(JEFF_INCDIR)/jtypes.h

JEFF_OBJECTS = $(OBJDIR)/jstring.o \
			   $(OBJDIR)/jdie.o \
			   $(OBJDIR)/jerr.o \
			   $(OBJDIR)/jlog.o \
			   $(OBJDIR)/jrandom.o \
			   $(OBJDIR)/jsignal.o \
			   $(OBJDIR)/jinput.o \
			   $(OBJDIR)/jautomata.o

JEFF_LIBS = $(LIBDIR)/libjeff.so \
			$(LIBDIR)/libjlua.so

JEFF_CFLAGS = $(CFLAGS) \
			  -fPIC

JEFF_LDFLAGS = -lc \
			   -lm \
			   -lpthread

JEFF_ACTIONS = cointoss \
			   jeff_lua_1 \
			   jparse \
			   yes_no

JEFF_LUA_H = $(JEFF_INCDIR)/jlua.h
JEFF_LUA_CFLAGS = $(JEFF_CFLAGS) \
				  -I/usr/include/luajit-2.1

JEFF_LUA_LDFLAGS = $(JEFF_LDFLAGS) \
				   -L/usr/lib/jeff \
				   -Llib \
				   -L. \
				   -ljeff \
				   -llua \
				   -lluajit-5.1

LUA_H = $(JEFF_INCDIR)/jlua.h

LUA_CFLAGS = -I/usr/include/luajit-2.1 \
			 -I/usr/include/jeff
LUA_LDFLAGS = -L/usr/lib/jeff \
			  -Llib \
			  -L. \
			  -ljeff \
			  -ljlua \
			  -llua \
			  -lluajit-5.1 \
			  -lpthread

ACTIONS = $(JEFF_ACTIONS)
