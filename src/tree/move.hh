/**
 ** \file tree/move.hh
 ** \brief Intermediate representation: move.hh
 **/

#pragma once

#include <iosfwd>
#include <tree/stm.hh>
#include <tree/exp.hh>

namespace tree
{

  /// \brief Copy the content of the second operand to the first operand.
  class Move : public Stm
  {
  public:
    /** \brief Build a Move node.
     **
     ** \param dst      Memory indirection or register.
     ** \param src      Direct value, register or memory indirection.
     */
    Move(const rExp& dst, const rExp& src);

    /** \name Accessors.
     ** \{ */

    /// Destination.
    rExp dst_get() const;

    /// Source.
    rExp src_get() const;

    /// move_kind.
    kind_tree_type kind_get() const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    std::ostream& tag_print(std::ostream& ostr) const override;

    /** \} */

  };

} // namespace tree

#include <tree/move.hxx>
