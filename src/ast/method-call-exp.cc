/**
 ** \file ast/method-call-exp.cc
 ** \brief Implementation of ast::MethodCallExp.
 */

#include <ast/visitor.hh>
#include <ast/method-call-exp.hh>

namespace ast
{

  MethodCallExp::MethodCallExp(const Location& location, Var::Var* lvalue);
  /// Destroy a MethodCallExp node.
  virtual MethodCallExp::~MethodCallExp();
  /** \} */

  /**
   * \name Visitors entry point.
   * \{ */
  /// Accept a const visitor \a v.
  void MethodCallExp::accept(ConstVisitor& v) const override;
  /// Accept a non-const visitor \a v.
  void MethodCallExp::accept(Visitor& v) override;

} // namespace ast

