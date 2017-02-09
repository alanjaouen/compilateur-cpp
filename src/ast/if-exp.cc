/**
 ** \file ast/if-exp.cc
 ** \brief Implementation of ast::IfExp.
 */

#include <ast/visitor.hh>
#include <ast/if-exp.hh>

namespace ast
{
  IfExp::IfExp(const Location& location, Exp* test, Exp* Bthen, Exp* Belse)
    : Exp(location)
    , test_(test)
    , Bthen_(Bthen)
    , Belse_(Belse)
  {}
  IfExp::~IfExp()
  {
    delete test_;
    delete Bthen_;
    if (Belse_ != nullptr)
      delete Belse_;
  }
  void
  IfExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  IfExp::accept(Visitor& v)
  {
    v(*this);
  }
  
} // namespace ast

