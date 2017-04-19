/**
 ** \file tree/tree.hh
 ** \brief Declaration of tree::Tree.
 **/

#pragma once

#include <iosfwd>

#include <temp/temp.hh>
#include <tree/fwd.hh>

// FIXME: This class is truly ugly and needs being reworked.  Pay
// attention to child_emplace_back and child_set, it is abnormal and they
// do more or less the same thing.

namespace tree
{

  class Tree
  {
  public:
    /// A fresh node.
    Tree();
    /// A new node with these \a children.
    Tree(const tree_list_type& children);
    /// Recursively destroy the children.
    virtual ~Tree();

    /// \name Kinds of Tree nodes.
    /// \{

    /// \brief The kinds of Tree instuctions.
    ///
    /// These flags are used to facilitate the pattern matching during
    /// instruction selection. This method is not very _clean_
    /// nevertheless this way is cleaner and more efficient than the
    /// use of dynamic_cast<>().
    enum kind_tree_type
      {
        const_kind, name_kind, temp_kind, binop_kind, mem_kind,
        call_kind, eseq_kind, move_kind, sxp_kind, jump_kind,
        cjump_kind, seq_kind, label_kind
      };

    /// The kind of this instruction.
    virtual kind_tree_type kind_get() const = 0;
    /// \}

    // All the children
    void child_emplace_back(const rTree& tree);
    tree_list_type& children_get();
    const tree_list_type& children_get() const;

    // Start at 0, of course.
    rTree& child_get(int nth);
    rTree child_get(int nth) const;
    rTree& left_get();
    rTree& right_get();

    // parent
    void parent_get_assert() const;
    Tree* parent_get();
    const Tree* parent_get() const;
    void parent_set(Tree* parent);

    // (in-place) replacement
    void replace_by(const rTree& tree);

    /// Report on \a o the kind of this instruction.
    virtual std::ostream& tag_print(std::ostream& o) const = 0;
    /// Report this instruction on \a o.
    virtual std::ostream& dump(std::ostream& o) const;

    // temp::Temp management for asm output.
    temp::Temp& asm_get();
    void asm_set(const temp::Temp& temp);

    // State management for asm output.
    void* state_get() const;
    void*& state_get();

    // Reduced state.
    bool reducible_get() const;
    void reducible_set(bool b);

  protected:
    friend std::ostream& operator<<(std::ostream& ostr, const Tree& tree);

    /// The arguments.
    tree_list_type children_;
    /// The Tree instruction this is a child from.
    Tree* parent_ = nullptr;
    /// The Temp for asm output.
    temp::Temp* temp_ = nullptr;
    /// The state for asm output.
    void* state_ = nullptr;
    /// Tell if the tree is reducible.
    bool reducible_ = true;

  private:
    void child_set(rTree& dst, const rTree& src);
  };

  /// Print \a t on \a o.
  std::ostream& operator<<(std::ostream& o, const Tree& t);
} // namespace tree

#include <tree/tree.hxx>
