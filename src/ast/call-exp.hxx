/**
 ** \file ast/call-exp.hxx
 ** \brief Inline methods of ast::CallExp.
 */

#pragma once

#include <ast/call-exp.hh>

namespace ast
{

  /// Return the call expression.
  inline const exps_type&
  CallExp::seq_get() const
  {
    return *seq_;
  }

  /// Return the call expression.
  inline exps_type&
  CallExp::seq_get()
  {
    return *seq_;
  }

  /// Return the function name.
  inline const misc::symbol&
  CallExp::name_get() const
  {
    return name_;
  }

  /// Return the function name.
  inline misc::symbol&
  CallExp::name_get()
  {
    return name_;
  }

  inline void
  CallExp::name_set(const misc::symbol& symbol)
  {
    name_ = symbol;
  }

  /// Return definition site.
  inline const FunctionDec*
  CallExp::def_get() const
  {
    return def_;
  }
  /// Return definition site.
  inline FunctionDec*
  CallExp::def_get()
  {
    return def_;
  }
  /// Set definition site.
  inline void
  CallExp::def_set(FunctionDec* def)
  {
    def_ = def;
  }
/** \} */

} // namespace ast

