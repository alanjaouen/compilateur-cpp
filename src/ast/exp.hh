/**
 ** \file ast/exp.hh
 ** \brief Declaration of ast::Exp.
 */

#pragma once

#include <ast/ast.hh>
#include <ast/typable.hh>

namespace ast
{

  /// Exp.
  class Exp : public Ast, public Typable
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an Exp node.
    Exp(const Location& location);
    /// Destroy an Exp node.
    virtual ~Exp() = default;
    bool is_test_get();
    void is_test_set(bool is_test);

    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override = 0;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override = 0;
    /// \}
  protected:
    bool is_test_ = false;
  };

} // namespace ast

#include <ast/exp.hxx>

