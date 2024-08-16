CPPFLAGS = -I. -Iinclude -DNDEBUG -D_GNU_SOURCE -D_FORTIFY_SOURCE=2
CFLAGS = $(CPPFLAGS) -march=znver3 -pipe -g -O2 -Wall -pedantic -pthread
CXXFLAGS = $(CFLAGS) -D_GLIBCXX_ASSERTIONS
LDFLAGS = -L. -Llib -ljerr -ljdie -ljoperators -ljstring -ljlog -lc

PKG_CONFIG_BIN := pkgconf

BINDIR := bin
INCDIR := include
LIBDIR := lib
OBJDIR := obj
SRCDIR := src

JEFF_INCDIR = $(INCDIR)/jeff
JEFF_H = $(JEFF_INCDIR)/jeff.h $(JEFF_INCDIR)/jmemory.h $(JEFF_INCDIR)/jstring.h $(JEFF_INCDIR)/jlog.h
JEFF_SRC = $(SRCDIR)/jdie.c $(SRCDIR)/jerr.c $(SRCDIR)/joperators.c $(SRCDIR)/jstring.c $(SRCDIR)/jlog.c
JEFF_OUT = $(OBJDIR)/jdie.o $(OBJDIR)/jerr.o $(OBJDIR)/joperators.o $(OBJDIR)/jstring.o $(SRCDIR)/jlog.o
JEFF_LIBS = $(LIBDIR)/libjdie.so $(LIBDIR)/libjerr.so \
			$(LIBDIR)/libjoperators.so $(LIBDIR)/libjstring.so \
			$(LIBDIR)/libjlog.so
JEFF_CFLAGS = $(CFLAGS) -fPIC
JEFF_LDFLAGS = -lc -lm
JEFF_ACTIONS = cointoss misc

SDL_CFLAGS = $(CFLAGS) \
			 -D_REENTRANT \
			 -I/usr/include/SDL2 \
			 -L/usr/lib \
			 -lSDL2 \
			 -lSDL2_image \
			 -lc
SDL_H = $(JEFF_INCDIR)/jeff_sdl.h
SDL_ACTIONS = sdl_1

GTK_CFLAGS = $(CFLAGS) -I/usr/include/gtk-4.0 \
			 -I/usr/include/blkid \
			 -I/usr/include/cairo \
			 -I/usr/include/freetype2 \
			 -I/usr/include/fribidi \
			 -I/usr/include/gdk-pixbuf-2.0 \
			 -I/usr/include/glib-2.0 \
			 -I/usr/include/graphene-1.0 \
			 -I/usr/include/harfbuzz \
			 -I/usr/include/libmount \
			 -I/usr/include/libpng16 \
			 -I/usr/include/pango-1.0 \
			 -I/usr/include/pixman-1 \
			 -I/usr/include/sysprof-6 \
			 -I/usr/lib/glib-2.0/include \
			 -I/usr/lib/graphene-1.0/include \
			 -lc \
			 -lcairo \
			 -lcairo-gobject \
			 -lgdk_pixbuf-2.0 \
			 -lgio-2.0 \
			 -lglib-2.0 \
			 -lgobject-2.0 \
			 -lgraphene-1.0 \
			 -lgtk-4 \
			 -lharfbuzz \
			 -lpango-1.0 \
			 -lpangocairo-1.0 \
			 -lvulkan \
			 -mfpmath=sse \
			 -msse \
			 -msse2 \
			 -pthread
GTK_H = $(JEFF_INCDIR)/jeff_gtk.h
GTK_ACTIONS = gtk_1 gtk_2 gtk_3 gtk_4 gtk_5

NCURSES_CFLAGS = $(CFLAGS) \
				 -D_DEFAULT_SOURCE \
				 -D_XOPEN_SOURCE=600 \
				 -lncursesw
NCURSES_H = $(JEFF_INCDIR)/jeff_ncurses.h
NCURSES_ACTIONS = ncurses_1

GL_CFLAGS = $(CFLAGS) \
			-lEGL \
			-lGL \
			-lGLEW \
			-lGLU \
			-lOpenGL \
			-lX11 \
			-lXi \
			-lXrandr \
			-lc \
			-ldl \
			-lglfw \
			-lglut \
			-lm \
			-lpthread \
			-pthread
GL_H = $(JEFF_INCDIR)/jeff_gl.h
GL_ACTIONS = gl_1 gl_2

LUA_CFLAGS = $(CFLAGS) \
			 -I/usr/include/luajit-2.1 \
			 -lc \
			 -llua \
			 -lluajit-5.1 \
			 -lm
LUA_H = $(JEFF_INCDIR)/jeff_lua.h
LUA_ACTIONS = lua_1

ACTIONS = libs $(JEFF_ACTIONS) \
		  $(GTK_ACTIONS) \
		  $(SDL_ACTIONS) \
		  $(NCURSES_ACTIONS) \
		  $(GL_ACTIONS) \
		  $(LUA_ACTIONS)
