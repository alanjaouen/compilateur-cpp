/**
 ** \file ast/field-var.hh
 ** \brief Declaration of ast::FieldVar.
 */

#pragma once

#include <ast/var.hh>
#include <misc/symbol.hh>

namespace ast
{


  /**
   * \class ast::FieldVar
   * \brief FIXME
   *
   * FIXME
   */

  /// FieldVar.
  class FieldVar : public Var
  {
  public:
    /**
     * \name Ctor & dtor.
     * \{ */
    /// Construct a FieldVar node.
    FieldVar(const Location& location, Var* lvalue, misc::symbol& name);
    /// Destroy a FieldVar node.
    virtual ~FieldVar();
    /** /} */

    /**
     * \name Visitors entry point.
     * \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /**  \} */

    /**
     * \name Accessors.
     * \{ */
    /// Return the field variable.
    const Var& lvalue_get() const;
    /// Return the field variable.
    Var& lvalue_get();
    /// Return the field of the variable.
    const misc::symbol& name_get() const;
    /// Return the name of the variable.
    misc::symbol& name_get();
    /** /} */

  protected:
    /// The field variable.
    Var* lvalue_;
    /// The field of the variable.
    misc::symbol& name_;
  };

} // namespace ast

#include <ast/field-var.hxx>

