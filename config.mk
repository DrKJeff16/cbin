CC := gcc
CXX := g++

LOCAL_PREFIX := $(HOME)/.local
GLOBAL_PREFIX := /usr
ASSET_DIR := $(LOCAL_PREFIX)/share/jassets
INSTALL_BIN_DIR := $(GLOBAL_PREFIX)/bin
BINDIR := bin
INCDIR := include
LIBDIR := lib
OBJDIR := obj
SRCDIR := src

ALL_DIRS = $(ASSET_DIR) \
		   $(BINDIR) \
		   $(INCDIR) \
		   $(LIBDIR) \
		   $(OBJDIR) \
		   $(SRCDIR)

CPPFLAGS = -Iinclude \
		   -I. \
		   -DNDEBUG \
		   -D_GNU_SOURCE \
		   -D_FORTIFY_SOURCE=2

CFLAGS = $(CPPFLAGS) \
		 -march=native \
		 -pipe \
		 -std=gnu99 \
		 -O2 \
		 -g \
		 -ggdb \
		 -Wall \
		 -Wextra \
		 -pedantic \
		 -pthread

CXXFLAGS = $(CPPFLAGS) \
		   -I/usr/include/docopt \
		   -std=c++17 \
		   -march=native \
		   -pipe \
		   -O2 \
		   -g \
		   -ggdb \
		   -Wall \
		   -Wextra \
		   -pedantic \
		   -pthread

LDFLAGS = -L/usr/lib/jeff -Llib -ljeff
LDXXFLAGS = -L/usr/lib/jeff -Llib -ldocopt

PKG_CONFIG_BIN := pkgconf

JEFF_INCDIR = $(INCDIR)/jeff
JEFF_H = $(JEFF_INCDIR)/jeff.h \
		 $(JEFF_INCDIR)/jautomata.h \
		 $(JEFF_INCDIR)/jinput.h \
		 $(JEFF_INCDIR)/jlog.h \
		 $(JEFF_INCDIR)/jlua.h \
		 $(JEFF_INCDIR)/jmemory.h \
		 $(JEFF_INCDIR)/jrandom.h \
		 $(JEFF_INCDIR)/jstring.h \
		 $(JEFF_INCDIR)/jtypes.h

JEFF_LIBS = $(LIBDIR)/libjeff.so $(LIBDIR)/libjlua.so

JEFF_CFLAGS = $(CFLAGS) -fPIC
JEFF_LDFLAGS = -lc -lpthread -lm
JEFF_ACTIONS = cointoss jparse

JEFF_LUA_H = $(JEFF_INCDIR)/jlua.h
JEFF_LUA_CFLAGS = $(JEFF_CFLAGS) -I/usr/include/luajit-2.1
JEFF_LUA_LDFLAGS = -L/usr/lib/jeff -Llib -L. $(JEFF_LDFLAGS) -ljeff -llua -lluajit-5.1

LUA_H = $(JEFF_INCDIR)/jlua.h
LUA_ACTIONS = lua_1

ACTIONS = dirs $(JEFF_ACTIONS)

# ACTIONS = dirs \
# 		  $(JEFF_ACTIONS) \
# 		  $(GTK_ACTIONS) \
# 		  $(SDL_ACTIONS) \
# 		  $(NCURSES_ACTIONS) \
# 		  $(GL_ACTIONS) \
# 		  $(LUA_ACTIONS)
