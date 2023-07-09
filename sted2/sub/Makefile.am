## Process this file with automake to produce Makefile.in

noinst_LIBRARIES = libx68funcs.a

localedir = $(datadir)/locale

INCLUDES =	-I$(top_srcdir)/sted2 \
		-I$(top_srcdir)/sted2/sayleen \
	  	-DSTED_LOCALE_DIR=\"$(localedir)\" \
		@x_cflags@ \
		@CURSES_INCLUDEDIR@

libx68funcs_a_SOURCES = \
	basic.c		\
	curses.c	\
	dos.c		\
	graph.c		\
	hprint.c	\
	iocs.c		\
	iocs_console.c	\
	iocs_graph.c	\
	iocs_key.c	\
	iocs_mouse.c	\
	iocs_tgraph.c	\
	mcpy.c		\
	midi_in.c	\
	nkflib.c	\
	ongraph.c	\
	rcdcheck.c	\
	scdsp.c		\
	x68funcs.c	\
	xwin.c		\
	xwin_col.c	\
	xwin_graph.c	\
	xwin_key.c	\
	xwin_mouse.c	\
	xwin_print.c

noinst_HEADERS = \
	doslib.h	\
	graph.h		\
	iocslib.h	\
	midi_in.h	\
	nkflib.h	\
	sted_c.h	\
	x68defines.h	\
	x68funcs.h	\
	xwin.h
