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
  void
  SeqExp::push_front(Exp* e)
  {
    seq_.emplace_front(e);
    location_.begin = e->location_get().begin;
  }

  void
  SeqExp::emplace_back(Exp* e)
  {
    seq_.emplace_back(e);
    location_.begin = e->location_get().end;
  }

  void
  SeqExp::splice_front(SeqExp& es)
  {
    seq_.splice(seq_.begin(), es.seq_get());
  }

  void
  SeqExp::splice_back(SeqExp& es)
  {
    seq_.splice(seq_.end(), es.seq_get());
  }

  SeqExp::SeqExp(const Location& location)
    : Exp(location)
  {}

  SeqExp::SeqExp(const Location& location,
                 const SeqExp::seq_type& seq)
    : Exp(location)
    , seq_(seq)
  {}

  SeqExp::~SeqExp()
  {
    misc::deep_clear(seq_);
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

