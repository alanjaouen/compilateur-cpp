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
  public:
    TypeConstructor();
    TypeConstructor(const type::Type* e);
    virtual  ~TypeConstructor() = default;
    void created_type_set (const type::Type*);
    const type::Type* created_type_get () const;
  private:
    const type::Type* new_type_;
  };

} // namespace ast

#include <ast/type-constructor.hxx>

