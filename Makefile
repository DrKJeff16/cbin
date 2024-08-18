SHELL = /bin/bash

include config.mk

CC := gcc
CXX := g++

all: $(ACTIONS)

$(INCDIR):
	mkdir -p $(INCDIR)

$(JEFF_INCDIR): $(INCDIR)
	mkdir -p $(JEFF_INCDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)


$(LIBDIR)/libjdie.so: $(LIBDIR) $(OBJDIR) $(JEFF_H) $(SRCDIR)/jdie.c
	$(CC) -c $(SRCDIR)/jdie.c $(JEFF_CFLAGS) -o $(OBJDIR)/jdie.o
	$(CC) $(OBJDIR)/jdie.o $(JEFF_LDFLAGS) -shared -o $(LIBDIR)/libjdie.so

$(LIBDIR)/libjerr.so: $(LIBDIR) $(OBJDIR) $(JEFF_H) $(SRCDIR)/jerr.c
	$(CC) -c $(SRCDIR)/jerr.c $(JEFF_CFLAGS) -o $(OBJDIR)/jerr.o
	$(CC) $(OBJDIR)/jerr.o $(JEFF_LDFLAGS) -shared -o $(LIBDIR)/libjerr.so

$(LIBDIR)/libjoperators.so: $(LIBDIR) $(OBJDIR) $(JEFF_H) $(SRCDIR)/joperators.c
	$(CC) -c $(SRCDIR)/joperators.c $(JEFF_CFLAGS) -o $(OBJDIR)/joperators.o
	$(CC) $(OBJDIR)/joperators.o $(JEFF_LDFLAGS) -shared -o $(LIBDIR)/libjoperators.so

$(LIBDIR)/libjstring.so: $(LIBDIR) $(OBJDIR) $(JEFF_H) $(SRCDIR)/jstring.c
	$(CC) -c $(SRCDIR)/jstring.c $(JEFF_CFLAGS) -o $(OBJDIR)/jstring.o
	$(CC) $(OBJDIR)/jstring.o $(JEFF_LDFLAGS) -shared -o $(LIBDIR)/libjstring.so

$(LIBDIR)/libjlog.so: $(LIBDIR) $(OBJDIR) $(JEFF_H) $(SRCDIR)/jlog.c
	$(CC) -c $(SRCDIR)/jlog.c $(JEFF_CFLAGS) -o $(OBJDIR)/jlog.o
	$(CC) $(OBJDIR)/jlog.o $(JEFF_LDFLAGS) -shared -o $(LIBDIR)/libjlog.so

$(LIBDIR)/libjlua.so: $(LIBDIR) $(OBJDIR) $(JEFF_H) $(SRCDIR)/jlua.c
	$(CC) -c $(SRCDIR)/jlua.c $(JEFF_LUA_CFLAGS) -o $(OBJDIR)/jlua.o
	$(CC) $(OBJDIR)/jlua.o $(JEFF_LUA_LDFLAGS) -shared -o $(LIBDIR)/libjlua.so


libs: $(JEFF_LIBS)


cointoss: $(BINDIR) $(BINDIR)/cointoss
misc: $(BINDIR) $(BINDIR)/misc
gl_1: $(BINDIR) $(BINDIR)/jeff_gl_1
gl_2: $(BINDIR) $(BINDIR)/jeff_gl_2
gtk_1: $(BINDIR) $(BINDIR)/jeff_gtk_1
gtk_2: $(BINDIR) $(BINDIR)/jeff_gtk_2
gtk_3: $(BINDIR) $(BINDIR)/jeff_gtk_3
gtk_4: $(BINDIR) $(BINDIR)/jeff_gtk_4
gtk_5: $(BINDIR) $(BINDIR)/jeff_gtk_5
lua_1: $(BINDIR) $(BINDIR)/jeff_lua_1
ncurses_1: $(BINDIR) $(BINDIR)/jeff_ncurses_1
sdl_1: $(BINDIR) $(BINDIR)/jeff_sdl_1


