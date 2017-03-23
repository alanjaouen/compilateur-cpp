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
    std::set<const Type*> sept;
    auto a = this;
    while (a)
      {
	if (!sept.insert(a).second)
	  return false;
	a = dynamic_cast<const Named*>(a->type_);
      }
    return true;
  }

  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Named).
  bool Named::compatible_with(const Type& other) const
  {
    return type_->compatible_with(other);
  }

} // namespace type
