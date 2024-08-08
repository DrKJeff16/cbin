SHELL = /bin/bash

include config.mk

CC := gcc
CXX := g++

all: $(ACTIONS)

libs: $(JEFF_LIBS)

install_libs/fast:
	install -m 755 $(LIBDIR)/libjdie.so ~/.local/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so ~/.local/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so ~/.local/lib/libjoperators.so
install_libs/stripped:
	install -m 755 $(LIBDIR)/libjdie.so ~/.local/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so ~/.local/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so ~/.local/lib/libjoperators.so
	strip ~/.local/lib/libj{die,err,operators}.so
install_global_libs/fast:
	install -m 755 $(LIBDIR)/libjdie.so /usr/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so /usr/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so /usr/lib/libjoperators.so
install_global_libs/stripped:
	install -m 755 $(LIBDIR)/libjdie.so /usr/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so /usr/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so /usr/lib/libjoperators.so
	strip /usr/lib/libj{die,err,operators}.so

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

$(BINDIR)/jeff_lua_1: $(BINDIR) $(OBJDIR)/jeff_lua_1.o libs $(LUA_H)
	$(CC) $(OBJDIR)/jeff_lua_1.o -o $@ $(LUA_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_lua_1.o: $(SRCDIR)/jeff_lua_1.c $(LUA_H)
	$(CC) -c $(SRCDIR)/jeff_lua_1.c -o $@ $(LUA_CFLAGS)

$(BINDIR)/jeff_gl_1: $(BINDIR) $(OBJDIR)/jeff_gl_1.o libs $(GL_H)
	$(CC) $(OBJDIR)/jeff_gl_1.o -o $@ $(GL_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_gl_1.o: $(SRCDIR)/jeff_gl_1.c $(GL_H)
	$(CC) -c $(SRCDIR)/jeff_gl_1.c -o $@ $(GL_CFLAGS)
$(BINDIR)/jeff_gl_2: $(BINDIR) $(OBJDIR)/jeff_gl_2.o libs $(GL_H)
	$(CC) $(OBJDIR)/jeff_gl_2.o -o $@ $(GL_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_gl_2.o: $(SRCDIR)/jeff_gl_2.c $(GL_H)
	$(CC) -c $(SRCDIR)/jeff_gl_2.c -o $@ $(GL_CFLAGS)
$(BINDIR)/jeff_gl_3: $(BINDIR) $(OBJDIR)/jeff_gl_3.o $(GL_H)
	$(CXX) $(OBJDIR)/jeff_gl_3.o -o $@ $(GL_CFLAGS)
$(OBJDIR)/jeff_gl_3.o: $(SRCDIR)/jeff_gl_3.cpp $(GL_H)
	$(CXX) -c $(SRCDIR)/jeff_gl_3.cpp -o $@ $(GL_CFLAGS) $(CXXFLAGS)

$(BINDIR)/jeff_gtk_1: $(BINDIR) $(OBJDIR)/jeff_gtk_1.o libs $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_1.o -o $@ $(GTK_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_gtk_1.o: $(SRCDIR)/jeff_gtk_1.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_1.c -o $@ $(GTK_CFLAGS)
$(BINDIR)/jeff_gtk_2: $(BINDIR) $(OBJDIR)/jeff_gtk_2.o libs $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_2.o -o $@ $(GTK_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_gtk_2.o: $(SRCDIR)/jeff_gtk_2.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_2.c -o $@ $(GTK_CFLAGS)
$(BINDIR)/jeff_gtk_3: $(BINDIR) $(OBJDIR)/jeff_gtk_3.o libs $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_3.o -o $@ $(GTK_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_gtk_3.o: $(SRCDIR)/jeff_gtk_3.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_3.c -o $@ $(GTK_CFLAGS)
$(BINDIR)/jeff_gtk_4: $(BINDIR) $(OBJDIR)/jeff_gtk_4.o libs $(GTK_H) $(SRCDIR)/builder.ui
	$(CC) $(OBJDIR)/jeff_gtk_4.o -o $@ $(GTK_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_gtk_4.o: $(SRCDIR)/jeff_gtk_4.c $(GTK_H) $(SRCDIR)/builder.ui
	$(CC) -c $(SRCDIR)/jeff_gtk_4.c -o $@ $(GTK_CFLAGS)
$(BINDIR)/jeff_gtk_5: $(BINDIR) $(OBJDIR)/jeff_gtk_5.o libs $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_5.o -o $@ $(GTK_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_gtk_5.o: $(SRCDIR)/jeff_gtk_5.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_5.c -o $@ $(GTK_CFLAGS)

$(BINDIR)/jeff_sdl_1: $(BINDIR) $(OBJDIR)/jeff_sdl_1.o libs $(SDL_H) $(SRCDIR)/face.png
	$(CC) $(OBJDIR)/jeff_sdl_1.o -o $@ $(SDL_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_sdl_1.o: $(SRCDIR)/jeff_sdl_1.c $(SDL_H) $(SRCDIR)/face.png
	$(CC) -c $(SRCDIR)/jeff_sdl_1.c -o $@ $(SDL_CFLAGS)

$(BINDIR)/jeff_ncurses_1: $(BINDIR) $(OBJDIR)/jeff_ncurses_1.o libs $(NCURSES_H) $(SRCDIR)/face.png
	$(CC) $(OBJDIR)/jeff_ncurses_1.o -o $@ $(NCURSES_CFLAGS) $(LDFLAGS)
$(OBJDIR)/jeff_ncurses_1.o: $(SRCDIR)/jeff_ncurses_1.c $(NCURSES_H) $(SRCDIR)/face.png
	$(CC) -c $(SRCDIR)/jeff_ncurses_1.c -o $@ $(NCURSES_CFLAGS)

$(BINDIR)/cointoss: $(BINDIR) $(OBJDIR)/cointoss.o $(INCDIR)/jeff/cointoss.h libs $(JEFF_H)
	$(CC) $(OBJDIR)/cointoss.o -o $@ $(CFLAGS) $(LDFLAGS)
$(OBJDIR)/cointoss.o: $(SRCDIR)/cointoss.c $(INCDIR)/jeff/cointoss.h $(JEFF_H)
	$(CC) -c $(SRCDIR)/cointoss.c -o $@ $(CFLAGS)

$(BINDIR)/misc: $(BINDIR) $(OBJDIR)/misc.o libs $(JEFF_H)
	$(CC) $(OBJDIR)/misc.o -o $@ $(CFLAGS) $(LDFLAGS)
$(OBJDIR)/misc.o: $(SRCDIR)/misc.c $(JEFF_H)
	$(CC) -c $(SRCDIR)/misc.c -o $@ $(CFLAGS)

$(LIBDIR)/libjdie.so: $(OBJDIR)/jdie.o $(JEFF_H)
	$(CC) -shared $(OBJDIR)/jdie.o -o $@ $(JEFF_LDFLAGS)
$(LIBDIR)/libjerr.so: $(OBJDIR)/jerr.o $(JEFF_H)
	$(CC) -shared $(OBJDIR)/jerr.o -o $@ $(JEFF_LDFLAGS)
$(LIBDIR)/libjoperators.so: $(OBJDIR)/joperators.o $(JEFF_H)
	$(CC) -shared $(OBJDIR)/joperators.o -o $@ $(JEFF_LDFLAGS)
$(OBJDIR)/jdie.o: $(SRCDIR)/jdie.c $(JEFF_H)
	$(CC) -c $(SRCDIR)/jdie.c -o $@ $(JEFF_CFLAGS)
$(OBJDIR)/jerr.o: $(SRCDIR)/jerr.c $(JEFF_H)
	$(CC) -c $(SRCDIR)/jerr.c -o $@ $(JEFF_CFLAGS)
$(OBJDIR)/joperators.o: $(SRCDIR)/joperators.c $(JEFF_H)
	$(CC) -c $(SRCDIR)/joperators.c -o $@ $(JEFF_CFLAGS)

clean:
	rm -f *.o $(BINDIR)/*.o obj/* lib/*.o src/*.o
distclean: clean
	rm -f $(BINDIR)/* *.so $(LIBDIR)/*

.PHONY: $(ACTIONS) distclean clean all libs \
	install_libs/fast install_libs/stripped \
	install_global_libs/fast install_global_libs/stripped
