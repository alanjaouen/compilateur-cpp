/**
 ** \file translate/fwd.hh
 ** \brief Forward declarations for translate:: items.
 */

#pragma once

#include <vector>
#include <misc/fwd.hh>

namespace translate
{
  // From level.hh.
  class Level;

  // From access.hh.
  class Access;
  using access_list_type = std::vector<const Access*>;

  // From exp.hh.
  class Exp;
  using rExp = misc::ref<Exp>;
} // namespace translate
