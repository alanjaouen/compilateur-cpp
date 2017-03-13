/**
 ** \file escapes/escapes-visitor.cc
 ** \brief Implementation for escapes/escapes-visitor.hh.
 */

#include <misc/contract.hh>

#include <ast/all.hh>
#include <escapes/escapes-visitor.hh>

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
  dmap depth_map_get()
  {

  }

  //reshearch in th map
  int get(misc::symbol sym)
  {

  }

  //add an elemet to the map
  void put(misc::symbol& sym, ast::vardec& var)
  {

  }

  //print the map on std::cout
  void dump()
  {

  }


} // namespace escapes
