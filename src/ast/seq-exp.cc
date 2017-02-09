/**
 ** \file ast/seq-exp.cc
 ** \brief Implementation of ast::SeqExp.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/seq-exp.hh>
#include <ast/exp.hh>

namespace ast
{

  SeqExp::SeqExp(const Location& location,
                 exps_type* seq)
    : Exp(location)
    , seq_(seq)
  {}

  SeqExp::~SeqExp()
  {
    for (auto a : *seq_)
      delete a;
    delete seq_;
  }

  void
  SeqExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  SeqExp::accept(Visitor& v)
  {
    v(*this);
  }


} // namespace ast

