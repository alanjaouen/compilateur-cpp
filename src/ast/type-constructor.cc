/**
 ** \file ast/type-constructor.cc
 ** \brief Implementation of ast::TypeConstructor.
 */

#include <ast/type-constructor.hh>
#include <ast/visitor.hh>

namespace ast
{
// FIXED by forest_b
TypeConstructor::TypeConstructor()
  : new_type_(nullptr)
{
}
TypeConstructor::TypeConstructor(const type::Type* e)
  : new_type_(e)
{
}

TypeConstructor::~TypeConstructor()
{
  if (new_type_)
    delete new_type_;
}

} // namespace ast
