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

  void
  Binder::operator()(ast::LetExp& e)
  {
    scope_begin();
    e.decs_get().accept(*this);
    scope_end();
  }

  void Binder::operator()(ast::ForExp& e)
  {
    scope_begin();
    e.accept(*this);
    scope_end();
  }
  void Binder::operator()(ast::WhileExp& e)
  {
    scope_begin();
    e.accept(*this);
    scope_end();
  }
  void Binder::operator()(ast::BreakExp& e)
  {
    
  }

  void Binder::operator()(ast::NameTy& e)
  {}
  void Binder::operator()(ast::RecordTy& e)
  {}
  void Binder::operator()(ast::ArrayTy& e)
  {
    
  }

  void Binder::operator()(ast::CallExp& e)
  {
    auto* res = function_scope_.get(e.name_get());
    if (!res)
      undeclared("variable", e);
    else
      e.def_set(res);
  }
  void Binder::operator()(ast::SimpleVar& e)
  {
    auto* res = var_scope_.get(e.name_get());
    if (!res)
      undeclared("variable", e);
    else
      e.def_set(res);
  }



  /*-------------------.
  | Visiting VarDecs.  |
  `-------------------*/

  void
  Binder::operator()(ast::VarDecs& e)
  {
    scope_begin();
    decs_visit<ast::VarDec>(e);
    scope_end();
  }


  /*------------------------.
  | Visiting FunctionDecs.  |
  `------------------------*/

  void
  Binder::operator()(ast::FunctionDecs& e)
  {
    scope_begin();
    decs_visit<ast::FunctionDec>(e);
    scope_end();
  }

  
  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/

  void
  Binder::operator()(ast::TypeDecs& e)
  {
    scope_begin();
    decs_visit<ast::TypeDec>(e);
    scope_end();
  }

  
} // namespace bind
