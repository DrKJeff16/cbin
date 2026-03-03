CC := ${CC}
CXX := ${CXX}
AR := gcc-ar

IWYU = include-what-you-use --error_always

GLOBAL_PREFIX := /usr
LOCAL_PREFIX := $(HOME)/.local

INSTALL_BIN_DIR = $(GLOBAL_PREFIX)/bin

BINDIR = bin
INCDIR = include
LIBDIR = lib
OBJDIR = obj
SRCDIR = src

ALL_DIRS = $(BINDIR) \
		   $(INCDIR) \
		   $(LIBDIR) \
		   $(OBJDIR) \
		   $(SRCDIR)

CPPFLAGS = -DNDEBUG \
		   -D_DEFAULT_SOURCE \
		   -D_FORTIFY_SOURCE=2 \
		   -D_GNU_SOURCE \
		   -I$(GLOBAL_PREFIX)/include/jeff \
		   -I. \
		   -Iinclude

CFLAGS = $(CPPFLAGS) \
		 -O2 \
		 -Wall \
		 -Wextra \
		 -Wformat-security \
		 -Wno-implicit-fallthrough \
		 -Wno-unused \
		 -g \
		 -ggdb \
		 -pedantic \
		 -pipe \
		 -pthread \
		 -std=gnu17

CXXFLAGS = $(CPPFLAGS) \
		   -D_GLIBCXX_ASSERTIONS \
		   -O2 \
		   -Wall \
		   -Wextra \
		   -Wno-implicit-fallthrough \
		   -Wno-unused \
		   -fcf-protection \
		   -flto \
		   -fomit-frame-pointer \
		   -fsanitize=address \
		   -fstack-clash-protection \
		   -fstack-protector \
		   -ftree-vectorize \
		   -g \
		   -ggdb \
		   -pedantic \
		   -pipe \
		   -pthread \
		   -std=c++17

LDFLAGS = -L$(GLOBAL_PREFIX)/lib/jeff \
		  -Llib \
		  -fcf-protection \
		  -flto \
		  -fomit-frame-pointer \
		  -fsanitize=address \
		  -fstack-clash-protection \
		  -fstack-protector \
		  -ftree-vectorize \
		  -ljeff

LDXXFLAGS = -L$(GLOBAL_PREFIX)/lib/jeff \
			-Llib \
			-fcf-protection \
			-flto \
			-fomit-frame-pointer \
			-fsanitize=address \
			-fstack-clash-protection \
			-fstack-protector \
			-ftree-vectorize \
			-ljeff

PKG_CONFIG_BIN := pkgconf

GTKMM_EXAMPLE_CFLAGS = $(CXXFLAGS) \
					   -I/usr/include/blkid \
					   -I/usr/include/cairo \
					   -I/usr/include/cairomm-1.16 \
					   -I/usr/include/freetype2 \
					   -I/usr/include/fribidi \
					   -I/usr/include/gdk-pixbuf-2.0 \
					   -I/usr/include/gio-unix-2.0 \
					   -I/usr/include/giomm-2.68 \
					   -I/usr/include/glib-2.0 \
					   -I/usr/include/glibmm-2.68 \
					   -I/usr/include/glycin-2 \
					   -I/usr/include/graphene-1.0 \
					   -I/usr/include/gtk-4.0 \
					   -I/usr/include/gtk-4.0/unix-print \
					   -I/usr/include/gtkmm-4.0 \
					   -I/usr/include/harfbuzz \
					   -I/usr/include/libmount \
					   -I/usr/include/libpng16 \
					   -I/usr/include/pango-1.0 \
					   -I/usr/include/pangomm-2.48 \
					   -I/usr/include/pixman-1 \
					   -I/usr/include/sigc++-3.0 \
					   -I/usr/include/sysprof-6 \
					   -I/usr/lib/cairomm-1.16/include \
					   -I/usr/lib/giomm-2.68/include \
					   -I/usr/lib/glib-2.0/include \
					   -I/usr/lib/glibmm-2.68/include \
					   -I/usr/lib/graphene-1.0/include \
					   -I/usr/lib/gtkmm-4.0/include \
					   -I/usr/lib/pangomm-2.48/include \
					   -I/usr/lib/sigc++-3.0/include \
					   -mfpmath=sse \
					   -msse \
					   -msse2

GTKMM_EXAMPLE_LDFLAGS = $(LDXXFLAGS) \
						-lcairo \
						-lcairo-gobject \
						-lcairomm-1.16 \
						-lgdk_pixbuf-2.0 \
						-lgio-2.0 \
						-lgiomm-2.68 \
						-lglib-2.0 \
						-lglibmm-2.68 \
						-lgobject-2.0 \
						-lgraphene-1.0 \
						-lgtk-4 \
						-lgtkmm-4.0 \
						-lharfbuzz \
						-lpango-1.0 \
						-lpangocairo-1.0 \
						-lpangomm-2.48 \
						-lsigc-3.0 \
						-lvulkan

JEFF_INCDIR = $(INCDIR)/jeff

JEFF_H = $(JEFF_INCDIR)/jeff.h \
		 $(JEFF_INCDIR)/jdie.h \
		 $(JEFF_INCDIR)/jerr.h \
		 $(JEFF_INCDIR)/jswap.h \
		 $(JEFF_INCDIR)/jhash.h \
		 $(JEFF_INCDIR)/jfile.h \
		 $(JEFF_INCDIR)/jinput.h \
		 $(JEFF_INCDIR)/jlog.h \
		 $(JEFF_INCDIR)/jmemory.h \
		 $(JEFF_INCDIR)/jrandom.h \
		 $(JEFF_INCDIR)/jsignal.h \
		 $(JEFF_INCDIR)/jstring.h \
		 $(JEFF_INCDIR)/jtypes.h

JEFF_OBJECTS =$(OBJDIR)/jdie.o \
			  $(OBJDIR)/jerr.o \
			  $(OBJDIR)/jhash.o \
			  $(OBJDIR)/jinput.o \
			  $(OBJDIR)/jfile.o \
			  $(OBJDIR)/jlog.o \
			  $(OBJDIR)/jrandom.o \
			  $(OBJDIR)/jsignal.o \
			  $(OBJDIR)/jstring.o

JEFF_LIBS = $(LIBDIR)/libjeff.so

JEFF_STATIC_LIBS = $(LIBDIR)/libjdie.a \
				   $(LIBDIR)/libjerr.a \
				   $(LIBDIR)/libjhash.a \
				   $(LIBDIR)/libjinput.a \
				   $(LIBDIR)/libjfile.a \
				   $(LIBDIR)/libjlog.a \
				   $(LIBDIR)/libjmemory.a \
				   $(LIBDIR)/libjrandom.a \
				   $(LIBDIR)/libjsignal.a \
				   $(LIBDIR)/libjstring.a

JEFF_CFLAGS = $(CFLAGS) -fPIC
JEFF_LDFLAGS = -lc

JEFF_ACTIONS = cointoss \
			   countdown \
			   gtkmm_example \
			   misc \
			   nwl_trim \
			   shrug \
			   yn

ACTIONS = $(JEFF_ACTIONS)

# vim: set ts=4 sts=4 sw=0 noet ai si sta:
