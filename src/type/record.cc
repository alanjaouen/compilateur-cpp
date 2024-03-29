/**
 ** \file type/record.cc
 ** \brief Implementation for type/record.hh.
 */

#include <ostream>

#include <algorithm>
#include <iterator>
#include <type/builtin-types.hh>
#include <type/nil.hh>
#include <type/record.hh>
#include <type/visitor.hh>

namespace type
{
void Record::accept(ConstVisitor& v) const
{
  v(*this);
}

void Record::accept(Visitor& v)
{
  v(*this);
}

// FIXED: Some code was deleted here (Field manipulators).
const Type* Record::field_type(const misc::symbol key) const
{
  for (const auto i : fields_)
  {
    if (i.name_get() == key)
      return &i.type_get();
  }
  return nullptr;
}

int Record::field_index(const misc::symbol key) const
{
  auto f = std::find_if(fields_.begin(), fields_.end(),
                        [key](Field f) { return f.name_get() == key; });
  auto pos = std::distance(fields_.begin(), f);
  if (pos > fields_.size())
    return -1;
  return pos;
}

// int
// field_index(const misc::symbol key)
// FIXED: Some code was deleted here (Special implementation of
// "compatible_with" for Record).
bool Record::compatible_with(const Type& other) const
{
  return &other == this || dynamic_cast<const Nil*>(&other);
}

} // namespace type
