/**
 ** \file tree/stm.hh
 ** \brief Intermediate representation: stm.hh
 **/

#pragma once

#include <tree/tree.hh>

namespace tree
{

  /** \brief Node that has no value, contrary to \a Exp.
   ** \see tree::Exp.
   */
  class Stm : public Tree
  {
  public:
    Stm(const tree_list_type& children) :
      Tree(children)
    {}

    Stm() = default;

    virtual ~Stm() = default;
  };

} // namespace tree
