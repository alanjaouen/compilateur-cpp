/**
 ** \file tree/mem.hh
 ** \brief Intermediate representation: mem.hh
 **/

#pragma once

#include <iosfwd>
#include <tree/exp.hh>

namespace tree
{

  /** \brief Memory indirection.
   **
   ** Allow the access of the memory at a given address.
   */
  class Mem : public Exp
  {
  public:
    /** \brief Construct a memory indirection.
     **
     ** \param exp      Expression of accessed address.
     */
    Mem(const rExp& exp);

    /** \name Accessors.
     ** \{ */

    /// Accessed address.
    rExp exp_get() const;
    void exp_set(const rExp& exp);

    /// mem_kind.
    kind_tree_type kind_get() const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    std::ostream& tag_print(std::ostream& ostr) const override;

    /** \} */

  };

} // namespace tree

#include <tree/mem.hxx>
