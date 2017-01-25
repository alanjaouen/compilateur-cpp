/**
 ** \file misc/variant.hh
 ** \brief Interface of misc::variant.
 **
 ** misc::variant is a wrapper over boost::variant that adds
 ** conversion operators to the original Boost variant class.
 ** misc::variant is used just like boost::variant, and you
 ** won't be disturbed when using it.
 **/

#pragma once

#include <boost/variant.hpp>

namespace misc
{
  /// A wrapper over boost::variant supporting conversion operators.
  ///
  /// Preconditions:
  /// - Each type must be unique.
  /// - No type may be const-qualified.
  ///
  /// Proper declaration form:
  ///   misc::variant<T, T1, ..., Tn>

  template <typename T, typename... Ts>
  class variant :
  // c++1z - std::variant
  // public std::variant<T, Ts ...>
    public boost::variant<T, Ts...>
  {
    static_assert(std::is_default_constructible<T>::value,
                  "the first parameter type of the variant must be"
                  " default-constructible");

  public:
    /// The type of this variant.
    using self_type = variant<T, Ts...>;
    /// Super type.

    // c++1z - std::variant
    // using super_type = std::variant<T, Ts ...>;
    using super_type = boost::variant<T, Ts...>;

    /// Constructors.
    /// \{
    variant() = default;
    template <typename U> variant(const U& rhs);
    /// \}

    template <typename U> self_type& operator=(const U&);

    /// \brief Convert this variant to a value of type \a U.
    ///
    /// This conversion relies on boost::get.  In particular, if the
    /// conversion fails, a boost::bad_get exception is thrown.
    template <typename U> operator U&();

    /// Likewise, const version.
    template <typename U> operator const U&() const;
  };

} // namespace misc

#include <misc/variant.hxx>
