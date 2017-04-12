/**
 ** \file tree/visitor.hxx
 ** \brief Visitors of Fragments of intermediate representation.
 */

#pragma once

#include <misc/algorithm.hh>
#include <tree/fragments.hh>
#include <tree/visitor.hh>

namespace tree
{

  template <template <typename> class Const>
  template <class E>
  void
  GenVisitor<Const>::operator()(E* e)
  {
    e->accept(*this);
  }


  template <template <typename> class Const>
  void
  GenVisitor<Const>::
  operator()(const_t<ProcFrag>&)
  {}

  template <template <typename> class Const>
  void
  GenVisitor<Const>::
  operator()(const_t<DataFrag>&)
  {}

  template <template <typename> class Const>
  void
  GenVisitor<Const>::
  operator()(const_t<Fragments>& frags)
  {
    misc::for_each(frags, *this);
  }

} // namespace tree
