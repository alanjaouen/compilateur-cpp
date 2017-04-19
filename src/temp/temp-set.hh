/**
 ** \file temp/temp-set.hh
 ** \brief Sets of temporaries.
 */

#pragma once

#include <temp/temp.hh>
#include <misc/set.hh>

namespace temp
{

  /// A sorted set of Temp's.
  using temp_set_type = misc::set<Temp>;

  /// Output a temp_set_type, sorted.
  std::ostream&
  operator<<(std::ostream& ostr, const temp_set_type& temps);

} // namespace temp
