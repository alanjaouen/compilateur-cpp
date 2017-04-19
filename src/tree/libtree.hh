/**
 ** \file tree/libtree.hh
 ** \brief Intermediate representation: Tree.
 */

#pragma once

#include <iostream> // std::cout

#include <tree/fwd.hh>

/// (Low/High) intermediate code.
namespace tree
{

  /// Display a list of fragments, by default on \a std::cout.
  std::ostream&
  dump(const tree::Fragments& fragments, std::ostream& ostr = std::cout);
} // namespace tree
