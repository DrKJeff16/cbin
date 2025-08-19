include config.mk

SHELL = /bin/bash

all: libs $(ACTIONS)

$(INCDIR):
	-@mkdir -p $@/$(JEFF_INCDIR)

$(LIBDIR):
	-@mkdir -p $@

$(BINDIR):
	-@mkdir -p $@

$(OBJDIR):
	-@mkdir -p $@


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


$(LIBDIR)/libjeff.so: $(JEFF_OBJECTS)
	$(CC) $(JEFF_OBJECTS) $(JEFF_CFLAGS) -shared -o $@ $(JEFF_LDFLAGS)

$(LIBDIR)/libjlua.so: $(OBJDIR)/jlua.o $(LIBDIR)/libjeff.so
	$(CC) $< $(JEFF_LUA_CFLAGS) -shared -o $@ $(JEFF_LUA_LDFLAGS)


$(OBJDIR)/cointoss.o: $(SRCDIR)/cointoss.c $(JEFF_INCDIR)/cointoss.h
	$(CC) -c $(SRCDIR)/cointoss.c $(CFLAGS) -o $@

$(OBJDIR)/jeff_lua_1.o: $(SRCDIR)/jeff_lua_1.c $(LUA_H)
	$(CC) -c $(SRCDIR)/jeff_lua_1.c $(LUA_CFLAGS) -o $@

$(OBJDIR)/jparse.o: $(SRCDIR)/jparse.cpp
	$(CXX) -c $(SRCDIR)/jparse.cpp $(CXXFLAGS) -o $@


$(BINDIR)/cointoss: $(OBJDIR)/cointoss.o $(JEFF_INCDIR)/cointoss.h
	$(CC) $(OBJDIR)/cointoss.o $(CFLAGS) -o $@ $(LDFLAGS)

$(BINDIR)/jparse: $(OBJDIR)/jparse.o
	$(CXX) $(OBJDIR)/jparse.o $(CXXFLAGS) -o $@ $(LDFLAGS) $(LDXXFLAGS)

$(BINDIR)/jeff_lua_1: $(OBJDIR)/jeff_lua_1.o $(LUA_H)
	$(CC) $(OBJDIR)/jeff_lua_1.o $(LUA_CFLAGS) -o $@ $(LUA_LDFLAGS)

libs: $(LIBDIR) $(OBJDIR) $(BINDIR) $(JEFF_LIBS)

cointoss: libs $(BINDIR)/cointoss
jparse: libs $(BINDIR)/jparse

strip/bin:
	strip $(BINDIR)/*

strip/libs:
	strip $(LIBDIR)/*.so

install_bin:
	-@mkdir -p $(GLOBAL_PREFIX)/bin
	install -m 755 $(BINDIR)/cointoss $(GLOBAL_PREFIX)/bin/cointoss

install_bin_stripped: install_bin
	-@strip $(GLOBAL_PREFIX)/bin/cointoss

install_local_bin:
	-@mkdir -p $(HOME)/.bin/cbin
	install -m 755 $(BINDIR)/cointoss $(HOME)/.bin/cbin/cointoss

install_local_bin_stripped: install_local_bin
	-@strip $(HOME)/.bin/cbin/cointoss

install_headers:
	-@rm -rf $(GLOBAL_PREFIX)/include/jeff
	-@mkdir -p $(GLOBAL_PREFIX)/include/jeff
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
	-@rm -rf $(LOCAL_PREFIX)/lib/jeff
	-@mkdir -p $(LOCAL_PREFIX)/lib/jeff
	install -m 755 $(LIBDIR)/libjeff.so $(LOCAL_PREFIX)/lib/jeff/libjeff.so
	install -m 755 $(LIBDIR)/libjlua.so $(LOCAL_PREFIX)/lib/jeff/libjlua.so

install_libs:
	-@rm -rf $(GLOBAL_PREFIX)/lib/jeff
	-@mkdir -p $(GLOBAL_PREFIX)/lib/jeff
	install -m 755 $(LIBDIR)/libjeff.so $(GLOBAL_PREFIX)/lib/jeff/libjeff.so
	install -m 755 $(LIBDIR)/libjlua.so $(GLOBAL_PREFIX)/lib/jeff/libjlua.so

install_local_libs_stripped: install_local_libs
	strip $(LOCAL_PREFIX)/lib/jeff/libj{eff,lua}.so

install_libs_stripped: install_libs
	strip $(GLOBAL_PREFIX)/lib/jeff/libj{eff,lua}.so

clean:
	rm -rf $(OBJDIR)/*

distclean: clean
	rm -rf $(BINDIR)/* $(LIBDIR)/* build compile_commands.json *.log


.PHONY: all \
	clean \
	distclean \
	install_bin \
	install_bin_stripped \
	install_headers \
	install_libs \
	install_libs_stripped \
	install_local_bin \
	install_local_bin_stripped \
	install_local_libs \
	install_local_libs_stripped \
	libs \
	strip/bin \
	strip/libs \
	$(ACTIONS)
