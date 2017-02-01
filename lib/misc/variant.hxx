/**
 ** \file misc/variant.hxx
 ** \brief Implementation of misc::variant.
 **/

#pragma once

#include <type_traits>
#include <boost/variant/get.hpp>
#include <misc/variant.hh>

namespace misc
{

  template <typename T, typename... Ts>
  template <typename U>
  variant<T, Ts...>::variant(const U& rhs)
    : super_type(rhs)
  {}

  template <typename T, typename... Ts>
  template <typename U>
  variant<T, Ts...>&
  variant<T, Ts...>::operator=(const U& rhs)
  {
    // Don't assign to oneself.
    if (static_cast<const void*>(&rhs) != static_cast<const void*>(this))
      super_type::operator=(rhs);
    return *this;
  }


  template <typename T, typename... Ts>
  template <typename U>
  variant<T, Ts...>::operator U& ()
  {
    // c++1z - std::variant
    // return std::get<U>(*this);
    return boost::get<U>(*this);
  }

  template <typename T, typename... Ts>
  template <typename U>
  variant<T, Ts...>::operator const U& () const
  {
    return boost::get<U>(*this);// FIXME: Some code was deleted here.
  }

} // namespace misc
