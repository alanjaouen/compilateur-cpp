/**
 ** \file ast/let-exp.hh
 ** \brief Declaration of ast::LetExp.
 */

#pragma once

#include <misc/contract.hh>
#include <ast/seq-exp.hh>
#include <ast/exp.hh>
#include <ast/decs-list.hh>

namespace ast
{

  // /// LetExp.
  // class LetExp : public Exp
  // {
  //   /** \name Ctor & dtor.
  //    ** \{ */
  //   /// Construct a LetExp node.
  //   LetExp(const Location& location, DecsList* decs_, );
  //   /// Destroy a LetExp node.
  //   virtual ~LetExp();
  //   /** \} */
  // protected:
  //   DecsList* decs_;


  // };

} // namespace ast

#include <ast/let-exp.hxx>

