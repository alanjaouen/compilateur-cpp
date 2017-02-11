/**
 ** \file ast/object-exp.cc
 ** \brief Implementation of ast::ObjectExp.
 */

#include <ast/visitor.hh>
#include <ast/object-exp.hh>

namespace ast
{

  ObjectExp::ObjectExp(const Location& location, Exp* exp, NameTy* type)
    : Exp(location)
    , exp_(exp)
    , type_(type)
  {}

  ObjectExp::~ObjectExp()
  {
    delete exp_;
    delete type_;
  }

} // namespace ast

