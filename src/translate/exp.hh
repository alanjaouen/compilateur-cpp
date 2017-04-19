/**
 ** \file translate/exp.hh
 ** \brief Classes Exp, Ex, Cx, Nx, and Ix.
 **
 ** The class defined in this file are helping tools for the
 ** translation.
 **
 ** The idea is quite simple: at some moment the tree::expressions
 ** should actually be used as simple tree::statement.  Also, it would
 ** be stupid to keep something like `a < b' as an expression which
 ** gives one or zero, and then, when used in a condition implement
 ** something like `if (a < b) <> 0 then...'.
 **
 ** The idea is that every tree::expression or tree::statement will be
 ** kept in a structure which reflects its *natural* usage, but this
 ** structure must be able to present an entity (such as a
 ** tree::expression) as a statement when needed, or as a conditional
 ** etc.
 **
 ** There are basically three families (actually, there are four, the
 ** fourth one being defined further below):
 **
 ** - Ex
 **
 **   The family of what is naturally a tree::expression, i.e.,
 **   something which has a value.  Can be used as an expression, or
 **   statement, or conditional (in which case what is important is
 **   whether it evaluates to zero, or not).
 **
 ** - Nx
 **
 **   The family of the statements, i.e., what has no value.  Can only
 **   be used as a statement: it is abnormal (hence abort()) to use it
 **   as an expression or a conditional.  This should never happen: the
 **   type checking actually guarantees it never happens.
 **
 ** - Cx
 **
 **   The family of the conditionals, i.e., what used to be written
 **   with relative operators in Tiger (<, <> etc.).  Since our goal is
 **   to translate a `if a < b then...' into `CJUMP(<, a, b, ...)', we
 **   need to remember what is the operator, and what are its
 **   arguments.  Of course, this can be used as a conditional (CJUMP),
 **   as an expression (in which case we must return 0 or 1), or as a
 **   statement (in case someone wrote `a < b' alone in Tiger for
 **   instance, even if it looks brain dead).
 **
 ** So we have Ex, Nx and Cx which we want to be able to read as if
 ** they were Ex (in which case we will un-Ex or de-Ex them thanks to
 ** un_ex(), or read as Nx thanks to un_nx(), or finally un_cx() if used
 ** as conditional.
 **
 ** un_ex and un_nx need no argument, but un_cx means building a CJUMP.
 ** A CJUMP, when you build it, needs 5 args: the operator and two
 ** arguments (which you always have or can easily simulate), and two
 ** NAMEs which correspond to the THEN and the ELSE.  Then, naturally, un_cx
 ** will need two additional arguments: the tree::Label to which you
 ** are branching.
 **
 ** Using this scheme works fine.
 **
 ** However, there is room for improvement.  Consider the following program:
 **
 **    if if 1 then 2 else 3 then 4 else 5
 **
 ** Using the implementation suggested above, you will first compute
 ** the result of the inner if-then-else into a temporary, and then
 ** check whether this temporary is 0 or not.  A better implementation
 ** would try to branch to `4' at the end of the `2' if 2 appears to be
 ** different from 0, otherwise branch to 5, and likewise in the else
 ** branch.
 **
 ** In other words, instead of having a cascade of `set a temporary,
 ** and then decode the temporary', the idea is to directly branch from
 ** the then and else parts.  This will typically give much better code
 ** for things like
 **
 ** if 0 < a & a < b & b < c & c < 3 then impossible := 1
 **
 ** In order to do this, you need to keep the structure of the
 ** if-then-else, i.e., keep the test, then and else clauses separated.
 ** An extra class is needed, Ix.
 **
 **
 ** The memory management is quite simple: calling un_xx will delete the
 ** object.  This means that each Exp object must be un_xx'ed exactly
 ** once: if less, there is a memory leak, if more, then a free'd object
 ** is reused.
 **/

#pragma once

#include <iosfwd>
#include <tree/all.hh>
#include <temp/fwd.hh>
#include <frame/frame.hh>


namespace translate
{

  /*------.
  | Exp.  |
  `------*/

  /// Root for all the following classes.
  class Exp
  {
  public:
    virtual ~Exp() = default;
    virtual std::ostream& dump(std::ostream&) const = 0;

    /// Pretend THIS was an Ex: return the expression part.
    virtual tree::rExp un_ex() = 0;

    /// Pretend THIS was an Nx: return the statement part.
    virtual tree::rStm un_nx() = 0;

    /// \brief Pretend THIS was a Cx: return the branching such that
    /// the resulting code jump to \a t if the conditional is
    /// satisfied, \a f otherwise.
    virtual tree::rStm un_cx(const temp::Label& t, const temp::Label& f) = 0;
  };

  /// Reference counted Exp pointer.
  using rExp = misc::ref<Exp>;

  /// Report \a exp on \a ostr.
  std::ostream& operator<< (std::ostream& ostr, const Exp& exp);


  /*-----.
  | Cx.  |
  `-----*/

  /// Natural representation for conditionals.
  class Cx : public Exp
  {
  public:
    Cx(tree::Cjump::Relop op,
       const tree::rExp& left, const tree::rExp& right);

    /// To convert a conditional into an expression means return 0 or 1.
    tree::rExp un_ex() override;
    tree::rStm un_nx() override;
    tree::rStm un_cx(const temp::Label& t, const temp::Label& f) override;

    std::ostream& dump(std::ostream& ostr) const override;

  private:
    tree::Cjump::Relop op_;
    tree::rExp left_;
    tree::rExp right_;
  };

  /// Reference counted Cx pointer.
  using rCx = misc::ref<Cx>;


  /*-----.
  | Ex.  |
  `-----*/

  /// Natural representation for expressions.
  class Ex : public Exp
  {
  public:
    Ex(const tree::rExp& exp);

    tree::rExp un_ex() override;
    tree::rStm un_nx() override;
    tree::rStm un_cx(const temp::Label& t, const temp::Label& f) override;

    std::ostream& dump(std::ostream& ostr) const override;

  private:
    tree::rExp exp_;
  };

  /// Reference counted Ex pointer.
  using rEx = misc::ref<Ex>;


  /*-----.
  | Nx.  |
  `-----*/

  /// Natural representation for statements.
  class Nx : public Exp
  {
  public:
    Nx(const tree::rStm& stm);

    tree::rExp un_ex() override;
    tree::rStm un_nx() override;
    tree::rStm un_cx(const temp::Label&, const temp::Label&) override;

    std::ostream& dump(std::ostream& ostr) const override;

  private:
    tree::rStm stm_;
  };

  /// Reference counted Nx pointer.
  using rNx = misc::ref<Nx>;


  /*-----.
  | Ix.  |
  `-----*/

  /// Specialization of Exp for branchings.
  class Ix : public Exp
  {
  public:
    Ix(rExp& cond, rExp& iftrue, rExp& iffalse);

    tree::rExp un_ex() override;
    tree::rStm un_nx() override;
    tree::rStm un_cx(const temp::Label& t_outer,
                     const temp::Label& f_outer) override;

    std::ostream& dump(std::ostream& ostr) const override;

  private:
    rExp cond_;
    rExp iftrue_;
    rExp iffalse_;
  };

  /// Reference counted Ix pointer.
  using rIx = misc::ref<Ix>;

} // namespace translate


#include <translate/exp.hxx>
