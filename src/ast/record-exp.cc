/**
 ** \file ast/record-exp.cc
 ** \brief Implementation of ast::RecordExp.
 */

#include <misc/algorithm.hh>
#include <ast/visitor.hh>
#include <ast/record-exp.hh>

namespace ast
{
  RecordExp::RecordExp(Location& location, FieldInits* vect)
    : Exp(location)
    , vect_(vect)
  {}
  RecordExp::~RecordExp()
  {
    // delete vect_;
  }
  void RecordExp::accept(Visitor& v)
  {
    v(*this);
  }
  void RecordExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }
    
} // namespace ast

