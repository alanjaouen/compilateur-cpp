#pragma once
#include <escapes/escapes-visitor.hh>

namespace escapes
{
  //increment the depth counter;
  inline void
  EscapesVisitor::incr()
  {
    depth_++;
  }

  //decrement the depth counter;
  inline void
  EscapesVisitor::decr()
  {
    depth_--;
  }

  //getter for deph_
  inline int
  EscapesVisitor::depth_get()
  {
    return depth_;
  }

  //getter for deph_map_
  inline EscapesVisitor::dmap&
  EscapesVisitor::depth_map_get()
  {
    return depth_map_;
  }

  //reshearch in th map
  inline int
  EscapesVisitor::get(misc::symbol sym)
  {
    return depth_map_[sym].second;
  }

}
