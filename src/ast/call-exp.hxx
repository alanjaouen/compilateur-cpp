/**
 ** \file ast/call-exp.hxx
 ** \brief Inline methods of ast::CallExp.
 */

#pragma once

#include <ast/call-exp.hh>

namespace ast
{


    inline const Exp&
    CallExp::exp_get() const
    {
        return *exp_;
    }
    inline Exp&
    CallExp::exp_get()
    {
        return *exp_;
    }
    inline const FunctionDec&
    CallExp::fun_get() const
    {
        return *fun_;
    }
    inline FunctionDec&
    CallExp::fun_get()
    {
        return *fun_;
    }


} // namespace ast

