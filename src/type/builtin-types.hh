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
  public:
    Singleton(const Singleton<D>&) = delete;
    Singleton(Singleton<D>&&) = delete;
    Singleton<D>& operator=(const Singleton<D>&) = delete;
    Singleton<D>& operator=(Singleton<D>&&) = delete;
    static const D& instance()
      {
        static D instance;
        return instance;
      }
  protected:
    Singleton() = default;
  };

  class String : public Type, public Singleton<type::String>
  {
  public:
    String() = default;
    ~String()
      {}
    void accept(ConstVisitor& v) const;
    void accept(Visitor& v);
    bool compatible_with(const Type& other) const;
    const Type& actual() const;

  };

  class Int : public type::Type, public Singleton<type::Int>
  {
  public:
    Int() = default;
    ~Int()
      {}
    void accept(ConstVisitor& v) const;
    void accept(Visitor& v);
    bool compatible_with(const Type& other) const;
    const Type& actual() const;
  };

  class Void : public type::Type, public Singleton<type::Void>
  {
  public:
    Void() = default;
    ~Void()
      {}
    void accept(ConstVisitor& v) const;
    void accept(Visitor& v);
    bool compatible_with(const Type& other) const;
    const Type& actual() const;

  };

} // namespace type
