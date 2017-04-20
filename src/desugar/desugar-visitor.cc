/**
 ** \file desugar/desugar-visitor.cc
 ** \brief Implementation of desugar::DesugarVisitor.
 */

#include <misc/algorithm.hh>
#include <ast/all.hh>
#include <ast/libast.hh>
#include <parse/libparse.hh>
#include <parse/tweast.hh>
#include <desugar/desugar-visitor.hh>
#include <misc/symbol.hh>

namespace desugar
{

  DesugarVisitor::DesugarVisitor(bool desugar_for_p,
                                 bool desugar_string_cmp_p)
    : super_type()
    , desugar_for_p_(desugar_for_p)
    , desugar_string_cmp_p_(desugar_string_cmp_p)
  {}


  /*-----------------------------.
  | Desugar string comparisons.  |
  `-----------------------------*/
  void
  DesugarVisitor::operator()(const ast::OpExp& e)
  {
  // FIXME: Some code was deleted here.
    if (e.left_get().type_get() == &type::String::instance()
      && e.right_get().type_get() == &type::String::instance())
    {
      if (e.oper_get() == ast::OpExp::Oper::eq)
      {   
        auto res = parse::parse(
          parse::Tweast() <<"streq(" << recurse(e.left_get()) << "," << recurse(e.right_get()) << ")");
        result_ = boost::get<ast::Exp*>(res);
      }
      else
      {
        auto res = parse::parse(
          parse::Tweast() <<"strcmp(" << recurse(e.left_get()) << "," << recurse(e.right_get()) << ") " << str(e.oper_get()) << " 0");
        result_ = boost::get<ast::Exp*>(res);
      }
    }
    else
    {
      //FIXME call cancerous supertype()
      const ast::Location& location = e.location_get();
      ast::Exp* left = recurse(e.left_get());
      ast::OpExp::Oper oper = e.oper_get();
      ast::Exp* right = recurse(e.right_get());
      result_ = new ast::OpExp(location, left, oper, right);
    }
  }


  /*----------------------.
  | Desugar `for' loops.  |
  `----------------------*/

  /*<<-
    Desugar `for' loops as `while' loops:

       for i := lo to hi do
         body

     is transformed as:

       let
         var _lo := lo
         var _hi := hi
         var i := _lo
       in
         if i <= _hi then
           while 1 do
             (
               body;
               if i = _hi then
                 break;
               i := i + 1
             )
       end

     Notice that:

     - a `_hi' variable is introduced so that `hi' is evaluated only
       once;

     - a `_lo' variable is introduced to prevent `i' from being in the
       scope of `_hi';

     - a first test is performed before entering the loop, so that the
       loop condition becomes `i < _hi' (instead of `i <= _hi'); this
       is done to prevent overflows on INT_MAX.
       ->>*/

  void
  DesugarVisitor::operator()(const ast::ForExp& e)
  {
  // FIXME: Some code was deleted here.
     
     //parse::tweast t = tweast("let ");
     //result_ = parse::parse(t);

  }


} // namespace desugar
