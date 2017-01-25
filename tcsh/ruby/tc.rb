# Tcsh's module loader.

# Use ltrequire, but don't append path prefixes to actual dynamic
# module names before calling require.
#
# When you load the same module with Kernel.require using two
# different names, for instance
#
#   require "foo"
#
# and
#
#   require "./foo"
#
# ruby treat them as two _different_ modules.  (You can check the
# return value the `require' calls: they will both be `true' --
# whereas loading twice the same module with the exact same name
# will give `false' after the first (successful) call to
# `require'.
#
# Within Ruby-Tcsh, `require' is used in two different ways:
#
# 1. as a call to the `Kernel.require' Ruby function, from a Ruby
# piece of code ;
#
# 2. as a call to the rb_require C function (of the C API of
# Ruby).
#
# The `ltrequire' module catches call to `Kernel.require' and does
# some work to have Ruby work with Libtool libraries.  In the case
# of the Tcsh dynamic modules (files named `tiger_*.la'), the path
# of the actual library (`.libs/tiger_*.so' or
# `.libs/tiger_*.bundle') is computed and `./' is appended to it
# (this is the place where the Libtool library resides, which is
# the current directory when the library is not yet installed).
#
# The problem is, SWIG generates calls to `rb_require' (from
# `%import' directives), and bypasses the mechanism of ltrequire's
# `require' function.  The `./' prefix is not appended to the
#  actual library, and the module gets loaded twice with two
# different names.  When the module is a classic Ruby file, this
# is not really annoying (apart from the fact that some code
# might be involuntarily executed twice); but when the module is a
# dynamic module (loaded by the dynamic linker on the request of
# the ruby interpreter), this can end in name clashes (symbols
# multiply defined).
#
# Our current solution is to try and prevent ruby from using
# different names for the same things; hence we remove any path
# prefix from the module name before requiring it, thanks to the
# The $LTREQUIRE_NO_PATH_PREFIX global variable.
require "ltrequire"
$LTREQUIRE_NO_PATH_PREFIX = true


module Tc
  def Tc::try_require(prefix, modules)
    modules.each do |mod|
      mod_name = prefix + mod
        begin
          require mod_name
        rescue LoadError
          # Continue.
        else
          # Create an alias inside the module `Tc'.
          Tc::const_set(mod.capitalize, Module::const_get(mod_name.capitalize))
        end
    end
  end

  # Query Tc for a module.
  def Tc::has?(module_name)
    Tc::constants.include? module_name
  end

  # Try to require all Tcsh modules.
  try_require("tiger_",
              ["ast", "misc", "common", "parse", "bind", "escapes", "type",
               "overload", "tree", "translate", "canon", "temp", "target",
               "liveness", "regalloc"])
end
