## ------------------------ ##
## Included sub makefiles.  ##
## ------------------------ ##

include $(top_srcdir)/tcsh/run.mk

rubydir = $(libdir)/ruby
ruby_LTLIBRARIES =

# Build a Swig wrapper for each module.
$(srcdir)/swig.mk: $(top_srcdir)/tcsh/generate-swig-mk
	$(AM_V_GEN)top_srcdir="$(top_srcdir)" $< ruby $@.tmp
	$(AM_V_at)mv -f $@.tmp $@
	$(AM_V_at)chmod -w $@
include $(srcdir)/swig.mk

AM_CPPFLAGS =							\
  $(RUBY_CPPFLAGS)						\
  -I$(top_srcdir)/lib -I$(top_srcdir)/src -I$(top_builddir)/src	\
  $(BOOST_CPPFLAGS)
AM_SWIGFLAGS = -c++ -ruby -I$(top_srcdir)/lib -I$(top_srcdir)/src
# On Mac OS X, the Ruby interpreter accepts only files ending in
# `.bundle' (and `.rb' of course).  Tell Libtool to use the `.bundle'
# extension instead of the default `.so'.
if DARWIN
  AM_LDFLAGS += -shrext .bundle
endif DARWIN

# ltrequire.rb: Extension of `require' understanding Libtool libraries.
ruby_SCRIPT = ltrequire.rb

# Tiger Compiler module loader.
ruby_SCRIPT += tc.rb

EXTRA_DIST =					\
  ltrequire.rb					\
  tc.rb


## --------- ##
## Testing.  ##
## --------- ##

EXTRA_DIST +=					\
  test-front-end.rb				\
  test-compiler.rb				\
  $(TESTS)

TESTS_ENVIRONMENT = \
  top_srcdir="$(top_srcdir)" top_builddir="$(top_builddir)" $(RUN)
# Ensure run is rebuilt before the tests are run.
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
