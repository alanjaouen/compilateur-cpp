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
  inline const fields_type&
  RecordTy::recs_get() const
  {
    return *vect_;
  }
  /// Return declarations.
  inline fields_type&
  RecordTy::recs_get()
  {
    return *vect_;
  }
  /** \} */
} // namespace ast

