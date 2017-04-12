/**
 ** \file temp/temp-set.cc
 ** \brief Implementation for temp/temp-set.hh.
 */

#include <ostream>
#include <temp/temp-set.hh>

namespace temp
{
  std::ostream&
  operator<<(std::ostream& ostr, const temp_set_type& temps)
  {
    for (temp_set_type::const_iterator i = temps.begin();
         i != temps.end(); ++i)
      ostr << (i != temps.begin() ? " " : "") << *i;
    return ostr;
  }

} // namespace temp
