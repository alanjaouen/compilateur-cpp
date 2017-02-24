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
    /// Output \a e on \a ostr.
    inline
    std::ostream&
    operator<< (std::ostream& ostr, const Escapable& e)
    {
      if (escapes_display(ostr)
  // FIXME: Some code was deleted here.
          )
        ostr << "/* escaping */ ";

      return ostr;
    }

    /// \brief Output \a e on \a ostr.
    ///
    /// Used to factor the output of the name declared,
    /// and its possible additional attributes.
    inline
    std::ostream&
    operator<< (std::ostream& ostr, const Dec& e)
    {
      ostr << e.name_get();
      if (bindings_display(ostr))
        ostr << " /* " << &e << " */";
      return ostr;
    }
  }



  PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ostr_(ostr)
  {}


  void
  PrettyPrinter::operator()(const SimpleVar& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */";
  }

  void
  PrettyPrinter::operator()(const FieldVar& e)
  {
    ostr_ << e.lvalue_get();
  }

  /* Foo[10]. */
  void
  PrettyPrinter::operator()(const SubscriptVar& e)
  {
    ostr_ << e.var_get() << '[' << misc::incindent << e.index_get()
          << misc::decindent << ']';
  }

  void
  PrettyPrinter::operator()(const CastVar& e)
  {
    ostr_ << "_cast(" << e.var_get() << ", " << e.ty_get() << ')';
  }

  void
  PrettyPrinter::operator()(const CastExp& e)
  {
    ostr_ << "_cast(" << e.exp_get() << ", " << e.ty_get() << ')';
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
  ostr_ << "\"" << misc::escape(e.value_get()) << "\"";
}

void PrettyPrinter::operator()(const ArrayExp& e)
{
  ostr_ << e.type_get().name_get() << '[' << e.l_exp_get() << "] of "
        << e.r_exp_get();
}

void PrettyPrinter::operator()(const RecordExp& e)
{
  ostr_ << e.id_get().name_get() << "{ ";
  for (const auto& exp : e.fini_get())
  {
    if (exp != e.fini_get().back())
      ostr_ << exp << " = " << exp->init_get() << " , ";
    else
      ostr_ << exp << " = " << exp->init_get();
  }
  ostr_ << " }";
}

void PrettyPrinter::operator()(const ObjectExp& e)
{
  ostr_ << "new " << e.type_get();
}

void PrettyPrinter::operator()(const CallExp& e)
{
  ostr_ << e.name_get();

  if (bindings_display(ostr_))
    ostr_ << " /* " << e.def_get() << " */";
  ostr_ << "(";
  for (auto& exp : e.seq_get())
  {
    if (exp != e.seq_get().back())
      ostr_ << *exp << ", ";
    else
      ostr_ << *exp;
  }
  ostr_ << ")";
}

void PrettyPrinter::operator()(const MethodCallExp& e)
{
  ostr_ << e.lvalue_get() << '.' << e.name_get() << misc::incendl << '('
        << misc::incendl;
  for (auto& exp : e.seq_get())
    ostr_ << exp;
  ostr_ << misc::decendl << ')' << misc::decindent;
}

void PrettyPrinter::operator()(const OpExp& e)
{
  ostr_  << "(" << e.left_get() << ' ' << str(e.oper_get()) << ' '
         << e.right_get() << ")";
}

void PrettyPrinter::operator()(const AssignExp& e)
{
  ostr_ << e.var_get();
  if (bindings_display(ostr_))
      ostr_ << "/* " << &e << " */";
  ostr_ << " := " << e.exp_get();
}

void PrettyPrinter::operator()(const IfExp& e)
{
  ostr_ << "(if " << e.test_get() << misc::incendl << "then " << e.then_get();
  if (e.else_get() != nullptr)
    ostr_ << misc::iendl << "else " << *e.else_get();
  ostr_  << ')' <<misc::decendl;
}

void PrettyPrinter::operator()(const WhileExp& e)
{
  ostr_ << "while ";
  if (bindings_display(ostr_))
      ostr_ << "/* " << &e << " */ ";
  ostr_ << e.test_get() << " do" << misc::incendl
        << misc::incendl << e.body_get() << misc::decendl 
        << misc::decendl;
}

void PrettyPrinter::operator()(const ForExp& e)
{
  ostr_ << "for ";
  if (bindings_display(ostr_))
      ostr_ << "/* " << &e << " */ ";
  ostr_ << e.vardec_get().name_get()
        << " := " << *e.vardec_get().init_get() << " to " << e.hi_get() << " do"
        << misc::incendl << e.body_get() << misc::decendl;
}

