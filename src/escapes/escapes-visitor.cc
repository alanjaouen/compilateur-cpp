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
    EscapesVisitor::put(&e);
    if (e.type_name_get())
      e.type_name_get()->accept(*this);
    if (e.init_get())
      e.init_get()->accept(*this);
  }

  void
  EscapesVisitor::operator()(ast::FunctionDec& e)
  {
    EscapesVisitor::incr();
    e.formals_get().accept(*this);
    if (e.result_get())
      e.result_get()->accept(*this);
    if (e.body_get())
      e.body_get()->accept(*this);
    EscapesVisitor::decr();
  }

  //add an elemet to the map
  void
  EscapesVisitor::put(ast::VarDec* var)
  {
    auto i = depth_map_.find(var->name_get());
    if (i != depth_map_.end())
      depth_map_.erase(i);
    depth_map_[var->name_get()] = std::pair<ast::VarDec*, int>
      (var, depth_get());
  }

  //print the map on std::cout
  void
  EscapesVisitor::dump()
  {
    std::cout << "===== PRINT ESCAPE MAP =====" << std::endl;
    for (auto i : depth_map_get())
      std::cout << i.first << " " << i.second.first->name_get() << " " << i.second.second << std::endl;
    std::cout << "============ END ===========" << std::endl;
  }

} // namespace escapes
