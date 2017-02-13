/** \file misc/scoped-map.hxx
 ** \brief Implementation of misc::scoped_map.
 */

#pragma once

#include <stdexcept>
#include <sstream>
#include <type_traits>

#include <misc/contract.hh>
#include <misc/algorithm.hh>
#include <misc/indent.hh>

namespace misc
{
  // FIXME: Some code was deleted here.

  template <typename Key, typename Data>
  inline std::ostream&
  operator<<(std::ostream& ostr, const scoped_map<Key, Data>& tbl)
  {
    return tbl.dump(ostr);
  }

} // namespace misc
