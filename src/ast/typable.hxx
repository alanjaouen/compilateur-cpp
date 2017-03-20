/**
 ** \file ast/typable.hxx
 ** \brief Inline methods of ast::Typable.
 */

#pragma once

#include <ast/typable.hh>

namespace ast
{

  // FIXED by forest_b
  inline void Typable::type_set(const type::Type* e)
  {
    type_ = e;
  }

  inline const type::Type* Typable::type_get() const
  {
    return type_;
  }

  
} // namespace ast

