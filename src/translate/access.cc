/**
 ** \file translate/access.cc
 ** \brief Implementation of translate::Access.
 */

#include <ostream>

#include <misc/separator.hh>
#include <temp/label.hh>
#include <tree/exp.hh>
#include <frame/access.hh>
#include <translate/access.hh>
#include <translate/level.hh>

namespace translate
{

  tree::rExp
  Access::exp(const Level& use) const
  {
    return access_->exp(home_.fp(use));
  }

  std::ostream&
  operator<<(std::ostream& o, const Access& a)
  {
    return o << "translate::Access ("
      // Don't display the whole level to avoid infloop.
            << "home = " << a.home_get().label_get()
            << ", "
            << "frame::access = " << *a.access_get()
            << ") ";
  }

  std::ostream&
  operator<<(std::ostream& o, const access_list_type& as)
  {
    return o << misc::separate(as, ", ");
  }

} // namespace translate
