/**
 ** \file object/tasks.cc
 ** \brief Object module related tasks' implementation.
 */

#include <memory>
#include <astclone/libastclone.hh>

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

    void
    object_types_compute()
    {
      task_error << ::object::types_check(*ast::tasks::the_program)
                 << &misc::error::exit_on_error;
    }

    static std::unique_ptr<class_names_type> class_names;

    void
    object_rename()
    {
      class_names.reset(::object::rename(*ast::tasks::the_program));
    }

    void
    object_desugar()
    {
      astclone::apply(::object::desugar, ast::tasks::the_program,
                      *class_names.get());
    }

    void
    raw_object_desugar()
    {
      astclone::apply(::object::raw_desugar, ast::tasks::the_program,
                      *class_names.get());
    }

  // FIXME: Some code was deleted here.


  } // namespace tasks

} // namespace object
