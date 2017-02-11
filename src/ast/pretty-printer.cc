/**
 ** \file ast/pretty-printer.cc
 ** \brief Implementation of ast::PrettyPrinter.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <ast/pretty-printer.hh>
#include <misc/escape.hh>
#include <misc/indent.hh>
#include <misc/pair.hh>
#include <misc/separator.hh>

namespace ast
{
// Anonymous namespace: these functions are private to this file.
namespace
{
  /// \brief Output \a e on \a ostr.
  ///
  /// Used to factor the output of the name declared,
  /// and its possible additional attributes.
  inline std::ostream& operator<<(std::ostream& ostr, const Dec& e)
  {
    ostr << e.name_get();
    return ostr;
  }
}

PrettyPrinter::PrettyPrinter(std::ostream& ostr)
  : ostr_(ostr)
{
}

void PrettyPrinter::operator()(const NilExp&)
{
  ostr_ << "nil";
}

void PrettyPrinter::operator()(const IntExp& e)
{
  ostr_ << e.value_get();
}

void PrettyPrinter::operator()(const StringExp& e)
{
  ostr_ << e.value_get();
}

void PrettyPrinter::operator()(const ArrayExp& e)
{
  ostr_ << e.type_get().name_get() << '[' << e.l_exp_get() << "] of "
        << e.r_exp_get();
}

void PrettyPrinter::operator()(const RecordExp& e)
{
  ostr_ << e.id_get().name_get() << '{';
  for (const auto& exp : e.fini_get())
    ostr_ << exp->name_get() << '=' << exp->init_get() << ',';
  ostr_ << '}';
}

void PrettyPrinter::operator()(const ObjectExp& e)
{
  ostr_ << "new " << e.type_get();
}

void PrettyPrinter::operator()(const SimpleVar& e)
{
  ostr_ << e.name_get();
}

void PrettyPrinter::operator()(const FieldVar& e)
{
  ostr_ << e.lvalue_get() << '.' << e.name_get();
}

/* Foo[10]. */
void PrettyPrinter::operator()(const SubscriptVar& e)
{
  ostr_ << e.var_get() << '[' << misc::incendl << e.index_get()
        << misc::decendl << ']';
}

void PrettyPrinter::operator()(const CastVar& e)
{
  ostr_ << "_cast(" << e.var_get() << ", " << e.ty_get() << ')';
}

void PrettyPrinter::operator()(const CastExp& e)
{
  ostr_ << "_cast(" << e.exp_get() << ", " << e.ty_get() << ')';
}

void PrettyPrinter::operator()(const CallExp& e)
{
  ostr_ << e.name_get() << '(';
  for (auto& exp : e.seq_get())
    ostr_ << *exp;
  ostr_ << ')';
}

void PrettyPrinter::operator()(const MethodCallExp& e)
{
  ostr_ << e.lvalue_get() << '.' << e.name_get() << misc::incendl << '('
        << misc::incendl;
  for (auto& exp : e.seq_get())
    ostr_ << exp;
  ostr_ << misc::decendl << ')' << misc::decendl;
}

void PrettyPrinter::operator()(const OpExp& e)
{
  ostr_ << e.left_get() << ' ';
  ostr_ << str(e.oper_get()) << ' ' << e.right_get();
}

void PrettyPrinter::operator()(const AssignExp& e)
{
  ostr_ << e.var_get() << " := " << e.exp_get();
}

void PrettyPrinter::operator()(const IfExp& e)
{
  ostr_ << "(" << misc::incendl << "if "  << e.test_get()  << " then"
        << misc::incendl << e.then_get() << misc::decendl;
  if (e.else_get() != nullptr) // void!
    ostr_  << "else "
           << misc::incendl << *e.else_get() << misc::decendl;
  ostr_ << misc::decendl << ')' ;
}

void PrettyPrinter::operator()(const WhileExp& e)
{
  ostr_ << "while " << e.test_get() << " do" << misc::incendl << "("
        << misc::incendl << e.body_get() << misc::decendl
        << ")" << misc::decendl;
}

void PrettyPrinter::operator()(const ForExp& e)
{
  ostr_ << "for " << e.vardec_get().name_get()
        << " := " << *e.vardec_get().init_get() << " to " << e.hi_get() << " do"
        << misc::incendl << e.body_get() << misc::decendl;
}

void PrettyPrinter::operator()(const BreakExp&)
{
  ostr_ << "break";
}

void PrettyPrinter::operator()(const LetExp& e)
{
  ostr_ << "let" << misc::incendl << e.decs_get() << misc::decendl << "in"
        << misc::incendl << e.seq_get() << misc::decendl << "end";
}

void PrettyPrinter::operator()(const TypeDec& e)
{
  ostr_ << "type " << e.name_get() << " = " << e.ty_get() << misc::iendl;
}

void PrettyPrinter::operator()(const ClassTy& e)
{
  ostr_ << "class [ extends " << e.super_get().name_get() << " ]" << misc::iendl
        <<"{" << misc::incendl;
  for (auto& var : e.decs_get().decs_get())
    ostr_ << var;
  ostr_ << misc::decendl << "}";
}

void PrettyPrinter::operator()(const VarDec& e)
{
  ostr_ << "var " << e.name_get();
  if (e.type_name_get() != nullptr)
    ostr_ << " : " << *e.type_name_get();
  if (e.init_get() != nullptr)
    ostr_ << " := " << *e.init_get();
}

void PrettyPrinter::operator()(const FunctionDec& e)
{
  if (e.body_get() != nullptr)
    ostr_ << "function ";
  else
    ostr_ << "primitive ";
  ostr_ << e.name_get() << '(' << e.formals_get() << ')';
  if (e.result_get() != nullptr)
    ostr_ << " : " << *e.result_get();
  if (e.body_get() != nullptr)
    ostr_ << " =" << misc::iendl << '(' << misc::incendl << *e.body_get()
          << misc::decendl << ')';
}

void PrettyPrinter::operator()(const MethodDec& e)
{
  ostr_ << "method ";
  ostr_ << e.name_get() << '(' << e.formals_get() << ')';
  if (e.result_get() != nullptr)
    ostr_ << " : " << *e.result_get();
  ostr_ << " = " << misc::iendl << '(' << misc::incendl << *e.body_get()
        << misc::decendl << ')';
}

void PrettyPrinter::operator()(const NameTy& e)
{
  ostr_ << e.name_get();
}

void PrettyPrinter::operator()(const RecordTy& e)
{
  ostr_ << '{';
  for (auto& field : e.recs_get())
    ostr_ << field->name_get() << " : " << field->type_name_get() << " , ";
  ostr_ << '}';
}

void PrettyPrinter::operator()(const ArrayTy& e)
{
  ostr_ << "array of " << e.base_type_get().name_get();
}

void PrettyPrinter::operator()(const SeqExp& e)
{
  ostr_ << "(" << misc::incendl;
  for (auto& exp : e.seq_get())
    ostr_ << *exp << misc::iendl;
  ostr_ << ")" << misc::decendl;
}
  
  
} // namespace ast
