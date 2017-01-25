#! /usr/bin/env python

import sys
import tc
import os
import tempfile

if len (sys.argv) != 2:
  print "Usage: ti.py file.tig"
  sys.exit (1)

# FIXME: Implement error handling.  Currently, we don't check the
# result of any stage!

# Parse the file.
lib = tc.misc.file_library ()
ast = tc.parse.parse ("builtin", sys.argv[1], lib)

if tc.has ("bind"):
  tc.bind.bind (ast)

if tc.has ("type"):
  tc.type.types_check (ast)

if tc.has ("translate"):
  # Compute HIR.
  fragments = tc.translate.translate (ast)

  # Dump it.
  hir = tempfile.NamedTemporaryFile ()
  print >> hir, fragments
  hir.flush ()

  # Run havm on it.
  os.system ("havm " + hir.name)

# Local Variables:
# mode: python
# End:
