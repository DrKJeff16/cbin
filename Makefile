SHELL = /bin/bash

include config.mk

CC := gcc
CXX := g++

all: $(ACTIONS)

$(LIBDIR):
	mkdir -p $(LIBDIR)
$(BINDIR):
	mkdir -p $(BINDIR)
$(OBJDIR):
	mkdir -p $(OBJDIR)

libs: $(LIBDIR) $(JEFF_SRC)
	$(CC) -c $(SRCDIR)/jdie.c -o $(OBJDIR)/jdie.o $(JEFF_CFLAGS)
	$(CC) -c $(SRCDIR)/jerr.c -o $(OBJDIR)/jerr.o $(JEFF_CFLAGS)
	$(CC) -c $(SRCDIR)/joperators.c -o $(OBJDIR)/joperators.o $(JEFF_CFLAGS)
	$(CC) -c $(SRCDIR)/jstring.c -o $(OBJDIR)/jstring.o $(JEFF_CFLAGS)
	$(CC) $(OBJDIR)/jdie.o -o $(LIBDIR)/libjdie.so $(JEFF_LDFLAGS) -shared
	$(CC) $(OBJDIR)/jerr.o -o $(LIBDIR)/libjerr.so $(JEFF_LDFLAGS) -shared
	$(CC) $(OBJDIR)/joperators.o -o $(LIBDIR)/libjoperators.so $(JEFF_LDFLAGS) -shared
	$(CC) $(OBJDIR)/jstring.o -o $(LIBDIR)/libjstring.so $(JEFF_LDFLAGS) -shared

