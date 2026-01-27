include config.mk

SUBDIRS = $(OBJDIR) \
		  $(JEFF_INCDIR) \
		  $(INCDIR) \
		  $(LIBDIR) \
		  $(BINDIR) \
		  $(JEFF_ASDIR) \
		  $(JEFF_PREPROCDIR)

.SUFFIXES: .c .o .cpp .c++ .cc. .C .h .hpp .hh .h++ .H .o .so .a

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
	$(ACTIONS) \
	$(AS_ACTIONS) \
	$(JEFF_AS) \
	$(JEFF_H) \
	$(JEFF_OBJECTS) \
	$(JEFF_PREPROC) \
	$(JEFF_STATIC_LIBS) \
	$(PREPROC_ACTIONS) \
	$(SUBDIRS)

SHELL = /bin/bash

all: $(ACTIONS)

$(JEFF_INCDIR):
	@mkdir -p $@

$(JEFF_PREPROCDIR):
	@mkdir -p $@

$(JEFF_ASDIR):
	@mkdir -p $@

$(LIBDIR):
	@mkdir -p $@

$(BINDIR):
	@mkdir -p $@

$(OBJDIR):
	@mkdir -p $@

$(ASDIR):
	@mkdir -p $@

$(PREPROCDIR):
	@mkdir -p $@

$(JEFF_PREPROCDIR)/jdie.i: $(SRCDIR)/jeff/jdie.c $(JEFF_PREPROCDIR)
	@mkdir -p $(JEFF_PREPROCCDIR) || true
	$(CC) -E $< $(JEFF_CFLAGS) -o $@

$(JEFF_PREPROCDIR)/jerr.i: $(SRCDIR)/jeff/jerr.c $(JEFF_PREPROCDIR)
	@mkdir -p $(JEFF_PREPROCCDIR) || true
	$(CC) -E $< $(JEFF_CFLAGS) -o $@

$(JEFF_PREPROCDIR)/jmemory.i: $(SRCDIR)/jeff/jmemory.c $(JEFF_PREPROCDIR)
	@mkdir -p $(JEFF_PREPROCCDIR) || true
	$(CC) -E $< $(JEFF_CFLAGS) -o $@

$(JEFF_PREPROCDIR)/jrandom.i: $(SRCDIR)/jeff/jrandom.c $(JEFF_PREPROCDIR)
	@mkdir -p $(JEFF_PREPROCCDIR) || true
	$(CC) -E $< $(JEFF_CFLAGS) -o $@

$(JEFF_PREPROCDIR)/jfile.i: $(SRCDIR)/jeff/jfile.c $(JEFF_PREPROCDIR)
	@mkdir -p $(JEFF_PREPROCCDIR) || true
	$(CC) -E $< $(JEFF_CFLAGS) -o $@

$(JEFF_PREPROCDIR)/jhash.i: $(SRCDIR)/jeff/jhash.c $(JEFF_PREPROCDIR)
	@mkdir -p $(JEFF_PREPROCCDIR) || true
	$(CC) -E $< $(JEFF_CFLAGS) -o $@

$(JEFF_PREPROCDIR)/jstring.i: $(SRCDIR)/jeff/jstring.c $(JEFF_PREPROCDIR)
	@mkdir -p $(JEFF_PREPROCCDIR) || true
	$(CC) -E $< $(JEFF_CFLAGS) -o $@

$(JEFF_PREPROCDIR)/jsignal.i: $(SRCDIR)/jeff/jsignal.c $(JEFF_PREPROCDIR)
	@mkdir -p $(JEFF_PREPROCCDIR) || true
	$(CC) -E $< $(JEFF_CFLAGS) -o $@

$(JEFF_PREPROCDIR)/jinput.i: $(SRCDIR)/jeff/jinput.c $(JEFF_PREPROCDIR)
	@mkdir -p $(JEFF_PREPROCCDIR) || true
	$(CC) -E $< $(JEFF_CFLAGS) -o $@

