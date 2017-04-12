/**
 ** \file tree/trees.hh
 ** \brief Intermediate representation: tree_list_type
 **/

#pragma once

#include <tree/fwd.hh>

namespace tree
{
  /// Print \a t on \a o.
  std::ostream& operator<<(std::ostream& o, const tree_list_type& t);
} // namespace tree
