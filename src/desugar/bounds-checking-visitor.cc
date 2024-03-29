/**
 ** \file desugar/bounds-checking-visitor.cc
 ** \brief Implementation of desugar::BoundsCheckingVisitor.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <parse/libparse.hh>
#include <desugar/bounds-checking-visitor.hh>
#include <misc/symbol.hh>

namespace desugar
{
  namespace
  {
    /// Return the name of the boxed type for \a s.
    std::string
    box(const misc::symbol& s)
    {
      return "_box_" + s.get();
    }
  }

  BoundsCheckingVisitor::BoundsCheckingVisitor()
    : super_type()
  {}

  /*-----------------------.
  | Array bounds checking.  |
  `-----------------------*/

  // FIXME: Some code was deleted here.

} // namespace desugar
