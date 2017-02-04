/**
 ** \file ast/array-exp.hxx
 ** \brief Inline methods of ast::ArrayExp.
 */

#pragma once

#include <ast/array-exp.hh>

namespace ast
{

  inline const NameTy&
  ArrayExp::type_get() const
  {
    return *type_;
  }
  inline NameTy&
  ArrayExp::type_get()
  {
    return *type_;
  }
  inline const Exp&
  ArrayExp::l_exp_get() const
  {
    return *l_exp_;
  }
  inline Exp&
  ArrayExp::l_exp_get()
  {
    return *l_exp_;
  }
  inline const Exp&
  ArrayExp::r_exp_get() const
  {
    return *r_exp_;
  }
  inline Exp&
  ArrayExp::r_exp_get()
  {
    return *r_exp_;
  }

} // namespace ast