strip/bin: $(BINDIR)
	strip $(BINDIR)/*

strip/libs: $(LIBDIR)
	strip $(LIBDIR)/*


install_headers/local: $(JEFF_H)
	mkdir -p $(HOME)/.local/include/jeff
	install -m 644 $(JEFF_INCDIR)/jeff.h $(HOME)/.local/include/jeff/jeff.h
	install -m 644 $(JEFF_INCDIR)/jmemory.h $(HOME)/.local/include/jeff/jmemory.h
	install -m 644 $(JEFF_INCDIR)/jstring.h $(HOME)/.local/include/jeff/jstring.h
	install -m 644 $(JEFF_INCDIR)/jlua.h $(HOME)/.local/include/jeff/jlua.h
	install -m 644 $(JEFF_INCDIR)/jlog.h $(HOME)/.local/include/jeff/jlog.h
	chown -Rcv $(USER)\:$(USER) $(HOME)/.local/include

install_headers/global: $(JEFF_H)
	mkdir -p /usr/include/jeff
	install -m 644 $(JEFF_INCDIR)/jeff.h /usr/include/jeff/jeff.h
	install -m 644 $(JEFF_INCDIR)/jmemory.h /usr/include/jeff/jmemory.h
	install -m 644 $(JEFF_INCDIR)/jstring.h /usr/include/jeff/jstring.h
	install -m 644 $(JEFF_INCDIR)/jlua.h $(HOME)/.local/include/jeff/jlua.h
	install -m 644 $(JEFF_INCDIR)/jlog.h /usr/include/jeff/jlog.h


install_libs/local/fast:
	install -m 755 $(LIBDIR)/libjdie.so $(HOME)/.local/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so $(HOME)/.local/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so $(HOME)/.local/lib/libjoperators.so
	install -m 755 $(LIBDIR)/libjstring.so $(HOME)/.local/lib/libjstring.so
	install -m 755 $(LIBDIR)/libjlua.so $(HOME)/.local/lib/libjlua.so
	install -m 755 $(LIBDIR)/libjlog.so $(HOME)/.local/lib/libjlog.so

install_libs/fast:
	install -m 755 $(LIBDIR)/libjdie.so /usr/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so /usr/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so /usr/lib/libjoperators.so
	install -m 755 $(LIBDIR)/libjstring.so /usr/lib/libjstring.so
	install -m 755 $(LIBDIR)/libjlua.so /usr/lib/libjlua.so
	install -m 755 $(LIBDIR)/libjlog.so /usr/lib/libjlog.so

install_libs/local/stripped: install_libs/local/fast
	strip $(HOME)/.local/lib/libj{die,err,operators,string,lua,log}.so

install_libs/stripped: install_libs/fast
	strip /usr/lib/libj{die,err,operators,string,lua,log}.so


$(BINDIR)/cointoss: $(JEFF_LIBS) $(BINDIR) $(SRCDIR)/cointoss.c $(JEFF_INCDIR)/cointoss.h
	$(CC) -c $(SRCDIR)/cointoss.c $(CFLAGS) -o $(OBJDIR)/cointoss.o
	$(CC) $(OBJDIR)/cointoss.o $(CFLAGS) $(LDFLAGS) -o $@

$(BINDIR)/misc: $(JEFF_LIBS) $(SRCDIR)/misc.c $(BINDIR) $(JEFF_INCDIR)/jmisc.h
	$(CC) -c $(SRCDIR)/misc.c $(CFLAGS) -o $(OBJDIR)/misc.o
	$(CC) $(OBJDIR)/misc.o $(CFLAGS) $(LDFLAGS) -o $@

$(BINDIR)/jeff_gl_1: $(JEFF_LIBS) $(SRCDIR)/jeff_gl_1.c $(BINDIR) $(GL_H)
	$(CC) -c $(SRCDIR)/jeff_gl_1.c $(GL_CFLAGS) -o $(OBJDIR)/jeff_gl_1.o
	$(CC) $(OBJDIR)/jeff_gl_1.o $(GL_CFLAGS) $(GL_LDFLAGS) -o $@

$(BINDIR)/jeff_gl_2: $(JEFF_LIBS) $(SRCDIR)/jeff_gl_2.c $(BINDIR) $(GL_H)
	$(CC) -c $(SRCDIR)/jeff_gl_2.c $(GL_CFLAGS) -o $(OBJDIR)/jeff_gl_2.o
	$(CC) $(OBJDIR)/jeff_gl_2.o $(GL_CFLAGS) $(GL_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_1: $(JEFF_LIBS) $(SRCDIR)/jeff_gtk_1.c $(BINDIR) $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_1.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_1.o
	$(CC) $(OBJDIR)/jeff_gtk_1.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_2: $(JEFF_LIBS) $(SRCDIR)/jeff_gtk_2.c $(BINDIR) $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_2.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_2.o
	$(CC) $(OBJDIR)/jeff_gtk_2.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_3: $(JEFF_LIBS) $(SRCDIR)/jeff_gtk_3.c $(BINDIR) $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_3.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_3.o
	$(CC) $(OBJDIR)/jeff_gtk_3.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_4: $(JEFF_LIBS) $(SRCDIR)/jeff_gtk_4.c $(BINDIR) $(GTK_H) $(ASSET_DIR)/builder.ui
	$(CC) -c $(SRCDIR)/jeff_gtk_4.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_4.o
	$(CC) $(OBJDIR)/jeff_gtk_4.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_5: $(JEFF_LIBS) $(SRCDIR)/jeff_gtk_5.c $(BINDIR) $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_5.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_5.o
	$(CC) $(OBJDIR)/jeff_gtk_5.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_sdl_1: $(JEFF_LIBS) $(SRCDIR)/jeff_sdl_1.c $(BINDIR) $(SDL_H) $(ASSET_DIR)/face.png
	$(CC) -c $(SRCDIR)/jeff_sdl_1.c $(SDL_CFLAGS) -o $(OBJDIR)/jeff_sdl_1.o
	$(CC) $(OBJDIR)/jeff_sdl_1.o $(SDL_CFLAGS) $(SDL_LDFLAGS) -o $@

$(BINDIR)/jeff_lua_1: $(JEFF_LIBS) $(SRCDIR)/jeff_lua_1.c $(BINDIR) $(LUA_H)
	$(CC) -c $(SRCDIR)/jeff_lua_1.c $(LUA_CFLAGS) -o $(OBJDIR)/jeff_lua_1.o
	$(CC) $(OBJDIR)/jeff_lua_1.o $(LUA_CFLAGS) $(LUA_LDFLAGS) -o $@

$(BINDIR)/jeff_ncurses_1: $(JEFF_LIBS) $(SRCDIR)/jeff_ncurses_1.c $(BINDIR) $(NCURSES_H)
	$(CC) -c $(SRCDIR)/jeff_ncurses_1.c $(NCURSES_CFLAGS) -o $(OBJDIR)/jeff_ncurses_1.o
	$(CC) $(OBJDIR)/jeff_ncurses_1.o $(NCURSES_CFLAGS) $(NCURSES_LDFLAGS) -o $@


clean:
	rm -rf *.o $(OBJDIR)

distclean: clean
	rm -rf $(BINDIR) *.so *.a $(LIBDIR) build compile_commands.json


.PHONY: $(ACTIONS) distclean clean all libs \
	strip/bin strip/libs \
	install_libs/fast install_libs/stripped \
	install_libs/local/fast install_libs/local/stripped \
	install_headers/local install_headers/global
