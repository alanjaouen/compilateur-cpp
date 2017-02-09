/**
 ** \file ast/if-exp.hxx
 ** \brief Inline methods of ast::IfExp.
 */

#pragma once

#include <ast/if-exp.hh>

namespace ast
{
  inline const Exp&
  IfExp::test_get() const
  {
    return *test_;
  }

  inline Exp&
  IfExp::test_get()
  {
    return *test_;
  }

  inline const Exp&
  IfExp::then_get() const
  {
    return *Bthen_;
  }

  inline Exp&
  IfExp::then_get()
  {
    return *Bthen_;
  }

  inline const Exp*
  IfExp::else_get() const
  {
    return Belse_;
  }

  inline Exp*
  IfExp::else_get()
  {
    return Belse_;
  }

} // namespace ast
