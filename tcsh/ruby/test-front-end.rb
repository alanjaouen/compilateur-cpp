#! /usr/bin/env ruby

if ENV.has_key? "TCSH_RUBY_PATH"
  $:.concat ENV["TCSH_RUBY_PATH"].split(":")
end

if ARGV.size != 1
  puts "Usage: ti.rb file.tig"
  exit 1
end

require "tempfile"
require "tc"


# Parse the file.
lib = Tc::Misc::File_library.new()
ast = Tc::Parse::parse("builtin", ARGV[0], lib)

if Tc::has? "Bind" then
  Tc::Bind::bind ast
end

if Tc::has? "Type" then
  Tc::Type::types_check ast
end

if Tc::has? "Translate" then
  # Compute HIR.
  fragments = Tc::Translate::translate ast

  # Dump it.
  hir = Tempfile.new "hir"
  hir.print fragments
  hir.flush

  # Run havm on it.
  system("havm", hir.path)
  hir.close
end
