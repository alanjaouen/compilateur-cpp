#! /usr/bin/env python

import sys
import tc

if len (sys.argv) != 2:
  print "Usage: test.py file.tig"
  sys.exit (1)

# FIXME: Implement error handling.  Currently, we don't check the
# result of any stage!

# Parse the file and dump the ast.
filename = sys.argv[1];
lib = tc.misc.file_library ()
ast = tc.parse.parse ("builtin", filename, lib)
print ast

# Bind.
if tc.has ("bind"):
  tc.bind.bind (ast)

# Compute escapes.
if tc.has ("escapes"):
  tc.escapes.escapes_compute (ast)

# Type check.
if tc.has ("type"):
  tc.type.types_check (ast)

# Compute and dump HIR.
if tc.has ("translate"):
  fragments = tc.translate.translate (ast)
  print fragments

if tc.has ("canon"):
  # Simplify HIR to LIR.
  tc.canon.canonicalize (fragments)
  print fragments
  # Normalize CJumps in LIR.
  tc.canon.make_traces (fragments)
  print fragments

if tc.has ("temp"):
  # Temporary map.  This is only a test; the actual tempmap will be
  # fetched from the CPU.
  tempmap_ = tc.temp.TempMap ()

if tc.has ("target"):
  # Target.
  target = tc.target.MipsTarget (tc.target.CpuLimits ())
  # Use this for x86.
  # target = tc.target.Ia32Target ()

  # Temporary map.
  tempmap = target.cpu_get ().tempmap_get ();

  # Code generator.
  codegen = target.codegen_get ()

  # Instruction selection.
  lir_fragments = tc.target.lir_to_assem (fragments, target)
  tc.target.instructions_dump (lir_fragments, target, tc.common.get_cout ())

  # Runtime display.
  tc.target.runtime_dump (target)

  # Nolimips display.
  # Run only when later stages (liveness analysis and register allocation) are
  # not performed, because it renders the fragments unusable for
  # liveness analysis.
  if not tc.has ("liveness") and not tc.has ("regalloc"):
    tc.target.frame_allocate (lir_fragments, target)
  # Dump instructions.
  tc.target.instructions_dump (lir_fragments, target, tc.common.get_cout ())

# Liveness analysis.
# FIXME: These statements generates files. Modify liveness so that it
# provides a way to dump the result to a stream instead.
# if tc.has ("liveness"):
#   tc.liveness.flowgraph_dump (filename, lir_fragments, tc.common.cvar.timer)
#   tc.liveness.liveness_dump (filename, lir_fragments, tempmap,
#                             tc.common.cvar.timer)
#   tc.liveness.interference_dump (filename, lir_fragments, tempmap,
#                                 tc.common.cvar.timer)

# Register allocation.
if tc.has ("regalloc"):
  tempmap = tc.regalloc.allocate_registers (lir_fragments, target,
                                            tempmap, tc.common.cvar.timer)
  tc.temp.dump (tempmap)

# Local Variables:
# mode: python
# End:
