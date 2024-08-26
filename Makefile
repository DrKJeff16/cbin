SHELL = /bin/bash

include config.mk

all: dirs libs $(ACTIONS)

dirs: $(JEFF_INCDIR) \
	$(LIBDIR) \
	$(OBJDIR) \
	$(BINDIR)

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


$(OBJDIR)/joperators.o: $(JEFF_H) $(SRCDIR)/joperators.c
	$(CC) -c $(SRCDIR)/joperators.c $(JEFF_CFLAGS) -o $(OBJDIR)/joperators.o

$(OBJDIR)/jdie.o: $(JEFF_H) $(SRCDIR)/jdie.c
	$(CC) -c $(SRCDIR)/jdie.c $(JEFF_CFLAGS) -o $(OBJDIR)/jdie.o

$(OBJDIR)/jerr.o: $(JEFF_H) $(SRCDIR)/jerr.c
	$(CC) -c $(SRCDIR)/jerr.c $(JEFF_CFLAGS) -o $(OBJDIR)/jerr.o

$(OBJDIR)/jstring.o: $(JEFF_H) $(SRCDIR)/jstring.c
	$(CC) -c $(SRCDIR)/jstring.c $(JEFF_CFLAGS) -o $(OBJDIR)/jstring.o

$(OBJDIR)/jlog.o: $(JEFF_H) $(SRCDIR)/jlog.c
	$(CC) -c $(SRCDIR)/jlog.c $(JEFF_CFLAGS) -o $(OBJDIR)/jlog.o

$(OBJDIR)/jlua.o: $(JEFF_H) $(SRCDIR)/jlua.c
	$(CC) -c $(SRCDIR)/jlua.c $(JEFF_LUA_CFLAGS) -o $(OBJDIR)/jlua.o


$(LIBDIR)/libjeff.so: $(JEFF_H) $(OBJDIR)/joperators.o $(OBJDIR)/jstring.o $(OBJDIR)/jdie.o $(OBJDIR)/jerr.o $(OBJDIR)/jlog.o
	$(CC) $(OBJDIR)/joperators.o $(OBJDIR)/jstring.o $(OBJDIR)/jdie.o $(OBJDIR)/jerr.o $(OBJDIR)/jlog.o $(JEFF_CFLAGS) -shared -o $(LIBDIR)/libjeff.so $(JEFF_LDFLAGS)

$(LIBDIR)/libjlua.so: $(JEFF_H) $(OBJDIR)/jlua.o $(OBJDIR)/jerr.o $(OBJDIR)/jstring.o $(OBJDIR)/jdie.o $(OBJDIR)/joperators.o
	$(CC) $(OBJDIR)/jlua.o $(OBJDIR)/jerr.o $(OBJDIR)/jstring.o $(OBJDIR)/jdie.o $(OBJDIR)/joperators.o $(JEFF_LUA_CFLAGS) -shared -o $(LIBDIR)/libjlua.so $(JEFF_LUA_LDFLAGS)


libs: dirs $(JEFF_LIBS)


cointoss: dirs $(BINDIR)/cointoss
jmisc: dirs $(BINDIR)/jmisc
gl_1: dirs $(BINDIR)/jeff_gl_1
gtk_1: dirs $(BINDIR)/jeff_gtk_1
gtk_2: dirs $(BINDIR)/jeff_gtk_2
gtk_3: dirs $(BINDIR)/jeff_gtk_3
gtk_4: dirs $(BINDIR)/jeff_gtk_4
gtk_5: dirs $(BINDIR)/jeff_gtk_5
lua_1: dirs $(BINDIR)/jeff_lua_1
ncurses_1: dirs $(BINDIR)/jeff_ncurses_1
sdl_1: dirs $(BINDIR)/jeff_sdl_1


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
	chown -Rc $(USER)\:$(USER) $(HOME)/.local/include

install_headers/global: $(JEFF_H)
	mkdir -p /usr/include/jeff
	install -m 644 $(JEFF_INCDIR)/jeff.h /usr/include/jeff/jeff.h
	install -m 644 $(JEFF_INCDIR)/jmemory.h /usr/include/jeff/jmemory.h
	install -m 644 $(JEFF_INCDIR)/jstring.h /usr/include/jeff/jstring.h
	install -m 644 $(JEFF_INCDIR)/jlua.h /usr/include/jeff/jlua.h
	install -m 644 $(JEFF_INCDIR)/jlog.h /usr/include/jeff/jlog.h


