# A test/script wrapper.

RUN = $(top_builddir)/tcsh/run
RUN_IN = $(top_srcdir)/tcsh/run.in
$(RUN): $(RUN_IN)
	cd $(top_builddir)/tcsh && $(MAKE) $(AM_MAKEFLAGS) run
