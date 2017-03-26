/**
 ** \file ast/typable.cc
 ** \brief Implementation of ast::Typable.
 */

#include <ast/typable.hh>
#include <ast/visitor.hh>

namespace ast
{
// FIXED by forest_b
Typable::Typable(const type::Type* type)
  : type_(type)
{
}

} // namespace ast
