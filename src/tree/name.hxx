/**
 ** \file tree/name.hxx
 ** \brief Inline methods for tree/name.hh.
 **/

#pragma once

#include <tree/name.hh>

namespace tree
{

  inline temp::Label
  Name::label_get() const
  {
    return label_;
  }

} // namespace tree
