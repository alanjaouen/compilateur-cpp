/**
 ** \file ast/record-ty.cc
 ** \brief Implementation of ast::RecordTy.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/record-ty.hh>

namespace ast
{

  RecordTy::RecordTy(const Location& location)
    : Ty(location)
  {}
  RecordTy::~RecordTy()
  {
    misc::deep_clear(recs_);
  }
  /// \name Visitors entry point.
  /// \{ */
  /// Accept a const visitor \a v.
  void RecordTy::accept(ConstVisitor& v) const
  {
    v(*this);
  }
  /// Accept a non-const visitor \a v.
  void RecordTy::accept(Visitor& v)
  {
    v(*this);
  }
  /// \}

  /// Prepend \a d.
  void RecordTy::push_front(Field* d)
  {
    recs_.emplace_front(d);
    location_.begin = d->location_get().begin;
  }
  /// Append \a d.
  void RecordTy::emplace_back(Field* d)
  {
        recs_.emplace_back(d);
    location_.end = d->location_get().end;
  }

  /// Splice the content of \a ds in front of this list.
  void RecordTy::splice_front(RecordTy& rs)
  {
    recs_.splice(recs_.begin(), rs.recs_get());
  }

  /// Splice the content of \a ds at the back this list.
  void RecordTy::splice_back(RecordTy& rs)
  {
    recs_.splice(recs_.end(), rs.recs_get());
  }


} // namespace ast

