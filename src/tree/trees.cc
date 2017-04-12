/**
 ** \file tree/trees.cc
 ** \brief Intermediate representation: tree_list_type
 **/

#include <misc/indent.hh>
#include <misc/separator.hh>
#include <tree/tree.hh>
#include <tree/trees.hh>

namespace tree
{

  std::ostream&
  operator<<(std::ostream& o, const tree_list_type& t)
  {
    return o << misc::separate(t, misc::iendl);
  }

} // namespace tree
