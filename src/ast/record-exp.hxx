/**
 ** \file ast/record-exp.hxx
 ** \brief Inline methods of ast::RecordExp.
 */

#pragma once

#include <ast/record-exp.hh>

namespace ast
{


    inline const NameTy&
    RecordExp::id_get() const
    {
        return *id_;
    }
    inline NameTy&
    RecordExp::id_get()
    {
        return *id_;
    }
    inline const fieldinits_type&
    RecordExp::fini_get() const
    {
        return *vect_;
    }
    inline fieldinits_type&
    RecordExp::fini_get()
    {
        return *vect_;
    }


} // namespace ast

