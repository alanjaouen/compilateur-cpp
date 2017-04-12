/**
 ** \file tree/const.cc
 ** \brief Implementation for tree/const.hh.
 **/

#include <ostream>

#include <tree/const.hh>

namespace tree
{

  Const::Const(int value)
    : value_(value)
  {}

  std::ostream&
  Const::tag_print(std::ostream& ostr) const
  {
    return ostr << "const " << value_;
  }

  Tree::kind_tree_type
  Const::kind_get() const
  {
    return const_kind;
  }

} // namespace tree
