/**
 ** \file tree/iterator.hxx
 ** \brief Implementation for tree/iterator.hh.
 **/

#pragma once

#include <tree/iterator.hh>
#include <misc/contract.hh>

namespace tree
{

  inline
  Iterator::Iterator(const rTree& entry)
    : entry_(entry)
  {}

  inline void
  Iterator::first()
  {
    list_.clear();
    list_.emplace_back(entry_);
  }

  inline bool
  Iterator::is_ok() const
  {
    return !list_.empty();
  }

  inline rTree
  Iterator::tree_get() const
  {
    precondition(is_ok());
    return list_.back();
  }

  inline void
  Iterator::next()
  {
    rTree cur_tree = tree_get();
    const tree_list_type& children = cur_tree->children_get();
    list_.pop_back();

    // Push all the children of this tree onto the stack, leaving
    // the leftmost child on the top.
    for (tree_list_type::const_reverse_iterator ichild = children.rbegin();
         ichild != children.rend();
         ++ichild)
      list_.emplace_back(*ichild);
  }

} // namespace tree
