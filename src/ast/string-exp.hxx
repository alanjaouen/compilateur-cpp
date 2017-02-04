/**
 ** \file ast/string-exp.hxx
 ** \brief Inline methods of ast::StringExp.
 */

#pragma once

#include <ast/string-exp.hh>

namespace ast
{
  inline std::string&
  StringExp::value_get() const
  {
    return str_;
  }
} // namespace ast

