/**
 ** \file ast/escapable.hxx
 ** \brief Inline methods of ast::Escapable.
 */

#pragma once

#include <ast/escapable.hh>

namespace ast
{

  // FIXME: Some code was deleted here.
	
  inline bool
  Escapable::is_escaped_get() const
  {
    return is_escaped_;
  }
  inline bool
  Escapable::is_escaped_get()
  {
    return is_escaped_;
  }
  inline void
  Escapable::is_escaped_set(bool bo)
  {
    this->is_escaped_ = bo;
  }

} // namespace ast

