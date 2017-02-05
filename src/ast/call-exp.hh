/**
 ** \file ast/call-exp.hh
 ** \brief Declaration of ast::CallExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/function-dec.hh>
#include <misc/symbol.hh>
#include <ast/seq-exp.hh>

namespace ast
{

  /// CallExp.
  class CallExp : public Exp
  {
  public:
    /**
     * \name Ctor & dtor.
     * \{ */
    /// Construct a CallExp node.
    CallExp(const Location& location, misc::symbol* name, SeqExp::seq_type* seq);
    /// Destroy a CallExp node.
    virtual ~CallExp();
    /** \} */

    /**
     * \name Visitors entry point.
     * \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /** \} */

    /**
     * \name Accessors.
     * \{ */
    /// Return the call expression.
    const SeqExp::seq_type& seq_get() const;
    /// Return the call expression.
    SeqExp::seq_type& seq_get();
    /// Return the function name.
    const misc::symbol* name_get() const;
    /// Return the function name.
    misc::symbol* name_get();
    /** \} */

  protected:
    /// The call expression.
    SeqExp::seq_type* seq_;
    //The function name.
    misc::symbol* name_;
  };

} // namespace ast

#include <ast/call-exp.hxx>

