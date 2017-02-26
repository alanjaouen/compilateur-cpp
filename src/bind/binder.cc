/**
 ** \file bind/binder.cc
 ** \brief Implementation for bind/binder.hh.
 */

#include <misc/contract.hh>

#include <ast/all.hh>
#include <bind/binder.hh>

namespace bind
{
  bool Binder::is_test = false;

  /*-----------------.
  | Error handling.  |
  `-----------------*/

  /// The error handler.
  const misc::error&
  Binder::error_get() const
  {
    return error_;
  }

  //fixed caradi_c
  void Binder::break_outside_loop(ast::BreakExp& e)
  {
      error_ << misc::error::bind << e.location_get() << ": break outside loop "
             << std::endl;

  }

  /*----------------.
  | Symbol tables.  |
  `----------------*/

  void
  Binder::scope_begin()
  {
    type_scope_.scope_begin();
    function_scope_.scope_begin();
    var_scope_.scope_begin();
  }

  void
  Binder::scope_end()
  {
    type_scope_.scope_end();
    function_scope_.scope_end();
    var_scope_.scope_end();
  }

  /*---------.
  | Visits.  |
  `---------*/

  // FIXME: Some code was deleted here.
  Binder::Binder()
  {
    scope_begin();
  }
  
  Binder::~Binder()
  {
    scope_end();
  }
  
  void
  Binder::operator()(ast::LetExp& e)
  {
    scope_begin();
    e.decs_get().accept(*this);
    e.seq_get().accept(*this);
    scope_end();
  }

  void Binder::operator()(ast::ForExp& e)
  {
    scope_begin();
    loop_scope_.push(&e);
    var_scope_.put(e.vardec_get().name_get(), &(e.vardec_get()));
    e.vardec_get().accept(*this);
    e.hi_get().accept(*this);
    e.body_get().accept(*this);
    loop_scope_.pop();
    scope_end();
  }

  void Binder::operator()(ast::WhileExp& e)
  {
    scope_begin();
    loop_scope_.push(&e);
    Binder::is_test=true;
    e.test_get().accept(*this);
    Binder::is_test=false;
    e.body_get().accept(*this);
    loop_scope_.pop();
    scope_end();
  }

  void Binder::operator()(ast::BreakExp& e)
  {
    if (Binder::is_test)
      break_outside_loop(e);
    if (loop_scope_.empty())
      break_outside_loop(e);
    auto res = loop_scope_.top();
    e.loop_set(res);
  }

  void Binder::operator()(ast::CallExp& e)
  {
    auto res = function_scope_.get(e.name_get());
    if (!res)
      undeclared("function", e);
    else
      {
        e.def_set(res);
        for (auto& i : e.seq_get())
          i->accept(*this);
      }
  }

  void Binder::operator()(ast::SimpleVar& e)
  {
    std::cout << "simple\n" << std::endl;
    auto* res = var_scope_.get(e.name_get());
    if (!res)
      undeclared("variable", e);
    else
      e.def_set(res);
  }

  // void Binder::operator()(ast::Field& e)
  // {
  //   auto* res = type_scope_.get(e.name_get());
  //   if (!res)
  //     undeclared("type", e);
  //   else
  //     e.def_set(res);
  // }

  void Binder::operator()(ast::NameTy& e)
  {
    auto res = type_scope_.get(e.name_get());
    if (e.name_get().get() == "string" || e.name_get().get() == "int")
    {
      e.def_set(nullptr);
      return;
    }
    if (!res)
      undeclared("type", e);
    else
      e.def_set(res);
  }

  // void Binder::operator()(ast::ArrayTy& e)
  // {
  //   e.base_type_get().accept(*this);
  // }

  // void Binder::operator()(ast::ArrayExp& e)
  // {
  //   e.type_get().accept(*this);
  //   e.l_exp_get().accept(*this);
  //   e.r_exp_get().accept(*this);
  // }

  // void Binder::operator()(ast::Field& e)
  // {
  //   e.type_name_get().accept(*this);
  // }

  // void Binder::operator()(ast::ClassTy& e)
  // {
  //   if (e.super_get())
  //     e.super_get()->accept(*this);
  //   e.decs_get().accept(*this);
  // }

  void
  Binder::operator()(ast::DecsList& e)
  {
    for (auto& i : e.decs_get())
      i->accept(*this);
  }

  /*-------------------.
  | Visiting VarDecs.  |
  `-------------------*/

  void
  Binder::operator()(ast::VarDecs& e)
  {
    decs_visit<ast::VarDec>(e);
  }


  /*------------------------.
  | Visiting FunctionDecs.  |
  `------------------------*/

  void
  Binder::operator()(ast::FunctionDecs& e)
  {
    decs_visit<ast::FunctionDec>(e);
  }


  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/

  void
  Binder::operator()(ast::TypeDecs& e)
  {
    decs_visit<ast::TypeDec>(e);
  }

  
} // namespace bind
