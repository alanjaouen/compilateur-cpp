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
  Singleton(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton& operator=(Singleton&&) = delete;
  static const Singleton& instance()
  {
    static Singleton instance;
    return instance;
  }
};

class String : public Singleton<String>, public Type
{
};

class Int : public Singleton<Int>, public Type
{
};

class Void : public Singleton<Void>, public Type
{
};

} // namespace type
