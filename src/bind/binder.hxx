/**
 ** \file bind/binder.hxx
 ** \brief Inline methods of bind::Binder.
 **/

#pragma once

#include <bind/binder.hh>

namespace bind
{
/*-----------------.
| Error handling.  |
`-----------------*/

// FIXED by forest_b
template <typename T>
void Binder::undeclared(const std::string& k, const T& e)
{
  error_ << misc::error::bind << e.location_get() << "undeclared" << k
         << e.name_get() << std::endl;
}
template <typename T>
void Binder::redefinition(const T& e1, const T& e2)
{
  error_ << misc::error::bind << e2.location_get()
         << "redefinition:" << e2.name_get() << std::endl
         << e1.location_get() << "first definiton" << std::endl;
}

/*-------------------.
| Definition sites.  |
`-------------------*/

// FIXME: Some code was deleted here.

/*------------------.
| Visiting /Decs/.  |
`------------------*/

template <class D>
void Binder::decs_visit(ast::AnyDecs<D>& e)
{
  // Shorthand.
  // using decs_type = ast::AnyDecs<D>;
  for (auto& i : e.decs_get())
  {
    visit_dec_header(*i);
    visit_dec_body(*i);
  }
}

/* These specializations are in bind/binder.hxx, so that derived
   visitors can use them (otherwise, they wouldn't see them).  */

template <>
inline void Binder::visit_dec_header<ast::TypeDec>(ast::TypeDec& e)
{
  type_scope_.put(e.name_get(), &e);
  e.ty_get().accept(*this);
}

template <>
inline void Binder::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
{
  function_scope_.put(e.name_get(), &e);
  decs_visit(e.formals_get());
  if (e.result_get())
    e.result_get()->accept(*this);
}

template <>
inline void Binder::visit_dec_header<ast::VarDec>(ast::VarDec& e)
{
  Var_scope_.put(e.name_get(), &e);
}

template <>
inline void Binder::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
{
}

template <>
inline void Binder::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
{
  super_type::operator()(e);
}

template <>
inline void Binder::visit_dec_body<ast::VarDec>(ast::VarDec& e)
{
  e.accept(*this);
}

} // namespace bind
