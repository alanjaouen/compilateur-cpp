/**
 ** \file frame/access.hh
 ** \brief Location of a local variable.
 */

#pragma once

#include <iosfwd>

#include <temp/fwd.hh>
#include <temp/temp.hh>
#include <tree/fwd.hh>
#include <frame/fwd.hh>

namespace frame
{

  /** \brief Variables have to be stored.  There are two kinds of
      places: saved in a register, or in the frame.  Access abstracts
      both.

      Actually, so called register here are temporaries, i.e., we
      pretend there is an infinite set of registers.  Later in the
      compiler, when allocating the registers, temporaries will be
      mapped onto real registers (maybe spilling some temporaries into
      the frame).

      An Access is the abstraction of this: either InRegister, or
      InFrame.  */
  class Access
  {
  public:
    Access() = default;
    virtual ~Access() = default;

    /// Used for debugging.
    virtual std::ostream& dump(std::ostream& ostr) const = 0;

    /** \brief Return a Tree expression that gives the location of THIS.
        If it is in the frame, then the result is something like
        Mem (Temp fp + OFFSET).  */
    virtual tree::rExp exp() const;

    /** \brief Same as above, but use FP instead of `Temp fp'.
        Useful to access escaped variables.  */
    virtual tree::rExp exp(const tree::rExp& fp) const = 0;

    /// \brief Return a copy of the actual Access.
    virtual Access* clone() const = 0;
  };

  /// Report \a acc on \a ostr.
  std::ostream& operator<< (std::ostream& ostr, const Access& acc);



  /*--------------.
  | InRegister.   |
  `--------------*/


  ///  Local variable stored in register.
  class InRegister : public Access
  {
  public:
    // Import overloaded virtual method.
    using Access::exp;

    InRegister();

    /// Used for special registers such as FP, RV, etc.
    InRegister(const temp::Temp& temp);

    /// The temporary referenced by this Access.
    temp::Temp temp_get() const;

    std::ostream& dump(std::ostream& ostr) const override;

    /**
     ** \see Access::exp ().*/
    tree::rExp exp(const tree::rExp& fp) const override;

    /**
     ** \see Access::clone ().*/
    InRegister* clone() const override;

  private:
    /// The temporary referenced here.
    temp::Temp temp_;
  };


  /*-----------.
  | InFrame.   |
  `-----------*/

  /// Local variable stored in the stack frame.
  class InFrame : public Access
  {
  public:
    // Import overloaded virtual method.
    using Access::exp;

    InFrame(int offset);

    /// The offset of this Access.
    int offset_get() const;

    std::ostream& dump(std::ostream& ostr) const override;

    /**
     ** \see Access::exp ().*/
    tree::rExp exp(const tree::rExp& fp) const override;

    /**
     ** \see Access::clone ().*/
    InFrame* clone() const override;

  private:
    /// The offset from the frame pointer referenced by this Access.
    int offset_;
  };

} // namespace frame

#include <frame/access.hxx>
