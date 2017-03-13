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
  // FIXMED: Alan

  EscapesVisitor()
  {}

  ~EscapesVisitor()
  {}

  //increment the depth counter;
  void incr()
  {
    EscapesVisitor.deph_++;
  }

  //decrement the depth counter;
  void decr()
  {
    EscapesVisitor.deph_--;
  }

  //getter for deph_
  int depth_get()
  {
    return EscapesVisitor.deph_;
  }

  //getter for deph_map_
  dmap& depth_map_get()
  {
    return EscapesVisitor.depth_map_;
  }

  //reshearch in th map
  int get(misc::symbol sym)
  {
    return EscapesVisitor.depth_map_[sym].second;
  }

  //add an elemet to the map
  void put(misc::symbol& sym, ast::VarDec& var)
  {
    EscapesVisitor.depth_map_[sym] = new std::pair<ast::VarDec&, int>
      (var, EscapesVisitor.depth_get());
  }

  //print the map on std::cout
  void dump()
  {
    std::cout << "===== PRINT ESCAPE MAP =====" << std::endl
    for (auto i : depth_map_get())
    {
      std::cout << i.first << " " << i.second.first << " " << i.second.second << std::endl;
    }
    std::cout << "============ END ===========" << std::endl
  }


} // namespace escapes
