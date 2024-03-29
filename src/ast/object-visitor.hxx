/**
 ** \file ast/object-visitor.hxx
 ** \brief Implementation for ast/object-visitor.hh.
 */

#pragma once

#include <ast/all.hh>
#include <ast/object-visitor.hh>
#include <misc/contract.hh>

namespace ast
{
template <template <typename> class Const>
GenObjectVisitor<Const>::GenObjectVisitor()
  : GenVisitor<Const>()
{
}

template <template <typename> class Const>
GenObjectVisitor<Const>::~GenObjectVisitor()
{
}

/*-------------------------------.
  | Object-related visit methods.  |
  `-------------------------------*/

template <template <typename> class Const>
void GenObjectVisitor<Const>::operator()(const_t<ClassTy>& e)
{
  e.super_get().accept(*this);
  e.decs_get().accept(*this);
}

template <template <typename> class Const>
void GenObjectVisitor<Const>::operator()(const_t<MethodDecs>& e)
{
  for (auto& method : e.decs_get())
  {
    method->accept(*this);
  }
}

template <template <typename> class Const>
void GenObjectVisitor<Const>::operator()(const_t<MethodDec>& e)
{
  for (auto& var : e.formals_get().decs_get())
    var->accept(*this);
  if (e.result_get() != nullptr)
    e.result_get()->accept(*this);
  if (e.body_get() != nullptr)
    e.body_get()->accept(*this);
}

template <template <typename> class Const>
void GenObjectVisitor<Const>::operator()(const_t<MethodCallExp>& e)
{
  e.lvalue_get().accept(*this);
  for (auto& exp : e.seq_get())
    exp->accept(*this);
}

template <template <typename> class Const>
void GenObjectVisitor<Const>::operator()(const_t<ObjectExp>& e)
{
  e.type_get().accept(*this);
}

} // namespace ast
