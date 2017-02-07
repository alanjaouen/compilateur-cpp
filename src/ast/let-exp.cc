/**
 ** \file ast/let-exp.cc
 ** \brief Implementation of ast::LetExp.
 */

#include <ast/visitor.hh>
#include <ast/let-exp.hh>

namespace ast
{

  LetExp::LetExp(const Location& location, DecsList* decs, exps_type* vect)
    : Exp(location)
    , decs_(decs)
    , vect_(vect)
  {}

  LetExp::~LetExp()
  {
    delete decs_;
    delete vect_;
  }

  void
  LetExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  LetExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

