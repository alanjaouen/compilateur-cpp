/**
 ** \file ast/method-call-exp.cc
 ** \brief Implementation of ast::MethodCallExp.
 */

#include <ast/visitor.hh>
#include <ast/method-call-exp.hh>

namespace ast
{

  MethodCallExp::MethodCallExp(const Location& location, const misc::symbol& name,
                               ast::exps_type* seq, Exp* lvalue)
    : CallExp(location, name, seq)
    , lvalue_(lvalue)
  {}
  /// Destroy a MethodCallExp node.
  MethodCallExp::~MethodCallExp()
  {
    delete lvalue_;
  }
  /** \} */

  /**
   * \name Visitors entry point.
   * \{ */
  /// Accept a const visitor \a v.
  void MethodCallExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }
  /// Accept a non-const visitor \a v.
  void MethodCallExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

