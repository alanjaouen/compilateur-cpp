/**
 ** \file ast/rule-dec.hxx
 ** \brief Inline methods of ast::RuleDec.
 */

#pragma once

#include <ast/rule-dec.hh>

namespace ast
{


  inline const Exp&
  RuleDec::match_get() const
  {
    return *match_;
  }
  inline Exp&
  RuleDec::match_get()
  {
    return *match_;
  }

  inline const Exp&
  RuleDec::build_get() const
  {
    return *build_;
  }
  inline Exp&
  RuleDec::build_get()
  {
    return *build_;
  }


} // namespace ast

