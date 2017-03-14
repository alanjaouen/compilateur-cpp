/**
 ** \file escapes/escapes-visitor.cc
 ** \brief Implementation for escapes/escapes-visitor.hh.
 */

#include <misc/contract.hh>

#include <ast/all.hh>
#include <escapes/escapes-visitor.hh>

#include <iostream>

namespace escapes
{
  // FIXED: Alan

  void
  EscapesVisitor::operator()(ast::VarDec& e)
  {
    put(&e);
    e.is_escaped_set(false);
    if (e.type_name_get())
      e.type_name_get()->accept(*this);
    if (e.init_get())
      e.init_get()->accept(*this);
  }

  void
  EscapesVisitor::operator()(ast::FunctionDec& e)
  {
    scope_begin();
    e.formals_get().accept(*this);
    if (e.result_get())
      e.result_get()->accept(*this);
    if (e.body_get())
      e.body_get()->accept(*this);
    scope_end();
  }

  void
  EscapesVisitor::operator()(ast::SimpleVar& e)
  {
    auto d = get(e.name_get());
    if (d != nullptr)
      d->is_escaped_set(true);
  }


  void EscapesVisitor::scope_begin()
  {
    var_scope_.scope_begin();
  }  
  void EscapesVisitor::scope_end()
  {
    var_scope_.scope_end();
  }

  //add an elemet to the map
  void
  EscapesVisitor::put(ast::VarDec* var)
  {
    var_scope_.put(var->name_get(), var);
  }

  //print the map on std::cout
  void
  EscapesVisitor::dump()
  {
    std::cout << "===== PRINT ESCAPE MAP =====" << std::endl;
    std::cout << var_scope_;
// for (auto i : depth_map_get())
    //   std::cout << i.first << " " << i.second.first->name_get() << " " << i.second.second << std::endl;
    std::cout << "============ END ===========" << std::endl;
  }

} // namespace escapes
