/**
 ** \file translate/level.hxx
 ** \brief Inline methods for translate::Level.
 **/

#pragma once

#include <translate/level.hh>

namespace translate
{

  inline const Level*
  Level::parent_get() const
  {
    return parent_;
  }

  inline frame::Frame&
  Level::frame_get()
  {
    return *frame_;
  }

  inline const frame::Frame&
  Level::frame_get() const
  {
    return *frame_;
  }

  inline const access_list_type&
  Level::formals_get() const
  {
    return formals_;
  }

  // Report.
  inline std::ostream&
  operator<<(std::ostream& o, const Level& l)
  {
    return l.dump(o);
  }

} // namespace translate
