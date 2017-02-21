/**
 ** \file misc/scoped-map.hh
 ** \brief Declaration of misc::scoped_map.
 **
 ** This implements a stack of dictionnaries.  Each time a scope is
 ** opened, a new dictionnary is added on the top of the stack; the
 ** dictionary is removed when the scope is closed.  Lookup of keys
 ** is done in the last added dictionnary first (LIFO).
 **
 ** In particular this class is used to implement symbol tables.
 **/

#pragma once

#include <vector>
#include <map>
#include <ostream>

namespace misc
{
  //Fixed by caradi_c
  template <typename Key, typename Data>
  class scoped_map
  {
  public:
    //Fixed
  public:
    using scope_slot = std::map<Key, Data>;
    using scope_type = std::vector<scope_slot>;

    scoped_map();
    // needed by lrde tests
    ~scoped_map() = default;

    ///Associate value to key in the current scope.
    void put (const Key& key, const Data& value);
    ///If key was associated to some Data in the open scopes, return the most recent insertion. Otherwise, if Data is a pointer type, then return the empty pointer, else throw a std::range_error. To implement this feature, see <type_traits>
    Data get (const Key& key) const;
    ///Send the content of this table on ostr in a human-readable manner, and return the stream. 
    std::ostream& dump (std::ostream& ostr) const;
    ///Open a new scope.
    void scope_begin ();
    ///Close the last scope, forgetting everything since the latest scope_begin(). 
    void scope_end ();

    const scope_type& scopes_get() const;
  private:

    scope_type scopes_;
    //End Fixed
  };

  template <typename Key, typename Data>
  std::ostream&
  operator<<(std::ostream& ostr, const scoped_map<Key, Data>& tbl);

  //Error function.
  template <typename Key, typename Data>
  std::enable_if_t<std::is_pointer<Data>::value, Data>
  throw_range_error()
  {
    return nullptr;
  }

  template <typename Key, typename Data>
  std::enable_if_t<!std::is_pointer<Data>::value, Data>
  throw_range_error()
  {
    throw(std::range_error("Impossible to find element in the current scope."));
  }

} // namespace misc

#include <misc/scoped-map.hxx>