$(JEFF_PREPROCDIR)/jlog.i: $(SRCDIR)/jeff/jlog.c $(JEFF_PREPROCDIR)
	@mkdir -p $(JEFF_PREPROCCDIR) || true
	$(CC) -E $< $(JEFF_CFLAGS) -o $@

$(JEFF_ASDIR)/jdie.s: $(JEFF_PREPROCDIR)/jdie.i $(JEFF_ASDIR)
	@mkdir -p $(JEFF_ASCDIR) || true
	$(CC) -S $< $(JEFF_CFLAGS) -o $@

$(JEFF_ASDIR)/jerr.s: $(JEFF_PREPROCDIR)/jerr.i $(JEFF_ASDIR)
	@mkdir -p $(JEFF_ASCDIR) || true
	$(CC) -S $< $(JEFF_CFLAGS) -o $@

$(JEFF_ASDIR)/jmemory.s: $(JEFF_PREPROCDIR)/jmemory.i $(JEFF_ASDIR)
	@mkdir -p $(JEFF_ASCDIR) || true
	$(CC) -S $< $(JEFF_CFLAGS) -o $@

$(JEFF_ASDIR)/jrandom.s: $(JEFF_PREPROCDIR)/jrandom.i $(JEFF_ASDIR)
	@mkdir -p $(JEFF_ASCDIR) || true
	$(CC) -S $< $(JEFF_CFLAGS) -o $@

$(JEFF_ASDIR)/jfile.s: $(JEFF_PREPROCDIR)/jfile.i $(JEFF_ASDIR)
	@mkdir -p $(JEFF_ASCDIR) || true
	$(CC) -S $< $(JEFF_CFLAGS) -o $@

$(JEFF_ASDIR)/jhash.s: $(JEFF_PREPROCDIR)/jhash.i $(JEFF_ASDIR)
	@mkdir -p $(JEFF_ASCDIR) || true
	$(CC) -S $< $(JEFF_CFLAGS) -o $@

$(JEFF_ASDIR)/jstring.s: $(JEFF_PREPROCDIR)/jstring.i $(JEFF_ASDIR)
	@mkdir -p $(JEFF_ASCDIR) || true
	$(CC) -S $< $(JEFF_CFLAGS) -o $@

$(JEFF_ASDIR)/jsignal.s: $(JEFF_PREPROCDIR)/jsignal.i $(JEFF_ASDIR)
	@mkdir -p $(JEFF_ASCDIR) || true
	$(CC) -S $< $(JEFF_CFLAGS) -o $@

$(JEFF_ASDIR)/jinput.s: $(JEFF_PREPROCDIR)/jinput.i $(JEFF_ASDIR)
	@mkdir -p $(JEFF_ASCDIR) || true
	$(CC) -S $< $(JEFF_CFLAGS) -o $@

$(JEFF_ASDIR)/jlog.s: $(JEFF_PREPROCDIR)/jlog.i $(JEFF_ASDIR)
	@mkdir -p $(JEFF_ASCDIR) || true
	$(CC) -S $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jdie.o: $(JEFF_ASDIR)/jdie.s
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jerr.o: $(JEFF_ASDIR)/jerr.s
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jmemory.o: $(JEFF_ASDIR)/jmemory.s
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jrandom.o: $(JEFF_ASDIR)/jrandom.s
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jfile.o: $(JEFF_ASDIR)/jfile.s
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jhash.o: $(JEFF_ASDIR)/jhash.s
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jstring.o: $(JEFF_ASDIR)/jstring.s
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jsignal.o: $(JEFF_ASDIR)/jsignal.s
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jinput.o: $(JEFF_ASDIR)/jinput.s
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jlog.o: $(JEFF_ASDIR)/jlog.s
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(LIBDIR)/libjdie.a: $(OBJDIR)/jdie.o
	@$(AR) rcs $@ $<

$(LIBDIR)/libjerr.a: $(OBJDIR)/jerr.o
	@$(AR) rcs $@ $<

