CC := ${CC}
CXX := ${CXX}
AR := gcc-ar

LTO := OFF

IWYU = include-what-you-use

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

CPPFLAGS = -DNDEBUG \
		   -D_DEFAULT_SOURCE \
		   -D_FORTIFY_SOURCE=2 \
		   -D_GNU_SOURCE \
		   -I$(GLOBAL_PREFIX)/include/jeff \
		   -I. \
		   -Iinclude

CFLAGS = $(CPPFLAGS) \
		 -O2 \
		 -Wall \
		 -Wextra \
		 -Wformat-security \
		 -Wno-implicit-fallthrough \
		 -Wno-unused \
		 -g \
		 -ggdb \
		 -march=native \
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
		   -fomit-frame-pointer \
		   -fsanitize=address \
		   -fstack-clash-protection \
		   -fstack-protector \
		   -ftree-vectorize \
		   -g \
		   -ggdb \
		   -march=native \
		   -pedantic \
		   -pipe \
		   -pthread \
		   -std=c++17

LDFLAGS = -L$(GLOBAL_PREFIX)/lib/jeff \
		  -Llib \
		  -fcf-protection \
		  -fomit-frame-pointer \
		  -fsanitize=address \
		  -fstack-clash-protection \
		  -fstack-protector \
		  -ftree-vectorize \
		  -lc \
		  -liniparser \
		  -ljeff

LDXXFLAGS = -L$(GLOBAL_PREFIX)/lib/jeff \
			-Llib \
			-fcf-protection \
			-fomit-frame-pointer \
			-fsanitize=address \
			-fstack-clash-protection \
			-fstack-protector \
			-ftree-vectorize \
			-ljeff

PKG_CONFIG_BIN := pkgconf

JEFF_INCDIR = $(INCDIR)/jeff

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

JEFF_OBJECTS =$(OBJDIR)/jdie.o \
			  $(OBJDIR)/jerr.o \
			  $(OBJDIR)/jhash.o \
			  $(OBJDIR)/jinput.o \
			  $(OBJDIR)/jfile.o \
			  $(OBJDIR)/jlog.o \
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
JEFF_LDFLAGS = -lc \
			   -liniparser

JEFF_ACTIONS = cointoss \
			   countdown \
			   jmisc \
			   ndice \
			   nwl_trim \
			   shrug \
			   yn

ACTIONS = $(JEFF_ACTIONS)

# vim: set ts=4 sts=4 sw=0 noet ai si sta:
