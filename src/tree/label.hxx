/**
 ** \file tree/label.hxx
 ** \brief Inline methods for tree/label.hh.
 **/

#pragma once

#include <tree/label.hh>

namespace tree
{

  inline temp::Label
  Label::label_get() const
  {
    return label_;
  }

} // namespace tree
