/**
 ** \file ast/method-call-exp.hh
 ** \brief Declaration of ast::MethodCallExp.
 */

#pragma once

#include <ast/call-exp.hh>
#include <ast/method-dec.hh>
#include <ast/var.hh>

namespace ast
{

  /** \class ast::MethodCallExp
   ** \brief Method call.
   **
   ** A method call is \em not a function call in the strict sense
   ** of object-oriented programming.  Inheritance is used as a
   ** factoring tool here.
   */

  class MethodCallExp : public CallExp
  {
  public:
    /**
     * \name Ctor & dtor.
     * \{ */
    /// Construct a MethodCallExp node.
    MethodCallExp(const Location& location, const misc::symbol& name,
                  ast::exps_type* seq, Exp* lvalue);
    /// Destroy a MethodCallExp node.
    virtual ~MethodCallExp();
    /** \} */

    /**
     * \name Visitors entry point.
     * \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;


    /**
     * \name Accessors.
     * \{ */
    /// Return the call expression.
    const Exp& lvalue_get() const;
    /// Return the call expression.
    Exp& lvalue_get();
    /** \} */


  protected:
    Exp* lvalue_;
  };

} // namespace ast

#include <ast/method-call-exp.hxx>

