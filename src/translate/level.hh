/**
 ** \file translate/level.hh
 ** \brief Wrapper around frame::Frame.
 **/

#pragma once

#include <iosfwd>
#include <misc/fwd.hh>
#include <frame/fwd.hh>
#include <translate/fwd.hh>

namespace translate
{
  /** \brief Stack frames for languages with non local variables.

  frame::Frame holds the information on the function stack frame.
  translate::Level adds information on the parents of
  the current Level (which is used to fetch escaping variables),
  and also the list of the Access'es to the formals of the
  functions.

  A frame::Frame is a frame::Access factory, and translate::Level
  is a translate::Access factory.
  */
  class Level
  {
  public:
    // \brief Ctor for all the inner levels.
    //
    // \param name        of this function.
    // \param parent      link the Level of the (static) parent, i.e. the
    //                    function declaring this function in the source.
    // \param formal_escapes
    //             list of Booleans: whether the arguments escape.
    //             Not const since we need to add the static link in there.
    Level(const misc::symbol& name,
          const Level* parent = nullptr,
          frame::bool_list_type formal_escapes = frame::bool_list_type());

    /** Destroy \a locals_ completely, but not \a formals_.

    \a locals_ and \a formals_ are translate::Access binding some
    frame::Access.  The frame::Frame keeps track of its formals,
    but not of its locals; hence it destroys by itself its locals
    and we must not do it here.  As a result, we have to destroy
    the high level parts of both formals and locals, and the low
    level part (frame::Access) only for \a locals_.    */
    ~Level();

    /// \name Accessors.
    /// \{
    /// Level of the enclosing function.
    const Level* parent_get() const;
    /// Stack frame that we enhance with static link support.
    frame::Frame& frame_get();
    /// Stack frame that we enhance with static link support.
    const frame::Frame& frame_get() const;
    /// Label of this function (from the Frame).
    temp::Label label_get() const;
    /// Accesses to the formals arguments.
    const access_list_type& formals_get() const;
    /// Size of the Frame.
    int frame_size_get() const;
    /// \}


    /// A Tree expression computing this level's static link.
    tree::rExp sl() const;

    /** \brief Return a Tree expression representing the frame pointer
        of \a this Level, but from the \a use level point of view (i.e.,
        climbing the static links from \a use level to \a this Level).

        This is used in at least two places:

        1. when calling a function (which needs a static link),
        to pass the location of the frame of its parent.

        2. when accessing a frame resident variable, to produce
        an expression computing the location of the frame it
        belongs to.  For instance this is `Temp fp' if the variable is
        in the function using it, but it is more complex when the
        function uses a variable from an enclosing function.
    **/
    tree::rExp fp(const Level& use) const;

    /// Report on stream \a o.
    std::ostream& dump(std::ostream& o) const;

    /// \brief Allocate a new local variable.
    /// \param   escapes  if true, make it frame resident.
    /// \returns          an Access to allocated memory.
    const Access* local_alloc(bool escapes);
    /// Similar to local_alloc () for formal arguments.
    const Access* formal_alloc(bool escapes);

  private:
    /// Level of the enclosing function.
    const Level* parent_;
    /// Stack frame that we enhance with static link support.
    frame::Frame* frame_;
    /// Accesses to the formal arguments.
    access_list_type formals_;
    /// Accesses to the local (automatic) variables.
    access_list_type locals_;
  };


  /// Report \a l on \a o.
  std::ostream& operator<<(std::ostream& o, const Level& l);

} // namespace translate

#include <translate/level.hxx>
