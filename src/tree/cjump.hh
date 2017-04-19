/**
 ** \file tree/cjump.hh
 ** \brief Declaration of tree::Cjump.
 **/

#pragma once

#include <iosfwd>

#include <temp/fwd.hh>
#include <tree/stm.hh>
#include <tree/exp.hh>
#include <tree/label.hh>
#include <tree/name.hh>

namespace tree
{
  /// Conditional branching.
  class Cjump : public Stm
  {
  public:
    /// Comparison of the condition.
    enum Relop
    {
      eq,
      ne,
      lt,
      gt,
      le,
      ge,
      ult,
      ule,
      ugt,
      uge
    };

    /** \brief Construct a conditional jump.
     **
     ** \param relop    Comparison operator
     ** \param left     Left operand
     ** \param right    Right operand
     ** \param iftrue   Destination label in case of positive test
     ** \param iffalse  Destination label in case of negative test
     **/
    Cjump(Relop relop,
          const rExp& left, const rExp& right,
          const rName& iftrue, const rName& iffalse);

    /** \name Accessors.
     ** \{ */

    /// Left operand
    rExp left_get() const;
    /// Right operand
    rExp right_get() const;

    /// Destination label in case of positive test.
    temp::Label label_true_get() const;
    /// Destination label in case of negative test.
    temp::Label label_false_get() const;

    /// Destination label in case of negative test.
    void label_false_set(const temp::Label& false_label);

    /// List of destination labels.
    temp::label_list_type labels_get() const;

    /// cjump_kind.
    kind_tree_type kind_get() const override;

    /** \} */

    /// Flip the test/destinations of this CJump.
    void flip();

    /// Comparison operator.
    const Relop& relop_get() const;

    /** \name Printing.
     ** \{ */

    std::ostream& tag_print(std::ostream& ostr) const override;

    /** \} */

  private:
    /// The comparison operator.
    Relop relop_;
  };

  /// Return the Relop R defined by: (x r y) <=> (y R x)
  Cjump::Relop
  symmetrize(const Cjump::Relop& r);

  /// Print Relop \a r on \a ostr.
  std::ostream&
  operator<<(std::ostream& ostr, const Cjump::Relop& r);

} // namespace tree

#include <tree/cjump.hxx>
