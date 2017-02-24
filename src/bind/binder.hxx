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
  error_ << misc::error::bind << e.location_get() << ": undeclared "
         << k << ": " << e.name_get() << std::endl;
}
template <typename T>
void Binder::redefinition(const T& e1, const T& e2)
{
  error_ << misc::error::bind << e2.location_get()
         << "redefinition: " << e2.name_get() << std::endl
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
    using decs_type = ast::AnyDecs<D>;
    auto& cdecs = e.decs_get();
    for (auto i = cdecs.begin(); i != cdecs.end(); i++)
      {
        for(auto j = cdecs.begin(); j != i; j++)
          {
            if ((*j)->name_get().get() == (*i)->name_get().get())
              {
                redefinition(**j, **i);
                break;
              }
          }
        visit_dec_header<D>(**i);
      }
    for (auto& i : e.decs_get())
      visit_dec_body(*i);
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
}


template <>
inline void Binder::visit_dec_header<ast::VarDec>(ast::VarDec& e)
{
  var_scope_.put(e.name_get(), &e);
}

template <>
inline void Binder::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
{
  scope_begin();
  e.ty_get().accept(*this);
  scope_end();
}

template <>
inline void Binder::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
{
  scope_begin();
  decs_visit<ast::VarDec>(e.formals_get());
  auto result = e.result_get();//TODO : gerer les types
  if (result)
    result->accept(*this);
  auto body = e.body_get();
  if (body)
    body->accept(*this);
  scope_end();
}

template <>
inline void Binder::visit_dec_body<ast::VarDec>(ast::VarDec& e)
{
  scope_begin();
  if (e.type_name_get())
    e.type_name_get()->accept(*this);
  if (e.init_get())
    e.init_get()->accept(*this);
  scope_end();
}

} // namespace bind
