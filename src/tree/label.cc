/**
 ** \file tree/label.cc
 ** \brief Implementation for tree/label.hh
 **/

#include <ostream>
#include <temp/label.hh>
#include <tree/label.hh>

namespace tree
{

  Label::Label(const temp::Label& label)
    : Stm()
    , label_(label)
  {}

  std::ostream&
  Label::tag_print(std::ostream& ostr) const
  {
    return ostr << "label " << label_;
  }

  Tree::kind_tree_type
  Label::kind_get() const
  {
    return label_kind;
  }

} // namespace tree
