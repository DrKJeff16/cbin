include config.mk

SHELL = /bin/bash

all: libs $(ACTIONS)

$(JEFF_INCDIR):
	mkdir -p $@

$(LIBDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $@

$(OBJDIR):
	mkdir -p $@


$(OBJDIR)/jdie.o: $(SRCDIR)/jdie.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jerr.o: $(SRCDIR)/jerr.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jrandom.o: $(SRCDIR)/jrandom.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jstring.o: $(SRCDIR)/jstring.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jinput.o: $(SRCDIR)/jinput.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jlog.o: $(SRCDIR)/jlog.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jautomata.o: $(SRCDIR)/jautomata.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jlua.o: $(SRCDIR)/jlua.c $(JEFF_H)
	$(CC) -c $< $(JEFF_LUA_CFLAGS) -o $@


$(LIBDIR)/libjeff.so: $(JEFF_OBJECTS)
	$(CC) $(JEFF_OBJECTS) $(JEFF_CFLAGS) -shared -o $@ $(JEFF_LDFLAGS)

$(LIBDIR)/libjlua.so: $(OBJDIR)/jlua.o
	$(CC) $< $(JEFF_LUA_CFLAGS) -shared -o $@ $(JEFF_LUA_LDFLAGS)


$(OBJDIR)/cointoss.o: $(SRCDIR)/cointoss.c $(INCDIR)/cointoss.h
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/jeff_lua_1.o: $(SRCDIR)/jeff_lua_1.c $(LUA_H)
	$(CC) -c $< $(LUA_CFLAGS) -o $@

$(OBJDIR)/yes_no.o: $(SRCDIR)/yes_no.c $(INCDIR)/yes_no.h
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/jparse.o: $(SRCDIR)/jparse.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@


$(BINDIR)/cointoss: $(OBJDIR)/cointoss.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

$(BINDIR)/jparse: $(OBJDIR)/jparse.o
	$(CXX) $< $(CXXFLAGS) -o $@ $(LDFLAGS) $(LDXXFLAGS)

$(BINDIR)/jeff_lua_1: $(OBJDIR)/jeff_lua_1.o
	$(CC) $< $(LUA_CFLAGS) -o $@ $(LUA_LDFLAGS)

$(BINDIR)/yes_no: $(OBJDIR)/yes_no.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

libs: $(LIBDIR) $(OBJDIR) $(BINDIR) $(JEFF_LIBS)


cointoss: libs $(BINDIR)/cointoss

jparse: libs $(BINDIR)/jparse

jeff_lua_1: $(BINDIR)/jeff_lua_1

yes_no: $(BINDIR)/yes_no

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
	rm -rf $(OBJDIR)/* *.log

distclean: clean
	rm -rf $(BINDIR)/* $(LIBDIR)/* compile_commands.json


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
