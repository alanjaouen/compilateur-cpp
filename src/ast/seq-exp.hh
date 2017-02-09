/**
 ** \file ast/seq-exp.hh
 ** \brief Declaration of ast::SeqExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{

  /// SeqExp.
  class SeqExp : public Exp
  {
  public:

    // /// Construct a SeqExp node.
    // SeqExp(const Location& location);

  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a SeqExp node.
    SeqExp(const Location& location, exps_type* seq);
    /// Destroy a SeqExp node.
    virtual ~SeqExp();
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
    /// Return declarations.
    const exps_type& seq_get() const;
    /// Return declarations.
    exps_type& seq_get();
    /** \} */
  protected:
    /// Declarations.
    exps_type* seq_;

  };

} // namespace ast

#include <ast/seq-exp.hxx>