$(LIBDIR)/libjmemory.a: $(OBJDIR)/jmemory.o
	@$(AR) rcs $@ $<

$(LIBDIR)/libjrandom.a: $(OBJDIR)/jrandom.o
	@$(AR) rcs $@ $<

$(LIBDIR)/libjfile.a: $(OBJDIR)/jfile.o
	@$(AR) rcs $@ $<

$(LIBDIR)/libjhash.a: $(OBJDIR)/jhash.o
	@$(AR) rcs $@ $<

$(LIBDIR)/libjstring.a: $(OBJDIR)/jstring.o
	@$(AR) rcs $@ $<

$(LIBDIR)/libjsignal.a: $(OBJDIR)/jsignal.o
	@$(AR) rcs $@ $<

$(LIBDIR)/libjinput.a: $(OBJDIR)/jinput.o
	@$(AR) rcs $@ $<

$(LIBDIR)/libjlog.a: $(OBJDIR)/jlog.o
	@$(AR) rcs $@ $<

$(LIBDIR)/libjeff.so: $(JEFF_OBJECTS)
	$(CC) $(JEFF_OBJECTS) $(JEFF_CFLAGS) -shared -o $@ $(JEFF_LDFLAGS)

$(PREPROCDIR)/cointoss.i: $(SRCDIR)/cointoss.c $(INCDIR)/cointoss.h
	$(CC) -E $< $(CFLAGS) -o $@

$(PREPROCDIR)/countdown.i: $(SRCDIR)/countdown.c $(INCDIR)/countdown.h
	$(CC) -E $< $(CFLAGS) -o $@

$(PREPROCDIR)/misc.i: $(SRCDIR)/misc.c
	$(CC) -E $< $(CFLAGS) -o $@

$(PREPROCDIR)/nwl_trim.i: $(SRCDIR)/nwl_trim.c $(INCDIR)/nwl_trim.h
	$(CC) -E $< $(CFLAGS) -o $@

$(PREPROCDIR)/yn.i: $(SRCDIR)/yn.c $(INCDIR)/yn.h
	$(CC) -E $< $(CFLAGS) -o $@

$(ASDIR)/cointoss.s: $(PREPROCDIR)/cointoss.i
	$(CC) -S $< $(CFLAGS) -o $@

$(ASDIR)/countdown.s: $(PREPROCDIR)/countdown.i
	$(CC) -S $< $(CFLAGS) -o $@

$(ASDIR)/misc.s: $(PREPROCDIR)/misc.i
	$(CC) -S $< $(CFLAGS) -o $@

$(ASDIR)/nwl_trim.s: $(PREPROCDIR)/nwl_trim.i
	$(CC) -S $< $(CFLAGS) -o $@

$(ASDIR)/yn.s: $(PREPROCDIR)/yn.i
	$(CC) -S $< $(CFLAGS) -o $@

$(OBJDIR)/cointoss.o: $(ASDIR)/cointoss.s
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/countdown.o: $(ASDIR)/countdown.s
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/misc.o: $(ASDIR)/misc.s
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/nwl_trim.o: $(ASDIR)/nwl_trim.s
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/yn.o: $(ASDIR)/yn.s
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

libs: $(SUBDIRS) $(JEFF_LIBS) $(JEFF_STATIC_LIBS)

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
	install -m 644 $(JEFF_INCDIR)/jmemory.h $(GLOBAL_PREFIX)/include/jeff/jmemory.h
	install -m 644 $(JEFF_INCDIR)/jrandom.h $(GLOBAL_PREFIX)/include/jeff/jrandom.h
	install -m 644 $(JEFF_INCDIR)/jsignal.h $(GLOBAL_PREFIX)/include/jeff/jsignal.h
	install -m 644 $(JEFF_INCDIR)/jstring.h $(GLOBAL_PREFIX)/include/jeff/jstring.h
	install -m 644 $(JEFF_INCDIR)/jswap.h $(GLOBAL_PREFIX)/include/jeff/jswap.h
	install -m 644 $(JEFF_INCDIR)/jtypes.h $(GLOBAL_PREFIX)/include/jeff/jtypes.h