strip/bin: $(BINDIR)
	strip $(BINDIR)/*
strip/libs: $(LIBDIR)
	strip $(LIBDIR)/*

install_libs/fast: libs
	install -m 755 $(LIBDIR)/libjdie.so ~/.local/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so ~/.local/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so ~/.local/lib/libjoperators.so
install_libs/stripped: libs
	install -m 755 $(LIBDIR)/libjdie.so ~/.local/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so ~/.local/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so ~/.local/lib/libjoperators.so
	strip ~/.local/lib/libj{die,err,operators}.so
install_global_libs/fast: libs
	install -m 755 $(LIBDIR)/libjdie.so /usr/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so /usr/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so /usr/lib/libjoperators.so
install_global_libs/stripped: libs
	install -m 755 $(LIBDIR)/libjdie.so /usr/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so /usr/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so /usr/lib/libjoperators.so
	strip /usr/lib/libj{die,err,operators}.so

cointoss: $(SRCDIR)/cointoss.c libs $(BINDIR) $(INCDIR)/jeff/cointoss.h $(JEFF_H)
	$(CC) -c $(SRCDIR)/cointoss.c -o $(OBJDIR)/cointoss.o $(CFLAGS)
	$(CC) $(OBJDIR)/cointoss.o -o $(BINDIR)/$@ $(CFLAGS) $(LDFLAGS)

misc: $(SRCDIR)/misc.c libs $(BINDIR) $(JEFF_H)
	$(CC) -c $(SRCDIR)/misc.c -o $(OBJDIR)/misc.o $(CFLAGS)
	$(CC) $(OBJDIR)/misc.o -o $(BINDIR)/$@ $(CFLAGS) $(LDFLAGS)

gl_1: $(SRCDIR)/jeff_gl_1.c libs  $(BINDIR) $(GL_H)
	$(CC) -c $(SRCDIR)/jeff_gl_1.c -o $(OBJDIR)/jeff_gl_1.o $(GL_CFLAGS)
	$(CC) $(OBJDIR)/jeff_gl_1.o -o $(BINDIR)/jeff_$@ $(GL_CFLAGS) $(LDFLAGS)

gl_2: $(SRCDIR)/jeff_gl_2.c libs $(BINDIR) $(GL_H)
	$(CC) -c $(SRCDIR)/jeff_gl_2.c -o $(OBJDIR)/jeff_gl_2.o $(GL_CFLAGS)
	$(CC) $(OBJDIR)/jeff_gl_2.o -o $(BINDIR)/jeff_$@ $(GL_CFLAGS) $(LDFLAGS)

gl_3: $(SRCDIR)/jeff_gl_3.cpp libs $(BINDIR) $(GL_H)
	$(CXX) -c $(SRCDIR)/jeff_gl_3.cpp -o $(OBJDIR)/jeff_gl_3.o $(GL_CFLAGS) $(CXXFLAGS)
	$(CXX) $(OBJDIR)/jeff_gl_3.o -o $(BINDIR)/jeff_$@ $(GL_CFLAGS)

gtk_1: $(SRCDIR)/jeff_gtk_1.c libs $(BINDIR) $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_1.c -o $(OBJDIR)/jeff_gtk_1.o $(GTK_CFLAGS)
	$(CC) $(OBJDIR)/jeff_gtk_1.o -o $(BINDIR)/jeff_$@ $(GTK_CFLAGS) $(LDFLAGS)

gtk_2: $(SRCDIR)/jeff_gtk_2.c libs $(BINDIR) $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_2.c -o $(OBJDIR)/jeff_gtk_2.o $(GTK_CFLAGS)
	$(CC) $(OBJDIR)/jeff_gtk_2.o -o $(BINDIR)/jeff_$@ $(GTK_CFLAGS) $(LDFLAGS)

gtk_3: $(SRCDIR)/jeff_gtk_3.c libs $(BINDIR) $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_3.c -o $(OBJDIR)/jeff_gtk_3.o $(GTK_CFLAGS)
	$(CC) $(OBJDIR)/jeff_gtk_3.o -o $(BINDIR)/jeff_$@ $(GTK_CFLAGS) $(LDFLAGS)

gtk_4: $(SRCDIR)/jeff_gtk_4.c libs $(BINDIR) $(GTK_H) $(SRCDIR)/builder.ui
	$(CC) -c $(SRCDIR)/jeff_gtk_4.c -o $(OBJDIR)/jeff_gtk_4.o $(GTK_CFLAGS)
	$(CC) $(OBJDIR)/jeff_gtk_4.o -o $(BINDIR)/jeff_$@ $(GTK_CFLAGS) $(LDFLAGS)

gtk_5: $(SRCDIR)/jeff_gtk_5.c libs $(BINDIR) $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_5.c -o $(OBJDIR)/jeff_gtk_5.o $(GTK_CFLAGS)
	$(CC) $(OBJDIR)/jeff_gtk_5.o -o $(BINDIR)/jeff_$@ $(GTK_CFLAGS) $(LDFLAGS)

sdl_1: $(SRCDIR)/jeff_sdl_1.c libs $(BINDIR) $(SDL_H) $(SRCDIR)/face.png
	$(CC) -c $(SRCDIR)/jeff_sdl_1.c -o $(OBJDIR)/jeff_sdl_1.o $(SDL_CFLAGS)
	$(CC) $(OBJDIR)/jeff_sdl_1.o -o $(BINDIR)/jeff_$@ $(SDL_CFLAGS) $(LDFLAGS)

lua_1: $(SRCDIR)/jeff_lua_1.c libs $(BINDIR) $(LUA_H)
	$(CC) -c $(SRCDIR)/jeff_lua_1.c -o $(OBJDIR)/jeff_lua_1.o $(LUA_CFLAGS)
	$(CC) $(OBJDIR)/jeff_lua_1.o -o $(BINDIR)/jeff_$@ $(LUA_CFLAGS) $(LDFLAGS)

ncurses_1: $(SRCDIR)/jeff_ncurses_1.c libs $(BINDIR) $(NCURSES_H) $(SRCDIR)/face.png
	$(CC) -c $(SRCDIR)/jeff_ncurses_1.c -o $(OBJDIR)/jeff_ncurses_1.o $(NCURSES_CFLAGS)
	$(CC) $(OBJDIR)/jeff_ncurses_1.o -o $(BINDIR)/jeff_$@ $(NCURSES_CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o $(BINDIR)/*.o $(OBJDIR)/* $(LIBDIR)/*.o $(SRCDIR)/*.o
distclean: clean
	rm -rf $(BINDIR)/* *.so *.a $(LIBDIR)/* build

.PHONY: $(ACTIONS) distclean clean all libs \
	strip/bin strip/libs \
	install_libs/fast install_libs/stripped \
	install_global_libs/fast install_global_libs/stripped
