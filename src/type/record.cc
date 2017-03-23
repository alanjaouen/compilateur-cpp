/**
 ** \file type/record.cc
 ** \brief Implementation for type/record.hh.
 */

#include <ostream>

#include <type/builtin-types.hh>
#include <type/visitor.hh>
#include <type/record.hh>
#include <type/nil.hh>

namespace type
{

  void
  Record::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  Record::accept(Visitor& v)
  {
    v(*this);
  }

  // FIXME: Some code was deleted here (Field manipulators).
  // const Type*
  // field_type(const misc::symbol key)
  // {
  //   for (auto i : fields_)
  //     {
  //       if (i.name_get() == key)
  //         return i.type_get();
  //     }
  //   throw "record.cc:field_type: search not found\n";
  // }

  // int
  // field_index(const misc::symbol key)
  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Record).
  bool
  Record::compatible_with(const Type& other) const
  {
    return &other == this || dynamic_cast<const Nil*>(&other);
  }

  
} // namespace type
