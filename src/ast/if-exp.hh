/**
 ** \file ast/if-exp.hh
 ** \brief Declaration of ast::IfExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/seq-exp.hh>

namespace ast
{

  /// IfExp.
  class IfExp : public Exp
  {
        /** \name Ctor & dtor.
     ** \{ */
    /// Construct a IfExp node.
    IfExp(Location& location, Exp* test, Exp* Bthen, Exp* Belse = nullptr);
    /// Destroy a IfExp node.
    virtual ~IfExp();
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
    /// Return test declaration.
    const Exp& test_get() const;
    /// Return test declaration.
    Exp& test_get();
    /// Return instructions executed in the then.
    const Exp& then_get() const;
    /// Return instructions executed in the then..
    Exp& then_get();
    /// Return instructions executed in the else clause.
    const Exp& else_get() const;
    /// Return instructions executed in the else clause.
    Exp& else_get();
    /** \} */

  protected:
    Exp* test_;
    Exp* Bthen_;
    Exp* Belse_;
  };

} // namespace ast

#include <ast/if-exp.hxx>

