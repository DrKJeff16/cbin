SHELL = /bin/bash

include config.mk

all: dirs $(ACTIONS)

dirs: $(ASDIR) \
	$(CPPDIR) \
	$(JEFF_INCDIR) \
	$(LIBDIR) \
	$(OBJDIR) \
	$(BINDIR)

$(ASDIR):
	mkdir -p $(ASDIR)

$(CPPDIR):
	mkdir -p $(CPPDIR)

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


$(LIBDIR)/libjdie.so: $(JEFF_H) $(SRCDIR)/jdie.c
	$(CC) -E $(SRCDIR)/jdie.c $(JEFF_CFLAGS) -o $(CPPDIR)/jdie.i
	$(CC) -S $(CPPDIR)/jdie.i $(JEFF_CFLAGS) -o $(ASDIR)/jdie.s
	$(CC) -c $(SRCDIR)/jdie.c $(JEFF_CFLAGS) -o $(OBJDIR)/jdie.o
	$(CC) $(OBJDIR)/jdie.o $(JEFF_LDFLAGS) -shared -o $(LIBDIR)/libjdie.so

$(LIBDIR)/libjerr.so: $(JEFF_H) $(SRCDIR)/jerr.c
	$(CC) -E $(SRCDIR)/jerr.c $(JEFF_CFLAGS) -o $(CPPDIR)/jerr.i
	$(CC) -S $(CPPDIR)/jerr.i $(JEFF_CFLAGS) -o $(ASDIR)/jerr.s
	$(CC) -c $(SRCDIR)/jerr.c $(JEFF_CFLAGS) -o $(OBJDIR)/jerr.o
	$(CC) $(OBJDIR)/jerr.o $(JEFF_LDFLAGS) -shared -o $(LIBDIR)/libjerr.so

$(LIBDIR)/libjoperators.so: $(JEFF_H) $(SRCDIR)/joperators.c
	$(CC) -E $(SRCDIR)/joperators.c $(JEFF_CFLAGS) -o $(CPPDIR)/joperators.i
	$(CC) -S $(CPPDIR)/joperators.i $(JEFF_CFLAGS) -o $(ASDIR)/joperators.s
	$(CC) -c $(SRCDIR)/joperators.c $(JEFF_CFLAGS) -o $(OBJDIR)/joperators.o
	$(CC) $(OBJDIR)/joperators.o $(JEFF_LDFLAGS) -shared -o $(LIBDIR)/libjoperators.so

$(LIBDIR)/libjstring.so: $(JEFF_H) $(SRCDIR)/jstring.c
	$(CC) -E $(SRCDIR)/jstring.c $(JEFF_CFLAGS) -o $(CPPDIR)/jstring.i
	$(CC) -S $(CPPDIR)/jstring.i $(JEFF_CFLAGS) -o $(ASDIR)/jstring.s
	$(CC) -c $(SRCDIR)/jstring.c $(JEFF_CFLAGS) -o $(OBJDIR)/jstring.o
	$(CC) $(OBJDIR)/jstring.o $(JEFF_LDFLAGS) -shared -o $(LIBDIR)/libjstring.so

$(LIBDIR)/libjlog.so: $(JEFF_H) $(SRCDIR)/jlog.c
	$(CC) -E $(SRCDIR)/jlog.c $(JEFF_CFLAGS) -o $(CPPDIR)/jlog.i
	$(CC) -S $(CPPDIR)/jlog.i $(JEFF_CFLAGS) -o $(ASDIR)/jlog.s
	$(CC) -c $(SRCDIR)/jlog.c $(JEFF_CFLAGS) -o $(OBJDIR)/jlog.o
	$(CC) $(OBJDIR)/jlog.o $(JEFF_LDFLAGS) -shared -o $(LIBDIR)/libjlog.so

$(LIBDIR)/libjlua.so: $(JEFF_H) $(SRCDIR)/jlua.c
	$(CC) -E $(SRCDIR)/jlua.c $(JEFF_CFLAGS) -o $(CPPDIR)/jlua.i
	$(CC) -S $(CPPDIR)/jlua.i $(JEFF_CFLAGS) -o $(ASDIR)/jlua.s
	$(CC) -c $(SRCDIR)/jlua.c $(JEFF_CFLAGS) -o $(OBJDIR)/jlua.o
	$(CC) $(OBJDIR)/jlua.o $(JEFF_LUA_LDFLAGS) -shared -o $(LIBDIR)/libjlua.so


libs: dirs $(JEFF_LIBS)


cointoss: dirs $(BINDIR)/cointoss
misc: dirs $(BINDIR)/jmisc
gl_1: dirs $(BINDIR)/jeff_gl_1
gl_2: dirs $(BINDIR)/jeff_gl_2
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
	install -m 644 $(JEFF_INCDIR)/jlua.h $(HOME)/.local/include/jeff/jlua.h
	install -m 644 $(JEFF_INCDIR)/jlog.h /usr/include/jeff/jlog.h


