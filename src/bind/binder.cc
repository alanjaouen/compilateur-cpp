/**
 ** \file bind/binder.cc
 ** \brief Implementation for bind/binder.hh.
 */

#include <misc/contract.hh>

#include <ast/all.hh>
#include <bind/binder.hh>

namespace bind
{

  /*-----------------.
  | Error handling.  |
  `-----------------*/

  /// The error handler.
  const misc::error&
  Binder::error_get() const
  {
    return error_;
  }

  // FIXME: Some code was deleted here (Error reporting).

  /*----------------.
  | Symbol tables.  |
  `----------------*/


  void
  Binder::scope_begin()
  {
    type_scope_.scope_begin();
    function_scope_.scope_begin();
    Var_scope_.scope_begin();
  }

  void
  Binder::scope_end()
  {
    type_scope_.scope_end();
    function_scope_.scope_end();
    Var_scope_.scope_end();

  }

  /*---------.
  | Visits.  |
  `---------*/

  // FIXME: Some code was deleted here.

  void
  Binder::operator()(ast::LetExp& e)
  {
    scope_begin();
    e.accept(*this);
    scope_end();
  }


  void Binder::operator()(ast::ForExp& e)
  {}
  void Binder::operator()(ast::WhileExp& e)
  {}
  void Binder::operator()(ast::BreakExp& e)
  {}

  void Binder::operator()(ast::NameTy& e)
  {}
  void Binder::operator()(ast::RecordTy& e)
  {}
  void Binder::operator()(ast::ArrayTy& e)
  {}

  void Binder::operator()(ast::CallExp& e)
  {}
  void Binder::operator()(ast::SimpleVar& e)
  {}



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
