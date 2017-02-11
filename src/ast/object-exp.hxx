/**
 ** \file ast/object-exp.hxx
 ** \brief Inline methods of ast::ObjectExp.
 */

#pragma once

#include <ast/object-exp.hh>

namespace ast
{

  inline const NameTy&
  ObjectExp::type_get() const
  {
    return *type_;
  }

  inline NameTy&
  ObjectExp::type_get()
  {
    return *type_;
  }

} // namespace ast

