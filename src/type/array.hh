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
  // FIXED: fixed by Alan
  public:
    virtual ~Array() = default;
    Array(const Type& type);

    void accept(ConstVisitor& v) const override;
    
    void accept(Visitor& v) override;

    const Type& type_get() const;
    
  private:
    /// Array's type.
    const Type& type_;
  };

} // namespace type

#include <type/array.hxx>
