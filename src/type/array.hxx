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
  Array::type_get() const
  {
    return type_;
  }

  
  inline void
  Array::accept(ConstVisitor& v) const
  {
    // v(*this);
  }
    /// Accept a non-const visitor \a v.
  inline void
  Array::accept(Visitor& v)
  {
    // v(*this);
  }

} // namespace type
