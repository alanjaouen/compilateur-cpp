/**
 ** \file ast/record-ty.hxx
 ** \brief Inline methods of ast::RecordTy.
 */

#pragma once

#include <ast/record-ty.hh>

namespace ast
{
  /** \name Accessors.
   ** \{ */
  /// Return declarations.
  inline const RecordTy::field_list&
  RecordTy::recs_get() const
  {
    return recs_;
  }
  /// Return declarations.
  inline RecordTy::field_list&
  RecordTy::recs_get()
  {
    return recs_;
  }
  /** \} */
} // namespace ast

