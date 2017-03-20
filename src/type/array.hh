/**
 ** \file type/array.hh
 ** \brief The class Array.
 */
#pragma once

#include <type/type.hh>
#include <type/fwd.hh>

namespace type
{

  /// Array types.
  class Array : public Type
  {
  // FIXME: fixed by Alan
  public:
    virtual ~Array() = default;
    Array(misc::symbol name, const Type& type);

    const Type& type_get() const;

	private:
    /// Array's type.
    const Type& type_;
  };

} // namespace type

#include <type/array.hxx>
