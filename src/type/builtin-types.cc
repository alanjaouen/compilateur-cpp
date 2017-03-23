/**
 ** \file type/builtin-types.cc
 ** \brief Implementation for type/builtin-types.hh.
 */

#include <ostream>

#include <type/builtin-types.hh>
#include <type/visitor.hh>

namespace type
{

  // FIXME: Some code was deleted here (Void, Int, and String).

  void String::accept(ConstVisitor& v) const
  {
    v(*this);
  }
  void String::accept(Visitor& v)
  {
    v(*this);
  }
  // bool String::compatible_with(const Type& other) const
  // {
    
  // }

  const Type& String::actual() const
  {
    return String::instance();
  }
  void Int::accept(ConstVisitor& v) const
  {
    v(*this);
  }
  void Int::accept(Visitor& v)
  {
    v(*this);
  }
  // bool Int::compatible_with(const Type& other) const
  // {
    
  // }
  const Type& Int::actual() const
  {
    return Int::instance();
  }

  void Void::accept(ConstVisitor& v) const
  {
    v(*this);
  }
  void Void::accept(Visitor& v)
  {
    v(*this);
  }
  // bool Void::compatible_with(const Type& other) const
  // {
    
  // }
  const Type& Void::actual() const
  {
    return Void::instance();
  }
} // namespace type
