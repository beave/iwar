AUTOMAKE_OPIONS=foreign no-dependencies

bin_PROGRAMS = iwar

iwar_SOURCES = iwar-engine.c iwar-ncurses.c iwar-iax2.c sysdep1.c 

AM_CFLAGS = -D_POSIX
#AM_CFLAGS =  -Wall -D_POSIX
#AM_CFLAGS =  -Wall -D_POSIX -D_SYSV -D_SELECT -D_HAVE_MACROS  

# Install BFD include file, and others that it needs.
install-data-local: 
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(sysconfdir)
	$(INSTALL_DATA) iwar.conf $(sysconfdir)/iwar.conf
	$(INSTALL_DATA) banners.txt $(sysconfdir)/banners.txt
	$(INSTALL_DATA) iwar-blacklist.txt $(sysconfdir)/iwar-blacklist.txt

