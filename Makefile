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

libs: $(JEFF_LIBS)

$(LIBDIR)/libjdie.so: $(OBJDIR)/jdie.o $(JEFF_H)
	$(CC) $(OBJDIR)/jdie.o -o $@ $(JEFF_LDFLAGS) -shared
$(LIBDIR)/libjerr.so: $(OBJDIR)/jerr.o $(JEFF_H)
	$(CC) $(OBJDIR)/jerr.o -o $@ $(JEFF_LDFLAGS) -shared
$(LIBDIR)/libjoperators.so: $(OBJDIR)/joperators.o $(JEFF_H)
	$(CC) $(OBJDIR)/joperators.o -o $@ $(JEFF_LDFLAGS) -shared
$(LIBDIR)/libjstring.so: $(OBJDIR)/jstring.o $(JEFF_H)
	$(CC) $(OBJDIR)/jstring.o -o $@ $(JEFF_LDFLAGS) -shared
$(OBJDIR)/jdie.o: $(SRCDIR)/jdie.c $(JEFF_H)
	$(CC) -c $(SRCDIR)/jdie.c -o $@ $(JEFF_CFLAGS)
$(OBJDIR)/jerr.o: $(SRCDIR)/jerr.c $(JEFF_H)
	$(CC) -c $(SRCDIR)/jerr.c -o $@ $(JEFF_CFLAGS)
$(OBJDIR)/joperators.o: $(SRCDIR)/joperators.c $(JEFF_H)
	$(CC) -c $(SRCDIR)/joperators.c -o $@ $(JEFF_CFLAGS)
$(OBJDIR)/jstring.o: $(SRCDIR)/jstring.c $(JEFF_H)
	$(CC) -c $(SRCDIR)/jstring.c -o $@ $(JEFF_CFLAGS)