install_local_libs:
	@rm -rf $(LOCAL_PREFIX)/lib/jeff
	@mkdir -p $(LOCAL_PREFIX)/lib/jeff
	install -m 644 $(LIBDIR)/libjdie.a $(LOCAL_PREFIX)/lib/jeff/libjdie.a
	install -m 644 $(LIBDIR)/libjerr.a $(LOCAL_PREFIX)/lib/jeff/libjerr.a
	install -m 644 $(LIBDIR)/libjhash.a $(LOCAL_PREFIX)/lib/jeff/libjhash.a
	install -m 644 $(LIBDIR)/libjinput.a $(LOCAL_PREFIX)/lib/jeff/libjinput.a
	install -m 644 $(LIBDIR)/libjfile.a $(LOCAL_PREFIX)/lib/jeff/libjfile.a
	install -m 644 $(LIBDIR)/libjlog.a $(LOCAL_PREFIX)/lib/jeff/libjlog.a
	install -m 644 $(LIBDIR)/libjmemory.a $(LOCAL_PREFIX)/lib/jeff/libjmemory.a
	install -m 644 $(LIBDIR)/libjrandom.a $(LOCAL_PREFIX)/lib/jeff/libjrandom.a
	install -m 644 $(LIBDIR)/libjsignal.a $(LOCAL_PREFIX)/lib/jeff/libjsignal.a
	install -m 644 $(LIBDIR)/libjstring.a $(LOCAL_PREFIX)/lib/jeff/libjstring.a
	install -m 755 $(LIBDIR)/libjeff.so $(LOCAL_PREFIX)/lib/jeff/libjeff.so

install_libs:
	@rm -rf $(GLOBAL_PREFIX)/lib/jeff
	@mkdir -p $(GLOBAL_PREFIX)/lib/jeff
	install -m 644 $(LIBDIR)/libjdie.a $(GLOBAL_PREFIX)/lib/jeff/libjdie.a
	install -m 644 $(LIBDIR)/libjerr.a $(GLOBAL_PREFIX)/lib/jeff/libjerr.a
	install -m 644 $(LIBDIR)/libjhash.a $(GLOBAL_PREFIX)/lib/jeff/libjhash.a
	install -m 644 $(LIBDIR)/libjinput.a $(GLOBAL_PREFIX)/lib/jeff/libjinput.a
	install -m 644 $(LIBDIR)/libjfile.a $(GLOBAL_PREFIX)/lib/jeff/libjfile.a
	install -m 644 $(LIBDIR)/libjlog.a $(GLOBAL_PREFIX)/lib/jeff/libjlog.a
	install -m 644 $(LIBDIR)/libjmemory.a $(GLOBAL_PREFIX)/lib/jeff/libjmemory.a
	install -m 644 $(LIBDIR)/libjrandom.a $(GLOBAL_PREFIX)/lib/jeff/libjrandom.a
	install -m 644 $(LIBDIR)/libjsignal.a $(GLOBAL_PREFIX)/lib/jeff/libjsignal.a
	install -m 644 $(LIBDIR)/libjstring.a $(GLOBAL_PREFIX)/lib/jeff/libjstring.a
	install -m 755 $(LIBDIR)/libjeff.so $(GLOBAL_PREFIX)/lib/jeff/libjeff.so

install_local_libs_stripped: install_local_libs
	@strip $(LOCAL_PREFIX)/lib/jeff/libjeff.so

install_libs_stripped: install_libs
	@strip $(GLOBAL_PREFIX)/lib/jeff/libjeff.so

clean:
	@rm -rf $(PREPROCDIR)/* $(ASDIR)/* $(OBJDIR)/* *.log

distclean: clean
	@rm -rf $(BINDIR)/* $(LIBDIR)/* compile_commands.json

# vim: set ts=4 sts=4 sw=0 noet ai si sta:
