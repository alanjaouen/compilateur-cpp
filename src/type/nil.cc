/**
 ** \file type/nil.cc
 ** \brief Implementation for type/nil.hh.
 */

#include <type/visitor.hh>
#include <type/record.hh>
#include <type/nil.hh>
#include <type/class.hh>

#include <ostream>

namespace type
{

  /*------.
  | Nil.  |
  `------*/

  void
  Nil::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  Nil::accept(Visitor& v)
  {
    v(*this);
  }

  bool Nil::compatible_with(const Type& other) const
  {
  // FIXED: Some code was deleted here.
    return dynamic_cast<const Record*>(&other.actual());
  }

  const Type*
  Nil::record_type_get() const
  {
    return record_type_;
  }

  void
  Nil::set_record_type(const Type& type) const
  {
    record_type_ = &type;
  }

} // namespace type
