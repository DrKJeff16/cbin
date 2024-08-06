SHELL = /bin/bash

CC := gcc
CXX := g++
CPPFLAGS := -I. -Iinclude -DNDEBUG -D_FORTIFY_SOURCE=2
CFLAGS := $(CPPFLAGS) -march=znver3 -pipe -g -ggdb -O2 -Wall -Llib -pedantic -pthread
CXXFLAGS := $(CFLAGS) -D_GLIBCXX_ASSERTIONS
LDFLAGS := -Llib -ljerr -ljdie -ljoperators

BINDIR := bin
INCDIR := include/jeff
LIBDIR := lib
OBJDIR := obj

JEFF_H = $(INCDIR)/jeff.h
JEFF_OUT = $(OBJDIR)/jdie.o $(OBJDIR)/jerr.o $(OBJDIR)/joperators.o
JEFF_LIBS = $(LIBDIR)/libjdie.so $(LIBDIR)/libjerr.so $(LIBDIR)/libjoperators.so
JEFF_CFLAGS = $(CPPFLAGS) -march=znver3 -pipe -g -ggdb -O2 -Wall -fPIC
JEFF_LDFLAGS = -Llib -fPIC
JEFF_ACTIONS = cointoss misc

SDL_CFLAGS = $(CFLAGS) `sdl2-config --cflags --libs` -lSDL2_image
SDL_H = $(INCDIR)/jeff_sdl.h
SDL_ACTIONS = sdl_1

GTK_CFLAGS = $(CFLAGS) `pkgconf gtk4 --cflags --libs`
GTK_H = $(INCDIR)/jeff_gtk.h
GTK_ACTIONS = gtk_1 gtk_2 gtk_3 gtk_4 gtk_5

NCURSES_CFLAGS = $(CFLAGS) `pkgconf ncurses --cflags --libs`
NCURSES_H = $(INCDIR)/jeff_ncurses.h
NCURSES_ACTIONS = ncurses_1

GL_CFLAGS = $(CFLAGS) `pkgconf --cflags --libs glfw3 x11 xrandr xi gl glew glu glut` -ldl -lpthread -lm
GL_H = $(INCDIR)/jeff_gl.h
GL_ACTIONS = gl_1 gl_2

LUA_CFLAGS = $(CFLAGS) `pkgconf --cflags --libs lua luajit`
LUA_H = $(INCDIR)/jeff_lua.h
LUA_ACTIONS = lua_1

ACTIONS = $(JEFF_LIBS) $(JEFF_ACTIONS) \
		  $(GTK_ACTIONS) \
		  $(SDL_ACTIONS) \
		  $(NCURSES_ACTIONS) \
		  $(GL_ACTIONS) \
		  $(LUA_ACTIONS)

all: $(ACTIONS)

