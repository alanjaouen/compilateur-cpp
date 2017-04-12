/**
 ** \file tree/jump.hxx
 ** \brief Inline implementation of tree::Jump.
 **/

#pragma once

#include <tree/jump.hh>
#include <tree/name.hh>
#include <temp/label.hh>

namespace tree
{

  inline rExp
  Jump::exp_get() const
  {
    return child_get(0).cast<Exp>();
  }

  inline
  temp::label_list_type
  Jump::label_get() const
  {
    return { child_get(0).cast<Name>()->label_get() };
  }

} //namespace tree
