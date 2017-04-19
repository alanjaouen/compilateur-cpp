/**
 ** \file temp/temp.hh
 ** \brief Fresh temporaries.
 */

#pragma once

#include <misc/vector.hh>
#include <misc/endomap.hh>
#include <temp/identifier.hh>

#ifndef MAYBE_EXTERN
# define MAYBE_EXTERN extern
#endif

namespace temp
{

  template <typename Tag_>
  struct temp_traits;

  template <>
  struct temp_traits<misc::symbol>
  {
    static const std::string prefix;
    static const int rank;
  };

  template <>
  struct temp_traits<unsigned>
  {
    static const std::string prefix;
    static const int rank;
  };

  /// Anonymous and named Temp.
  using Temp = Identifier<temp_traits>;

  // Static member specialization declaration.
  //
  // Do not use the `Temp' typedef to make it clear that template<>
  // is required.
  template <> unsigned Identifier<temp_traits>::count_;

  /// Temp Map.
  using TempMap = misc::endomap<Temp>;


  // Explicit template instantiation declarations.
  MAYBE_EXTERN template class Identifier<temp_traits>;

  MAYBE_EXTERN template
  std::ostream& operator<<(std::ostream& ostr,
                           const Identifier<temp_traits>& obj);

} // namespace temp

namespace misc
{

  // Explicit template instantiation declarations.
  MAYBE_EXTERN template class endomap<temp::Temp>;

  MAYBE_EXTERN template
  std::ostream& operator<<(std::ostream& ostr,
                           const map<temp::Temp, temp::Temp>& m);

  MAYBE_EXTERN template class vector<temp::Temp>;
  MAYBE_EXTERN template
  vector<temp::Temp>::vector(misc::set<temp::Temp>::const_iterator b,
                             misc::set<temp::Temp>::const_iterator e);
  MAYBE_EXTERN template
  vector<temp::Temp>::vector(vector<temp::Temp>::const_iterator b,
                             vector<temp::Temp>::const_iterator e);
  MAYBE_EXTERN template
  vector<temp::Temp>::vector(const misc::set<temp::Temp>& s);
  MAYBE_EXTERN template std::ostream& operator<<(std::ostream& ostr,
                                                 const vector<temp::Temp>& l);

} // namespace misc
