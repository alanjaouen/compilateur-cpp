/**
 ** \file bind/libbind.cc
 ** \brief Define exported bind functions.
 */

#include <bind/binder.hh>
#include <bind/libbind.hh>

namespace bind
{
  
  void bind_compute(ast::Ast& tree)
  {
    Binder bindings_compute;
    bindings_compute(tree);
  }
}
