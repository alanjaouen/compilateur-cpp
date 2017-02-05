/**
 ** \file ast/record-exp.hxx
 ** \brief Inline methods of ast::RecordExp.
 */

#pragma once

#include <ast/record-exp.hh>

namespace ast
{


    inline const Exp&
    RecordExp::exp_get() const
    {
        return *exp_;
    }
    inline Exp&
    RecordExp::exp_get()
    {
        return *exp_;
    }
    inline const FieldInits&
    RecordExp::fini_get() const
    {
        return *vect_;
    }
    inline FieldInits&
    RecordExp::fini_get()
    {
        return *vect_;
    }


} // namespace ast

