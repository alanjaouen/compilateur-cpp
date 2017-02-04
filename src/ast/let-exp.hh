/**
 ** \file ast/let-exp.hh
 ** \brief Declaration of ast::LetExp.
 */

#pragma once

#include <misc/contract.hh>
#include <ast/seq-exp.hh>
#include <ast/exp.hh>
#include <ast/decs-list.hh>

namespace ast
{

  /// LetExp.
  class LetExp : public Exp
  {
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a LetExp node.
    LetExp(const Location& location, DecsList* decs, SeqExp* seq);
    /// Destroy a LetExp node.
    virtual ~LetExp();
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    ///Return decs_.
    const DecsList & decs_get() const;
    ///Return decs_.
    DecsList& decs_get();
    ///Return seq_.
    const SeqExp& seq_get() const;
    ///Return seq_.
    SeqExp& seq_get();
    /** \} */

  protected:
    DecsList* decs_;
    SeqExp* seq_;

  };

} // namespace ast

#include <ast/let-exp.hxx>

