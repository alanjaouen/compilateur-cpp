/**
 ** \file ast/assign-exp.cc
 ** \brief Implementation of ast::AssignExp.
 */

#include <ast/visitor.hh>
#include <ast/assign-exp.hh>

namespace ast
{
  AssignExp::AssignExp(Location& location, Var* lvalue, Exp* exp)
    : Exp(location)
    , lvalue_(lvalue)
    , exp_(exp)
  {}
  AssignExp::~AssignExp()
    {
      delete lvalue_;
      delete exp_;
    }
  
  void
  AssignExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  AssignExp::accept(Visitor& v)
  {
    v(*this);
  }


} // namespace ast

