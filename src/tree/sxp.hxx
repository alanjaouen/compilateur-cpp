/**
 ** \file tree/sxp.hxx
 ** \brief Inline methods for tree/sxp.hh.
 **/

#pragma once

#include <tree/sxp.hh>

namespace tree
{

  inline rExp
  Sxp::exp_get() const
  {
    return child_get(0).cast<Exp>();
  }

} // namespace tree
