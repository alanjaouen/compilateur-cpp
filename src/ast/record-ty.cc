/**
 ** \file ast/record-ty.cc
 ** \brief Implementation of ast::RecordTy.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/record-ty.hh>

namespace ast
{

  RecordTy::RecordTy(const Location& location, fields_type* vect)
    : Ty(location)
    , vect_(vect)
  {}
  RecordTy::~RecordTy()
  {
    delete vect_;
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


} // namespace ast

