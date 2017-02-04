/**
 ** \file ast/let-exp.hxx
 ** \brief Inline methods of ast::LetExp.
 */

#pragma once

#include <ast/let-exp.hh>

namespace ast
{
  inline
  const DecsList&
  LetExp::decs_get() const
  {
    return *decs_;
  }

  inline DecsList&
  LetExp::decs_get()
  {
    return *decs_;
  }

  inline const SeqExp&
  LetExp::seq_get() const
  {
    return *seq_;
  }

  inline SeqExp&
  LetExp::seq_get()
  {
    return *seq_;
  }

} // namespace ast

