#pragma once
#include <escapes/escapes-visitor.hh>

namespace escapes
{

  //reshearch in th map
  inline ast::VarDec*
  EscapesVisitor::get(misc::symbol sym)
  {
    auto cur = var_scope_.scopes_get().back();
    return cur[sym];
  }

}
