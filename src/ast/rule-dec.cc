/**
 ** \file ast/rule-dec.cc
 ** \brief Implementation of ast::RuleDec.
 */

#include <ast/visitor.hh>
#include <ast/rule-dec.hh>

namespace ast
{

  RuleDec::RuleDec(const Location& location, const misc::symbol& name,
                   Exp* match, Exp* build)
    : Dec(location, name)
    , match_(match)
    , build_(build)
  {}

  RuleDec::~RuleDec()
  {
    delete match_;
    delete build_;
  }

  void
  RuleDec::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  RuleDec::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

