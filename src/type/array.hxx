/**
 ** \file type/array.hxx
 ** \brief Inline methods for type::Array.
 */
#pragma once

#include <type/array.hh>
#include <misc/contract.hh>

namespace type
{
  // FIXED: (alan) Some code was deleted here (Ctor & Dtor).

  inline const Type&
  Type::type_get() const
  {
    return type_;
  }
} // namespace type
