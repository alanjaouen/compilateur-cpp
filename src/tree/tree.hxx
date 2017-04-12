/**
 ** \file tree/tree.hxx
 ** \brief Inline implementation of tree::Tree.
 **/

#pragma once

#include <algorithm>
#include <iostream>

#include <misc/contract.hh>
#include <misc/ref.hh>
#include <tree/tree.hh>

namespace tree
{

  inline void
  Tree::child_emplace_back(const rTree& tree)
  {
    children_.emplace_back(tree);
    if (tree)
      tree->parent_set(this);
  }

  inline tree_list_type&
  Tree::children_get()
  {
    return children_;
  }

  inline const tree_list_type&
  Tree::children_get() const
  {
    return children_;
  }

  inline void
  Tree::child_set(rTree& dst, const rTree& src)
  {
    dst = src;
    if (src)
      src->parent_set(this);
  }

  // Start at 0, of course.
  inline rTree&
  Tree::child_get(int nth)
  {
    tree_list_type::iterator ichild = children_.begin();
    advance(ichild, nth);
    postcondition(*ichild);
    return *ichild;
  }

  inline rTree
  Tree::child_get(int nth) const
  {
    tree_list_type::const_iterator ichild = children_.begin();
    advance(ichild, nth);
    postcondition(*ichild);
    return *ichild;
  }

  inline rTree&
  Tree::left_get()
  {
    return child_get(0);
  }

  inline rTree&
  Tree::right_get()
  {
    return child_get(1);
  }

  inline Tree*
  Tree::parent_get()
  {
    return parent_;
  }

  inline const Tree*
  Tree::parent_get() const
  {
    return parent_;
  }

  inline void
  Tree::parent_set(Tree* parent)
  {
    parent_ = parent;
  }

  inline temp::Temp&
  Tree::asm_get()
  {
    if (not temp_)
      temp_ = new temp::Temp();
    return *temp_;
  }

  inline void
  Tree::asm_set(const temp::Temp& temp)
  {
    temp_ = new temp::Temp(temp);
  }

  inline void*
  Tree::state_get() const
  {
    return state_;
  }

  inline void*&
  Tree::state_get()
  {
    return state_;
  }

  inline bool
  Tree::reducible_get() const
  {
    return reducible_;
  }

  inline void
  Tree::reducible_set(bool b)
  {
    if (reducible_ == b)
      return;
    reducible_ = b;
    for (const rTree& tree : children_)
      tree->reducible_set(b);
  }

  inline std::ostream&
  operator<<(std::ostream& ostr, const Tree& tree)
  {
    return tree.dump(ostr);
  }

} // namespace tree
