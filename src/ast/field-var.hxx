/**
 ** \file ast/field-var.hxx
 ** \brief Inline methods of ast::FieldVar.
 */

#pragma once

#include <ast/field-var.hh>

namespace ast
{


    inline const Var&
    FieldVar::var_get() const
    {
        return *var_;
    }
    inline Var&
    FieldVar::var_get()
    {
        return *var_;
    }

    inline const Field&
    FieldVar::field_get() const
    {
        return *field_;
    }
    inline Field&
    FieldVar::field_get()
    {
        return *field_;
    }

} // namespace ast

