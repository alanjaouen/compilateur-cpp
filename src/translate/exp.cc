/**
 ** \file translate/exp.cc
 ** \brief Implementation for translate/exp.hh.
 **/

#include <iostream>

#include <temp/temp.hh>
#include <temp/label.hh>
#include <translate/exp.hh>

namespace translate
{
  /*-----.
  | Cx.  |
  `-----*/


  // To convert a conditional into an expression means return 0 or
  // 1.
  tree::rExp
  Cx::un_ex()
  {
  // FIXME: Some code was deleted here.
  }

  tree::rStm
  Cx::un_nx()
  {
  // FIXME: Some code was deleted here.
  }

  tree::rStm
  Cx::un_cx(const temp::Label& t, const temp::Label& f)
  {
    return new tree::Cjump(op_,
                           left_, right_,
                           new tree::Name(t), new tree::Name(f));
  }

  std::ostream&
  Cx::dump(std::ostream& ostr) const
  {
    return ostr << "Cx(" << op_ << ", "
           << *left_ << ", " << *right_ << ")";
  }


  /*-----.
  | Ex.  |
  `-----*/

  tree::rExp
  Ex::un_ex()
  {
  // FIXED forest_b
    return exp_;
  }

  tree::rStm
  Ex::un_nx()
  {
  // FIXME: Some code was deleted here.
    return Nx(
              new tree::Sxp(exp_)).un_nx();
  }

  tree::rStm
  Ex::un_cx(const temp::Label& t, const temp::Label& f)
  {
    return Cx(tree::Cjump::ne,
              exp_,
              new tree::Const(0)).un_cx(t, f);
  }

  std::ostream&
  Ex::dump(std::ostream& ostr) const
  {
    return ostr << "Ex(" << *exp_ << ")";
  }


  /*-----.
  | Nx.  |
  `-----*/

  tree::rExp
  Nx::un_ex()
  {
    // Impossible.
    std::cerr << "Trying to tree::Exp& un_ex(): "
              << *this
              << std::endl;
    unreachable();
  }

  tree::rStm
  Nx::un_nx()
  {
    return stm_;
  }

  tree::rStm
  Nx::un_cx(const temp::Label&, const temp::Label&)
  {
    // Impossible.
    std::cerr << "Trying to tree::Stm& un_cx(): "
              << *this
              << std::endl;
    unreachable();
  }

  std::ostream&
  Nx::dump(std::ostream& ostr) const
  {
    return ostr << "Nx(" << *stm_ << ")";
  }



  /*-----.
  | Ix.  |
  `-----*/

  tree::rExp
  Ix::un_ex()
  {
    // The value computed by both branches is wanted, save it in
    // RESULT.
    temp::Temp result;
    temp::Label t;
    temp::Label f;
    temp::Label join;

    tree::rSeq s = new tree::Seq
    {
      cond_->un_cx(t, f),
      new tree::Label(t),
      new tree::Move(new tree::Temp(result), iftrue_->un_ex()),
      new tree::Jump(new tree::Name(join)),
      new tree::Label(f),
      new tree::Move(new tree::Temp(result), iffalse_->un_ex()),
      new tree::Label(join)
    };
    return new tree::Eseq(s, new tree::Temp(result));
  }

  tree::rStm
  Ix::un_nx()
  {
  // FIXME: Some code was deleted here.
  }

  tree::rStm
  Ix::un_cx(const temp::Label& t_outer, const temp::Label& f_outer)
  {
  // FIXME: Some code was deleted here.
  }

  std::ostream&
  Ix::dump(std::ostream& ostr) const
  {
    return ostr << "Ix("
           << *cond_ << ", " << *iftrue_ << ", " << *iffalse_
           << ")";
  }

} // namespace translate
