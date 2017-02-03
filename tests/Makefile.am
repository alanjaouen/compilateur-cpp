EXTRA_DIST = $(srcdir)

check-local: epitestsuite

epitestsuite: pypi-install
	$(srcdir)/epitestsuite.py

pypi-install:
	$(srcdir)/install.sh
