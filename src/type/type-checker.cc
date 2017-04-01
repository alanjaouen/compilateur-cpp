/**
 ** \file type/type-checker.cc
 ** \brief Implementation for type/type-checker.hh.
 */

#include <ast/all.hh>
#include <type/type-checker.hh>
#include <type/types.hh>

#include <memory>

namespace type
{
namespace
{
  // Try to cast the type into a nil type.
  // If it's not actually a `type::Nil`, return `nullptr`.
  // This allows us to write more clear code like:
  // if (auto nil = to_nil(e.type_get())
  // ...
  const Nil* to_nil(const Type& type)
  {
    return dynamic_cast<const Nil*>(&type.actual());
  }
}

TypeChecker::TypeChecker()
  : super_type()
  , error_()
{
}

const Type* TypeChecker::type(ast::Typable& e)
{
  // FIXED by forest_b
  if (!e.type_get())
    e.accept(*this);
  return e.type_get();
}

const Record* TypeChecker::type(const ast::fields_type& e)
{
  auto res = new Record;
  // FIXED by forest_b
  for (const auto i : e)
    res->field_add(i->name_get(), *type(i->type_name_get()));
  return res;
}

const Record* TypeChecker::type(const ast::VarDecs& e)
{
  auto res = new Record;
  for (const auto& i : e.decs_get())
    res->field_add(i->name_get(), *type(*i));

  return res;
}

const misc::error& TypeChecker::error_get() const
{
  return error_;
}

/*-----------------.
| Error handling.  |
`-----------------*/

void TypeChecker::print_type_our(const Type& type1)
{
  error_ << misc::error::type << " type: " << type1 << std::endl;
}

void TypeChecker::error(const ast::Ast& loc, const std::string& msg)
{
  error_ << misc::error::type << loc.location_get() << ": " << msg << std::endl;
}

void TypeChecker::type_mismatch(const ast::Ast& loc, const std::string& exp1,
                                const Type& type1, const std::string& exp2,
                                const Type& type2)
{
  error_ << misc::error::type << loc.location_get() << ": type mismatch"
         << misc::incendl << exp1 << " type: " << type1 << misc::iendl << exp2
         << " type: " << type2 << misc::decendl;
}

void TypeChecker::check_types(const ast::Ast& loc, const std::string& exp1,
                              const Type& type1, const std::string& exp2,
                              const Type& type2)
{
  // FIXED by forest_b
  if (!(type1.compatible_with(type2.actual())))
    type_mismatch(loc, exp1, type1, exp2, type2);
}

void TypeChecker::check_types(const ast::Ast& loc, const std::string& exp1,
                              ast::Typable& type1, const std::string& exp2,
                              ast::Typable& type2)
{
  // Ensure evaluation order.
  const auto a = type(type1);
  const auto b = type(type2);
  // FIXED by forest_b
  if (!(a->compatible_with(b->actual())))
    type_mismatch(loc, exp1, *a, exp2, *b);
}

/*--------------------------.
| The core of the visitor.  |
`--------------------------*/

/*-----------------.
| Visiting /Var/.  |
`-----------------*/

void TypeChecker::operator()(ast::SimpleVar& e)
{
  // FIXED: Some code was deleted here.
  if (e.def_get()->type_get())
    type_default(e, e.def_get()->type_get());
  else if (e.def_get())
  {
    type(*e.def_get());
    type_default(e, e.def_get()->type_get());
  }
  else
  {
    if (e.name_get() == "string")
      type_default(e, &String::instance());
    else if (e.name_get() == "int")
      type_default(e, &Int::instance());
  }
}
void TypeChecker::operator()(ast::FieldVar& e)
{
  type(e.lvalue_get());
  type_default(e, &Void::instance());
  auto ty = dynamic_cast<const Record*>(&e.lvalue_get().type_get()->actual());
  if (ty == nullptr)
    error(e, "is not a record");
  else
  {
    auto ctype = ty->field_type(e.name_get());
    if (ctype == nullptr)
      error(e, ("unknown field " + e.name_get().get()));
    else
      e.type_set(ctype);
  }
}

void TypeChecker::operator()(ast::SubscriptVar& e)
{
  type(e.var_get());
  type(e.index_get());
  check_type(e.index_get(), "type mismatch SubscriptVar, expected int",
             Int::instance());
  auto gg = dynamic_cast<const Array*>(&e.var_get().type_get()->actual());
  if (!gg)
    error(e, " is not an array");
  else
    e.type_set(&gg->type_get());
}

void TypeChecker::operator()(ast::CastVar& e)
{
  type(e.var_get());
  type(e.ty_get());
  type_set(e.var_get(), e.ty_get().type_get());
}

/*-----------------.
| Visiting /Exp/.  |
`-----------------*/

// Literals.
void TypeChecker::operator()(ast::NilExp& e)
{
  auto nil_ptr = std::make_unique<Nil>();
  type_default(e, nil_ptr.get());
  created_type_default(e, nil_ptr.release());
  //    std::cout<< e.type_get()<<std::endl;
}

void TypeChecker::operator()(ast::IntExp& e)
{
  // FIXED by forest_b
  e.type_set(&Int::instance());
}

void TypeChecker::operator()(ast::StringExp& e)
{
  // FIXED by forest_b
  e.type_set(&String::instance());
}

// Complex values.

void TypeChecker::operator()(ast::RecordExp& e)
{
  // print_type_our(*e.id_get().def_get()->type_get());

  // If no error occured, check for nil types in the record initialization.
  // If any error occured, there's no need to set any nil types.
  // If there are any record initializations, set the `record_type_`
  // of the `Nil` to the expected type.
  // FIXED by caradi_c
  e.id_get().accept(*this);
  auto named = dynamic_cast<const Named*>(e.id_get().def_get()->type_get());
  auto res = dynamic_cast<const Record*>(named->type_get());
  /*for (auto i : res->fields_get())
    std::cout << i.name_get() << '\n';
  std::cout << std::endl;*/
  e.type_set(res);
}

void TypeChecker::operator()(ast::OpExp& e)
{
  // FIXED: (Alan) Some code was deleted here.
  type(e.left_get());
  type(e.right_get());

  // If any of the operands are of type Nil, set the `record_type_` to the
  // type of the opposite operand.
  if (auto nil = to_nil(*e.left_get().type_get()))
    if (auto nil2 = to_nil(*e.right_get().type_get()))
      type_mismatch(e, "right operand is", *(e.right_get().type_get()),
                    "and left operand is", *(e.left_get().type_get()));

  if (auto nil = to_nil(*e.left_get().type_get())) /* if nil OP EXP */
  {
    if (nil->compatible_with(e.right_get().type_get()->actual()))
      nil->set_record_type(*e.right_get().type_get());
    else
      type_mismatch(e, "right operand", *e.left_get().type_get(),
                    "expected reccord, given", *(e.right_get().type_get()));
  }

  if (auto nil = to_nil(*e.right_get().type_get())) /* if EXP OP nil */
  {
    if (nil->compatible_with(e.left_get().type_get()->actual()))
      nil->set_record_type(*e.left_get().type_get());
    else
      type_mismatch(e, "right operand", *e.right_get().type_get(),
                    "expected reccord, given", *(e.left_get().type_get()));
  }

  if (!error_)
  {
    if (!e.left_get().type_get()->compatible_with(*e.right_get().type_get()))
      type_mismatch(e, "right operand", *(e.right_get().type_get()), "expected",
                    *(e.left_get().type_get()));
  }
  e.type_set(&Int::instance());
}

void TypeChecker::operator()(ast::AssignExp& e)
{
  type(e.var_get());
  type(e.exp_get());
  e.type_set(&Void::instance());

  auto svar = dynamic_cast<ast::SimpleVar*>(&e.var_get());
  if (svar != nullptr &&
      var_read_only_.find(svar->def_get()) != var_read_only_.end())
    error(e, "for loop var is read only");
  else
  {
    if (auto nil = to_nil(*e.exp_get().type_get()))
    {
      if (auto nil2 = to_nil(e.var_get().type_get()->actual()))
        nil->set_record_type(nil2->record_type_get()->actual());
      else
        nil->set_record_type(e.var_get().type_get()->actual());
      return;
    }
    if (!e.var_get().type_get()->actual().compatible_with(
          e.exp_get().type_get()->actual()))
      type_mismatch(e, "assigned", *(e.var_get().type_get()), "expected",
                    *(e.exp_get().type_get()));
  }
}

void TypeChecker::operator()(ast::IfExp& e)
{
  type(e.test_get());
  check_type(e.test_get(), "type mismatch IfExp", Int::instance());
  //    type(e.then_get())
  if (e.else_get())
    check_types(e, "then clause type ", e.then_get(), "else clause type",
                *e.else_get());
  else
  {
    type(e.then_get());
    check_types(e, "then clause type ", *(e.then_get().type_get()),
                "else clause type", Void::instance());
  }
  e.type_set(e.then_get().type_get());
}

void TypeChecker::operator()(ast::ArrayExp& e)
{
  type(e.type_get());
  type(e.l_exp_get());
  type(e.r_exp_get());
  auto res =
    dynamic_cast<const Array*>(&(e.type_get().def_get()->type_get()->actual()));
  if (!res)
    error(e, " is not a array");
  else
  {
    check_type(e.l_exp_get(), "type mismatch ArrayExp", Int::instance());
    check_type(e.r_exp_get(), "type mismatch ArrayExp",
               res->type_get().actual());
  }
  e.type_set(res);
}
void TypeChecker::operator()(ast::CallExp& e)
{
  // FIXED (Alan)
  auto type = e.def_get()->type_get();
  auto arg = dynamic_cast<const Function*>(type);
  if (!arg)
    error(e, "function is not declared");
  auto it = arg->formals_get().begin();
  auto end = arg->formals_get().end();
  for (auto& exp : e.seq_get())
  {
    exp->accept(*this);
    if (!it->type_get().compatible_with(exp->type_get()->actual()) || it == end)
    {
      type_mismatch(e, "assigned", *exp->type_get(), "expected",
                    it->type_get());
    }
    it++;
  }
  if (it != end)
    error(e, "missing argument");
  e.type_set(&arg->result_get());
}
void TypeChecker::operator()(ast::LetExp& e)
{
  e.decs_get().accept(*this);
  e.seq_get().accept(*this);
  e.type_set(e.seq_get().type_get());
}
void TypeChecker::operator()(ast::SeqExp& e)
{
  for (auto& exp : e.seq_get())
    exp->accept(*this);
  if (e.seq_get().size() > 0)
    e.type_set(e.seq_get().back()->type_get());
  else
    e.type_set(&Void::instance());
}

// LOOP

void TypeChecker::operator()(ast::ForExp& e)
{
  type(e.vardec_get());
  type(e.hi_get());
  check_type(e.vardec_get(), "for variable type mismatch ", Int::instance());
  check_type(e.hi_get(), "loop bound type mismatch ", Int::instance());
  var_read_only_.insert(&e.vardec_get());
  type(e.body_get());
  check_type(e.body_get(), "body type is not void", Void::instance());
  type_default(e, &Void::instance());
}
void TypeChecker::operator()(ast::BreakExp& e)
{
  e.type_set(&Void::instance());
}

void TypeChecker::operator()(ast::WhileExp& e)
{
  type(e.test_get());
  check_type(e.test_get(), "\e[91mWhile condition\e[0m MUST be \e[92mint\e[0m",
             Int::instance());
  type(e.body_get());
  check_type(e.body_get(), "While body MUST be void", Void::instance());
  e.type_set(&Void::instance());
}

/*-----------------.
| Visiting /Dec/.  |
`-----------------*/

/*------------------------.
| Visiting FunctionDecs.  |
`------------------------*/

void TypeChecker::operator()(ast::FunctionDecs& e)
{
  decs_visit<ast::FunctionDec>(e);
}

void TypeChecker::operator()(ast::FunctionDec&)
{
  // We must not be here.
  unreachable();
}

// Store the type of this function.
template <>
void TypeChecker::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
{
  // FIXED: Some code was deleted here.
  Function* p;
  if (e.result_get())
    p = new Function(type(e.formals_get()), *type(*e.result_get()));
  else
    p = new Function(type(e.formals_get()), Void::instance());
  e.type_set(p);
  e.created_type_set(p);
}

// Type check this function's body.
template <>
void TypeChecker::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
{
  visit_routine_body<Function>(e);
  // Check for Nil types in the function body.
  if (!error_ && e.body_get())
  {
    // FIXED: Some code was deleted here.
    if (auto nill = to_nil(*e.body_get()->type_get()))
      nill->set_record_type(*e.result_get()->type_get());
  }
}

/*---------------.
| Visit VarDec.  |
`---------------*/

void TypeChecker::operator()(ast::VarDec& e)
{
  // FIXED: caradi_c - Alan

  if (e.init_get())
  {
    e.init_get()->accept(*this);

    if (
      !e
         .type_name_get()) /* pas de type specifier on affecte automatiquement
                              le type */
    {
      if (auto nil = to_nil(*e.init_get()->type_get()))
        error(e, "initialization is nil with no type specifier");
      else
        e.type_set(e.init_get()->type_get());
    }
    else if (!e.type_name_get()->def_get()) /* type primitif */
    {
      if (e.type_name_get()->name_get() == "string")
        e.type_set(&String::instance());
      else if (e.type_name_get()->name_get() == "int")
        e.type_set(&Int::instance());

      if (!e.type_get()->compatible_with(
            *e.init_get()->type_get())) /*on teste la compatibilite*/
        type_mismatch(e, "variable declaration", *(e.type_get()),
                      "variable initialization", *(e.init_get()->type_get()));
    }
    else /*type créé*/
      if (e.type_name_get()->def_get()->type_get()->compatible_with(
            *e.init_get()->type_get()))
    {
      if (auto nil = to_nil(*e.init_get()->type_get()))
        nil->set_record_type(
          e.type_name_get()->def_get()->type_get()->actual());
      e.type_set(e.init_get()->type_get());
    }
    else
      type_mismatch(e, "variable declaration",
                    *e.type_name_get()->def_get()->type_get(),
                    "variable initialization", *(e.init_get()->type_get()));
  }
  else if (
    e.type_name_get()) /*Si c'est ni un type primitif, ni un type creer, ni un
                          sans type*/
  {
    e.type_name_get()->accept(*this);
    e.type_set(e.type_name_get()->type_get());
  }
  else
    e.type_set(&Void::instance());
}

/*--------------------.
| Visiting TypeDecs.  |
`--------------------*/

void TypeChecker::operator()(ast::TypeDecs& e)
{
  decs_visit<ast::TypeDec>(e);
}

void TypeChecker::operator()(ast::TypeDec&)
{
  // We must not be here.
  unreachable();
}

// Store this type.
template <>
void TypeChecker::visit_dec_header<ast::TypeDec>(ast::TypeDec& e)
{
  // We only process the head of the type declaration, to set its
  // name in E.  A declaration has no type in itself; here we store
  // the type declared by E.
  // FIXED: (alan) Some code was deleted here.
  Named* ptr = new Named(e.name_get());
  e.type_set(ptr);
  e.created_type_set(ptr);
}

// Bind the type body to its name.
template <>
void TypeChecker::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
{
  // FIXED: (Alan) Some code was deleted here.
  e.ty_get().accept(*this);
  delete e.type_get();
  Named* ptr = new Named(e.name_get(), e.ty_get().type_get());
  e.type_set(ptr);
  e.created_type_set(ptr);
  if(!ptr->sound())
    error(e, "Endless type recursion");
}

/*------------------.
| Visiting /Decs/.  |
`------------------*/

template <class D>
void TypeChecker::decs_visit(ast::AnyDecs<D>& e)
{
  // FIXED:(Alan) Some code was deleted here.
  for (auto dec : e.decs_get())
  {
    visit_dec_header<D>(*dec);
  }
  for (auto dec : e.decs_get())
  {
    visit_dec_body<D>(*dec);
  }
}

/*-------------.
| Visit /Ty/.  |
`-------------*/

void TypeChecker::operator()(ast::NameTy& e)
{
  // FIXED: Some code was deleted here (Recognize user defined types, and
  // built-in types).
  if (e.name_get() == "string")
    e.type_set(&String::instance());
  else if (e.name_get() == "int")
    e.type_set(&Int::instance());
  else
    e.type_set(e.def_get()->type_get());
}

void TypeChecker::operator()(ast::RecordTy& e)
{
  // FIXED: Some code was deleted here.
  Record* ptr = new Record;

  for (auto i : e.recs_get())
  {
    type(i->type_name_get());
    ptr->field_add(i->name_get(), *i->type_name_get().type_get());
  }
  e.type_set(ptr);
  e.created_type_set(ptr);
}

void TypeChecker::operator()(ast::ArrayTy& e)
{
  // FIXED by forest_b
  e.base_type_get().accept(*this);
  auto a = new Array(*e.base_type_get().type_get());
  type_default(e, a);
}

} // namespace type
