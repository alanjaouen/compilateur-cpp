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
  // FIXED forest_b
    : Identifier(misc::symbol(str))
  {  }

  template <template <typename Tag_> class Traits_>
  Identifier<Traits_>::Identifier(const char* str)
  // FIXED forest_b
    : Identifier(misc::symbol(str))
  {  }

  template <template <typename Tag_> class Traits_>
  Identifier<Traits_>::Identifier(const Identifier<Traits_>& id)
  // FIXED forest_b
    : value_(id.value_get())
    , prefix_(&id.prefix_get())
    , rank_(id.rank_get())
  {}


  template <template <typename Tag_> class Traits_>
  std::ostream&
  Identifier<Traits_>::dump(std::ostream& ostr) const
  {
  // FIXED forest_b
    ostr << *prefix_ << value_;  // boost::get<misc::symbol>(value_);
    return ostr;
  }

  template <template <typename Tag_> class Traits_>
  std::string
  Identifier<Traits_>::string_get() const
  {
  // FIXED forest_b
    std::string res = "rank: ";
    res += rank_;
    res += " prefix: ";
    res += prefix_get();
    res += " value: ";
    res += boost::get<misc::symbol>(value_);
    return res;
  }

  template <template <typename Tag_> class Traits_>
  const typename Identifier<Traits_>::value_type&
  Identifier<Traits_>::value_get() const
  {
    //FIXED by forest_b
    return value_;
  }

  template <template <typename Tag_> class Traits_>
  const std::string&
  Identifier<Traits_>::prefix_get() const
  {
  // FIXED by forest_b
    return *prefix_;
  }

  template <template <typename Tag_> class Traits_>
  int
  Identifier<Traits_>::rank_get() const
  {
  // FIXED forest_b
    return rank_;
  }


  template <template <typename Tag_> class Traits_>
  Identifier<Traits_>&
  Identifier<Traits_>::operator=(const Identifier<Traits_>& rhs)
  {
  // FIXED forest_b
    value_ = rhs.value_;
    rank_ = rhs.rank_;
    prefix_ = rhs.prefix_;
    return *this;
  }

  template <template <typename Tag_> class Traits_>
  bool
  Identifier<Traits_>::operator==(const Identifier<Traits_>& rhs) const
  {
   // FIXED forest_b
    return rank_get() == rhs.rank_get()
      && boost::apply_visitor(IdentifierEqualToVisitor(), value_, rhs.value_get());
  }

  template <template <typename Tag_> class Traits_>
  bool
  Identifier<Traits_>::operator!=(const Identifier<Traits_>& rhs) const
  {
    // FIXED by forest_b
    return !(rank_get() == rhs.rank_get()
             && boost::apply_visitor(IdentifierEqualToVisitor(), value_, rhs.value_get()));

  }

  template <template <typename Tag_> class Traits_>
  bool
  Identifier<Traits_>::operator<(const Identifier<Traits_>& rhs) const
  {
    // FIXED by forest_b
    return rank_get() < rhs.rank_get() || boost::apply_visitor(IdentifierLessThanVisitor(), value_, rhs.value_get());
  }

  template <template <typename Tag_> class Traits_>
  bool
  Identifier<Traits_>::operator<=(const Identifier<Traits_>& rhs) const
  {
    // FIXED by forest_b
    return *this < rhs || *this == rhs;
  }

  template <template <typename Tag_> class Traits_>
  bool
  Identifier<Traits_>::operator>(const Identifier<Traits_>& rhs) const
  {
  // FIXED by forest_b
    return rank_get() > rhs.rank_get() && !boost::apply_visitor(IdentifierLessThanVisitor(), value_, rhs.value_);

  }

  template <template <typename Tag_> class Traits_>
  bool
  Identifier<Traits_>::operator>=(const Identifier<Traits_>& rhs) const
  {
    // FIXED by forest_b
    return *this > rhs || *this == rhs;
  }


  /*------------------.
  | Variant visitor.  |
  `------------------*/

  // FIXED ? forest_b
  template <template <typename Elt_> class Cmp_>
  template <typename T, typename U>
  bool  IdentifierCompareVisitor<Cmp_>::operator()(const T&, const U&) const
  {
    //FIXME
    return false;
  }

  template <template <typename Elt_> class Cmp_>
  template <typename T>
  bool  IdentifierCompareVisitor<Cmp_>::operator()(const T& lhs, const T& rhs) const
  {
    //FIXED forest_b
    auto cmp = Cmp_<T>();
    return cmp(lhs, rhs);
  }

  
} // namespace temp
