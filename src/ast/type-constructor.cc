/**
 ** \file ast/type-constructor.cc
 ** \brief Implementation of ast::TypeConstructor.
 */

#include <ast/visitor.hh>
#include <ast/type-constructor.hh>

namespace ast
{
  // FIXED by forest_b
  TypeConstructor::TypeConstructor()
      : new_type_(nullptr)
      {}
  TypeConstructor::TypeConstructor(const type::Type* e)
      : new_type_(e)
      {}

} // namespace ast

