/**
 ** \file ast/array-exp.cc
 ** \brief Implementation of ast::ArrayExp.
 */

#include <ast/visitor.hh>
#include <ast/array-exp.hh>

namespace ast
{

  ArrayExp::ArrayExp(const Location& location, NameTy* type, Exp* l_exp,
                    Exp* r_exp)
    : Exp(location)
    , type_(type)
    , l_exp_(l_exp)
    , r_exp_(r_exp)
{}

  ArrayExp::~ArrayExp()
  {
    delete type_;
    delete l_exp_;
    delete r_exp_;
  }

  /// \name Visitors entry point.
  /// \{ */
  /// Accept a const visitor \a v.
    void ArrayExp::accept(ConstVisitor& v) const
    {
      v(*this);
    }
  /// Accept a non-const visitor \a v.
  void ArrayExp::accept(Visitor& v)
  {
    v(*this);
  }
  /// \}


} // namespace ast

