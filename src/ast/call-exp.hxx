/**
 ** \file ast/call-exp.hxx
 ** \brief Inline methods of ast::CallExp.
 */

#pragma once

#include <ast/call-exp.hh>

namespace ast
{

  /// Return the call expression.
  inline const SeqExp::seq_type&
  CallExp::seq_get() const
  {
    return *seq_;
  }

  /// Return the call expression.
  inline SeqExp::seq_type&
  CallExp::seq_get()
  {
    return *seq_;
  }

  /// Return the function name.
  inline const misc::symbol*
  CallExp::name_get() const
  {
    return name_;
  }

  /// Return the function name.
  inline misc::symbol*
  CallExp::name_get()
  {
    return name_;
  }
  /** \} */

} // namespace ast

