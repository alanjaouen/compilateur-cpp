/**
 ** \file ast/record-exp.hh
 ** \brief Declaration of ast::RecordExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/field-init.hh>
#include <ast/name-ty.hh>
#include <ast/any-decs.hh>
namespace ast
{

  /// RecordExp.
  class RecordExp : public Exp
  {

  public:
    RecordExp(Location& location, FieldInits* vect);
    ~RecordExp();
    void accept(Visitor& v);
    void accept(ConstVisitor& v) const;
    
  private:
    FieldInits *vect_;
  };

} // namespace ast

#include <ast/record-exp.hxx>

