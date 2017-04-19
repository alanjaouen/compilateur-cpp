/**
 ** \file tree/name.cc
 ** \brief Implementation for tree/name.hh.
 **/

#include <ostream>

#include <temp/label.hh>
#include <tree/name.hh>

namespace tree
{

  Name::Name(const temp::Label& label)
    : Exp()
    , label_(label)
  {}

  std::ostream&
  Name::tag_print(std::ostream& ostr) const
  {
    return ostr << "name " << label_;
  }

  Tree::kind_tree_type
  Name::kind_get() const
  {
    return name_kind;
  }

} // namespace tree
