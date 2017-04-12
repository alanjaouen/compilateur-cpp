/**
 ** \file tree/seq.hxx
 ** \brief Inline methods for tree/seq.hh.
 **/

#pragma once

#include <tree/seq.hh>

namespace tree
{

  inline void
  Seq::emplace_back(const rStm& stm)
  {
    child_emplace_back(stm);
  }

} // namespace tree
