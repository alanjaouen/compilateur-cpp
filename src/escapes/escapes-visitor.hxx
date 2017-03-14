#pragma once
#include <escapes/escapes-visitor.hh>

namespace escapes
{

  //reshearch in th map
  inline ast::VarDec*
  EscapesVisitor::get(misc::symbol sym)
  {
    auto cur = var_scope_.scopes_get();
    ast::VarDec* res = nullptr;
    for (auto i = cur.rbegin()+1; i != cur.rend() && res == nullptr; i++)
    {
      res = (*i)[sym];
    }
    return res;
  }

}
