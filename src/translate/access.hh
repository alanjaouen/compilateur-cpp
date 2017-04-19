/**
 ** \file translate/access.hh
 ** \brief Access: Static link aware accesses.
 */

#pragma once

#include <iosfwd>

#include <tree/fwd.hh>
#include <frame/fwd.hh>
#include <translate/fwd.hh>

namespace translate
{

  /** \brief Wrapper around frame::Access.
   **
   ** A translate::Access is composed of a frame::Access and
   ** a pointer to the translate::Level which includes this access.
   ** This is used when we are using the static links.  This is also
   ** why we don't see this in frame::Access: the frame module is not
   ** supposed to be tuned for Tiger especially, and therefore should
   ** not include Tiger related things such as static links.
   **/
  class Access
  {
  public:
    Access(const Level& home, const frame::Access* access);

    /// The Level \a this Access belongs to.
    const Level& home_get() const;
    /// The underlying, SL unaware, Frame Access.
    const frame::Access* access_get() const;

    /** \brief The \a use level wants to use \a this Access.  Return a Tree
     ** expression computing this access (including all the static
     ** links manipulations to compute the location of the level/frame
     ** hosting this variable).
     **/
    tree::rExp exp(const Level& use) const;

  private:
    /// The Level \a this Access belongs to.
    const Level& home_;
    /// The underlying, SL unaware, Frame Access.
    const frame::Access* access_;
  };

  /// Report \a a on \a o for debugging.
  std::ostream& operator<<(std::ostream& o, const Access& a);

  /// Report \a as on \a o for debugging.
  std::ostream& operator<<(std::ostream& o, const access_list_type& as);

} // namespace translate

#include <translate/access.hxx>
