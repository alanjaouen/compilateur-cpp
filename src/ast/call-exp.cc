/**
 ** \file ast/call-exp.cc
 ** \brief Implementation of ast::CallExp.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/call-exp.hh>

namespace ast
{

  CallExp::CallExp(const Location& location, misc::symbol* name,
                   SeqExp::seq_type* seq)
    : Exp(location)
    , name_(name)
    , seq_(seq)
  {}

  CallExp::~CallExp()
  {
    delete seq_;
    delete name_;
  }

  void
  CallExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  CallExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

