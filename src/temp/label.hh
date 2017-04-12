/**
 ** \file temp/label.hh
 ** \brief Fresh labels.
 */

#pragma once

#include <temp/identifier.hh>
#include <misc/vector.hh>

# ifndef MAYBE_EXTERN
#  define MAYBE_EXTERN extern
# endif

namespace temp
{

  template <typename Tag_>
  struct label_traits;

  template <>
  struct label_traits<misc::symbol>
  {
    static const std::string prefix;
    static const int rank;
  };

  template <>
  struct label_traits<unsigned>
  {
    static const std::string prefix;
    static const int rank;
  };

  /// Anonymous and named Label.
  using Label = Identifier<label_traits>;

  // Static member specialization declaration.
  //
  // Do not use the `Label' typedef to make it clear that template<>
  // is required.
  template<> unsigned Identifier<label_traits>::count_;

  // Explicit template instantiation declarations.
  MAYBE_EXTERN template class Identifier<label_traits>;

  MAYBE_EXTERN template
  std::ostream& operator<<(std::ostream& ostr,
                           const Identifier<label_traits>& obj);
} // namespace temp

namespace misc
{

  // Explicit template instantiation declarations.
  MAYBE_EXTERN template class endomap<temp::Label>;

  MAYBE_EXTERN template
  std::ostream& operator<<(std::ostream& ostr,
                           const map<temp::Label, temp::Label>& m);
  MAYBE_EXTERN template class vector<temp::Label>;
  MAYBE_EXTERN template std::ostream& operator<<(std::ostream& ostr,
                                                 const vector<temp::Label>& l);
} // namespace misc
