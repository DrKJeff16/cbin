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

libs: $(LIBDIR) $(JEFF_SRC) $(JEFF_H)
	$(CC) -c $(SRCDIR)/jdie.c $(JEFF_CFLAGS) -o $(OBJDIR)/jdie.o
	$(CC) -c $(SRCDIR)/jerr.c $(JEFF_CFLAGS) -o $(OBJDIR)/jerr.o
	$(CC) -c $(SRCDIR)/joperators.c $(JEFF_CFLAGS) -o $(OBJDIR)/joperators.o
	$(CC) -c $(SRCDIR)/jstring.c $(JEFF_CFLAGS) -o $(OBJDIR)/jstring.o
	$(CC) $(OBJDIR)/jdie.o $(JEFF_LDFLAGS) -shared -o $(LIBDIR)/libjdie.so
	$(CC) $(OBJDIR)/jerr.o $(JEFF_LDFLAGS) -shared -o $(LIBDIR)/libjerr.so
	$(CC) $(OBJDIR)/joperators.o $(JEFF_LDFLAGS) -shared -o $(LIBDIR)/libjoperators.so
	$(CC) $(OBJDIR)/jstring.o $(JEFF_LDFLAGS) -shared -o $(LIBDIR)/libjstring.so

strip/bin: $(BINDIR)
	strip $(BINDIR)/*
strip/libs: $(LIBDIR)
	strip $(LIBDIR)/*

install_libs/fast: libs
	install -m 755 $(LIBDIR)/libjdie.so ~/.local/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so ~/.local/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so ~/.local/lib/libjoperators.so
	install -m 755 $(LIBDIR)/libjstring.so ~/.local/lib/libjstring.so
install_libs/stripped: libs
	install -m 755 $(LIBDIR)/libjdie.so ~/.local/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so ~/.local/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so ~/.local/lib/libjoperators.so
	install -m 755 $(LIBDIR)/libjstring.so ~/.local/lib/libjstring.so
	strip ~/.local/lib/libj{die,err,operators,string}.so
install_global_libs/fast: libs
	install -m 755 $(LIBDIR)/libjdie.so /usr/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so /usr/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so /usr/lib/libjoperators.so
	install -m 755 $(LIBDIR)/libjstring.so /usr/lib/libjstring.so
install_global_libs/stripped: libs
	install -m 755 $(LIBDIR)/libjdie.so /usr/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so /usr/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so /usr/lib/libjoperators.so
	install -m 755 $(LIBDIR)/libjstring.so /usr/lib/libjstring.so
	strip /usr/lib/libj{die,err,operators,string}.so

cointoss: $(SRCDIR)/cointoss.c libs $(BINDIR) $(JEFF_INCDIR)/cointoss.h $(JEFF_H)
	$(CC) -c $(SRCDIR)/cointoss.c $(CFLAGS) -o $(OBJDIR)/$@.o
	$(CC) $(OBJDIR)/cointoss.o $(CFLAGS) $(LDFLAGS) -o $(BINDIR)/$@

misc: $(SRCDIR)/misc.c libs $(BINDIR) $(JEFF_INCDIR)/jmisc.h $(JEFF_H)
	$(CC) -c $(SRCDIR)/misc.c $(CFLAGS) -o $(OBJDIR)/$@.o
	$(CC) $(OBJDIR)/misc.o $(CFLAGS) $(LDFLAGS) -o $(BINDIR)/$@

gl_1: $(SRCDIR)/jeff_gl_1.c libs  $(BINDIR) $(GL_H)
	$(CC) -c $(SRCDIR)/jeff_gl_1.c $(GL_CFLAGS) -o $(OBJDIR)/jeff_$@.o
	$(CC) $(OBJDIR)/jeff_gl_1.o $(GL_CFLAGS) $(LDFLAGS) -o $(BINDIR)/jeff_$@

gl_2: $(SRCDIR)/jeff_gl_2.c libs $(BINDIR) $(GL_H)
	$(CC) -c $(SRCDIR)/jeff_gl_2.c $(GL_CFLAGS) -o $(OBJDIR)/jeff_$@.o
	$(CC) $(OBJDIR)/jeff_gl_2.o $(GL_CFLAGS) $(LDFLAGS) -o $(BINDIR)/jeff_$@

gl_3: $(SRCDIR)/jeff_gl_3.cpp libs $(BINDIR) $(GL_H)
	$(CXX) -c $(SRCDIR)/jeff_gl_3.cpp $(GL_CFLAGS) $(CXXFLAGS) -o $(OBJDIR)/jeff_$@.o
	$(CXX) $(OBJDIR)/jeff_gl_3.o $(GL_CFLAGS) -o $(BINDIR)/jeff_$@

gtk_1: $(SRCDIR)/jeff_gtk_1.c libs $(BINDIR) $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_1.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_$@.o
	$(CC) $(OBJDIR)/jeff_gtk_1.o $(GTK_CFLAGS) $(LDFLAGS) -o $(BINDIR)/jeff_$@

gtk_2: $(SRCDIR)/jeff_gtk_2.c libs $(BINDIR) $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_2.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_$@.o
	$(CC) $(OBJDIR)/jeff_gtk_2.o $(GTK_CFLAGS) $(LDFLAGS) -o $(BINDIR)/jeff_$@

gtk_3: $(SRCDIR)/jeff_gtk_3.c libs $(BINDIR) $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_3.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_$@.o
	$(CC) $(OBJDIR)/jeff_gtk_3.o $(GTK_CFLAGS) $(LDFLAGS) -o $(BINDIR)/jeff_$@

gtk_4: $(SRCDIR)/jeff_gtk_4.c libs $(BINDIR) $(GTK_H) assets/builder.ui
	$(CC) -c $(SRCDIR)/jeff_gtk_4.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_$@.o
	$(CC) $(OBJDIR)/jeff_gtk_4.o $(GTK_CFLAGS) $(LDFLAGS) -o $(BINDIR)/jeff_$@

gtk_5: $(SRCDIR)/jeff_gtk_5.c libs $(BINDIR) $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_5.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_$@.o
	$(CC) $(OBJDIR)/jeff_gtk_5.o $(GTK_CFLAGS) $(LDFLAGS) -o $(BINDIR)/jeff_$@

sdl_1: $(SRCDIR)/jeff_sdl_1.c libs $(BINDIR) $(SDL_H) assets/face.png
	$(CC) -c $(SRCDIR)/jeff_sdl_1.c $(SDL_CFLAGS) -o $(OBJDIR)/jeff_$@.o
	$(CC) $(OBJDIR)/jeff_sdl_1.o $(SDL_CFLAGS) $(LDFLAGS) -o $(BINDIR)/jeff_$@

lua_1: $(SRCDIR)/jeff_lua_1.c libs $(BINDIR) $(LUA_H)
	$(CC) -c $(SRCDIR)/jeff_lua_1.c $(LUA_CFLAGS) -o $(OBJDIR)/jeff_$@.o
	$(CC) $(OBJDIR)/jeff_lua_1.o $(LUA_CFLAGS) $(LDFLAGS) -o $(BINDIR)/jeff_$@

ncurses_1: $(SRCDIR)/jeff_ncurses_1.c libs $(BINDIR) $(NCURSES_H)
	$(CC) -c $(SRCDIR)/jeff_ncurses_1.c $(NCURSES_CFLAGS) -o $(OBJDIR)/jeff_$@.o
	$(CC) $(OBJDIR)/jeff_ncurses_1.o $(NCURSES_CFLAGS) $(LDFLAGS) -o $(BINDIR)/jeff_$@

clean:
	rm -rf *.o $(BINDIR)/*.o $(OBJDIR)/* $(LIBDIR)/*.o $(SRCDIR)/*.o
distclean: clean
	rm -rf $(BINDIR)/* *.so *.a $(LIBDIR)/* build

.PHONY: $(ACTIONS) distclean clean all libs \
	strip/bin strip/libs \
	install_libs/fast install_libs/stripped \
	install_global_libs/fast install_global_libs/stripped
