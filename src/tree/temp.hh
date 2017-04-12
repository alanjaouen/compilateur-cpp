/**
 ** \file tree/temp.hh
 ** \brief Declaration of tree::Temp.
 **/

#pragma once

#include <iosfwd>

#include <temp/fwd.hh>
#include <tree/exp.hh>
#include <temp/temp.hh>

namespace tree
{

  /// An Exp for a temporary (pseudo register).
  class Temp : public Exp
  {
  public:
    /// Build a node representing the temporary \a temp.
    Temp(const temp::Temp& temp);

    /** \name Accessors.
     ** \{ */

    /// Pseudo register.
    temp::Temp temp_get() const;

    /// Temp kind.
    kind_tree_type kind_get() const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    std::ostream& tag_print(std::ostream& ostr) const override;

    /** \} */

  private:
    /// Pseudo register.
    temp::Temp temp_;
  };

} // namespace temp

#include <tree/temp.hxx>
