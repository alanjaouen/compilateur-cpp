/**
 ** \file ast/assign-exp.hh
 ** \brief Declaration of ast::AssignExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/var.hh>

namespace ast
{

  /// AssignExp.
  class AssignExp : public Exp
  {
  public:
    AssignExp(Location& location, Var* lvalue, Exp* exp);
    virtual ~AssignExp();

    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;


    const Var& var_get() const;
    Var& var_get();
    const Exp& exp_get() const;
    Exp& exp_get();


  protected:
    Var* lvalue_;
    Exp* exp_;
  };

} // namespace ast

#include <ast/assign-exp.hxx>

