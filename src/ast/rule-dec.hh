/**
 ** \file ast/rule-dec.hh
 ** \brief Declaration of ast::RuleDec.
 */

#pragma once

#include <ast/dec.hh>
#include <ast/exp.hh>

namespace ast
{

  /// RuleDec.
  class RuleDec : public Dec
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a RuleDec node.
    RuleDec(const Location& location, const misc::symbol& name, Exp* match,
            Exp* build);
    /// Destroy a RuleDec node.
    virtual ~RuleDec();
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
    /// Return pattern to match.
    const Exp& match_get() const;
    /// Return pattern to match.
    Exp& match_get();
    /// Return code to build upon a match.
    const Exp& build_get() const;
    /// Return code to build upon a match.
    Exp& build_get();
    /** \} */

  protected:
    /// Pattern to match.
    Exp* match_;
    /// Code to build upon a match.
    Exp* build_;
  };

} // namespace ast

#include <ast/rule-dec.hxx>

