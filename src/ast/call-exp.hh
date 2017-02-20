/**
 ** \file ast/call-exp.hh
 ** \brief Declaration of ast::CallExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/function-dec.hh>
#include <ast/seq-exp.hh>
#include <misc/symbol.hh>

namespace ast
{
/**
 * \class ast::CallExp.
 * \brief FIXME
 *
 * FIXME
 */

/// CallExp.
class CallExp : public Exp
{
public:
  /**
   * \name Ctor & dtor.
   * \{ */
  /// Construct a CallExp node.
  CallExp(const Location& location, misc::symbol name, exps_type* seq);
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
  const exps_type& seq_get() const;
  /// Return the call expression.
  exps_type& seq_get();
  /// Return the function name.
  const misc::symbol& name_get() const;
  /// Return the function name.
  misc::symbol& name_get();
  /// Return definition site.
  const FunctionDec* def_get() const;
  /// Return definition site.
  FunctionDec* def_get();
  /// Set definition site.
  void def_set(FunctionDec*);

  /** \} */

protected:
  /// The call expression.
  exps_type* seq_;
  // The function name.
  misc::symbol name_;
  FunctionDec* def_;
};

} // namespace ast

#include <ast/call-exp.hxx>
