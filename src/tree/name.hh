/**
 ** \file tree/name.hh
 ** \brief Intermediate representation: name.hh
 **/

#pragma once

#include <iosfwd>

#include <tree/exp.hh>
#include <tree/label.hh>
#include <temp/label.hh>

namespace tree
{

  class Name : public Exp
  {
  public:
    /// Build a reference to \a label.
    Name(const temp::Label& label);

    /** \name Accessors.
     ** \{ */

    /// Referenced label.
    temp::Label label_get() const;

    /// name_kind.
    kind_tree_type kind_get() const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    std::ostream& tag_print(std::ostream& ostr) const override;

    /** \} */

  private:
    /// Referenced label.
    temp::Label label_;
  };

} // namespace tree

#include <tree/name.hxx>
