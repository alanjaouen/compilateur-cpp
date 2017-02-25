/**
 ** \file bind/libbind.cc
 ** \brief Define exported bind functions.
 */

#include <bind/binder.hh>
#include <bind/libbind.hh>
#include <bind/renamer.hh>

namespace bind
{
  
  misc::error bind(ast::Ast& tree)
  {
    Binder bindings_compute;
    bindings_compute(tree);
    return bindings_compute.error_get();
      //bindings_compute.error_get().ice_here();
  }
  void rename(ast::Ast& tree)
  {
    Renamer renamer_compute;
    renamer_compute(tree);
  }
}
