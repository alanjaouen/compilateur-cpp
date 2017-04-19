/**
 ** \file temp/temp.cc
 ** \brief Implementation for temp/temp.hh.
 */

#include <misc/endomap.hh>
#include <misc/set.hh>

#define MAYBE_EXTERN
#include <temp/temp.hh>
#undef MAYBE_EXTERN

namespace temp
{
  // Static member specialization definition.
  //
  // Do not use the `Temp' typedef to make it clear that template<>
  // is required.
  template <> unsigned Identifier<temp_traits>::count_ = 0;

  const std::string temp_traits<misc::symbol>::prefix = "";
  const int temp_traits<misc::symbol>::rank = 0;

  const std::string temp_traits<unsigned>::prefix = "t";
  const int temp_traits<unsigned>::rank = 1;

} // namespace temp
