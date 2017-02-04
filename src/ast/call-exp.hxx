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


} // namespace ast

