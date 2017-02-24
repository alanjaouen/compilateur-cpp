/**
 ** \file ast/method-call-exp.hxx
 ** \brief Inline methods of ast::MethodCallExp.
 */

#pragma once

#include <ast/method-call-exp.hh>

namespace ast
{

    inline const Exp&
    MethodCallExp::lvalue_get() const
    {
      return *lvalue_;
    }

    inline Exp&
    MethodCallExp::lvalue_get()
    {
      return *lvalue_;
    }

} // namespace ast