install_libs/local/fast:
	install -m 755 $(LIBDIR)/libjdie.so $(HOME)/.local/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so $(HOME)/.local/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so $(HOME)/.local/lib/libjoperators.so
	install -m 755 $(LIBDIR)/libjstring.so $(HOME)/.local/lib/libjstring.so
	install -m 755 $(LIBDIR)/libjlua.so $(HOME)/.local/lib/libjlua.so
	install -m 755 $(LIBDIR)/libjlog.so $(HOME)/.local/lib/libjlog.so
	chown -R $(USER)\:$(USER) $(HOME)/.local/lib

install_libs/fast:
	install -m 755 $(LIBDIR)/libjdie.so /usr/lib/libjdie.so
	install -m 755 $(LIBDIR)/libjerr.so /usr/lib/libjerr.so
	install -m 755 $(LIBDIR)/libjoperators.so /usr/lib/libjoperators.so
	install -m 755 $(LIBDIR)/libjstring.so /usr/lib/libjstring.so
	install -m 755 $(LIBDIR)/libjlua.so /usr/lib/libjlua.so
	install -m 755 $(LIBDIR)/libjlog.so /usr/lib/libjlog.so

install_libs/local/stripped: install_libs/local/fast
	strip $(HOME)/.local/lib/libj{die,err,operators,string,lua,log}.so
	chown -R $(USER)\:$(USER) $(HOME)/.local/lib

install_libs/stripped: install_libs/fast
	strip /usr/lib/libj{die,err,operators,string,lua,log}.so


$(BINDIR)/cointoss: $(SRCDIR)/cointoss.c $(JEFF_INCDIR)/cointoss.h
	$(CC) -E $(SRCDIR)/cointoss.c $(CFLAGS) -o $(CPPDIR)/cointoss.i
	$(CC) -S $(CPPDIR)/cointoss.i $(CFLAGS) -o $(ASDIR)/cointoss.s
	$(CC) -c $(SRCDIR)/cointoss.c $(CFLAGS) -o $(OBJDIR)/cointoss.o
	$(CC) $(OBJDIR)/cointoss.o $(CFLAGS) $(LDFLAGS) -o $@

$(BINDIR)/jmisc: $(SRCDIR)/jmisc.c $(JEFF_INCDIR)/jmisc.h
	$(CC) -E $(SRCDIR)/jmisc.c $(CFLAGS) -o $(CPPDIR)/jmisc.i
	$(CC) -S $(CPPDIR)/jmisc.i $(CFLAGS) -o $(ASDIR)/jmisc.s
	$(CC) -c $(SRCDIR)/jmisc.c $(CFLAGS) -o $(OBJDIR)/jmisc.o
	$(CC) $(OBJDIR)/jmisc.o $(CFLAGS) $(LDFLAGS) -o $@

$(BINDIR)/jeff_gl_1: $(SRCDIR)/jeff_gl_1.c $(GL_H)
	$(CC) -E $(SRCDIR)/jeff_gl_1.c $(GL_CFLAGS) -o $(CPPDIR)/jeff_gl_1.i
	$(CC) -S $(CPPDIR)/jeff_gl_1.i $(GL_CFLAGS) -o $(ASDIR)/jeff_gl_1.s
	$(CC) -c $(SRCDIR)/jeff_gl_1.c $(GL_CFLAGS) -o $(OBJDIR)/jeff_gl_1.o
	$(CC) $(OBJDIR)/jeff_gl_1.o $(GL_CFLAGS) $(GL_LDFLAGS) -o $@

