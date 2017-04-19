/**
 ** \file tree/tree.cc
 ** \brief Implementation of tree::Tree.
 **/

#include <iostream>

#include <misc/algorithm.hh>
#include <misc/indent.hh>
#include <tree/tree.hh>
#include <tree/trees.hh>


namespace tree
{

  Tree::Tree(const tree_list_type& children)
    : children_(children)
  {}

  Tree::Tree()
    : children_()
  {}

  Tree::~Tree()
  {
    delete temp_;
  }

  void
  Tree::parent_get_assert() const
  {
    if (parent_ == nullptr)
      {
        std::cerr
          << "This tree has no parent:"
          << misc::incendl
          << *this
          << misc::decindent;
        precondition(parent_ != nullptr);
      }
  }

  void
  Tree::replace_by(const rTree& tree)
  {
    parent_get_assert();
    precondition(tree);
    precondition(tree != this);

    // Find who we are for our parent.
    tree_list_type& siblings = parent_->children_;
    tree_list_type::iterator me = misc::find(siblings, this);

    assertion(me != siblings.end());

    parent_->child_set(*me, tree);
    this->parent_ = nullptr;
  }

  std::ostream&
  Tree::dump(std::ostream& o) const
  {
    tag_print(o);
    if (!children_.empty())
      o << misc::incendl
        << children_
        << misc::decindent;
    return o;
  }

} // namespace tree
