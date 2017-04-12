/**
 ** \file tree/const.hh
 ** \brief Intermediate representation: const.hh
 **/

#pragma once

#include <iosfwd>
#include <tree/exp.hh>

namespace tree
{

  class Const : public Exp
  {
  public:
    /// Build a constant integer value.
    explicit Const(int value);

    /** \name Accessors.
     ** \{ */

    /// Return constant integer value.
    const int& value_get() const;

    /// const_kind.
    kind_tree_type kind_get() const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    std::ostream& tag_print(std::ostream& ostr) const override;

    /** \} */

  private:
    const int value_;
  };

} // namespace tree

#include <tree/const.hxx>
