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


libs: dirs $(JEFF_LIBS)


cointoss: libs dirs $(BINDIR)/cointoss
jmisc: libs dirs $(BINDIR)/jmisc
gl_1: libs dirs $(BINDIR)/jeff_gl_1
gtk_1: libs dirs $(BINDIR)/jeff_gtk_1
gtk_2: libs dirs $(BINDIR)/jeff_gtk_2
gtk_3: libs dirs $(BINDIR)/jeff_gtk_3
gtk_4: libs dirs $(BINDIR)/jeff_gtk_4
gtk_5: libs dirs $(BINDIR)/jeff_gtk_5
lua_1: libs dirs $(BINDIR)/jeff_lua_1
ncurses_1: libs dirs $(BINDIR)/jeff_ncurses_1
sdl_1: libs dirs $(BINDIR)/jeff_sdl_1


strip/bin:
	strip $(BINDIR)/*

strip/libs:
	strip $(LIBDIR)/*.so


install_headers/local: $(JEFF_H)
	mkdir -p $(HOME)/.local/include/jeff
	install -m 644 $(JEFF_INCDIR)/jeff.h $(HOME)/.local/include/jeff/jeff.h
	install -m 644 $(JEFF_INCDIR)/jmemory.h $(HOME)/.local/include/jeff/jmemory.h
	install -m 644 $(JEFF_INCDIR)/jrandom.h $(HOME)/.local/include/jeff/jrandom.h
	install -m 644 $(JEFF_INCDIR)/jstring.h $(HOME)/.local/include/jeff/jstring.h
	install -m 644 $(JEFF_INCDIR)/jlua.h $(HOME)/.local/include/jeff/jlua.h
	install -m 644 $(JEFF_INCDIR)/jinput.h $(HOME)/.local/include/jeff/jinput.h
	install -m 644 $(JEFF_INCDIR)/jlog.h $(HOME)/.local/include/jeff/jlog.h

install_headers/global: $(JEFF_H)
	mkdir -p /usr/include/jeff
	install -m 644 $(JEFF_INCDIR)/jeff.h /usr/include/jeff/jeff.h
	install -m 644 $(JEFF_INCDIR)/jmemory.h /usr/include/jeff/jmemory.h
	install -m 644 $(JEFF_INCDIR)/jrandom.h /usr/include/jeff/jrandom.h
	install -m 644 $(JEFF_INCDIR)/jinput.h /usr/include/jeff/jinput.h
	install -m 644 $(JEFF_INCDIR)/jstring.h /usr/include/jeff/jstring.h
	install -m 644 $(JEFF_INCDIR)/jlua.h /usr/include/jeff/jlua.h
	install -m 644 $(JEFF_INCDIR)/jautomata.h /usr/include/jeff/jautomata.h
	install -m 644 $(JEFF_INCDIR)/jlog.h /usr/include/jeff/jlog.h


install_libs/local/fast:
	mkdir -p $(HOME)/.local/lib/jeff
	install -m 755 $(LIBDIR)/libjeff.so $(HOME)/.local/lib/jeff/libjeff.so
	install -m 755 $(LIBDIR)/libjautomata.so $(HOME)/.local/lib/jeff/libjautomata.so
	install -m 755 $(LIBDIR)/libjlua.so $(HOME)/.local/lib/jeff/libjlua.so

install_libs/fast:
	mkdir -p /usr/lib/jeff
	install -m 755 $(LIBDIR)/libjeff.so /usr/lib/jeff/libjeff.so
	install -m 755 $(LIBDIR)/libjautomata.so /usr/lib/jeff/libjautomata.so
	install -m 755 $(LIBDIR)/libjlua.so /usr/lib/jeff/libjlua.so

install_libs/local/stripped: install_libs/local/fast
	strip $(HOME)/.local/lib/libj{eff,automata,lua}.so

install_libs/stripped: install_libs/fast
	strip /usr/lib/libj{eff,automata,lua}.so


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
$(BINDIR)/jeff_gtk_4: $(OBJDIR)/jeff_gtk_4.o $(GTK_H) $(ASSET_DIR)/builder.ui
	$(CC) $(OBJDIR)/jeff_gtk_4.o $(GTK_CFLAGS) -o $@ $(GTK_LDFLAGS)

$(OBJDIR)/jeff_gtk_5.o: $(SRCDIR)/jeff_gtk_5.c $(GTK_H)
	$(CC) -c $(SRCDIR)/jeff_gtk_5.c $(GTK_CFLAGS) -o $@
$(BINDIR)/jeff_gtk_5: $(OBJDIR)/jeff_gtk_5.o $(GTK_H)
	$(CC) $(OBJDIR)/jeff_gtk_5.o $(GTK_CFLAGS) -o $@ $(GTK_LDFLAGS)

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