cointoss: $(BINDIR)/cointoss
misc: $(BINDIR)/misc
gl_1: $(BINDIR)/jeff_gl_1
gl_2: $(BINDIR)/jeff_gl_2
gl_3: $(BINDIR)/jeff_gl_3
gtk_1: $(BINDIR)/jeff_gtk_1
gtk_2: $(BINDIR)/jeff_gtk_2
gtk_3: $(BINDIR)/jeff_gtk_3
gtk_4: $(BINDIR)/jeff_gtk_4
gtk_5: $(BINDIR)/jeff_gtk_5
sdl_1: $(BINDIR)/jeff_sdl_1
lua_1: $(BINDIR)/jeff_lua_1
ncurses_1: $(BINDIR)/jeff_ncurses_1

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/jeff_lua_1: $(BINDIR) $(OBJDIR)/jeff_lua_1.o $(JEFF_LIBS) $(LUA_H)
	$(CC) $(OBJDIR)/jeff_lua_1.o -o $@ $(LUA_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_lua_1.o: jeff_lua_1.c $(LUA_H)
	$(CC) -c jeff_lua_1.c -o $@ $(LUA_CFLAGS)

$(BINDIR)/jeff_gl_1: $(BINDIR) $(OBJDIR)/jeff_gl_1.o $(JEFF_LIBS) $(GL_H)
	$(CC) $(OBJDIR)/jeff_gl_1.o -o $@ $(GL_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_gl_1.o: jeff_gl_1.c $(GL_H)
	$(CC) -c jeff_gl_1.c -o $@ $(GL_CFLAGS)
$(BINDIR)/jeff_gl_2: $(BINDIR) $(OBJDIR)/jeff_gl_2.o $(JEFF_LIBS) $(GL_H)
	$(CC) $(OBJDIR)/jeff_gl_2.o -o $@ $(GL_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_gl_2.o: jeff_gl_2.c $(GL_H)
	$(CC) -c jeff_gl_2.c -o $@ $(GL_CFLAGS)
$(BINDIR)/jeff_gl_3: $(BINDIR) $(OBJDIR)/jeff_gl_3.o $(GL_H)
	$(CXX) $(OBJDIR)/jeff_gl_3.o -o $@ $(GL_CFLAGS)
$(OBJDIR)/jeff_gl_3.o: jeff_gl_3.cpp $(GL_H)
	$(CXX) -c jeff_gl_3.cpp -o $@ $(GL_CFLAGS) $(CXXFLAGS)

$(BINDIR)/jeff_gtk_1: $(BINDIR) $(OBJDIR)/jeff_gtk_1.o $(JEFF_LIBS) $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_1.o -o $@ $(GTK_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_gtk_1.o: jeff_gtk_1.c $(GTK_H)
	$(CC) -c jeff_gtk_1.c -o $@ $(GTK_CFLAGS)
$(BINDIR)/jeff_gtk_2: $(BINDIR) $(OBJDIR)/jeff_gtk_2.o $(JEFF_LIBS) $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_2.o -o $@ $(GTK_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_gtk_2.o: jeff_gtk_2.c $(GTK_H)
	$(CC) -c jeff_gtk_2.c -o $@ $(GTK_CFLAGS)
$(BINDIR)/jeff_gtk_3: $(BINDIR) $(OBJDIR)/jeff_gtk_3.o $(JEFF_LIBS) $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_3.o -o $@ $(GTK_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_gtk_3.o: jeff_gtk_3.c $(GTK_H)
	$(CC) -c jeff_gtk_3.c -o $@ $(GTK_CFLAGS)
$(BINDIR)/jeff_gtk_4: $(BINDIR) $(OBJDIR)/jeff_gtk_4.o $(JEFF_LIBS) $(GTK_H) builder.ui
	$(CC) $(OBJDIR)/jeff_gtk_4.o -o $@ $(GTK_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_gtk_4.o: jeff_gtk_4.c $(GTK_H) builder.ui
	$(CC) -c jeff_gtk_4.c -o $@ $(GTK_CFLAGS)
$(BINDIR)/jeff_gtk_5: $(BINDIR) $(OBJDIR)/jeff_gtk_5.o $(JEFF_LIBS) $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_5.o -o $@ $(GTK_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_gtk_5.o: jeff_gtk_5.c $(GTK_H)
	$(CC) -c jeff_gtk_5.c -o $@ $(GTK_CFLAGS)

$(BINDIR)/jeff_sdl_1: $(BINDIR) $(OBJDIR)/jeff_sdl_1.o $(JEFF_LIBS) $(SDL_H) face.png
	$(CC) $(OBJDIR)/jeff_sdl_1.o -o $@ $(SDL_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_sdl_1.o: jeff_sdl_1.c $(SDL_H) face.png
	$(CC) -c jeff_sdl_1.c -o $@ $(SDL_CFLAGS)

$(BINDIR)/jeff_ncurses_1: $(BINDIR) $(OBJDIR)/jeff_ncurses_1.o $(JEFF_LIBS) $(NCURSES_H) face.png
	$(CC) $(OBJDIR)/jeff_ncurses_1.o -o $@ $(NCURSES_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_ncurses_1.o: jeff_ncurses_1.c $(NCURSES_H) face.png
	$(CC) -c jeff_ncurses_1.c -o $@ $(NCURSES_CFLAGS)

$(BINDIR)/cointoss: $(BINDIR) $(OBJDIR)/cointoss.o $(INCDIR)/cointoss.h $(JEFF_LIBS) $(JEFF_H)
	$(CC) $(OBJDIR)/cointoss.o -o $@ $(CFLAGS) $(LDFLAGS)
$(OBJDIR)/cointoss.o: cointoss.c $(INCDIR)/cointoss.h $(JEFF_H)
	$(CC) -c cointoss.c -o $@ $(CFLAGS)

$(BINDIR)/misc: $(BINDIR) $(OBJDIR)/misc.o $(JEFF_LIBS) $(JEFF_H)
	$(CC) $(OBJDIR)/misc.o -o $@ $(CFLAGS) $(LDFLAGS)
$(OBJDIR)/misc.o: misc.c $(JEFF_H)
	$(CC) -c misc.c -o $@ $(CFLAGS)

$(LIBDIR)/libjdie.so: $(OBJDIR)/jdie.o $(JEFF_H)
	$(CC) -shared $(OBJDIR)/jdie.o -o $@ $(JEFF_LDFLAGS)
$(LIBDIR)/libjerr.so: $(OBJDIR)/jerr.o $(JEFF_H)
	$(CC) -shared $(OBJDIR)/jerr.o -o $@ $(JEFF_LDFLAGS)
$(LIBDIR)/libjoperators.so: $(OBJDIR)/joperators.o $(JEFF_H)
	$(CC) -shared $(OBJDIR)/joperators.o -o $@ $(JEFF_LDFLAGS)
$(OBJDIR)/jdie.o: jdie.c $(JEFF_H)
	$(CC) -c jdie.c -o $@ $(JEFF_CFLAGS)
$(OBJDIR)/jerr.o: jerr.c $(JEFF_H)
	$(CC) -c jerr.c -o $@ $(JEFF_CFLAGS)
$(OBJDIR)/joperators.o: joperators.c $(JEFF_H)
	$(CC) -c joperators.c -o $@ $(JEFF_CFLAGS)

libs: $(JEFF_LIBS)

install_libs:
	install -m 755 $(LIBDIR)/libjdie.so ~/.local/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so ~/.local/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so ~/.local/lib/libjoperators.so
install_global_libs:
	install -m 755 $(LIBDIR)/libjdie.so /usr/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so /usr/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so /usr/lib/libjoperators.so

distclean: clean
	rm -f $(BINDIR)/* *.so $(LIBDIR)/*
clean:
	rm -f *.o $(BINDIR)/*.o obj/*

.PHONY: $(ACTIONS) distclean clean all libs
