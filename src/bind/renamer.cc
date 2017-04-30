/**
 ** \file bind/renamer.cc
 ** \brief Implementation of bind::Renamer.
 */

#include <bind/renamer.hh>

namespace bind
{
  using namespace ast;

  Renamer::Renamer()
    : super_type(), new_names_()
  {}

  //fix by caradi_c
  void Renamer::operator()(ast::VarDec& e)
  {
    if (new_names_.find(&e) == new_names_.end())
      {
	auto a = new_name(e);
	e.name_set(a);
	new_names_[&e] = a;
      }
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::FunctionDec& e)
  {
    if (new_names_.find(&e) == new_names_.end())
      {
	auto a = new_name(e);
	e.name_set(a);
	new_names_[&e] = a;
      }
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::TypeDec& e)
  {
    if (new_names_.find(&e) == new_names_.end())
      {
	auto a = new_name(e);
	e.name_set(a);
	new_names_[&e] = a;
      }
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::SimpleVar& e)
  {
    e.name_set(new_names_[e.def_get()]);
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::CallExp& e)
  {
    e.name_set(new_names_[e.def_get()]);
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::NameTy& e)
  {
    if (e.def_get())
      {
	if (new_names_.find(e.def_get()) != new_names_.end())
	  {
	    e.name_set(new_names_[e.def_get()]);
	    super_type::operator()(e);
	  }
	else
	  {
	    super_type::operator()(e.def_get());
	    e.name_set(new_names_[e.def_get()]);
	    super_type::operator()(e);
	  }
      }
  }

}// namespace bind
