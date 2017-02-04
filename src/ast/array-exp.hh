/**
 ** \file ast/array-exp.hh
 ** \brief Declaration of ast::ArrayExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{

  /// ArrayExp.
  class ArrayExp : public Exp
  {
  public:
    ArrayExp(const Location& location, NameTy* type, Exp* l_exp, Exp* r_exp);
    virtual ~ArrayExp();

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return the name of the type.
    const NameTy& type_get() const;
    /// Set the name of the type.
    NameTy& type_get();
    ///Return l_exp
    const Exp& l_exp_get() const;
    Exp& l_exp_get();
    const Exp& r_exp_get() const;
    Exp& r_exp_get();
    /** \} */

  protected:
    NameTy* type_;
    Exp* l_exp_;
    Exp* r_exp_;
  };

} // namespace ast

#include <ast/array-exp.hxx>

