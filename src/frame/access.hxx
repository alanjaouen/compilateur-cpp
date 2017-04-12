/**
 ** \file frame/access.hxx
 ** \brief Inline methods for frame/access.hh.
 */

#pragma once

#include <frame/access.hh>

namespace frame
{

  inline
  temp::Temp
  InRegister::temp_get() const
  {
    return temp_;
  }

  inline
  int
  InFrame::offset_get() const
  {
    return offset_;
  }

} // namespace frame
