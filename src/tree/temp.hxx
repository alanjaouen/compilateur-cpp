/**
 ** \file tree/temp.hxx
 ** \brief Inline methods for tree/temp.hh.
 **/

#pragma once

#include <tree/temp.hh>

namespace tree
{

  inline temp::Temp
  Temp::temp_get() const
  {
    return temp_;
  }

} // namespace tree
