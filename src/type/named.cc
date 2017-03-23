/**
 ** \file type/named.cc
 ** \brief Implementation for type/named.hh.
 */

#include <ostream>
#include <set>

#include <type/named.hh>
#include <type/visitor.hh>

namespace type
{
  Named::Named(misc::symbol name)
    : name_(name)
    , type_(nullptr)
  {}

  Named::Named(misc::symbol name, const Type* type)
    : name_(name)
  {
    type_set(type);
  }

  // FIXME: Some code was deleted here (Inherited functions).

  void Named::accept(ConstVisitor& v) const
  {
    v(*this);
  }
    /// Accept a non-const visitor \a v.
  void Named::accept(Visitor& v)
  {
    v(*this);
  }

  // FIXME: Some code was deleted here (Sound).
  bool Named::sound() const
  {
    return true;
  }
  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Named).
  bool Named::compatible_with(const Type& other) const
  {
    
  }

} // namespace type
