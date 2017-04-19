/**
 ** \file tree/mem.hxx
 ** \brief Inline methods for tree/mem.hh.
 **/

#pragma once

#include <tree/mem.hh>

namespace tree
{

  inline rExp
  Mem::exp_get() const
  {
    return child_get(0).cast<Exp>();
  }

  inline void
  Mem::exp_set(const rExp& exp)
  {
    children_.pop_back();
    children_.emplace_back(exp);
  }

} // namespace tree
