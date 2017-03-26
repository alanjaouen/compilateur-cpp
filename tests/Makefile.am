EXTRA_DIST = $(srcdir)

check-local: epitestsuite

epitestsuite: pypi-install
	$(srcdir)/epitestsuite.py --my @abs_top_builddir@/src/tc -p TBA

pypi-install:
	$(srcdir)/install.sh
