CC := gcc
CXX := g++

ASSET_DIR := $(HOME)/.local/share/jassets
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
		   -DNDEBUG \
		   -D_GNU_SOURCE \
		   -D_FORTIFY_SOURCE=2
CFLAGS = $(CPPFLAGS) \
		 -march=znver3 \
		 -pipe \
		 -std=gnu11 \
		 -O2 \
		 -g \
		 -ggdb \
		 -Wall \
		 -pedantic \
		 -pthread
CXXFLAGS = $(CPPFLAGS) \
		   -std=gnu++17 \
		   -march=znver3 \
		   -pipe \
		   -O2 \
		   -g \
		   -ggdb \
		   -Wall \
		   -pedantic \
		   -pthread
LDFLAGS = -Llib -L/usr/lib/jeff -ljeff -lc -lm -lpthread

PKG_CONFIG_BIN := pkgconf

JEFF_INCDIR = $(INCDIR)/jeff
JEFF_H = $(JEFF_INCDIR)/jeff.h \
		 $(JEFF_INCDIR)/jmemory.h \
		 $(JEFF_INCDIR)/jstring.h \
		 $(JEFF_INCDIR)/jlua.h \
		 $(JEFF_INCDIR)/jlog.h
JEFF_LIBS = $(LIBDIR)/libjeff.so \
			$(LIBDIR)/libjlua.so
JEFF_CFLAGS = $(CFLAGS) -fPIC
JEFF_LDFLAGS = -L/usr/lib/jeff -lc -lm
JEFF_ACTIONS = cointoss jmisc

JEFF_LUA_H = $(JEFF_INCDIR)/jlua.h
JEFF_LUA_CFLAGS = $(JEFF_CFLAGS)
JEFF_LUA_LDFLAGS = $(JEFF_LDFLAGS) -llua

SDL_CFLAGS = $(CFLAGS) \
			 -D_JASSET_PATH="\"$(ASSET_DIR)/face.png\"" \
			 -D_REENTRANT \
			 -I/usr/include/SDL2
SDL_LDFLAGS = $(LDFLAGS) \
			  -lSDL2 \
			  -lSDL2_image
SDL_H = $(JEFF_INCDIR)/jeff_sdl.h
SDL_ACTIONS = sdl_1

GTK_CFLAGS = $(CFLAGS) \
			 -I/usr/include/gtk-4.0 \
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
			 -D_JASSET_PATH="\"$(ASSET_DIR)/builder.ui\"" \
			 -pthread
GTK_LDFLAGS = $(LDFLAGS) \
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
			  -lpthread \
			  -lvulkan \
			  -mfpmath=sse \
			  -msse \
			  -msse2
GTK_H = $(JEFF_INCDIR)/jeff_gtk.h
GTK_ACTIONS = gtk_1 gtk_2 gtk_3 gtk_4 gtk_5

NCURSES_CFLAGS = $(CFLAGS) \
				 -D_DEFAULT_SOURCE \
				 -D_XOPEN_SOURCE=600
NCURSES_LDFLAGS = $(LDFLAGS) \
				  -lncursesw
NCURSES_H = $(JEFF_INCDIR)/jeff_ncurses.h
NCURSES_ACTIONS = ncurses_1

GL_CFLAGS = $(CFLAGS) \
			-pthread
GL_LDFLAGS = $(LDFLAGS) \
			 -lEGL \
			 -lGL \
			 -lGLEW \
			 -lGLU \
			 -lOpenGL \
			 -lX11 \
			 -lXi \
			 -lXrandr \
			 -ldl \
			 -lglfw \
			 -lglut \
			 -lpthread
GL_H = $(JEFF_INCDIR)/jeff_gl.h
GL_ACTIONS = gl_1

LUA_CFLAGS = $(CFLAGS) \
			 -I/usr/include/luajit-2.1
LUA_LDFLAGS = $(LDFLAGS) \
			  -ljlua \
			  -llua \
			  -lluajit-5.1
LUA_H = $(JEFF_INCDIR)/jlua.h
LUA_ACTIONS = lua_1

ACTIONS = dirs \
		  $(JEFF_ACTIONS) \
		  $(GTK_ACTIONS) \
		  $(SDL_ACTIONS) \
		  $(NCURSES_ACTIONS) \
		  $(GL_ACTIONS) \
		  $(LUA_ACTIONS)