strip/bin: $(LIBDIR)
	strip $(BINDIR)/*
strip/libs: $(LIBDIR)
	strip $(LIBDIR)/*

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

cointoss: $(OBJDIR)/cointoss.o libs $(BINDIR) $(INCDIR)/jeff/cointoss.h $(JEFF_H)
	$(CC) $(OBJDIR)/cointoss.o -o $(BINDIR)/$@ $(CFLAGS) $(LDFLAGS)
misc: $(OBJDIR)/misc.o libs $(BINDIR) $(JEFF_H)
	$(CC) $(OBJDIR)/misc.o -o $(BINDIR)/$@ $(CFLAGS) $(LDFLAGS)
gl_1: $(OBJDIR)/jeff_gl_1.o libs $(BINDIR) $(GL_H)
	$(CC) $(OBJDIR)/jeff_gl_1.o -o $(BINDIR)/jeff_$@ $(GL_CFLAGS) $(LDFLAGS)
gl_2: $(OBJDIR)/jeff_gl_2.o libs $(BINDIR) $(GL_H)
	$(CC) $(OBJDIR)/jeff_gl_2.o -o $(BINDIR)/jeff_$@ $(GL_CFLAGS) $(LDFLAGS)
gl_3: $(OBJDIR)/jeff_gl_3.o libs $(BINDIR) $(GL_H)
	$(CXX) $(OBJDIR)/jeff_gl_3.o -o $(BINDIR)/jeff_$@ $(GL_CFLAGS)
gtk_1: $(OBJDIR)/jeff_gtk_1.o libs $(BINDIR) $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_1.o -o $(BINDIR)/jeff_$@ $(GTK_CFLAGS) $(LDFLAGS)
gtk_2: $(OBJDIR)/jeff_gtk_2.o libs $(BINDIR) $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_2.o -o $(BINDIR)/jeff_$@ $(GTK_CFLAGS) $(LDFLAGS)
gtk_3: $(OBJDIR)/jeff_gtk_3.o libs $(BINDIR) $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_3.o -o $(BINDIR)/jeff_$@ $(GTK_CFLAGS) $(LDFLAGS)
gtk_4: $(OBJDIR)/jeff_gtk_4.o libs $(BINDIR) $(GTK_H) $(SRCDIR)/builder.ui
	$(CC) $(OBJDIR)/jeff_gtk_4.o -o $(BINDIR)/jeff_$@ $(GTK_CFLAGS) $(LDFLAGS)
gtk_5: $(OBJDIR)/jeff_gtk_5.o libs $(BINDIR) $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_5.o -o $(BINDIR)/jeff_$@ $(GTK_CFLAGS) $(LDFLAGS)
sdl_1: $(OBJDIR)/jeff_sdl_1.o libs $(BINDIR) $(SDL_H) $(SRCDIR)/face.png
	$(CC) $(OBJDIR)/jeff_sdl_1.o -o $(BINDIR)/jeff_$@ $(SDL_CFLAGS) $(LDFLAGS)
lua_1: $(OBJDIR)/jeff_lua_1.o libs $(BINDIR) $(LUA_H)
	$(CC) $(OBJDIR)/jeff_lua_1.o -o $(BINDIR)/jeff_$@ $(LUA_CFLAGS) $(LDFLAGS)
ncurses_1: $(OBJDIR)/jeff_ncurses_1.o libs $(BINDIR) $(NCURSES_H) $(SRCDIR)/face.png
	$(CC) $(OBJDIR)/jeff_ncurses_1.o -o $(BINDIR)/jeff_$@ $(NCURSES_CFLAGS) $(LDFLAGS)

$(OBJDIR)/jeff_lua_1.o: $(SRCDIR)/jeff_lua_1.c $(LUA_H)
	$(CC) -c $(SRCDIR)/jeff_lua_1.c -o $@ $(LUA_CFLAGS)
$(OBJDIR)/jeff_gl_1.o: $(SRCDIR)/jeff_gl_1.c $(GL_H)
	$(CC) -c $(SRCDIR)/jeff_gl_1.c -o $@ $(GL_CFLAGS)
$(OBJDIR)/jeff_gl_2.o: $(SRCDIR)/jeff_gl_2.c $(GL_H)
	$(CC) -c $(SRCDIR)/jeff_gl_2.c -o $@ $(GL_CFLAGS)
$(OBJDIR)/jeff_gl_3.o: $(SRCDIR)/jeff_gl_3.cpp $(GL_H)
	$(CXX) -c $(SRCDIR)/jeff_gl_3.cpp -o $@ $(GL_CFLAGS) $(CXXFLAGS)
$(OBJDIR)/jeff_gtk_1.o: $(SRCDIR)/jeff_gtk_1.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_1.c -o $@ $(GTK_CFLAGS)
$(OBJDIR)/jeff_gtk_2.o: $(SRCDIR)/jeff_gtk_2.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_2.c -o $@ $(GTK_CFLAGS)
$(OBJDIR)/jeff_gtk_3.o: $(SRCDIR)/jeff_gtk_3.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_3.c -o $@ $(GTK_CFLAGS)
$(OBJDIR)/jeff_gtk_4.o: $(SRCDIR)/jeff_gtk_4.c $(GTK_H) $(SRCDIR)/builder.ui
	$(CC) -c $(SRCDIR)/jeff_gtk_4.c -o $@ $(GTK_CFLAGS)
$(OBJDIR)/jeff_gtk_5.o: $(SRCDIR)/jeff_gtk_5.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_5.c -o $@ $(GTK_CFLAGS)
$(OBJDIR)/jeff_sdl_1.o: $(SRCDIR)/jeff_sdl_1.c $(SDL_H) $(SRCDIR)/face.png
	$(CC) -c $(SRCDIR)/jeff_sdl_1.c -o $@ $(SDL_CFLAGS)
$(OBJDIR)/jeff_ncurses_1.o: $(SRCDIR)/jeff_ncurses_1.c $(NCURSES_H) $(SRCDIR)/face.png
	$(CC) -c $(SRCDIR)/jeff_ncurses_1.c -o $@ $(NCURSES_CFLAGS)

$(OBJDIR)/cointoss.o: $(SRCDIR)/cointoss.c $(INCDIR)/jeff/cointoss.h $(JEFF_H)
	$(CC) -c $(SRCDIR)/cointoss.c -o $@ $(CFLAGS)

$(OBJDIR)/misc.o: $(SRCDIR)/misc.c $(JEFF_H)
	$(CC) -c $(SRCDIR)/misc.c -o $@ $(CFLAGS)

clean:
	rm -f *.o $(BINDIR)/*.o obj/* lib/*.o src/*.o
distclean: clean
	rm -f $(BINDIR)/* *.so $(LIBDIR)/*

.PHONY: $(ACTIONS) distclean clean all libs \
	strip/bin strip/libs \
	install_libs/fast install_libs/stripped \
	install_global_libs/fast install_global_libs/stripped
