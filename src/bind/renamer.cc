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
    auto a = new_name(e);
    e.name_set(a);
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::FunctionDec& e)
  {
    auto a = new_name(e);
    e.name_set(a);
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::TypeDec& e)
  {
    auto a = new_name(e);
    e.name_set(a);
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::SimpleVar& e)
  {
    e.name_set(e.def_get()->name_get());
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::CallExp& e)
  {
    e.name_set(e.def_get()->name_get());
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::NameTy& e)
  {
    if (e.def_get())
      {
        e.name_set(e.def_get()->name_get());
        super_type::operator()(e);
      }
  }

}// namespace bind
