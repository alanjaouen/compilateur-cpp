/**
 ** \file type/builtin-types.hh
 ** \brief The classes Void, Int, String.
 */
#pragma once

#include <type/fwd.hh>
#include <type/type.hh>

namespace type
{
// FIXME: Some code was deleted here (Other types : String, Int, Void).

template <class D>
class Singleton
{
  Singleton(const Singleton<D>&) = delete;
  Singleton(Singleton<D>&&) = delete;
  Singleton<D>& operator=(const Singleton<D>&) = delete;
  Singleton<D>& operator=(Singleton<D>&&) = delete;
  static const Singleton<D>& instance()
  {
    static Singleton<D> instance;
    return instance;
  }
};

  class String : public Singleton<type::String>, public Type
{
  String();
  ~String();
  
};

  class Int : public Singleton<type::Int>, public Type
{
  Int();
  ~Int();
};

  class Void : public Singleton<type::Void>, public Type
{
  Void();
  ~Void();
};

} // namespace type
