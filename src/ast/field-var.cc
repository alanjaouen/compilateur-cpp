/**
 ** \file ast/field-var.cc
 ** \brief Implementation of ast::FieldVar.
 */

#include <ast/visitor.hh>
#include <ast/field-var.hh>

namespace ast
{

  FieldVar::FieldVar(const Location& location, Var* lvalue, misc::symbol& name)
    : Var(location)
    , lvalue_(lvalue)
    , name_(name)
  {}
  /// Destroy a FieldVar node.
  FieldVar::~FieldVar()
  {
    delete lvalue_;
  }
  /** /} */

  /**
   * \name Visitors entry point.
   * \{ */
  /// Accept a const visitor \a v.
  void FieldVar::accept(ConstVisitor& v) const
  {
    v(*this);
  }
  /// Accept a non-const visitor \a v.
  void FieldVar::accept(Visitor& v)
  {
    v(*this);
  }
  /**  \} */

} // namespace ast

