include config.mk

SHELL = /bin/bash

all: dirs libs $(ACTIONS)

dirs: $(JEFF_INCDIR) $(LIBDIR) $(OBJDIR) $(BINDIR)

$(INCDIR):
	mkdir -p $(INCDIR)
	mkdir -p $(JEFF_INCDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)


$(OBJDIR)/jdie.o: $(JEFF_H) $(SRCDIR)/jdie.c
	$(CC) -c $(SRCDIR)/jdie.c $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jerr.o: $(JEFF_H) $(SRCDIR)/jerr.c
	$(CC) -c $(SRCDIR)/jerr.c $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jrandom.o: $(JEFF_H) $(SRCDIR)/jrandom.c
	$(CC) -c $(SRCDIR)/jrandom.c $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jstring.o: $(JEFF_H) $(SRCDIR)/jstring.c
	$(CC) -c $(SRCDIR)/jstring.c $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jinput.o: $(JEFF_H) $(SRCDIR)/jinput.c
	$(CC) -c $(SRCDIR)/jinput.c $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jlog.o: $(JEFF_H) $(SRCDIR)/jlog.c
	$(CC) -c $(SRCDIR)/jlog.c $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jautomata.o: $(JEFF_H) $(SRCDIR)/jautomata.c
	$(CC) -c $(SRCDIR)/jautomata.c $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jlua.o: $(JEFF_H) $(SRCDIR)/jlua.c
	$(CC) -c $(SRCDIR)/jlua.c $(JEFF_LUA_CFLAGS) -o $@


$(LIBDIR)/libjeff.so: $(JEFF_H) $(OBJDIR)/jstring.o $(OBJDIR)/jdie.o $(OBJDIR)/jerr.o $(OBJDIR)/jlog.o $(OBJDIR)/jrandom.o $(OBJDIR)/jinput.o
	$(CC) $(OBJDIR)/jdie.o $(OBJDIR)/jerr.o $(OBJDIR)/jstring.o $(OBJDIR)/jlog.o $(OBJDIR)/jrandom.o $(OBJDIR)/jinput.o $(JEFF_CFLAGS) -shared -o $@ $(JEFF_LDFLAGS)

$(LIBDIR)/libjautomata.so: $(JEFF_H) $(LIBDIR)/libjeff.so $(OBJDIR)/jautomata.o
	$(CC) $(OBJDIR)/jautomata.o $(JEFF_CFLAGS) -shared -o $@ -Llib -L/usr/lib/jeff -ljeff $(JEFF_LDFLAGS)

$(LIBDIR)/libjlua.so: $(JEFF_H) $(LIBDIR)/libjeff.so $(OBJDIR)/jlua.o
	$(CC) $(OBJDIR)/jlua.o $(JEFF_LUA_CFLAGS) -shared -o $@ $(JEFF_LUA_LDFLAGS)


$(OBJDIR)/cointoss.o: $(SRCDIR)/cointoss.c $(JEFF_INCDIR)/cointoss.h
	$(CC) -c $(SRCDIR)/cointoss.c $(CFLAGS) -o $@
$(BINDIR)/cointoss: $(OBJDIR)/cointoss.o $(JEFF_INCDIR)/cointoss.h
	$(CC) $(OBJDIR)/cointoss.o $(CFLAGS) -o $@ $(LDFLAGS)

$(OBJDIR)/jmisc.o: $(SRCDIR)/jmisc.c $(JEFF_INCDIR)/jmisc.h
	$(CC) -c $(SRCDIR)/jmisc.c $(CFLAGS) -o $@

$(BINDIR)/jmisc: $(OBJDIR)/jmisc.o $(JEFF_INCDIR)/jmisc.h
	$(CC) $(OBJDIR)/jmisc.o $(CFLAGS) -o $@ $(LDFLAGS)

$(OBJDIR)/jeff_gl_1.o: $(SRCDIR)/jeff_gl_1.c $(GL_H)
	$(CC) -c $(SRCDIR)/jeff_gl_1.c $(GL_CFLAGS) -o $@

$(BINDIR)/jeff_gl_1: $(OBJDIR)/jeff_gl_1.o $(GL_H)
	$(CC) $(OBJDIR)/jeff_gl_1.o $(GL_CFLAGS) -o $@ $(GL_LDFLAGS)

$(OBJDIR)/jeff_gtk_1.o: $(SRCDIR)/jeff_gtk_1.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_1.c $(GTK_CFLAGS) -o $@

