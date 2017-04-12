/**
 ** \file tree/const.hxx
 ** \brief Inline methods for tree/const.hh.
 **/

#pragma once

#include <tree/const.hh>

namespace tree
{

  inline const int&
  Const::value_get() const
  {
    return value_;
  }

} // namespace tree
