/**
 ** \file translate/translation.hh
 ** \brief Interface between the `tree' and `translate' modules.
 **
 ** The Translator should never be bothered with low level
 ** details, and the tree module is considered low level.  All the
 ** functions below make it simple for Translator to create the
 ** intermediate representation.
 **
 ** In order to produce good IR code, we cannot just
 ** use tree directly, rather we use another layer (translate::rExp), so
 ** actually the function of the following function is to provide an
 ** easy API to `translate::', masking bureaucratic details from
 ** `tree::' and `translate::rExp'.
 **/

#pragma once

#include <frame/frame.hh>
#include <translate/fwd.hh>

namespace translate
{

  /*--------.
  | /Var/.  |
  `--------*/

  /// \name ast::Var.
  /// \{

  // The USE_LEVEL wants to use THIS Access.  Return a Tree expression
  // computing this access (including all the static links
  // manipulations).
  rExp simple_var(const Access& access, const Level& use_level);
  rExp field_var(rExp var_exp, int index);
  rExp subscript_var(rExp var_exp, rExp index_exp);

  /// \}


  /*--------.
  | /Exp/.  |
  `--------*/

  /// \name ast::Exp.
  /// \{

  rExp nil_exp();
  rExp int_exp(int value);

  // Strings cannot be used as values, rather, we need to store them
  // somewhere with a label, and return a NAME to that label.
  // FRAGMENT is set to the snippet which defines the string.
  rExp string_exp(const std::string& value, tree::Fragment*& fragment);

  rExp record_exp(std::vector<rExp> args);

  /// Compute the value of the static link for a function about to be called.
  /// \param  decl  the level in which the function was declared
  /// \param  use   the level in which the function is called
  rExp static_link(const Level* decl, const Level* use);

  /// Call the function LABEL.
  rExp call_exp(const temp::Label& label, std::vector<rExp> args);
  /// Shorthand.
  rExp call_exp(const std::string& label, rExp arg1, rExp arg2 = nullptr);

  /// Translation of ast::OpExp.
  rExp op_exp(const ast::OpExp::Oper oper, rExp left, rExp right);


  /// Translate an ast::SeqExp.
  rExp seq_exp(std::vector<rExp>& exps);

  // Try to produce simple code for simple cases.
  rExp eseq_exp(std::vector<rExp>& exps);

  rExp assign_exp(rExp dst, rExp src);

  // All the work is delayed until we know how the IfExp will be used,
  // i.e., once the Ix is "un'ed".
  rExp if_exp(rExp test, rExp then_clause, rExp else_clause);



  rExp while_exp(rExp test, rExp body, const temp::Label& ldone);

  // FIXME: Some code was deleted here (for_exp -- "for" loop translation).

  rExp break_exp(const temp::Label& loop_end);
  rExp array_exp(rExp array_size, rExp init_val);

  /// \}

  /*--------.
  | /Dec/.  |
  `--------*/

  /// \name ast::Dec.
  /// \{

  // A function or a procedure being declared has no value by itself.
  // Just store its body in a FRAGMENT which will be handled later on.

  tree::ProcFrag* procedure_dec(const temp::Label& label,
                                const misc::symbol& name,
                                rExp body,
                                frame::Frame* frame);

  // A function must save its value into the `return value' register.
  tree::ProcFrag* function_dec(const temp::Label& label,
                               const misc::symbol& name,
                               rExp value,
                               frame::Frame* frame);

  /// \}
} // namespace translate