install_libs/local/fast:
	mkdir -p $(HOME)/.local/lib/jeff
	install -m 755 $(LIBDIR)/libjeff.so $(HOME)/.local/lib/jeff/libjeff.so
	install -m 755 $(LIBDIR)/libjlua.so $(HOME)/.local/lib/jeff/libjlua.so
	chown -R $(USER)\:$(USER) $(HOME)/.local/lib

install_libs/fast:
	mkdir -p /usr/lib/jeff
	install -m 755 $(LIBDIR)/libjeff.so /usr/lib/jeff/libjeff.so
	install -m 755 $(LIBDIR)/libjlua.so /usr/lib/jeff/libjlua.so

install_libs/local/stripped: install_libs/local/fast
	strip $(HOME)/.local/lib/libj{eff,lua}.so

install_libs/stripped: install_libs/fast
	strip /usr/lib/libj{eff,lua}.so


$(BINDIR)/cointoss: $(SRCDIR)/cointoss.c $(JEFF_INCDIR)/cointoss.h
	$(CC) -c $(SRCDIR)/cointoss.c $(CFLAGS) -o $(OBJDIR)/cointoss.o
	$(CC) $(OBJDIR)/cointoss.o $(CFLAGS) $(LDFLAGS) -o $@

$(BINDIR)/jmisc: $(SRCDIR)/jmisc.c $(JEFF_INCDIR)/jmisc.h
	$(CC) -c $(SRCDIR)/jmisc.c $(CFLAGS) -o $(OBJDIR)/jmisc.o
	$(CC) $(OBJDIR)/jmisc.o $(CFLAGS) $(LDFLAGS) -o $@

$(BINDIR)/jeff_gl_1: $(SRCDIR)/jeff_gl_1.c $(GL_H)
	$(CC) -c $(SRCDIR)/jeff_gl_1.c $(GL_CFLAGS) -o $(OBJDIR)/jeff_gl_1.o
	$(CC) $(OBJDIR)/jeff_gl_1.o $(GL_CFLAGS) $(GL_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_1: $(SRCDIR)/jeff_gtk_1.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_1.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_1.o
	$(CC) $(OBJDIR)/jeff_gtk_1.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_2: $(SRCDIR)/jeff_gtk_2.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_2.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_2.o
	$(CC) $(OBJDIR)/jeff_gtk_2.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_3: $(SRCDIR)/jeff_gtk_3.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_3.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_3.o
	$(CC) $(OBJDIR)/jeff_gtk_3.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_4: $(SRCDIR)/jeff_gtk_4.c $(GTK_H) $(ASSET_DIR)/builder.ui
	$(CC) -c $(SRCDIR)/jeff_gtk_4.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_4.o
	$(CC) $(OBJDIR)/jeff_gtk_4.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_5: $(SRCDIR)/jeff_gtk_5.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_5.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_5.o
	$(CC) $(OBJDIR)/jeff_gtk_5.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_sdl_1: $(SRCDIR)/jeff_sdl_1.c $(SDL_H) $(ASSET_DIR)/face.png
	$(CC) -c $(SRCDIR)/jeff_sdl_1.c $(SDL_CFLAGS) -o $(OBJDIR)/jeff_sdl_1.o
	$(CC) $(OBJDIR)/jeff_sdl_1.o $(SDL_CFLAGS) $(SDL_LDFLAGS) -o $@

$(BINDIR)/jeff_lua_1: $(SRCDIR)/jeff_lua_1.c $(LUA_H)
	$(CC) -c $(SRCDIR)/jeff_lua_1.c $(LUA_CFLAGS) -o $(OBJDIR)/jeff_lua_1.o
	$(CC) $(OBJDIR)/jeff_lua_1.o $(LUA_CFLAGS) $(LUA_LDFLAGS) -o $@

$(BINDIR)/jeff_ncurses_1: $(SRCDIR)/jeff_ncurses_1.c $(NCURSES_H)
	$(CC) -c $(SRCDIR)/jeff_ncurses_1.c $(NCURSES_CFLAGS) -o $(OBJDIR)/jeff_ncurses_1.o
	$(CC) $(OBJDIR)/jeff_ncurses_1.o $(NCURSES_CFLAGS) $(NCURSES_LDFLAGS) -o $@


clean:
	rm -rf $(OBJDIR)/*

distclean: clean
	rm -rf $(BINDIR)/* $(LIBDIR)/* build compile_commands.json *.log


.PHONY: all \
	clean \
	distclean \
	install_headers/local install_headers/global \
	install_libs/fast \
	install_libs/local/fast \
	install_libs/local/stripped \
	install_libs/stripped \
	libs \
	strip/bin \
	strip/libs \
	$(ACTIONS)
