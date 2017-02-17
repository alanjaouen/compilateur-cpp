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

  template <typename Key, typename Data>
  scoped_map<Key, Data>::scoped_map() :
    scopes_()
  {}

  // template <typename Key, typename Data>
  // scoped_map<Key, Data>::scoped_map(const Key key, const Data value)
  // {
  //   scope_type* list = new scope_type();
  //   scope_slot& slot = new scope_slot(key, value);
  //   list.push_back(slot);
  //   scopes_ = list;
  // }

  template <typename Key, typename Data>
  void scoped_map<Key, Data>::put(const Key& key, const Data& value)
  {
    scopes_.back()[key] = value;
  }

  template <typename Key, typename Data>
  Data scoped_map<Key, Data>::get(const Key& key) const
  {
    for (auto i = scopes_.rbegin(); i != scopes_.rend(); i++)
      {
	auto res = i->find(key);
	if (res != i->end())
	  return res->second;
      }
    return throw_range_error<Key, Data>();
    //return res->second;
  }

  template <typename Key, typename Data>
  std::ostream& scoped_map<Key, Data>::dump(std::ostream& ostr) const
  {
    for (const auto& i : scopes_)
      {
        ostr << "( ";
        for (const auto& j : i)
          ostr << j.first << ", ";
        ostr << " )";
      }
    return ostr;
  }

  template <typename Key, typename Data>
  void scoped_map<Key, Data>::scope_begin()
  {
    scopes_.push_back(scope_slot());
  }

  template <typename Key, typename Data>
  void scoped_map<Key, Data>::scope_end()
  {
    scopes_.pop_back();
  }

  template <typename Key, typename Data>
  inline const typename scoped_map<Key, Data>::scope_type
  scoped_map<Key, Data>::scopes_get() const
  {
    return scopes_;
  }

  template <typename Key, typename Data>
  inline std::ostream&
  operator<<(std::ostream& ostr, const scoped_map<Key, Data>& tbl)
  {
    return tbl.dump(ostr);
  }

} // namespace misc
