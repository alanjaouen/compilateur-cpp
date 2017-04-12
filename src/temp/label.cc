/**
 ** \file temp/label.cc
 ** \brief temp::Label.
 */

#include <misc/endomap.hh>

#define MAYBE_EXTERN
#include <temp/label.hh>
#undef MAYBE_EXTERN

namespace temp
{

  // Static member specialization definition.
  //
  // Do not use the `Label' typedef to make it clear that template<>
  // is required.
  template<> unsigned Identifier<label_traits>::count_ = 0;

  const std::string label_traits<misc::symbol>::prefix = "";
  const int label_traits<misc::symbol>::rank = 0;

  const std::string label_traits<unsigned>::prefix = "l";
  const int label_traits<unsigned>::rank = 1;

} // namespace temp