void PrettyPrinter::operator()(const BreakExp& e)
{
  ostr_ << "break";
  if (bindings_display(ostr_))
    ostr_ << "/* " << e.loop_get() << " */";
}

void PrettyPrinter::operator()(const LetExp& e)
{
  ostr_ << "let" << misc::incendl << e.decs_get()
        << misc::decendl << "in" << misc::incendl << e.seq_get() << misc::decendl
        << "end";
}

  void PrettyPrinter::operator()(const TypeDec& e)
  {
    ostr_ << "type " << e << " = " << e.ty_get() << misc::iendl;
  }

void PrettyPrinter::operator()(const ClassTy& e)
{
  ostr_ << "class ";
  if (e.super_get() != nullptr)
    ostr_<<  " extends " << e.super_get()->name_get();
  ostr_ << misc::incendl << "{" << misc::iendl;
  for (auto* var : e.decs_get().decs_get())
  {
    if (var != nullptr)
      ostr_ << *var << misc::iendl;
  }
  ostr_ << misc::decendl << "}";
}

void PrettyPrinter::operator()(const VarDec& e)
{
  const ast::Dec& dec = e;
  ostr_ << "var " << dec;
  if (e.type_name_get() != nullptr)
    ostr_ << " : " << *e.type_name_get();
  if (e.init_get() != nullptr)
    ostr_ << " := " << *e.init_get();
  ostr_ << misc::iendl;
}

void PrettyPrinter::operator()(const FunctionDec& e)
{
  //ostr_ << misc::iendl;
  if (e.body_get() != nullptr)
    ostr_ << "function ";
  else
    ostr_ << "primitive ";
  ostr_ << e << '(';
  for (auto& var : e.formals_get().decs_get())
  {
    ast::Dec& dec = *var;
    if (var != e.formals_get().decs_get().back())
    {
      ostr_ << dec;
      if (var->type_name_get() != nullptr)
        ostr_ << " : " << *var->type_name_get();
      if (var->init_get() != nullptr)
        ostr_ << " := " << *var->init_get();
      ostr_ << ", ";
    }
    else
    {
      ostr_ << dec;
      if (var->type_name_get() != nullptr)
        ostr_ << " : " << *var->type_name_get();
      if (var->init_get() != nullptr)
        ostr_ << " := " << *var->init_get();
    }
  }
  ostr_ << ')';
  if (e.result_get() != nullptr)
    ostr_ << " : " << *e.result_get();
  if (e.body_get() != nullptr)
    ostr_ << " = " << misc::iendl  << '(' << misc::incendl << *e.body_get()
          << misc::decendl << ')' ;
  ostr_ << misc::iendl;
}

void PrettyPrinter::operator()(const MethodDec& e)
{
  ostr_ << "method ";
  ostr_ << e.name_get() << '(' << e.formals_get() << ')';
  if (e.result_get() != nullptr)
    ostr_ << " : " << *e.result_get();
  if (e.body_get() != nullptr)
    ostr_ << " = "  << misc::incendl << *e.body_get()
          << misc::decendl;
}

void PrettyPrinter::operator()(const NameTy& e)
{
  ostr_ << e.name_get();
  if (bindings_display(ostr_))
    ostr_ << " /* " << e.def_get() << " */";
}

void PrettyPrinter::operator()(const RecordTy& e)
{
  ostr_ << "{ ";
  for (auto& field : e.recs_get())
    if (field != e.recs_get().back())
      ostr_ << *field << " : " << field->type_name_get() << " , ";
    else
      ostr_ << *field << " : " << field->type_name_get();
  ostr_ << " }";
}

void PrettyPrinter::operator()(const Field& e)
{
  ostr_ << e.name_get();
  if (bindings_display(ostr_))
    ostr_ << " /* " << e.name_get() << " */";
}

  
void PrettyPrinter::operator()(const ArrayTy& e)
{
  ostr_ << "array of " << e.base_type_get();
}

void PrettyPrinter::operator()(const SeqExp& e)
{
  if (e.seq_get().size() == 0)
  {
    ostr_ << "()";
    return;
  }
  if (e.seq_get().size() == 1)
  {
    ostr_ << *e.seq_get().front();
    return;
  }
      ostr_ << '(' << misc::incendl;
    for (auto& exp : e.seq_get())
    {
      if (exp != e.seq_get().back())
        ostr_ << *exp  << ";" << misc::iendl;
      else
        ostr_ << *exp << misc::decendl;
    }
    ostr_ << ')';

}

} // namespace ast