$(BINDIR)/jeff_gtk_1: $(OBJDIR)/jeff_gtk_1.o $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_1.o $(GTK_CFLAGS) -o $@ $(GTK_LDFLAGS)

$(OBJDIR)/jeff_gtk_2.o: $(SRCDIR)/jeff_gtk_2.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_2.c $(GTK_CFLAGS) -o $@

$(BINDIR)/jeff_gtk_2: $(OBJDIR)/jeff_gtk_2.o $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_2.o $(GTK_CFLAGS) -o $@ $(GTK_LDFLAGS)

$(OBJDIR)/jeff_gtk_3.o: $(SRCDIR)/jeff_gtk_3.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_3.c $(GTK_CFLAGS) -o $@

$(BINDIR)/jeff_gtk_3: $(OBJDIR)/jeff_gtk_3.o $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_3.o $(GTK_CFLAGS) -o $@ $(GTK_LDFLAGS)

$(OBJDIR)/jeff_gtk_4.o: $(SRCDIR)/jeff_gtk_4.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_4.c $(GTK_CFLAGS) -o $@

$(BINDIR)/jeff_gtk_4: $(OBJDIR)/jeff_gtk_4.o $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_4.o $(GTK_CFLAGS) -o $@ $(GTK_LDFLAGS)

$(OBJDIR)/jeff_sdl_1.o: $(SRCDIR)/jeff_sdl_1.c $(SDL_H) $(ASSET_DIR)/face.png
	$(CC) -c $(SRCDIR)/jeff_sdl_1.c $(SDL_CFLAGS) -o $@

$(BINDIR)/jeff_sdl_1: $(OBJDIR)/jeff_sdl_1.o $(SDL_H) $(ASSET_DIR)/face.png
	$(CC) $(OBJDIR)/jeff_sdl_1.o $(SDL_CFLAGS) -o $@ $(SDL_LDFLAGS)

$(OBJDIR)/jeff_lua_1.o: $(SRCDIR)/jeff_lua_1.c $(LUA_H)
	$(CC) -c $(SRCDIR)/jeff_lua_1.c $(LUA_CFLAGS) -o $@

$(BINDIR)/jeff_lua_1: $(OBJDIR)/jeff_lua_1.o $(LUA_H)
	$(CC) $(OBJDIR)/jeff_lua_1.o $(LUA_CFLAGS) -o $@ $(LUA_LDFLAGS)

$(OBJDIR)/jeff_ncurses_1.o: $(SRCDIR)/jeff_ncurses_1.c $(NCURSES_H)
	$(CC) -c $(SRCDIR)/jeff_ncurses_1.c $(NCURSES_CFLAGS) -o $@

$(BINDIR)/jeff_ncurses_1: $(OBJDIR)/jeff_ncurses_1.o $(NCURSES_H)
	$(CC) $(OBJDIR)/jeff_ncurses_1.o $(NCURSES_CFLAGS) -o $@ $(NCURSES_LDFLAGS)

libs: dirs $(JEFF_LIBS)

cointoss: libs $(BINDIR)/cointoss
jmisc: libs $(BINDIR)/jmisc
gl_1: libs $(BINDIR)/jeff_gl_1
gtk_1: libs $(BINDIR)/jeff_gtk_1
gtk_2: libs $(BINDIR)/jeff_gtk_2
gtk_3: libs $(BINDIR)/jeff_gtk_3
gtk_4: libs $(BINDIR)/jeff_gtk_4
lua_1: libs $(BINDIR)/jeff_lua_1
ncurses_1: libs $(BINDIR)/jeff_ncurses_1
sdl_1: libs $(BINDIR)/jeff_sdl_1

