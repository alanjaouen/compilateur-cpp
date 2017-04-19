/**
 ** \file tree/eseq.hxx
 ** \brief Inline methods for tree/eseq.hh.
 **/

#pragma once

#include <tree/eseq.hh>

namespace tree
{

  inline rStm
  Eseq::stm_get() const
  {
    return child_get(0).cast<Stm>();
  }

  inline rExp
  Eseq::exp_get() const
  {
    return child_get(1).cast<Exp>();
  }

} // namespace tree
