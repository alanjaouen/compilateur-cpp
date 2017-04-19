/**
 ** \file temp/fwd.hh
 ** \brief Forward declarations of temp classes
 */

#pragma once

#include <misc/symbol.hh>
#include <misc/set.hh>
#include <misc/endomap.hh>
#include <misc/vector.hh>
#include <misc/fwd.hh>

namespace temp
{

  // From identifier.hh.
  template <template <typename Tag_> class Traits_>
  class Identifier;

  // From temp.hh.
  template <typename Tag_>
  struct temp_traits;
  using Temp = Identifier<temp_traits>;
  using TempMap = misc::endomap<Temp>;
  using temp_list_type = misc::vector<Temp>;

  // From temp-set.hh.
  using temp_set_type = misc::set<Temp>;

  // From label.hh.
  template <typename Tag_>
  struct label_traits;
  using Label = Identifier<label_traits>;

  using label_list_type = misc::vector<Label>;

} // namespace temp
