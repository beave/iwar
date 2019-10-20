AUTOMAKE_OPIONS=foreign no-dependencies subdir-objects
ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src

install-data-local:

	test -z "$(DESTDIR)$(sysconfdir)" || /bin/mkdir -p "$(DESTDIR)$(sysconfdir)"
	test -z "$(DESTDIR)$(sbindir)" || /bin/mkdir -p "$(DESTDIR)$(bindir)"
	$(INSTALL) -d "$(DESTDIR)$(mandir)/man8"
	$(INSTALL) -m 755 src/iwar "$(DESTDIR)$(bindir)/iwar"
	$(INSTALL) -m 755 etc/iwar.conf "$(DESTDIR)$(sysconfdir)/iwar.conf"
	$(INSTALL) -m 755 etc/iwar-blacklist.txt "$(DESTDIR)$(sysconfdir)/iwar-blacklist.txt"
	$(INSTALL) -m 755 etc/iwar-banners.txt "$(DESTDIR)$(sysconfdir)/iwar-banners.txt"
	mkdir -p $(DESTDIR)$(mandir)/man1/
	$(INSTALL) -m 644 iwar.1 $(DESTDIR)$(mandir)/man1/

	@echo ""
	@echo "------------------------------------------------------------------------------"
	@echo "iWar has been installed! You still need to do a few more things before your"
	@echo "up and running.  Review your iwar.conf before continuing."
	@echo "------------------------------------------------------------------------------"
	@echo ""


