/**
 ** \file tree/jump.cc
 ** \brief Implementation of tree::Jump.
 **/

#include <ostream>

#include <tree/jump.hh>

namespace tree
{

  Jump::Jump(const rExp& exp)
    : Stm()
  {
    child_emplace_back(exp);
  }

  std::ostream&
  Jump::tag_print(std::ostream& ostr) const
  {
    return ostr << "jump";
  }

  Tree::kind_tree_type
  Jump::kind_get() const
  {
    return jump_kind;
  }

} // namespace tree
