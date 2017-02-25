/**
 ** \file bind/tasks.cc
 ** \brief Bind module tasks implementation.
 */

  // FIXED forest_b


#include <ast/libast.hh>
#include <ast/tasks.hh>

#include <bind/libbind.hh>

#include <parse/libparse.hh>

#define DEFINE_TASKS 3
#include <bind/tasks.hh>
#undef DEFINE_TASKS

namespace bind
{
  namespace tasks
  {
    void bound()
    {}

    void bind()
    {
      precondition(ast::tasks::the_program);
      auto e = bind::bind(*ast::tasks::the_program);
      if (e)
        e.exit_on_error();
    }

    void bind_display()
    {
      ast::bindings_display(std::cout) = true;
    }

    void object_bind()
    {}

    void rename()
    {
      bind::rename(*ast::tasks::the_program);
    }
  }
}
