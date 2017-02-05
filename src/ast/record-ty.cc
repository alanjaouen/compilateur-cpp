/**
 ** \file ast/record-ty.cc
 ** \brief Implementation of ast::RecordTy.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/record-ty.hh>

namespace ast
{

  RecordTy(const Location& location)
    : Ty(location)
  {}
  virtual ~RecordTy()
  {
    delete recs;
  }
  /// \name Visitors entry point.
  /// \{ */
  /// Accept a const visitor \a v.
  void accept(ConstVisitor& v) const override
  {}
  /// Accept a non-const visitor \a v.
  void accept(Visitor& v) override
  {}
  /// \}

  /// Prepend \a d.
  void push_front(Field* d)
  {
    decs_.emplace_front(d);
    location_.begin = d->location_get().begin;
  }
  /// Append \a d.
  void emplace_back(Field* d)
  {
        decs_.emplace_back(d);
    location_.end = d->location_get().end;
  }

  /// Splice the content of \a ds in front of this list.
  void splice_front(RecordTy& rs)
  {
    decs_.splice(decs_.begin(), ds.decs_get());
  }
  /// Splice the content of \a ds at the back this list.
  void splice_back(RecordTy& rs)
  {}


} // namespace ast

