/**
 ** \file object/tasks.cc
 ** \brief Object module related tasks' implementation.
 */


#include <common.hh>

#include <ast/tasks.hh>

#define DEFINE_TASKS 1
#include <object/tasks.hh>
#undef DEFINE_TASKS
#include <object/libobject.hh>

namespace object
{

  namespace tasks
  {
    void
    object_parse()
    {}

    //fix by caradi_c
    void
    bind_obj()
    {
      auto res = object::bind_obj(*ast::tasks::the_program);
      if (!res)
        task_error.exit();
    }




  } // namespace tasks

} // namespace object
