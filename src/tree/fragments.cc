/**
 ** \file tree/fragments.cc
 ** \brief Implementation of tree::Fragments.
 **/

#include <misc/separator.hh>
#include <tree/fragment.hh>
#include <tree/fragments.hh>

namespace tree
{

  Fragments::~Fragments()
  {
    misc::deep_clear(*this);
  }

  std::ostream&
  operator<<(std::ostream& o, const Fragments& f)
  {
    return o << misc::separate(f, '\n');
  }

} // namespace tree
