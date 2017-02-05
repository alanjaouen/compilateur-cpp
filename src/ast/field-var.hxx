/**
 ** \file ast/field-var.hxx
 ** \brief Inline methods of ast::FieldVar.
 */

#pragma once

#include <ast/field-var.hh>

namespace ast
{


  inline const Var&
  FieldVar::lvalue_get() const
  {
    return *lvalue_;
  }
  inline Var&
  FieldVar::lvalue_get()
  {
    return *lvalue_;
  }

  inline const misc::symbol&
  FieldVar::name_get() const
  {
    return *name_;
  }
  inline misc::symbol&
  FieldVar::name_get()
  {
    return *name_;
  }

} // namespace ast

