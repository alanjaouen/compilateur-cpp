/**
 ** \file type/type-checker.cc
 ** \brief Implementation for type/type-checker.hh.
 */

#include <ast/all.hh>
#include <type/types.hh>
#include <type/type-checker.hh>

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
  {}

  const Type*
  TypeChecker::type(ast::Typable& e)
  {
  // FIXED by forest_b
    if (!e.type_get())
      e.accept(*this);
    return e.type_get();
  }

  const Record*
  TypeChecker::type(const ast::fields_type& e)
  {
    auto res = new Record;
  // FIXED by forest_b
    for (const auto i : e)
      res->field_add(i->name_get(), *type(i->type_name_get()));
    return res;
  }

  const Record*
  TypeChecker::type(const ast::VarDecs& e)
  {
    auto res = new Record;
    for (const auto& i : e.decs_get())
      res->field_add(i->name_get(), *type(*i));

    return res;
  }

  const misc::error&
  TypeChecker::error_get() const
  {
    return error_;
  }


  /*-----------------.
  | Error handling.  |
  `-----------------*/



  void
  TypeChecker::print_type_our(const Type& type1)
  {
    error_ << misc::error::type << " type: " << type1 << std::endl;
  }


  void
  TypeChecker::error(const ast::Ast& loc, const std::string& msg)
  {
    error_ << misc::error::type
           << loc.location_get() << ": " << msg << std::endl;
  }

  void
  TypeChecker::type_mismatch(const ast::Ast& loc,
                             const std::string& exp1, const Type& type1,
                             const std::string& exp2, const Type& type2)
  {
    error_ << misc::error::type
           << loc.location_get() << ": type mismatch" << misc::incendl
           << exp1 << " type: " << type1 << misc::iendl
           << exp2 << " type: " << type2 << misc::decendl;
  }

  void
  TypeChecker::check_types(const ast::Ast& loc,
                           const std::string& exp1, const Type& type1,
                           const std::string& exp2, const Type& type2)
  {
  // FIXED by forest_b
    if (!(type1.compatible_with(type2)))
      type_mismatch(loc, exp1, type1, exp2, type2);
  }


  void
  TypeChecker::check_types(const ast::Ast& loc,
                           const std::string& exp1, ast::Typable& type1,
                           const std::string& exp2, ast::Typable& type2)
  {
    // Ensure evaluation order.
    const auto a = type(type1);
    const auto b = type(type2);
    // FIXED by forest_b
    if (!(a->compatible_with(*b)))
      type_mismatch(loc, exp1, *a, exp2, *b);

  }


  /*--------------------------.
  | The core of the visitor.  |
  `--------------------------*/

  /*-----------------.
  | Visiting /Var/.  |
  `-----------------*/

  void
  TypeChecker::operator()(ast::SimpleVar& e)
  {
  // FIXME: Some code was deleted here.
  }

  // FIXME: Some code was deleted here.



  /*-----------------.
  | Visiting /Exp/.  |
  `-----------------*/

  // Literals.
  void
  TypeChecker::operator()(ast::NilExp& e)
  {
    auto nil_ptr = std::make_unique<Nil>();
    type_default(e, nil_ptr.get());
    created_type_default(e, nil_ptr.release());
    std::cout<< e.type_get()<<std::endl;
  }

  void
  TypeChecker::operator()(ast::IntExp& e)
  {
  // FIXED by forest_b
    e.type_set(&Int::instance());
  }

  void
  TypeChecker::operator()(ast::StringExp& e)
  {
  // FIXED by forest_b
    e.type_set(&String::instance());
  }


  // Complex values.

  void
  TypeChecker::operator()(ast::RecordExp& e)
  {
    // If no error occured, check for nil types in the record initialization.
    // If any error occured, there's no need to set any nil types.
    // If there are any record initializations, set the `record_type_`
    // of the `Nil` to the expected type.
  // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::operator()(ast::OpExp& e)
  {
    std::cout<< "her"<<std::endl;
  // FIXME: Some code was deleted here.
    type(e.left_get());
    type(e.right_get());


    // If any of the operands are of type Nil, set the `record_type_` to the
    // type of the opposite operand.
    if (auto nil = to_nil(*e.left_get().type_get()))
      if (auto nil2 = to_nil(*e.right_get().type_get()))
      {
        std::cout << "nil = nil" << std::endl;
        type_mismatch(e, "right operand", *(e.right_get().type_get()),
          "expected", *(e.left_get().type_get()));
      }

    if (auto nil = to_nil(*e.left_get().type_get()))
      nil->set_record_type(*e.right_get().type_get());
    if (auto nil = to_nil(*e.right_get().type_get()))
      nil->set_record_type(*e.left_get().type_get());

    if (!error_)
    {
  // FIXME: Some code was deleted here.
      std::cout<< "!error_"<<std::endl;
      if (! e.left_get().type_get()->compatible_with(*e.right_get().type_get()))
        type_mismatch(e, "right operand", *(e.right_get().type_get()),
        "expected", *(e.left_get().type_get()));
      e.type_set(e.left_get().type_get());
    }
  }

  // FIXME: Some code was deleted here.


  /*-----------------.
  | Visiting /Dec/.  |
  `-----------------*/

  /*------------------------.
  | Visiting FunctionDecs.  |
  `------------------------*/

  void
  TypeChecker::operator()(ast::FunctionDecs& e)
  {
    decs_visit<ast::FunctionDec>(e);
  }


  void
  TypeChecker::operator()(ast::FunctionDec&)
  {
    // We must not be here.
    unreachable();
  }


  // Store the type of this function.
  template <>
  void
  TypeChecker::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
  {
  // FIXME: Some code was deleted here.
    Named *ptr = new Named(e.name_get());
    e.type_set(ptr);
    e.created_type_set(ptr);
  }


  // Type check this function's body.
  template <>
  void
  TypeChecker::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
  {
    visit_routine_body<Function>(e);
    e.type_set(&(Void::instance()));
    if (e.body_get())
      e.body_get()->accept(*this);
    // Check for Nil types in the function body.
    if (!error_ && e.body_get())
      {
	// FIXME: Some code was deleted here.
      }
  }


  /*---------------.
  | Visit VarDec.  |
  `---------------*/

  void
  TypeChecker::operator()(ast::VarDec& e)
  {
    std::cout << e.name_get() << std::endl;
    // FIXED: caradi_c - Alan
    if (e.init_get())
    {
    	e.init_get()->accept(*this);

      if (!e.type_name_get()) /* pas de type specifier on affecte automatiquement le type */
        e.type_set(e.init_get()->type_get());

      else if (!e.type_name_get()->def_get()) /* type primitif */
      {
        if (e.type_name_get()->name_get() == "string")
          e.type_set(&String::instance());
        else if (e.type_name_get()->name_get() == "int")
          e.type_set(&Int::instance());

        if (!e.type_get()->compatible_with(*e.init_get()->type_get())) /*on teste la compatibilite*/
          type_mismatch(e, "variable declaration", *(e.type_get()),
            "variable initialization", *(e.init_get()->type_get()));
      }
      else /*type créé*/
    	  if(e.type_name_get()->def_get()->type_get()->compatible_with(*e.init_get()->type_get()))
        e.type_set(e.init_get()->type_get());
        else
          type_mismatch(e,"variable declaration",*e.type_name_get()->def_get()->type_get(),
            "variable initialization", *(e.init_get()->type_get()));
    }
    else /*Si c'est ni un type primitif, ni un type creer, ni un sans type*/
      e.type_set(&(Void::instance()));
  }


  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/

  void
  TypeChecker::operator()(ast::TypeDecs& e)
  {
    decs_visit<ast::TypeDec>(e);
  }


  void
  TypeChecker::operator()(ast::TypeDec&)
  {
    // We must not be here.
    unreachable();
  }


  // Store this type.
  template <>
  void
  TypeChecker::visit_dec_header<ast::TypeDec>(ast::TypeDec& e)
  {
    // We only process the head of the type declaration, to set its
    // name in E.  A declaration has no type in itself; here we store
    // the type declared by E.
    // FIXED: (alan) Some code was deleted here.
    Named *ptr = new Named(e.name_get());
    e.type_set(ptr);
    e.created_type_set(ptr);
  }

  // Bind the type body to its name.
  template <>
  void
  TypeChecker::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
  {
    // FIXED: (Alan) Some code was deleted here.
    e.ty_get().accept(*this);
    delete e.type_get();
    Named *ptr = new Named(e.name_get(), e.ty_get().type_get());
    e.type_set(ptr);
    e.created_type_set(ptr);

  }

  /*------------------.
  | Visiting /Decs/.  |
  `------------------*/

  template <class D>
  void
  TypeChecker::decs_visit(ast::AnyDecs<D>& e)
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

  void
  TypeChecker::operator()(ast::NameTy& e)
  {
  // FIXME: Some code was deleted here (Recognize user defined types, and built-in types).
    if (e.name_get() == "string")
      e.type_set(&String::instance());
    else if (e.name_get() == "int")
      e.type_set(&Int::instance());
    else 
      e.type_set(e.def_get()->type_get());
  }

  void
  TypeChecker::operator()(ast::RecordTy& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  TypeChecker::operator()(ast::ArrayTy& e)
  {
  // FIXME: Some code was deleted here.
  }

} // namespace type
