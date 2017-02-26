/**
 ** \file object/libobject.cc
 ** \brief Define exported object functions.
 */


#include <object/libobject.hh>
#include <ast/libast.hh>
#include <object/binder.hh>

namespace object
{
  /*-------.
  | Bind.  |
  `-------*/


  misc::error bind(ast::Ast& e)
  {
  }
  misc::error bind_obj(ast::Ast& e)
  {
    Binder bind_compute;
    bind_compute(e);
    return bind_compute.error_get();
  }



} // namespace object
