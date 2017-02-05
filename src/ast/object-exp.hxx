/**
 ** \file ast/object-exp.hxx
 ** \brief Inline methods of ast::ObjectExp.
 */

#pragma once

#include <ast/object-exp.hh>

namespace ast
{

    inline const Exp& ObjectExp::exp_get() const
    {
        return *exp_;
    }
    inline Exp& ObjectExp::exp_get()
    {
        return *exp_;
    }
    inline const NameTy& ObjectExp::type_get() const
    {
        return *type_;
    }
    inline NameTy& ObjectExp::type_get()
    {
        return *type_;
    }

} // namespace ast

