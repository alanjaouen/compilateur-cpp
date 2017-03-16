/**
 ** \file ast/type-constructor.hh
 ** \brief Declaration of ast::TypeConstructor.
 */

#pragma once

#include <type/fwd.hh>
#include <ast/fwd.hh>

namespace ast
{


  /** \class ast::TypeConstructor
   ** \brief Create a new type.
   */

  class TypeConstructor
  {
    void created_type_set (const type::Type*);
    const type::Type* created_type_get () const;
  };

} // namespace ast

#include <ast/type-constructor.hxx>

