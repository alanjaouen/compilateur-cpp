/**
 ** \file tree/fragments.hh
 ** \brief Declaration of tree::Fragments.
 **/

#pragma once

#include <vector>
#include <tree/fwd.hh>

namespace tree
{

  /// Fragments: Fragment list.
  class Fragments : public std::vector<tree::Fragment*>
  {
  public:
    using super_type = std::vector<tree::Fragment*>;

    // Inherit constructors from base class.
    using super_type::super_type;

    virtual ~Fragments();
  };

  /// Report \a fragments on \a ostr.
  std::ostream& operator<<(std::ostream& o, const Fragments& f);

} // namespace tree
