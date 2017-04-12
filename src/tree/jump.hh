/**
 ** \file tree/jump.hh
 ** \brief Declaration of tree::Jump.
 **/

#pragma once

#include <iosfwd>
#include <temp/fwd.hh>
#include <tree/stm.hh>
#include <tree/exp.hh>

namespace tree
{
  /// Inconditional branching.
  ///
  /// Our tree::Jump instruction is simpler than Appel's, which
  /// requires a list of all the possible destinations (for later
  /// dataflow analysis).  Our implementation assumes the expression
  /// used as a destination is always a tree::Name.  Therefore,
  /// tree::Name::label_get always returns a singleton list.
  class Jump : public Stm
  {
  public:
    Jump(const rExp& exp);

    /** \name Accessors.
     ** \{ */

    /// The destination.
    rExp exp_get() const;

    /// The list of destination labels.
    temp::label_list_type label_get() const;

    /// jump_kind.
    kind_tree_type kind_get() const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    /// Print JUMP.
    std::ostream& tag_print(std::ostream& ostr) const override;

    /** \} */

  };

} // namespace tree

#include <tree/jump.hxx>
