/**
 ** \file tree/fragment.hh
 ** \brief Declaration of tree::Fragment.
 **
 ** This file may change in the future, if you need to change
 ** something, first tell me why.
 **/

#pragma once

#include <iosfwd>

#include <misc/symbol.hh>
#include <frame/frame.hh>
#include <temp/temp.hh>
#include <tree/fwd.hh>
#include <tree/visitor.hh>
#include <temp/label.hh>
#include <temp/temp.hh>

namespace tree
{

  /*-----------.
  | Fragment.  |
  `-----------*/

  /** \brief Piece of intermediate representation resource.

  A Tiger program may include strings.  These strings are not left as
  is in the body of the IR, rather we associate a label to them, and
  use that label instead.

  We store the string elsewhere, to be output in a format which is
  assembly language dependent.  DataFrag are used for this.  It is
  under the responsibility of translate:: to keep all the fragments.

  The same thing happens with function declarations: they will be
  output elsewhere.  This is what ProcFrag is used for.  */
  class Fragment
  {
  public:
    virtual std::ostream& dump(std::ostream& o) const = 0;

    virtual ~Fragment() = default;

    /** \name Visitors entry point.
     ** \{ */
  public:
    /// Accept a Visitor \a v.
    virtual void accept(Visitor& v) = 0;
    virtual void accept(ConstVisitor& v) const = 0;
    /** \} */
  };

  std::ostream& operator<<(std::ostream& o, const Fragment& f);


  /*--------------------.
  | DataFrag: strings.  |
  `--------------------*/

  /// Fragment for a string data.
  class DataFrag : public Fragment
  {
  public:
    DataFrag(const temp::Label& label, const std::string& data);

    std::ostream& dump(std::ostream& o) const override;

    /** \name Accessors.
     ** \{ */
    /// Data label.
    temp::Label label_get() const;

    /// Data.
    const std::string& data_get() const;
    /** \} */

    /** \name Visitors entry point.
     ** \{ */
  public:
    /// Accept a Visitor \a v.
    void accept(Visitor& v) override;
    void accept(ConstVisitor& v) const override;
    /** \} */

  protected:
    temp::Label label_;
    std::string data_;
  };


  /*-----------------------.
  | ProcFrag: procedures.  |
  `-----------------------*/

  /** \brief Fragment for some code `data'.

  Procedures need a LABEL, so that we can jump to them, a BODY to
  execute, but also details in the prologue and the epilogue which
  depend upon the content of the frame of the function.  So we also
  need to store its FRAME. */
  class ProcFrag : public Fragment
  {
  public:
    /** \name Constructor and Destructor.
     ** \{ */
    ProcFrag(const temp::Label& label,
             const misc::symbol& name,
             const rStm& body,
             const frame::Frame* frame);

    ~ProcFrag();
    /** \} */

    /** \name Accessors.
     ** \{ */
    /// Code label.
    temp::Label label_get() const;

    /// Procedure name.
    const misc::symbol& name_get() const;

    /// Body.
    rStm body_get() const;
    void body_set(const rStm& body);

    /// Procedure frame.
    const frame::Frame& frame_get() const;
    /** \} */

    /// Display this fragment.
    std::ostream& dump(std::ostream& o) const override;

     /** \name Visitors entry point.
     ** \{ */
  public:
    /// Accept a Visitor \a v.
    void accept(Visitor& v) override;
    void accept(ConstVisitor& v) const override;
    /** \} */

  private:
    /// This function's label.
    temp::Label label_;
    /// The function's original (possibly ambiguous) name.
    const misc::symbol name_;
    /// The function's body.
    rStm body_;
    /// The frame, including accesses to locals and formals.
    const frame::Frame* frame_;
    /// To save/restore the frame pointer.
    temp::Temp save_fp_;
  };


} // namespace tree

#include <tree/fragment.hxx>
