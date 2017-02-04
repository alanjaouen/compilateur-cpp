/**
 ** \file ast/break-exp.cc
 ** \brief Implementation of ast::BreakExp.
 */

#include <ast/visitor.hh>
#include <ast/break-exp.hh>

namespace ast
{
  BreakExp::BreakExp(const Location& location) : Exp(location)
  {}

  BreakExp::~BreakExp()
  {}

  void
  BreakExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  BreakExp::accept(Visitor& v)
  {
    v(*this);
  }

  // FIXME: Some code was deleted here.

} // namespace ast

