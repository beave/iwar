ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPIONS=foreign no-dependencies subdir-objects
AM_CFLAGS = -D_POSIX


                bin_PROGRAMS = iwar
                               iwar_CPPFLAGS = -I$(top_srcdir) $(LIBFASTJSON_CFLAGS) $(LIBESTR_CFLAGS)
                                       iwar_LDADD = $(LIBFASTJSON_LIBS) $(LIBLOGNORM_LIBS) $(LIBESTR_LIBS)

                                               iwar_SOURCES = iwar-engine.c \
							      iwar-ncurses.c \
							      sysdep1.c


                                                       install-data-local:

