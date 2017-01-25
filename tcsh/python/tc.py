# Tiger Compiler module loader.

import sys
import imp

def try_import (prefix, modules):
  for mod in modules:
    mod_name = prefix + mod
    # Look for module MOD_NAME...
    try:
      file, pathname, description = imp.find_module (mod_name)
    except ImportError:
      continue
    # ...and try to load it.
    try:
      globals ()[mod] = imp.load_module (mod_name, file, pathname, description)
    finally:
      # Since we may exit via an exception, close FILE explicitly
      # (see http://docs.python.org/lib/examples-imp.html).
      if file:
        file.close ()

# Query tc for a module.
def has (module_name):
  return (module_name in globals ())

try_import ("tiger_",
            ["ast", "misc", "common", "parse", "bind", "object", "escapes",
             "type", "overload", "tree", "translate", "canon", "temp",
             "target", "liveness", "regalloc"])

# Shortcuts
Cout = common.cvar.Cout
Cerr = common.cvar.Cerr
Ofstream = common.Ofstream
