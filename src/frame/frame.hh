/**
 ** \file frame/frame.hh
 ** \brief Declaration of frame::Frame.
 */

#pragma once

#include <iosfwd>

#include <temp/fwd.hh>
#include <frame/fwd.hh>
#include <temp/label.hh>

namespace frame
{

  /** \brief Stack frame (or activation record) of a function.

     The module frame is in charge of the ``low level frames''.
     ``Higher level frames'' are translate::Level.  A Level is
     basically a Frame that knows the Frame of its parent.

     To allocate a new local variable, call frame::Frame::local_alloc ()
     which returns a frame::Access.  That makes Frame a Factory of Access.

     The top level, which is the equivalent of ``main'' in C, of course,
     also needs a frame.

     In its suggestion of implementation, Andrew Appel stores in the class
     Frame the names of the frame pointer register, and of the return value
     register.  This introduces weird dependencies upon Frame in various
     places, or worse yet: it causes Frame to depend upon some value
     of target::Cpu.  It turns out it is not necessary: we can use the
     names `fp' and `rv' directly, and have them translated to their real
     name much later.  One problem remains that the sources are scattered
     with temp::TempFactory::create () invocation to create these registers.
     This should be factored out.
     */

  class Frame
  {
  public:
    Frame(const temp::Label& label);
    /// \brief Allocate a new frame.
    /// \param label    the name of the function
    /// \param escapes  a list of one Boolean per formal, stating whether
    ///                 it escapes.
    Frame(const temp::Label& label, const bool_list_type& escapes);
    /// Copy constructor.
    Frame(const Frame& src);

    /// Destroy this frame, and registered arguments (Frame::formals_).
    ~Frame();

    Frame& operator= (const Frame& src);

    /** \name Accessors.
     ** \{ */
    temp::Label label_get() const;
    const access_list_type& formals_get() const;
    int get_current_frame_size() const;
    /** \} */


    /** \name Allocation.
     ** \{ */
    /// Allocate space for a frame resident local.
    const InFrame* frame_alloc();

    /** \brief Allocate space for a local.
     **
     ** If it \a escapes, then store it in the frame. */
    const Access* local_alloc(bool escapes);

    /** \brief Allocate space for a new formal.
     **
     ** If it \a escapes, then store it in the frame. */
    const Access* formal_alloc(bool escapes);

    /// Allocate space for several possibly escaping formals.
    void formal_alloc(const bool_list_type& escapes);

    /** \brief Allocate at least \a n arguments dedicated word (s) in frame.
     **
     ** Used in code generation, when function's arguments need to be stored
     ** in frame. */
    void arg_add(size_t n);


  protected:
    const Access* alloc(bool escapes);

    /// Label of this frame: basically the name of the function.
    temp::Label label_;

    /** \brief Arguments of this function.

       The module `frame' depends upon the target, i.e., the
       architecture for which we are going to compile.  Because the
       call conventions depend upon the target, the module frame needs
       to know what are the formals of a function.  This is why they
       are stored here.  For other reasons, translate::Level also
       needs to store the formals of a function, giving a taste of
       duplication.  */
    access_list_type formals_;
    access_list_type locals_;

    /// Current local variable offset (i.e. size) in the stack frame.
    size_t offset_ = 0;
    /// Current argument offset.
    size_t arg_offset_ = 0;
  };

  /// Report \a f on \a o for debugging purpose.
  std::ostream& operator<< (std::ostream& o, const Frame& f);

} // namespace frame
