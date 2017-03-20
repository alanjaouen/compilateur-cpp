/**
 ** \file type/tasks.cc
 ** \brief Type module task implementations.
 */

#include <common.hh>

#include <ast/tasks.hh>

#define DEFINE_TASKS 1
#include <type/tasks.hh>
#undef DEFINE_TASKS
#include <type/libtype.hh>

// Type module related tasks' implementation.
namespace type
{

  namespace tasks
  {

    void
    types_check()
    {
      task_error << ::type::types_check(*ast::tasks::the_program)
                 << &misc::error::exit_on_error;
    }

  } // namespace tasks

} // namespace type
