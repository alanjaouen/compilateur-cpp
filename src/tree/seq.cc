/**
 ** \file tree/seq.cc
 ** \brief Implementation for tree/seq.hh.
 **/

#include <ostream>

#include <misc/indent.hh>
#include <tree/seq.hh>
#include <tree/trees.hh>

namespace tree
{

  Seq::Seq(const tree_list_type& children)
    : Stm(children)
  {}

  Seq::Seq(const rStm& left, const rStm& right)
    : Stm()
  {
    emplace_back(left);
    emplace_back(right);
  }

  Seq::Seq(const rStm& left)
    : Stm()
  {
    emplace_back(left);
  }

  Seq::Seq(std::initializer_list<rStm> l)
    : Stm()
  {
    for (const rStm& p : l)
      emplace_back(p);
  }

  std::ostream&
  Seq::tag_print(std::ostream&) const
  {
    unreachable();
  }

  std::ostream&
  Seq::dump(std::ostream& ostr) const
  {
    return ostr << "seq"
                << misc::incendl
                << children_get()
                << misc::decendl
                << "seq end";
  }

  Tree::kind_tree_type
  Seq::kind_get() const
  {
    return seq_kind;
  }

} // namespace tree
