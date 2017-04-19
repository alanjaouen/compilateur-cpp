/**                                                             -*- C++ -*-
 ** \file temp/identifier.hxx
 ** \brief Implementation of Identifier & TaggedIdentifier templates.
 */

#pragma once

#include <cstdlib>

#include <sstream>
#include <iostream>

#include <boost/variant.hpp>

#include <misc/contract.hh>
#include <temp/identifier.hh>

namespace temp
{

  /*-------------.
  | Identifier.  |
  `-------------*/

  template <template <typename Tag_> class Traits_>
  const misc::xalloc<typename Identifier<Traits_>::map_type*>
  Identifier<Traits_>::map;

  template <template <typename Tag_> class Traits_>
  std::ostream&
  operator<<(std::ostream& ostr, const Identifier<Traits_>& obj)
  {
    typename Identifier<Traits_>::map_type* m =
      Identifier<Traits_>::map(ostr);
    if (m)
      return (*m)(obj).dump(ostr);
    else
      return obj.dump(ostr);
  }


  template <template <typename Tag_> class Traits_>
  Identifier<Traits_>::Identifier()
    : value_(count_)
    , prefix_(&Traits_<unsigned>::prefix)
    , rank_(Traits_<unsigned>::rank)
  {
    ++count_;
  }

  template <template <typename Tag_> class Traits_>
  Identifier<Traits_>::Identifier(const misc::symbol& sym)
    : value_(sym)
    , prefix_(&Traits_<misc::symbol>::prefix)
    , rank_(Traits_<misc::symbol>::rank)
  {}


  template <template <typename Tag_> class Traits_>
  Identifier<Traits_>::Identifier(const std::string& str)
  // FIXME: Some code was deleted here.
  {}

  template <template <typename Tag_> class Traits_>
  Identifier<Traits_>::Identifier(const char* str)
  // FIXME: Some code was deleted here.
  {}

  template <template <typename Tag_> class Traits_>
  Identifier<Traits_>::Identifier(const Identifier<Traits_>& id)
  // FIXME: Some code was deleted here.
  {}


  template <template <typename Tag_> class Traits_>
  std::ostream&
  Identifier<Traits_>::dump(std::ostream& ostr) const
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename Tag_> class Traits_>
  std::string
  Identifier<Traits_>::string_get() const
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename Tag_> class Traits_>
  const typename Identifier<Traits_>::value_type&
  Identifier<Traits_>::value_get() const
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename Tag_> class Traits_>
  const std::string&
  Identifier<Traits_>::prefix_get() const
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename Tag_> class Traits_>
  int
  Identifier<Traits_>::rank_get() const
  {
  // FIXME: Some code was deleted here.
  }


  template <template <typename Tag_> class Traits_>
  Identifier<Traits_>&
  Identifier<Traits_>::operator=(const Identifier<Traits_>& rhs)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename Tag_> class Traits_>
  bool
  Identifier<Traits_>::operator==(const Identifier<Traits_>& rhs) const
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename Tag_> class Traits_>
  bool
  Identifier<Traits_>::operator!=(const Identifier<Traits_>& rhs) const
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename Tag_> class Traits_>
  bool
  Identifier<Traits_>::operator<(const Identifier<Traits_>& rhs) const
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename Tag_> class Traits_>
  bool
  Identifier<Traits_>::operator<=(const Identifier<Traits_>& rhs) const
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename Tag_> class Traits_>
  bool
  Identifier<Traits_>::operator>(const Identifier<Traits_>& rhs) const
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename Tag_> class Traits_>
  bool
  Identifier<Traits_>::operator>=(const Identifier<Traits_>& rhs) const
  {
  // FIXME: Some code was deleted here.
  }


  /*------------------.
  | Variant visitor.  |
  `------------------*/

  // FIXME: Some code was deleted here.

} // namespace temp
