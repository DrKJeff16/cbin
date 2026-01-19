include config.mk

SUBDIRS = $(OBJDIR) $(JEFF_INCDIR) $(INCDIR) $(LIBDIR) $(BINDIR)

.SUFFIXES: .c .o .cpp .c++ .cc. .C .h .hpp .hh .h++ .H .o .so

.PHONY: all \
	clean \
	cointoss \
	countdown \
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
	nwl_trim \
	strip_bin \
	strip_libs \
	yn \
	$(SUBDIRS) \
	$(ACTIONS)

SHELL = /bin/bash

all: $(ACTIONS)

$(JEFF_INCDIR):
	@mkdir -p $@

$(LIBDIR):
	@mkdir -p $@

$(BINDIR):
	@mkdir -p $@

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/jdie.o: $(SRCDIR)/jeff/jdie.c
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jerr.o: $(SRCDIR)/jeff/jerr.c
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jmemory.o: $(SRCDIR)/jeff/jmemory.c
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jrandom.o: $(SRCDIR)/jeff/jrandom.c
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jfile.o: $(SRCDIR)/jeff/jfile.c
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jhash.o: $(SRCDIR)/jeff/jhash.c
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jstring.o: $(SRCDIR)/jeff/jstring.c
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jsignal.o: $(SRCDIR)/jeff/jsignal.c
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jinput.o: $(SRCDIR)/jeff/jinput.c
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jlog.o: $(SRCDIR)/jeff/jlog.c
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jluajit.o: $(SRCDIR)/jeff/jluajit.c
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(LIBDIR)/libjeff.so: $(JEFF_OBJECTS)
	$(CC) $(JEFF_OBJECTS) $(JEFF_CFLAGS) -shared -o $@ $(JEFF_LDFLAGS)

$(OBJDIR)/cointoss.o: $(SRCDIR)/cointoss.c $(INCDIR)/cointoss.h
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/countdown.o: $(SRCDIR)/countdown.c $(INCDIR)/countdown.h
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/misc.o: $(SRCDIR)/misc.c
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/nwl_trim.o: $(SRCDIR)/nwl_trim.c $(INCDIR)/nwl_trim.h
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/yn.o: $(SRCDIR)/yn.c $(INCDIR)/yn.h
	$(CC) -c $< $(CFLAGS) -o $@

$(BINDIR)/cointoss: $(OBJDIR)/cointoss.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

$(BINDIR)/countdown: $(OBJDIR)/countdown.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

$(BINDIR)/misc: $(OBJDIR)/misc.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

$(BINDIR)/nwl_trim: $(OBJDIR)/nwl_trim.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

$(BINDIR)/yn: $(OBJDIR)/yn.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

libs: $(LIBDIR) $(OBJDIR) $(BINDIR) $(JEFF_LIBS)

cointoss: $(BINDIR)/cointoss

countdown: $(BINDIR)/countdown

misc: $(BINDIR)/misc

nwl_trim: $(BINDIR)/nwl_trim

yn: $(BINDIR)/yn

strip_bin:
	@strip $(BINDIR)/*

strip_libs:
	@strip $(LIBDIR)/*.so

install_bin: cointoss yn countdown nwl_trim
	@mkdir -p $(GLOBAL_PREFIX)/bin
	install -m 755 $(BINDIR)/cointoss $(GLOBAL_PREFIX)/bin/cointoss
	install -m 755 $(BINDIR)/countdown $(GLOBAL_PREFIX)/bin/countdown
	install -m 755 $(BINDIR)/nwl_trim $(GLOBAL_PREFIX)/bin/nwl_trim
	install -m 755 $(BINDIR)/yn $(GLOBAL_PREFIX)/bin/yn

install_bin_stripped: install_bin
	@strip $(GLOBAL_PREFIX)/bin/{cointoss,countdown,nwl_trim,yn}

install_local_bin: cointoss yn countdown
	@mkdir -p $(HOME)/.bin/cbin
	install -m 755 $(BINDIR)/cointoss $(HOME)/.bin/cbin/cointoss
	install -m 755 $(BINDIR)/countdown $(HOME)/.bin/cbin/countdown
	install -m 755 $(BINDIR)/nwl_trim $(HOME)/.bin/cbin/nwl_trim
	install -m 755 $(BINDIR)/yn $(HOME)/.bin/cbin/yn

install_local_bin_stripped: install_local_bin
	@strip $(HOME)/.bin/cbin/{cointoss,countdown,nwl_trim,yn}

install_headers:
	@rm -rf $(GLOBAL_PREFIX)/include/jeff
	@mkdir -p $(GLOBAL_PREFIX)/include/jeff
	install -m 644 $(JEFF_INCDIR)/jdie.h $(GLOBAL_PREFIX)/include/jeff/jdie.h
	install -m 644 $(JEFF_INCDIR)/jeff.h $(GLOBAL_PREFIX)/include/jeff/jeff.h
	install -m 644 $(JEFF_INCDIR)/jerr.h $(GLOBAL_PREFIX)/include/jeff/jerr.h
	install -m 644 $(JEFF_INCDIR)/jinput.h $(GLOBAL_PREFIX)/include/jeff/jinput.h
	install -m 644 $(JEFF_INCDIR)/jlog.h $(GLOBAL_PREFIX)/include/jeff/jlog.h
	install -m 644 $(JEFF_INCDIR)/jluajit.h $(GLOBAL_PREFIX)/include/jeff/jluajit.h
	install -m 644 $(JEFF_INCDIR)/jmemory.h $(GLOBAL_PREFIX)/include/jeff/jmemory.h
	install -m 644 $(JEFF_INCDIR)/jrandom.h $(GLOBAL_PREFIX)/include/jeff/jrandom.h
	install -m 644 $(JEFF_INCDIR)/jsignal.h $(GLOBAL_PREFIX)/include/jeff/jsignal.h
	install -m 644 $(JEFF_INCDIR)/jstring.h $(GLOBAL_PREFIX)/include/jeff/jstring.h
	install -m 644 $(JEFF_INCDIR)/jswap.h $(GLOBAL_PREFIX)/include/jeff/jswap.h
	install -m 644 $(JEFF_INCDIR)/jtypes.h $(GLOBAL_PREFIX)/include/jeff/jtypes.h

install_local_libs:
	@rm -rf $(LOCAL_PREFIX)/lib/jeff
	@mkdir -p $(LOCAL_PREFIX)/lib/jeff
	install -m 755 $(LIBDIR)/libjeff.so $(LOCAL_PREFIX)/lib/jeff/libjeff.so

install_libs:
	@rm -rf $(GLOBAL_PREFIX)/lib/jeff
	@mkdir -p $(GLOBAL_PREFIX)/lib/jeff
	install -m 755 $(LIBDIR)/libjeff.so $(GLOBAL_PREFIX)/lib/jeff/libjeff.so

install_local_libs_stripped: install_local_libs
	@strip $(LOCAL_PREFIX)/lib/jeff/libjeff.so

install_libs_stripped: install_libs
	@strip $(GLOBAL_PREFIX)/lib/jeff/libjeff.so

clean:
	@rm -rf $(OBJDIR)/* *.log

distclean: clean
	@rm -rf $(BINDIR)/* $(LIBDIR)/* compile_commands.json

# vim: set ts=4 sts=4 sw=0 noet ai si sta:
