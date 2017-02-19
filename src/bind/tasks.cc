/**
 ** \file bind/tasks.cc
 ** \brief Bind module tasks implementation.
 */

  // FIXED forest_b


#include <ast/libast.hh>
#include <ast/tasks.hh>

#include <bind/libbind.hh>
#define DEFINE_TASKS 3
#include <bind/tasks.hh>
#undef DEFINE_TASKS

namespace bind
{
  namespace tasks
  {
    void bound()
    {
      
    }

    void bind()
    {
      //precondition(the_program);
      bind::bind_compute(*ast::tasks::the_program);
    }

    void bind_display()
    {
      ast::bindings_display(std::cout) = true;
    }

    void object_bind()
    {
      
    }
  }
}
