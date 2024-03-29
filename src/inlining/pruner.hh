/**
 ** \file inlining/pruner.hh
 ** \brief Declaration of inlining::Pruner.
 */

#pragma once

#include <map>
#include <astclone/cloner.hh>
#include <misc/set.hh>

namespace inlining
{

  /// Prune useless function declarations within an AST.
  class Pruner : public astclone::Cloner
  {
  public:
    using super_type = astclone::Cloner;

    // Import overloaded virtual functions.
    using super_type::operator();

    using func_vect = std::vector<ast::FunctionDec*>;
    using callexp_vect = std::vector<const ast::CallExp*>;
    using func_count = std::map<misc::symbol, int>;
    using callexp_map = std::map<misc::symbol, callexp_vect>;

    /// \name Visit methods.
    /// \{
  // FIXME: Some code was deleted here.
    /// \}

    ast::FunctionDecs* prune(ast::FunctionDecs& e);

  private:
    // Need to keep the current function
    const ast::FunctionDec* current_function_ = nullptr;

    // Associate function dec with the number of CallExp calling it
    func_count called_functions_;

    // Link the CallExp to the current function
    callexp_map called_exps_;

  };

} // namespace inlining
