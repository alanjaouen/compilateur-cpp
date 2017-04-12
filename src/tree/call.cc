/**
 ** \file tree/call.cc
 ** \brief Implementation for tree/call.hh.
 **/

#include <misc/indent.hh>
#include <tree/call.hh>
#include <tree/trees.hh>

namespace tree
{

  Call::Call(const rExp& func, const std::vector<rExp>& args)
    : Exp()
  {
    child_emplace_back(func);

    for (const rExp& exp : args)
      child_emplace_back(exp);
  }

  std::ostream&
  Call::tag_print(std::ostream&) const
  {
    unreachable();
  }

  std::ostream&
  Call::dump(std::ostream& ostr) const
  {
    return ostr << "call"
                << misc::incendl
                << children_get()
                << misc::decendl
                << "call end";
  }

  Tree::kind_tree_type
  Call::kind_get() const
  {
    return call_kind;
  }

} // namespace tree