$(BINDIR)/jeff_gl_2: $(SRCDIR)/jeff_gl_2.c $(GL_H)
	$(CC) -E $(SRCDIR)/jeff_gl_2.c $(GL_CFLAGS) -o $(CPPDIR)/jeff_gl_2.i
	$(CC) -S $(CPPDIR)/jeff_gl_2.i $(GL_CFLAGS) -o $(ASDIR)/jeff_gl_2.s
	$(CC) -c $(SRCDIR)/jeff_gl_2.c $(GL_CFLAGS) -o $(OBJDIR)/jeff_gl_2.o
	$(CC) $(OBJDIR)/jeff_gl_2.o $(GL_CFLAGS) $(GL_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_1: $(SRCDIR)/jeff_gtk_1.c $(GTK_H)
	$(CC) -E $(SRCDIR)/jeff_gtk_1.c $(GTK_CFLAGS) -o $(CPPDIR)/jeff_gtk_1.i
	$(CC) -S $(CPPDIR)/jeff_gtk_1.i $(GTK_CFLAGS) -o $(ASDIR)/jeff_gtk_1.s
	$(CC) -c $(SRCDIR)/jeff_gtk_1.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_1.o
	$(CC) $(OBJDIR)/jeff_gtk_1.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_2: $(SRCDIR)/jeff_gtk_2.c $(GTK_H)
	$(CC) -E $(SRCDIR)/jeff_gtk_2.c $(GTK_CFLAGS) -o $(CPPDIR)/jeff_gtk_2.i
	$(CC) -S $(CPPDIR)/jeff_gtk_2.i $(GTK_CFLAGS) -o $(ASDIR)/jeff_gtk_2.s
	$(CC) -c $(SRCDIR)/jeff_gtk_2.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_2.o
	$(CC) $(OBJDIR)/jeff_gtk_2.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_3: $(SRCDIR)/jeff_gtk_3.c $(GTK_H)
	$(CC) -E $(SRCDIR)/jeff_gtk_3.c $(GTK_CFLAGS) -o $(CPPDIR)/jeff_gtk_3.i
	$(CC) -S $(CPPDIR)/jeff_gtk_3.i $(GTK_CFLAGS) -o $(ASDIR)/jeff_gtk_3.s
	$(CC) -c $(SRCDIR)/jeff_gtk_3.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_3.o
	$(CC) $(OBJDIR)/jeff_gtk_3.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_4: $(SRCDIR)/jeff_gtk_4.c $(GTK_H) $(ASSET_DIR)/builder.ui
	$(CC) -E $(SRCDIR)/jeff_gtk_4.c $(GTK_CFLAGS) -o $(CPPDIR)/jeff_gtk_4.i
	$(CC) -S $(CPPDIR)/jeff_gtk_4.i $(GTK_CFLAGS) -o $(ASDIR)/jeff_gtk_4.s
	$(CC) -c $(SRCDIR)/jeff_gtk_4.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_4.o
	$(CC) $(OBJDIR)/jeff_gtk_4.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_gtk_5: $(SRCDIR)/jeff_gtk_5.c $(GTK_H)
	$(CC) -E $(SRCDIR)/jeff_gtk_5.c $(GTK_CFLAGS) -o $(CPPDIR)/jeff_gtk_5.i
	$(CC) -S $(CPPDIR)/jeff_gtk_5.i $(GTK_CFLAGS) -o $(ASDIR)/jeff_gtk_5.s
	$(CC) -c $(SRCDIR)/jeff_gtk_5.c $(GTK_CFLAGS) -o $(OBJDIR)/jeff_gtk_5.o
	$(CC) $(OBJDIR)/jeff_gtk_5.o $(GTK_CFLAGS) $(GTK_LDFLAGS) -o $@

$(BINDIR)/jeff_sdl_1: $(SRCDIR)/jeff_sdl_1.c $(SDL_H) $(ASSET_DIR)/face.png
	$(CC) -E $(SRCDIR)/jeff_sdl_1.c $(SDL_CFLAGS) -o $(CPPDIR)/jeff_sdl_1.i
	$(CC) -S $(CPPDIR)/jeff_sdl_1.i $(SDL_CFLAGS) -o $(ASDIR)/jeff_sdl_1.s
	$(CC) -c $(SRCDIR)/jeff_sdl_1.c $(SDL_CFLAGS) -o $(OBJDIR)/jeff_sdl_1.o
	$(CC) $(OBJDIR)/jeff_sdl_1.o $(SDL_CFLAGS) $(SDL_LDFLAGS) -o $@

$(BINDIR)/jeff_lua_1: $(SRCDIR)/jeff_lua_1.c $(LUA_H)
	$(CC) -E $(SRCDIR)/jeff_lua_1.c $(LUA_CFLAGS) -o $(CPPDIR)/jeff_lua_1.i
	$(CC) -S $(CPPDIR)/jeff_lua_1.i $(LUA_CFLAGS) -o $(ASDIR)/jeff_lua_1.s
	$(CC) -c $(SRCDIR)/jeff_lua_1.c $(LUA_CFLAGS) -o $(OBJDIR)/jeff_lua_1.o
	$(CC) $(OBJDIR)/jeff_lua_1.o $(LUA_CFLAGS) $(LUA_LDFLAGS) -o $@

$(BINDIR)/jeff_ncurses_1: $(SRCDIR)/jeff_ncurses_1.c $(NCURSES_H)
	$(CC) -E $(SRCDIR)/jeff_ncurses_1.c $(NCURSES_CFLAGS) -o $(CPPDIR)/jeff_ncurses_1.i
	$(CC) -S $(CPPDIR)/jeff_ncurses_1.i $(NCURSES_CFLAGS) -o $(ASDIR)/jeff_ncurses_1.s
	$(CC) -c $(SRCDIR)/jeff_ncurses_1.c $(NCURSES_CFLAGS) -o $(OBJDIR)/jeff_ncurses_1.o
	$(CC) $(OBJDIR)/jeff_ncurses_1.o $(NCURSES_CFLAGS) $(NCURSES_LDFLAGS) -o $@


clean:
	rm -rf *.o *.i *.s *.S $(OBJDIR) $(ASDIR) $(CPPDIR)

distclean: clean
	rm -rf $(BINDIR) *.so *.a $(LIBDIR) build compile_commands.json *.log


.PHONY: all \
	distclean \
	clean \
	libs \
	strip/bin \
	strip/libs \
	install_libs/fast \
	install_libs/stripped \
	install_libs/local/fast \
	install_libs/local/stripped \
	install_headers/local install_headers/global \
	$(ACTIONS)
