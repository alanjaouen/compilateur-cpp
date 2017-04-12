/**
 ** \file tree/call.hh
 ** \brief Intermediate representation: call.hh
 **/

#pragma once

#include <vector>
#include <iosfwd>
#include <tree/exp.hh>

namespace tree
{

  class Call : public Exp
  {
  public:
    /** \brief Construct a call to a function.
     **
     ** \param func     Function called
     ** \param args     Arguments of the function, including static link
     **                 if required.
     */
    Call(const rExp& func, const std::vector<rExp>& args);

    /** \name Accessors.
     ** \{ */

    /// call_kind.
    kind_tree_type kind_get() const override;

    /** \} */

    /** \name Printing.
     ** \{ */

    std::ostream& tag_print(std::ostream&) const override;

    // Lists need a closer.
    std::ostream& dump(std::ostream& ostr) const override;

    /** \} */

  };

} // namespace tree
