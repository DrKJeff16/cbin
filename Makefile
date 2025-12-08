include config.mk

SHELL = /bin/bash

all: $(ACTIONS)

$(JEFF_INCDIR):
	mkdir -p $@

$(LIBDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $@

$(OBJDIR):
	mkdir -p $@


$(OBJDIR)/jdie.o: $(SRCDIR)/jeff/jdie.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jerr.o: $(SRCDIR)/jeff/jerr.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jmemory.o: $(SRCDIR)/jeff/jmemory.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jrandom.o: $(SRCDIR)/jeff/jrandom.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jstring.o: $(SRCDIR)/jeff/jstring.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jsignal.o: $(SRCDIR)/jeff/jsignal.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jinput.o: $(SRCDIR)/jeff/jinput.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jlog.o: $(SRCDIR)/jeff/jlog.c $(JEFF_H)
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jlua.o: $(SRCDIR)/jeff/jlua.c $(JEFF_H)
	$(CC) -c $< $(JEFF_LUA_CFLAGS) -o $@


$(LIBDIR)/libjeff.so: $(JEFF_OBJECTS)
	$(CC) $(JEFF_OBJECTS) $(JEFF_CFLAGS) -shared -o $@ $(JEFF_LDFLAGS)

$(LIBDIR)/libjlua.so: $(OBJDIR)/jlua.o
	$(CC) $< $(JEFF_LUA_CFLAGS) -shared -o $@ $(JEFF_LUA_LDFLAGS)


$(OBJDIR)/cointoss.o: $(SRCDIR)/cointoss.c $(INCDIR)/cointoss.h
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/yn.o: $(SRCDIR)/yn.c $(INCDIR)/yn.h
	$(CC) -c $< $(CFLAGS) -o $@


$(BINDIR)/cointoss: $(OBJDIR)/cointoss.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

$(BINDIR)/yn: $(OBJDIR)/yn.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

libs: $(LIBDIR) $(OBJDIR) $(BINDIR) $(JEFF_LIBS)


cointoss: $(BINDIR)/cointoss

yn: $(BINDIR)/yn


strip_bin:
	@strip $(BINDIR)/*

strip_libs:
	@strip $(LIBDIR)/*.so

install_bin:
	@mkdir -p $(GLOBAL_PREFIX)/bin
	install -m 755 $(BINDIR)/cointoss $(GLOBAL_PREFIX)/bin/cointoss
	install -m 755 $(BINDIR)/yn $(GLOBAL_PREFIX)/bin/yn

install_bin_stripped: install_bin
	@strip $(GLOBAL_PREFIX)/bin/cointoss
	@strip $(GLOBAL_PREFIX)/bin/yn

install_local_bin: cointoss yn
	@mkdir -p $(HOME)/.bin/cbin
	install -m 755 $(BINDIR)/cointoss $(HOME)/.bin/cbin/cointoss
	install -m 755 $(BINDIR)/yn $(HOME)/.bin/cbin/yn

install_local_bin_stripped: install_local_bin
	strip $(HOME)/.bin/cbin/cointoss
	strip $(HOME)/.bin/cbin/yn

install_headers:
	rm -rf $(GLOBAL_PREFIX)/include/jeff
	mkdir -p $(GLOBAL_PREFIX)/include/jeff
	install -m 644 $(JEFF_INCDIR)/jeff.h $(GLOBAL_PREFIX)/include/jeff/jeff.h
	install -m 644 $(JEFF_INCDIR)/jinput.h $(GLOBAL_PREFIX)/include/jeff/jinput.h
	install -m 644 $(JEFF_INCDIR)/jlog.h $(GLOBAL_PREFIX)/include/jeff/jlog.h
	install -m 644 $(JEFF_INCDIR)/jlua.h $(GLOBAL_PREFIX)/include/jeff/jlua.h
	install -m 644 $(JEFF_INCDIR)/jmemory.h $(GLOBAL_PREFIX)/include/jeff/jmemory.h
	install -m 644 $(JEFF_INCDIR)/jrandom.h $(GLOBAL_PREFIX)/include/jeff/jrandom.h
	install -m 644 $(JEFF_INCDIR)/jsignal.h $(GLOBAL_PREFIX)/include/jeff/jsignal.h
	install -m 644 $(JEFF_INCDIR)/jstring.h $(GLOBAL_PREFIX)/include/jeff/jstring.h
	install -m 644 $(JEFF_INCDIR)/jswap.h $(GLOBAL_PREFIX)/include/jeff/jswap.h
	install -m 644 $(JEFF_INCDIR)/jtypes.h $(GLOBAL_PREFIX)/include/jeff/jtypes.h

install_local_libs:
	rm -rf $(LOCAL_PREFIX)/lib/jeff
	mkdir -p $(LOCAL_PREFIX)/lib/jeff
	install -m 755 $(LIBDIR)/libjeff.so $(LOCAL_PREFIX)/lib/jeff/libjeff.so
	install -m 755 $(LIBDIR)/libjlua.so $(LOCAL_PREFIX)/lib/jeff/libjlua.so

install_libs:
	rm -rf $(GLOBAL_PREFIX)/lib/jeff
	mkdir -p $(GLOBAL_PREFIX)/lib/jeff
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
	cointoss \
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
	strip_bin \
	strip_libs \
	yn \
	$(ACTIONS)
