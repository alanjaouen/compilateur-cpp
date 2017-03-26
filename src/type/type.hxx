/**
 ** \file type/type.hxx
 ** \brief Inline methods for type::Type.
 */
#pragma once

#include <type/type.hh>
#include <misc/contract.hh>

namespace type
{
  inline bool
  operator==(const Type& lhs, const Type& rhs)
  {
  // FIXED: (Alan) Some code was deleted here.
    return &lhs.actual() == &rhs.actual(); 
  }

  inline bool
  operator!=(const Type& lhs, const Type& rhs)
  {
  // FIXED by forest_b
    return !(lhs == rhs);
  }

} // namespace type
