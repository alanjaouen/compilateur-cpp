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
  inline const RecordTy::field_list& rrecs_get() const
  {
    return recs_;
  }
  /// Return declarations.
  inline RecordTy::field_list& recs_get()
  {
    return recs_;
  }
  /** \} */
} // namespace ast

