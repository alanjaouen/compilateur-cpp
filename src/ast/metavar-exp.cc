/**
 ** \file ast/metavar-exp.cc
 ** \brief Implementation of ast::MetavarExp.
 */

#include <ast/visitor.hh>
#include <ast/metavar-exp.hh>

namespace ast
{

  MetavarExp::MetavarExp(const Location& location, unsigned id)
    : Exp(location)
    , Metavariable(id)
  {}


  void
  MetavarExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  MetavarExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

