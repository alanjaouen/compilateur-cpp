/**
 ** \file ast/exp.hxx
 ** \brief Inline methods of ast::Exp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{

  inline bool
  Exp::is_test_get()
  {
    return is_test_;
  }

  inline void
  Exp::is_test_set(bool is_test)
  {
    is_test_ = is_test_;
  }

} // namespace ast

