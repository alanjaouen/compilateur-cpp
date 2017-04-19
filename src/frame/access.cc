/**
 ** \file frame/access.cc
 ** \brief Location of a local variable.
 */

#include <temp/temp.hh>
#include <tree/all.hh>
#include <frame/access.hh>
#include <frame/frame.hh>

namespace frame
{

  /*---------.
  | Access.  |
  `---------*/

  // When called without specifying the value of the frame pointer,
  // assume it is relatively to the *current* frame pointer.
  tree::rExp
  Access::exp() const
  {
    temp::Temp fp("fp");
    return exp(new tree::Temp(fp));
  }

  std::ostream&
  operator<<(std::ostream& ostr, const Access& acc)
  {
    return acc.dump(ostr);
  }


  /*--------------.
  | InRegister.   |
  `--------------*/

  InRegister::InRegister()
    : temp_(temp::Temp())
  {}

  InRegister::InRegister(const temp::Temp& temp)
    : temp_(temp)
  {}

  tree::rExp
  InRegister::exp(const tree::rExp&) const
  {
    return new tree::Temp(temp_);
  }

  InRegister*
  InRegister::clone() const
  {
    return new InRegister(temp_get());
  }

  std::ostream&
  InRegister::dump(std::ostream& ostr) const
  {
    return ostr << "InReg (" << temp_ << ")";
  }


  /*-----------.
  | InFrame.   |
  `-----------*/

  InFrame::InFrame(int offset)
    : offset_(offset)
  {}

  tree::rExp
  InFrame::exp(const tree::rExp& fp) const
  {
    tree::rExp indir;
    if (offset_)
      indir = new tree::Binop(tree::Binop::add,
                              fp,
                              new tree::Const(offset_));
    else
      indir = fp;
    return new tree::Mem(indir);
  }

  InFrame*
  InFrame::clone() const
  {
    return new InFrame(offset_get());
  }

  std::ostream&
  InFrame::dump(std::ostream& ostr) const
  {
    return ostr << "InFrame (" << offset_ << ")";
  }

} // namespace frame
