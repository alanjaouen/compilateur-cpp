/**
 ** \file translate/translator.cc
 ** \brief Implementation of translate::Translator.
 */

#include <set>

#include <misc/contract.hh>

#include <ast/all.hh>
#include <temp/label.hh>
#include <type/types.hh>
#include <tree/fragment.hh>
#include <tree/fragments.hh>
#include <translate/exp.hh>
#include <translate/level.hh>
#include <translate/translator.hh>
#include <translate/translation.hh>

namespace translate
{

  Translator::Translator()
    : exp_(nullptr)
    , fragments_(new tree::Fragments)
    , level_(nullptr)

  {}

  Translator::~Translator()
  {
    delete level_;

    using amap_type = std::map<const ast::Ast*, const Level*>;
    for (amap_type::value_type i : fun_level_)
      {
        delete i.second;
        i.second = nullptr;
      }
  }

  void
  Translator::operator()(const ast::Ast& e)
  {
    translate(e);
    exp_ = nullptr;
  }

  tree::Fragments*
  Translator::fragments_get()
  {
    return fragments_;
  }


  rExp
  Translator::translate(const ast::Ast& node)
  {
    node.accept(*this);
    return exp_;
  }

  template <typename T>
  std::vector<rExp>
  Translator::translate(const std::vector<T*>& es)
  {
    std::vector<rExp> res;
    for (const T* i : es)
      {
  // FIXME: Some code was deleted here.
      }
    return res;
  }


  /*--------------------------.
  | The core of the visitor.  |
  `--------------------------*/

  void
  Translator::operator()(const ast::SimpleVar& e)
  {
    exp_ = simple_var(*var_access_[e.def_get()], *level_);
  }

  void
  Translator::operator()(const ast::FieldVar& e)
  {
  // FIXME: Some code was deleted here.
  }
  void
  Translator::operator()(const ast::SubscriptVar& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::CastVar& e)
  {
  // FIXME: Some code was deleted here.
  }

  /*--------.
  | /Exp/.  |
  `--------*/

  void
  Translator::operator()(const ast::NilExp&)
  {
    exp_ = nil_exp();
  }
  void
  Translator::operator()(const ast::IntExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::StringExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::RecordExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::CallExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::OpExp& e)
  {
    rExp l = translate(e.left_get());
    rExp r = translate(e.right_get());

  // FIXME: Some code was deleted here (The translation depends upon the type of the arguments).
  }

  void
  Translator::operator()(const ast::SeqExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::AssignExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::IfExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::WhileExp& e)
  {
  // FIXME: Some code was deleted here.
  }


  void
  Translator::operator()(const ast::ForExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::BreakExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::LetExp& e)
  {
    exps_.push(std::vector<rExp>());

    // Chain the initialization code and then the body.
  // FIXME: Some code was deleted here.

    // Chain the declarations (initializations) with the body.
    bool void_instance;
  // FIXME: Some code was deleted here (Initialize void_instance).
    if (void_instance)
      exp_ = seq_exp(exps_.top());
    else
      exp_ = eseq_exp(exps_.top());
    exps_.pop();
  }

  void
  Translator::operator()(const ast::ArrayExp& e)
  {
  // FIXME: Some code was deleted here.
  }


  void
  Translator::operator()(const ast::CastExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::VarDecs& e)
  {
    std::vector<rExp>& top = exps_.top();
    std::vector<rExp> res = translate(e.decs_get());
    misc::append_and_move(top, res);
  }

  void
  Translator::operator()(const ast::TypeDecs&)
  {}

  void
  Translator::operator()(const ast::FunctionDecs& e)
  {
    for (const ast::FunctionDec* i : e.decs_get())
      visit_function_dec_header(*i);
    for (const ast::FunctionDec* i : e.decs_get())
      // There is nothing to translate for primitives.
      if (i->body_get())
        visit_function_dec_body(*i);
  }

  void
  Translator::operator()(const ast::FunctionDec&)
  {
    // We must not be here.
    unreachable();
  }

  void
  Translator::visit_function_dec_header(const ast::FunctionDec& e)
  {
    if (!e.body_get())
      {
        // Primitives have no level (and it is better so, otherwise we
        // waste the temporaries as primitive formal argument).  Their
        // name is also their label.
        fun_level_[&e] = 0;
        misc::put(fun_label_, &e, e.name_get());
      }
    else if (e.name_get() == "_main")
      {
        fun_level_[&e] = new Level("main");
        misc::put(fun_label_, &e, temp::Label("main"));
      }
    else
      {
        // Create the level of this function, but don't get into it,
        // visit_function_dec_body will.
        //
        // Note: If the escapes have not been computed, simply have
        // ast::FunctionDec::escapes_get return a list of Booleans
        // whose number is equal to the number of formals, all set to
        // true (meaning ``by default, every variable escapes'').
        fun_level_[&e] = new Level(e.name_get(), level_,
                                   e.escapes_get());
        misc::put(fun_label_, &e, temp::Label());
      }
  }

  void
  Translator::visit_function_dec_body(const ast::FunctionDec& e)
  {
    // Enter into the function's level (aka, frame).
    Level* saved_level = level_;
    // FIXME: Quick and dirty.
    level_ = const_cast<Level*>(fun_level_[&e]);

    access_list_type::const_iterator k = level_->formals_get().begin();
    // Skip the static link.
      ++k;

    // Put the accesses to the formals in the environment.
    for (const ast::VarDecs::Ds::value_type i : e.formals_get().decs_get())
      {
        var_access_[i] = *k;
        ++k;
      }
    translate(*e.body_get());

    tree::Fragment* frag = nullptr;
    // Procedure have no type declaration.
    if (e.result_get())
      frag = function_dec(fun_label_[&e], e.name_get(),
                         exp_, &level_->frame_get());
    else
      frag = procedure_dec(fun_label_[&e], e.name_get(),
                          exp_, &level_->frame_get());
    fragments_->emplace_back(frag);

    // Restore the current level.
    level_ = saved_level;
    // There is no value to find here.
    exp_ = nullptr;
  }

  void
  Translator::operator()(const ast::VarDec& e)
  {
    // init is not null.
    rExp init = translate(*e.init_get());

    // Initialization of a variable is just like an assignment.
    // Beforehand allocate space for this variable.
    /* FIXME: Variable declarations outside a level are not yet
       handled.  We might want to allow it (i.e., have global
       variables), but then we'll have to handle their
       initializations.  Or prevent it (we might want someone else to
       trigger the error then, type::TypeChecker for instance).
       For the moment, use the quick n' dirty solution: assertion().  */
    assertion(level_);

  /* FIXME: Some code was deleted here. */
  }

} // namespace translate
