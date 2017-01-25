/**
 ** \file tc.cc
 ** \brief The compiler driver.
 */

#include <cstdlib>

#include <iostream>
#include <exception>
#include <stdexcept>

#include <common.hh>
#include <task/task-register.hh>

int
main(int argc, char** argv)
{
  program_name = argv [0];

  try
    {
      task_timer.start();
      task_timer.push("rest");

      filename = task::TaskRegister::instance().parse_arg(argc, argv);
      task_error.exit_on_error();

      // If `help', `usage' or `version' is called, just exit.
      if (filename == nullptr)
        return 0;

      if (task::TaskRegister::instance().nb_of_task_to_execute_get() == 0)
        task::TaskRegister::instance().enable_task("parse");

      task::TaskRegister::instance().execute();
      task_timer << task::TaskRegister::instance().timer_get();
      task_error.exit_on_error();
    }

  // Required to enable stack unwinding.
  catch (std::invalid_argument& e)
    {
      return 64;
    }
  catch (std::runtime_error& e)
    {
      if (e.what() != std::string(""))
        std::cerr << e.what() << std::endl;
    }
  catch (misc::error& e)
    {
      std::cerr << e;
      exit(e.status_get());
    }
}
