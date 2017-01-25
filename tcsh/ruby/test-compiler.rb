#! /usr/bin/env ruby

if ENV.has_key? "TCSH_RUBY_PATH"
  $:.concat ENV["TCSH_RUBY_PATH"].split(":")
end

if ARGV.size != 1
  puts "Usage: test.rb file.tig"
  exit 1
end

require "tempfile"
require "tc"


# Parse the file and dump the ast.
filename = ARGV[0];
lib = Tc::Misc::File_library.new()
ast = Tc::Parse::parse("builtin", filename, lib)
print ast

# Bind.
if Tc::has? "Bind" then
  Tc::Bind::bind ast
end

# Compute escapes.
if Tc::has? "Escapes" then
  Tc::Escapes::escapes_compute ast
end

# Type check.
if Tc::has? "Type" then
  Tc::Type::types_check ast
end

# Compute and dump HIR.
if Tc::has? "Translate" then
  fragments = Tc::Translate::translate ast
  print fragments
end

if Tc::has? "Canon" then
  # Simplify HIR to LIR.
  Tc::Canon::canonicalize fragments
  print fragments
  # Normalize CJumps in LIR.
  Tc::Canon::make_traces fragments
  print fragments
end

if Tc::has? "Temp" then
  # Temporary map.  This is only a test; the actual tempmap will be
  # fetched from the CPU.
  tempmap_ = Tc::Temp::TempMap.new
end

if Tc::has? "Target" then
  # Target.
  target = Tc::Target::MipsTarget.new(Tc::Target::CpuLimits.new)
  # Use this for x86.
  # target = Tc::Target::Ia32Target.new

  # Temporary map.
  tempmap = target.cpu_get.tempmap_get

  # Code generator.
  codegen = target.codegen_get

  # Instruction selection.
  lir_fragments = Tc::Target::lir_to_assem(fragments, target)
  Tc::Target::instructions_dump(lir_fragments, target, Tc::Common::get_cout)

  # Runtime display.
  Tc::Target::runtime_dump target

  # Nolimips display.
  # Run only when later stages (liveness analysis and register allocation) are
  # not performed, because it renders the fragments unusable for
  # liveness analysis.
  if not Tc::has? "Liveness" and not Tc::has? "Regalloc" then
    Tc::Target::frame_allocate(lir_fragments, target)
  end
  # Dump instructions.
  Tc::Target::instructions_dump(lir_fragments, target, Tc::Common::get_cout)
end

# Liveness analysis.
# FIXME: These statements generates files. Modify liveness so that it
# provides a way to dump the result to a stream instead.
# if Tc::has? "Liveness" then
#   Tc::Liveness::flowgraph_dump(filename, lir_fragments,
#                                Tc::Common::timer)
#   Tc::Liveness::liveness_dump(filename, lir_fragments, tempmap,
#                               Tc::Common::timer)
#   Tc::Liveness::interference_dump(filename, lir_fragments, tempmap,
#                                   Tc::Common::timer)
# end

# Register allocation.
if Tc::has? "Regalloc" then
  tempmap = Tc::Regalloc::allocate_registers(lir_fragments, target,
                                             tempmap, Tc::Common::timer)
  Tc::Temp::dump tempmap
end
