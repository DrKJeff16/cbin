include config.mk

ifeq ($(CC),)
	CC := gcc
	AR := gcc-ar
endif
ifeq ($(CXX),)
	CXX := g++
	AR := gcc-ar
endif

ifeq ($(CC), cc)
	AR := gcc-ar
endif
ifeq ($(CC), gcc)
	AR := gcc-ar
endif
ifeq ($(CC), clang)
	AR := llvm-ar
endif

ifeq ($(CXX), c++)
	AR := gcc-ar
endif
ifeq ($(CXX), g++)
	AR := gcc-ar
endif
ifeq ($(CXX), clang++)
	AR := llvm-ar
endif

SUBDIRS = $(OBJDIR) \
		  $(JEFF_INCDIR) \
		  $(INCDIR) \
		  $(LIBDIR) \
		  $(BINDIR) \

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
	iwyu \
	libs \
	nwl_trim \
	strip_bin \
	strip_libs \
	yn \
	$(ACTIONS) \
	$(JEFF_H) \
	$(JEFF_OBJECTS) \
	$(JEFF_STATIC_LIBS) \
	$(SUBDIRS)

SHELL = /bin/bash

all: $(ACTIONS)

$(JEFF_INCDIR):
	@mkdir -p $@

$(JEFF_PREPROCDIR):
	@mkdir -p $@

$(LIBDIR):
	@mkdir -p $@

$(BINDIR):
	@mkdir -p $@

$(OBJDIR):
	@mkdir -p $@

$(PREPROCDIR):
	@mkdir -p $@

$(OBJDIR)/jdie.o: $(SRCDIR)/jeff/jdie.c
	$(IWYU) $(JEFF_CFLAGS) $<
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jerr.o: $(SRCDIR)/jeff/jerr.c
	$(IWYU) $(JEFF_CFLAGS) $<
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jrandom.o: $(SRCDIR)/jeff/jrandom.c
	$(IWYU) $(JEFF_CFLAGS) $<
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jfile.o: $(SRCDIR)/jeff/jfile.c
	$(IWYU) $(JEFF_CFLAGS) $<
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jhash.o: $(SRCDIR)/jeff/jhash.c
	$(IWYU) $(JEFF_CFLAGS) $<
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jstring.o: $(SRCDIR)/jeff/jstring.c
	$(IWYU) $(JEFF_CFLAGS) $<
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jsignal.o: $(SRCDIR)/jeff/jsignal.c
	$(IWYU) $(JEFF_CFLAGS) $<
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jinput.o: $(SRCDIR)/jeff/jinput.c
	$(IWYU) $(JEFF_CFLAGS) $<
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(OBJDIR)/jlog.o: $(SRCDIR)/jeff/jlog.c
	$(IWYU) $(JEFF_CFLAGS) $<
	$(CC) -c $< $(JEFF_CFLAGS) -o $@

$(LIBDIR)/libjdie.a: $(OBJDIR)/jdie.o
	$(AR) rcs $@ $<

$(LIBDIR)/libjerr.a: $(OBJDIR)/jerr.o
	$(AR) rcs $@ $<

$(LIBDIR)/libjrandom.a: $(OBJDIR)/jrandom.o
	$(AR) rcs $@ $<

$(LIBDIR)/libjfile.a: $(OBJDIR)/jfile.o
	$(AR) rcs $@ $<

$(LIBDIR)/libjhash.a: $(OBJDIR)/jhash.o
	$(AR) rcs $@ $<

$(LIBDIR)/libjstring.a: $(OBJDIR)/jstring.o
	$(AR) rcs $@ $<

$(LIBDIR)/libjsignal.a: $(OBJDIR)/jsignal.o
	$(AR) rcs $@ $<

$(LIBDIR)/libjinput.a: $(OBJDIR)/jinput.o
	$(AR) rcs $@ $<

$(LIBDIR)/libjlog.a: $(OBJDIR)/jlog.o
	$(AR) rcs $@ $<

$(LIBDIR)/libjeff.so: $(JEFF_OBJECTS)
	$(CC) $(JEFF_OBJECTS) $(JEFF_CFLAGS) -shared -o $@ $(JEFF_LDFLAGS)

$(OBJDIR)/cointoss.o: $(SRCDIR)/cointoss.c
	$(IWYU) $(CFLAGS) $<
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/countdown.o: $(SRCDIR)/countdown.c
	$(IWYU) $(CFLAGS) $<
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/gtkmm_example.o: $(SRCDIR)/gtkmm_example.cpp
	$(IWYU) $(GTKMM_EXAMPLE_CFLAGS) $<
	$(CXX) -c $< $(GTKMM_EXAMPLE_CFLAGS) -o $@

$(OBJDIR)/misc.o: $(SRCDIR)/misc.c
	$(IWYU) $(CFLAGS) $<
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/nwl_trim.o: $(SRCDIR)/nwl_trim.c
	$(IWYU) $(CFLAGS) $<
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/shrug.o: $(SRCDIR)/shrug.c
	$(IWYU) $(CFLAGS) $<
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/yn.o: $(SRCDIR)/yn.c
	$(IWYU) $(CFLAGS) $<
	$(CC) -c $< $(CFLAGS) -o $@

$(BINDIR)/cointoss: $(OBJDIR)/cointoss.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

$(BINDIR)/countdown: $(OBJDIR)/countdown.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

$(BINDIR)/gtkmm_example: $(OBJDIR)/gtkmm_example.o
	$(CXX) $< $(GTKMM_EXAMPLE_CFLAGS) -o $@ $(GTKMM_EXAMPLE_LDFLAGS)

$(BINDIR)/misc: $(OBJDIR)/misc.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

$(BINDIR)/nwl_trim: $(OBJDIR)/nwl_trim.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

$(BINDIR)/shrug: $(OBJDIR)/shrug.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

$(BINDIR)/yn: $(OBJDIR)/yn.o
	$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

libs: $(SUBDIRS) $(JEFF_LIBS) $(JEFF_STATIC_LIBS)

cointoss: $(BINDIR)/cointoss

countdown: $(BINDIR)/countdown

gtkmm_example: $(BINDIR)/gtkmm_example

misc: $(BINDIR)/misc

nwl_trim: $(BINDIR)/nwl_trim

shrug: $(BINDIR)/shrug

yn: $(BINDIR)/yn

strip_bin:
	@strip $(BINDIR)/*

strip_libs:
	@strip $(LIBDIR)/*.so

install_bin:
	@mkdir -p $(GLOBAL_PREFIX)/bin
	install -m 755 $(BINDIR)/cointoss $(GLOBAL_PREFIX)/bin/cointoss
	install -m 755 $(BINDIR)/countdown $(GLOBAL_PREFIX)/bin/countdown
	install -m 755 $(BINDIR)/nwl_trim $(GLOBAL_PREFIX)/bin/nwl_trim
	install -m 755 $(BINDIR)/shrug $(GLOBAL_PREFIX)/bin/shrug
	install -m 755 $(BINDIR)/yn $(GLOBAL_PREFIX)/bin/yn

install_bin_stripped: install_bin
	@strip $(GLOBAL_PREFIX)/bin/{cointoss,countdown,nwl_trim,shrug,yn}

install_local_bin:
	@mkdir -p $(HOME)/.bin/cbin
	install -m 755 $(BINDIR)/cointoss $(HOME)/.bin/cbin/cointoss
	install -m 755 $(BINDIR)/countdown $(HOME)/.bin/cbin/countdown
	install -m 755 $(BINDIR)/nwl_trim $(HOME)/.bin/cbin/nwl_trim
	install -m 755 $(BINDIR)/shrug $(HOME)/.bin/cbin/shrug
	install -m 755 $(BINDIR)/yn $(HOME)/.bin/cbin/yn

install_local_bin_stripped: install_local_bin
	@strip $(HOME)/.bin/cbin/{cointoss,countdown,nwl_trim,shrug,yn}

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
	install -m 644 $(LIBDIR)/libjrandom.a $(GLOBAL_PREFIX)/lib/jeff/libjrandom.a
	install -m 644 $(LIBDIR)/libjsignal.a $(GLOBAL_PREFIX)/lib/jeff/libjsignal.a
	install -m 644 $(LIBDIR)/libjstring.a $(GLOBAL_PREFIX)/lib/jeff/libjstring.a
	install -m 755 $(LIBDIR)/libjeff.so $(GLOBAL_PREFIX)/lib/jeff/libjeff.so

install_local_libs_stripped: install_local_libs
	@strip $(LOCAL_PREFIX)/lib/jeff/libjeff.so

install_libs_stripped: install_libs
	@strip $(GLOBAL_PREFIX)/lib/jeff/libjeff.so

clean:
	@rm -rf $(OBJDIR)/* *.log *.out

distclean: clean
	@rm -rf $(BINDIR)/* $(LIBDIR)/* compile_commands.json

# vim: set ts=4 sts=4 sw=0 noet ai si sta:
