CPPFLAGS = -I. -I../include -Iinclude -DNDEBUG -D_GNU_SOURCE -D_FORTIFY_SOURCE=2
CFLAGS = $(CPPFLAGS) -march=znver3 -pipe -g -O2 -Wall -pedantic -pthread
CXXFLAGS = $(CFLAGS) -D_GLIBCXX_ASSERTIONS
LDFLAGS = -L. -L../lib -Llib -ljerr -ljdie -ljoperators -ljstring

PKG_CONFIG_BIN := pkgconf

BINDIR = bin
INCDIR = include
LIBDIR = lib
OBJDIR = obj
SRCDIR = src

JEFF_H = $(INCDIR)/jeff/jeff.h $(INCDIR)/jeff/jmemory.h $(INCDIR)/jeff/jstring.h
JEFF_SRC = $(SRCDIR)/jdie.c $(SRCDIR)/jerr.c $(SRCDIR)/joperators.c $(SRCDIR)/jstring.c
JEFF_OUT = $(OBJDIR)/jdie.o $(OBJDIR)/jerr.o $(OBJDIR)/joperators.o $(OBJDIR)/jstring.o
JEFF_LIBS = $(LIBDIR)/libjdie.so $(LIBDIR)/libjerr.so $(LIBDIR)/libjoperators.so $(LIBDIR)/libjstring.so
JEFF_CFLAGS = $(CPPFLAGS) -march=znver3 -pipe -g -O2 -Wall -pedantic -fPIC
JEFF_LDFLAGS = -fPIC
JEFF_ACTIONS = cointoss misc

SDL_CFLAGS = $(CFLAGS) `sdl2-config --cflags --libs` -lSDL2_image
SDL_H = $(INCDIR)/jeff/jeff_sdl.h
SDL_ACTIONS = sdl_1

GTK_CFLAGS = $(CFLAGS) `$(PKG_CONFIG_BIN) gtk4 --cflags --libs`
GTK_H = $(INCDIR)/jeff/jeff_gtk.h
GTK_ACTIONS = gtk_1 gtk_2 gtk_3 gtk_4 gtk_5

NCURSES_CFLAGS = $(CFLAGS) `$(PKG_CONFIG_BIN) ncurses --cflags --libs`
NCURSES_H = $(INCDIR)/jeff/jeff_ncurses.h
NCURSES_ACTIONS = ncurses_1

GL_CFLAGS = $(CFLAGS) `$(PKG_CONFIG_BIN) --cflags --libs glfw3 x11 xrandr xi gl glew glu glut` -ldl -lpthread -lm
GL_H = $(INCDIR)/jeff/jeff_gl.h
GL_ACTIONS = gl_1 gl_2

LUA_CFLAGS = $(CFLAGS) `$(PKG_CONFIG_BIN) --cflags --libs lua luajit`
LUA_H = $(INCDIR)/jeff/jeff_lua.h
LUA_ACTIONS = lua_1

ACTIONS = libs $(JEFF_ACTIONS) \
		  $(GTK_ACTIONS) \
		  $(SDL_ACTIONS) \
		  $(NCURSES_ACTIONS) \
		  $(GL_ACTIONS) \
		  $(LUA_ACTIONS)
