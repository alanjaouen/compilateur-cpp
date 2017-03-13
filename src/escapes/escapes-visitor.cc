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
    
  }

  void
  EscapesVisitor::operator()(ast::FunctionDecs& e)
  {

  }

  //add an elemet to the map
  void
  EscapesVisitor::put(misc::symbol& sym, ast::VarDec* var)
  {
    auto i = depth_map_.find(sym);
    if (i != depth_map_.end())
      depth_map_.erase(i);
    depth_map_[sym] = std::pair<ast::VarDec*, int>
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
