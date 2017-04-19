/**
 ** \file translate/access.hxx
 ** \brief Inline methods for translate/access.hh.
 */

#pragma once

#include <translate/fwd.hh>
#include <translate/access.hh>

namespace translate
{

  inline
  Access::Access(const Level& home,
                 const frame::Access* access) :
    home_(home),
    access_(access)
  {}

  inline const Level&
  Access::home_get() const
  {
    return home_;
  }

  inline const frame::Access*
  Access::access_get() const
  {
    return access_;
  }

} // namespace translate
