/**
 ** \file inlining/tasks.cc
 ** \brief Inlining module related tasks' implementation.
 **/

#include <common.hh>

#include <ast/tasks.hh>

#include <astclone/libastclone.hh>
#include <inlining/libinlining.hh>
#define DEFINE_TASKS 1
#include <inlining/tasks.hh>
#undef DEFINE_TASKS

namespace inlining
{

  namespace tasks
  {
    /*-----------.
    | Inlining.  |
    `-----------*/

    void
    inline_expand()
    {
      astclone::apply(::inlining::inline_expand, ast::tasks::the_program);
    }

  // FIXME: Some code was deleted here (Overload and inline).


    /*-------------------.
    | Function pruning.  |
    `-------------------*/

    void
    prune()
    {
      astclone::apply(::inlining::prune, ast::tasks::the_program);
    }

  // FIXME: Some code was deleted here (Overload and prune).

  } // namespace tasks

} // namespace inlining
