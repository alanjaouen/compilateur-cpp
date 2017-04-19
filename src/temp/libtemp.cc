/**
 ** \file temp/libtemp.cc
 ** \brief Handle temps.
 */

#include <iostream>

#include <temp/libtemp.hh>
#include <temp/temp.hh>

namespace temp
{

  std::ostream&
  dump(const temp::TempMap& map, std::ostream& ostr)
  {
    return ostr << map;
  }

} // namespace temp
