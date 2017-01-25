## ------------------------ ##
## Included sub makefiles.  ##
## ------------------------ ##

include $(top_srcdir)/tcsh/run.mk

pyexec_LTLIBRARIES =

# Build a Swig wrapper for each module.
$(srcdir)/swig.mk: $(top_srcdir)/tcsh/generate-swig-mk
	$(AM_V_GEN)top_srcdir="$(top_srcdir)" $< python $@.tmp
	$(AM_V_at)mv -f $@.tmp $@
	$(AM_V_at)chmod -w $@
include $(srcdir)/swig.mk

AM_CPPFLAGS =							\
  -I$(top_srcdir)/lib -I$(top_srcdir)/src -I$(top_builddir)/src	\
  $(BOOST_CPPFLAGS)						\
  -I$(PYTHONINC)
AM_SWIGFLAGS = -c++ -python -I$(top_srcdir)/lib -I$(top_srcdir)/src

# Tiger Compiler module loader.
python_PYTHON = tc.py



## --------- ##
## Testing.  ##
## --------- ##

EXTRA_DIST =					\
  test-front-end.py				\
  test-compiler.py				\
  $(TESTS)

TESTS_ENVIRONMENT = \
  top_srcdir="$(top_srcdir)" top_builddir="$(top_builddir)" $(RUN)
# Ensure `run' is rebuilt before the tests are run.
$(TESTS): $(srcdir)/run.stamp
# The dependency is on `run.in' and not `run', since `run' is
# regenerated at distribution time, and voids the time stamps (which
# we don't want!).
EXTRA_DIST += $(srcdir)/run.stamp
$(srcdir)/run.stamp: $(RUN_IN)
	$(AM_V_GEN)rm -f $@ $@.tmp
	$(AM_V_at)touch $@.tmp
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) $(RUN)
	$(AM_V_at)mv -f $@.tmp $@

TESTS = tcsh.test
