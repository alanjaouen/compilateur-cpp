/**
 ** \file translate/tasks.cc
 ** \brief Translate tasks.
 */

#include <iostream>

#include <ast/tasks.hh>
#include <tree/fragments.hh>
#define DEFINE_TASKS 1
#include <translate/tasks.hh>
#undef DEFINE_TASKS
#include <translate/libtranslate.hh>

namespace translate
{

  namespace tasks
  {

    std::unique_ptr<tree::Fragments> fragments;

    /// Translate the AST to HIR.
    void
    hir_compute()
    {
      fragments = translate(*ast::tasks::the_program
                           );
    }

    /// Display the HIR.
    void
    hir_display()
    {
      std::cout
          << "/* == High Level Intermediate representation. == */\n"
          << *fragments;
    }

  } // namespace tasks

} // namespace translate
