CC := gcc
CXX := g++
AR := gcc-ar

GLOBAL_PREFIX := /usr
LOCAL_PREFIX := $(HOME)/.local

INSTALL_BIN_DIR = $(GLOBAL_PREFIX)/bin

BINDIR = bin
INCDIR = include
LIBDIR = lib
OBJDIR = obj
SRCDIR = src
ASDIR = as
PREPROCDIR = preproc

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
		 -O2 \
		 -Wall \
		 -Wextra \
		 -Wformat-security \
		 -Wno-implicit-fallthrough \
		 -Wno-unused \
		 -g \
		 -ggdb \
		 -pedantic \
		 -pipe \
		 -pthread \
		 -std=gnu17

CXXFLAGS = $(CPPFLAGS) \
		   -D_GLIBCXX_ASSERTIONS \
		   -O2 \
		   -Wall \
		   -Wextra \
		   -Wno-implicit-fallthrough \
		   -Wno-unused \
		   -fcf-protection \
		   -flto \
		   -fomit-frame-pointer \
		   -fsanitize=address \
		   -fstack-clash-protection \
		   -fstack-protector \
		   -ftree-vectorize \
		   -g \
		   -ggdb \
		   -pedantic \
		   -pipe \
		   -pthread \
		   -std=c++17

LDFLAGS = -L$(GLOBAL_PREFIX)/lib/jeff \
		  -Llib \
		  -ljeff \
		  -fcf-protection \
		  -flto \
		  -fomit-frame-pointer \
		  -fsanitize=address \
		  -fstack-clash-protection \
		  -fstack-protector \
		  -ftree-vectorize

LDXXFLAGS = -L$(GLOBAL_PREFIX)/lib/jeff \
			-Llib \
			-ljeff \
			-fcf-protection \
			-flto \
			-fomit-frame-pointer \
			-fsanitize=address \
			-fstack-clash-protection \
			-fstack-protector \
			-ftree-vectorize

PKG_CONFIG_BIN := pkgconf

JEFF_INCDIR = $(INCDIR)/jeff
JEFF_PREPROCDIR = $(PREPROCDIR)/jeff
JEFF_ASDIR = $(ASDIR)/jeff
JEFF_H = $(JEFF_INCDIR)/jeff.h \
		 $(JEFF_INCDIR)/jdie.h \
		 $(JEFF_INCDIR)/jerr.h \
		 $(JEFF_INCDIR)/jswap.h \
		 $(JEFF_INCDIR)/jhash.h \
		 $(JEFF_INCDIR)/jfile.h \
		 $(JEFF_INCDIR)/jinput.h \
		 $(JEFF_INCDIR)/jlog.h \
		 $(JEFF_INCDIR)/jmemory.h \
		 $(JEFF_INCDIR)/jrandom.h \
		 $(JEFF_INCDIR)/jsignal.h \
		 $(JEFF_INCDIR)/jstring.h \
		 $(JEFF_INCDIR)/jtypes.h

JEFF_PREPROC =$(JEFF_PREPROCDIR)/jdie.i \
			  $(JEFF_PREPROCDIR)/jerr.i \
			  $(JEFF_PREPROCDIR)/jhash.i \
			  $(JEFF_PREPROCDIR)/jinput.i \
			  $(JEFF_PREPROCDIR)/jfile.i \
			  $(JEFF_PREPROCDIR)/jlog.i \
			  $(JEFF_PREPROCDIR)/jmemory.i \
			  $(JEFF_PREPROCDIR)/jrandom.i \
			  $(JEFF_PREPROCDIR)/jsignal.i \
			  $(JEFF_PREPROCDIR)/jstring.i

JEFF_AS =$(JEFF_ASDIR)/jdie.s \
		 $(JEFF_ASDIR)/jerr.s \
		 $(JEFF_ASDIR)/jhash.s \
		 $(JEFF_ASDIR)/jinput.s \
		 $(JEFF_ASDIR)/jfile.s \
		 $(JEFF_ASDIR)/jlog.s \
		 $(JEFF_ASDIR)/jmemory.s \
		 $(JEFF_ASDIR)/jrandom.s \
		 $(JEFF_ASDIR)/jsignal.s \
		 $(JEFF_ASDIR)/jstring.s

JEFF_OBJECTS =$(OBJDIR)/jdie.o \
			  $(OBJDIR)/jerr.o \
			  $(OBJDIR)/jhash.o \
			  $(OBJDIR)/jinput.o \
			  $(OBJDIR)/jfile.o \
			  $(OBJDIR)/jlog.o \
			  $(OBJDIR)/jmemory.o \
			  $(OBJDIR)/jrandom.o \
			  $(OBJDIR)/jsignal.o \
			  $(OBJDIR)/jstring.o

JEFF_LIBS = $(LIBDIR)/libjeff.so

JEFF_STATIC_LIBS = $(LIBDIR)/libjdie.a \
				   $(LIBDIR)/libjerr.a \
				   $(LIBDIR)/libjhash.a \
				   $(LIBDIR)/libjinput.a \
				   $(LIBDIR)/libjfile.a \
				   $(LIBDIR)/libjlog.a \
				   $(LIBDIR)/libjmemory.a \
				   $(LIBDIR)/libjrandom.a \
				   $(LIBDIR)/libjsignal.a \
				   $(LIBDIR)/libjstring.a

JEFF_CFLAGS = $(CFLAGS) -fPIC
JEFF_LDFLAGS = -lc

PREFROC_ACTIONS = $(PREPROCDIR)/cointoss.i \
				  $(PREPROCDIR)/countdown.i \
				  $(PREPROCDIR)/misc.i \
				  $(PREPROCDIR)/nwl_trim.i \
				  $(PREPROCDIR)/shrug.i \
				  $(PREPROCDIR)/yn.i

AS_ACTIONS = $(ASDIR)/cointoss.s \
			 $(ASDIR)/countdown.s \
			 $(ASDIR)/misc.s \
			 $(ASDIR)/nwl_trim.s \
			 $(ASDIR)/shrug.s \
			 $(ASDIR)/yn.s

JEFF_ACTIONS = cointoss \
			   countdown \
			   misc \
			   nwl_trim \
			   shrug \
			   yn

ACTIONS = $(JEFF_ACTIONS)

# vim: set ts=4 sts=4 sw=0 noet ai si sta:
