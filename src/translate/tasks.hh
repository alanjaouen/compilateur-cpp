/**
 ** \file translate/tasks.hh
 ** \brief Translate module tasks.
 */

#pragma once

#include <tree/fwd.hh>
#include <task/libtask.hh>

namespace translate
{

  namespace tasks
  {

    /// The global translation of ast::tasks::the_program.
    extern std::unique_ptr<tree::Fragments> fragments;

    TASK_GROUP("5. Translation to High Level Intermediate Representation");

    /// Translate the AST to HIR.
    TASK_DECLARE("hir-compute", "translate to HIR", hir_compute, "desugar-for desugar-string-cmp desugar");

    /// Translate the AST to HIR.
    TASK_DECLARE("H|hir-display", "display the HIR",
                 hir_display, "hir-compute");

  } // namespace tasks
} // namespace translate