strip/bin:
	strip $(BINDIR)/*

strip/libs:
	strip $(LIBDIR)/*.so

install_bin:
	mkdir -p $(GLOBAL_PREFIX)/bin
	install -m 755 $(BINDIR)/cointoss $(GLOBAL_PREFIX)/bin/cointoss

install_bin/stripped: install_bin
	strip $(GLOBAL_PREFIX)/bin/cointoss

install_local_bin:
	mkdir -p $(HOME)/.bin/cbin
	install -m 755 $(BINDIR)/cointoss $(HOME)/.bin/cbin/cointoss

install_local_bin/stripped: install_local_bin
	strip $(HOME)/.bin/cbin/cointoss

install_local_headers:
	mkdir -p $(LOCAL_PREFIX)/include/jeff
	install -m 644 $(JEFF_INCDIR)/jeff.h $(LOCAL_PREFIX)/include/jeff/jeff.h
	install -m 644 $(JEFF_INCDIR)/jtypes.h $(LOCAL_PREFIX)/include/jeff/jtypes.h
	install -m 644 $(JEFF_INCDIR)/jmemory.h $(LOCAL_PREFIX)/include/jeff/jmemory.h
	install -m 644 $(JEFF_INCDIR)/jrandom.h $(LOCAL_PREFIX)/include/jeff/jrandom.h
	install -m 644 $(JEFF_INCDIR)/jstring.h $(LOCAL_PREFIX)/include/jeff/jstring.h
	install -m 644 $(JEFF_INCDIR)/jlua.h $(LOCAL_PREFIX)/include/jeff/jlua.h
	install -m 644 $(JEFF_INCDIR)/jinput.h $(LOCAL_PREFIX)/include/jeff/jinput.h
	install -m 644 $(JEFF_INCDIR)/jlog.h $(LOCAL_PREFIX)/include/jeff/jlog.h

install_headers:
	mkdir -p $(GLOBAL_PREFIX)/include/jeff
	install -m 644 $(JEFF_INCDIR)/jeff.h $(GLOBAL_PREFIX)/include/jeff/jeff.h
	install -m 644 $(JEFF_INCDIR)/jtypes.h $(GLOBAL_PREFIX)/include/jeff/jtypes.h
	install -m 644 $(JEFF_INCDIR)/jmemory.h $(GLOBAL_PREFIX)/include/jeff/jmemory.h
	install -m 644 $(JEFF_INCDIR)/jrandom.h $(GLOBAL_PREFIX)/include/jeff/jrandom.h
	install -m 644 $(JEFF_INCDIR)/jinput.h $(GLOBAL_PREFIX)/include/jeff/jinput.h
	install -m 644 $(JEFF_INCDIR)/jstring.h $(GLOBAL_PREFIX)/include/jeff/jstring.h
	install -m 644 $(JEFF_INCDIR)/jlua.h $(GLOBAL_PREFIX)/include/jeff/jlua.h
	install -m 644 $(JEFF_INCDIR)/jautomata.h $(GLOBAL_PREFIX)/include/jeff/jautomata.h
	install -m 644 $(JEFF_INCDIR)/jlog.h $(GLOBAL_PREFIX)/include/jeff/jlog.h

install_local_libs:
	mkdir -p $(LOCAL_PREFIX)/lib/jeff
	install -m 755 $(LIBDIR)/libjeff.so $(LOCAL_PREFIX)/lib/jeff/libjeff.so
	install -m 755 $(LIBDIR)/libjautomata.so $(LOCAL_PREFIX)/lib/jeff/libjautomata.so
	install -m 755 $(LIBDIR)/libjlua.so $(LOCAL_PREFIX)/lib/jeff/libjlua.so

install_libs:
	mkdir -p $(GLOBAL_PREFIX)/lib/jeff
	install -m 755 $(LIBDIR)/libjeff.so $(GLOBAL_PREFIX)/lib/jeff/libjeff.so
	install -m 755 $(LIBDIR)/libjautomata.so $(GLOBAL_PREFIX)/lib/jeff/libjautomata.so
	install -m 755 $(LIBDIR)/libjlua.so $(GLOBAL_PREFIX)/lib/jeff/libjlua.so

install_local_libs/stripped: install_local_libs
	strip $(LOCAL_PREFIX)/lib/jeff/libj{eff,automata,lua}.so

install_libs/stripped: install_libs
	strip $(GLOBAL_PREFIX)/lib/jeff/libj{eff,automata,lua}.so

clean:
	rm -rf $(OBJDIR)/*

distclean: clean
	rm -rf $(BINDIR)/* $(LIBDIR)/* build compile_commands.json *.log


.PHONY: all \
	clean \
	distclean \
	install_bin \
	install_bin/stripped \
	install_headers \
	install_libs \
	install_libs/stripped \
	install_local_bin \
	install_local_bin/stripped \
	install_local_headers \
	install_local_libs \
	install_local_libs/stripped \
	libs \
	strip/bin \
	strip/libs \
	$(JEFF_INCDIR) \
	$(ACTIONS)
