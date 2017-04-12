/**
 ** \file tree/eseq.hh
 ** \brief Intermediate representation: eseq.hh
 **/

#pragma once

#include <iosfwd>
#include <tree/exp.hh>
#include <tree/stm.hh>
#include <tree/seq.hh>

namespace tree
{

  class Eseq : public Exp
  {
  public:
    /** \brief Build a list of expressions.
     **
     ** \param stm      Statement list
     ** \param exp      Last expression
     */
    Eseq(const rStm& stm, const rExp& exp);

    /** \name Accessors.
     ** \{ */

    /// Statement list
    rStm stm_get() const;

    /// Last expression
    rExp exp_get() const;

    /// eseq_kind.
    kind_tree_type kind_get() const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    std::ostream& tag_print(std::ostream&) const override;
    std::ostream& dump(std::ostream& ostr) const override;

    /** \} */

  };

} // namespace tree

#include <tree/eseq.hxx>
