/**
 ** \file temp/libtemp.hh
 ** \brief Handle temps.
 */

#pragma once

#include <iostream>
#include <temp/fwd.hh>
#include <temp/temp.hh>

/// Managing Temp and Label.
namespace temp
{

  /// Print the map of temps on ostr.
  std::ostream&
  dump(const temp::TempMap& map, std::ostream& ostr = std::cout);

} // namespace temp
