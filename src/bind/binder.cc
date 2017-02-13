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
  // FIXME: Some code was deleted here.
  }

  void
  Binder::scope_end()
  {
  // FIXME: Some code was deleted here.
  }

  /*---------.
  | Visits.  |
  `---------*/

  // FIXME: Some code was deleted here.

  void
  Binder::operator()(ast::LetExp& e)
  {
  // FIXME: Some code was deleted here.
  }


  /*-------------------.
  | Visiting VarDecs.  |
  `-------------------*/

  // FIXME: Some code was deleted here.


  /*------------------------.
  | Visiting FunctionDecs.  |
  `------------------------*/

  // FIXME: Some code was deleted here.

  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/
  // FIXME: Some code was deleted here.

} // namespace bind
