/**
 ** \file type/type-checker.hxx
 ** \brief Inline methods of type::TypeChecker.
 */

#pragma once

#include <ast/all.hh>
#include <type/pretty-printer.hh>
#include <type/type-checker.hh>
#include <type/types.hh>

namespace type
{

  namespace
  {

    static const Nil nil_error_instance{};

  }

  /*----------------.
  | Setting types.  |
  `----------------*/

  template <typename NodeType>
  void
  TypeChecker::type_default(NodeType& e, const type::Type* type)
  {
  // FIXED by forest_b
    if (e.type_get() == nullptr)
      e.type_set(type);
  }

  template <typename NodeType>
  void
  TypeChecker::created_type_default(NodeType& e, const type::Type* type)
  {
  // FIXED by forest_b
    if (e.created_type_get() == nullptr)
      e.created_type_set(type);
  }

  template <typename NodeType>
  void
  TypeChecker::type_set(NodeType& e, const type::Type* type)
  {
  // FIXED by forest_b
    e.type_set(type);
  }


  /*-----------------.
  | Error handling.  |
  `-----------------*/

  template <typename T>
  void
  TypeChecker::error(const ast::Ast& loc, const std::string& msg,
                     const T& exp)
  {
    error_ << misc::error::type
           << loc.location_get() << ": " << msg << ": " << exp << std::endl;
  }

  template <typename T, typename U>
  void
  TypeChecker::error_and_recover(T& loc, const std::string& msg, const U& exp)
  {
    error(loc, msg, exp);
    loc.type_set(&nil_error_instance);
  }

  template <typename NodeType>
  void
  TypeChecker::check_type(NodeType& e, const std::string& s, const Type& expected)
  {
  // FIXED by forest_b
    if (!(e.compatible_with(expected)))
    {
      error(e, s);
      e.type_set(expected);
    }
  }

  /*------------.
  | Functions.  |
  `------------*/

  template <typename Routine_Type, typename Routine_Node>
  void
  TypeChecker::visit_routine_body(Routine_Node& e)
  {
  // FIXME: Some code was deleted here.
  }
} // namespace type
