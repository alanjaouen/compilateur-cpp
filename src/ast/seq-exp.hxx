/**
 ** \file ast/seq-exp.hxx
 ** \brief Inline methods of ast::SeqExp.
 */

#pragma once

#include <ast/seq-exp.hh>

namespace ast
{

  inline const exps_type&
  SeqExp::seq_get() const
  {
    return *seq_;
  }
  inline exps_type&
  SeqExp::seq_get()
  {
    return *seq_;
  }

} // namespace ast

