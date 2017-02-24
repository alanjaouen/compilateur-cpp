/**
 ** \file ast/break-exp.hxx
 ** \brief Inline methods of ast::BreakExp.
 */

#pragma once

#include <ast/break-exp.hh>

// Hint: this needs to be done at TC-3.


namespace ast
{
  inline const Exp*
  BreakExp::loop_get() const
  {
    return loop_;
  }

  inline Exp*
  BreakExp::loop_get()
  {
    return loop_;
  }

  inline void
  BreakExp::loop_set(Exp* loop)
  {
    this->loop_ = loop;
  }
} // namespace ast

