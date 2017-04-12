/**
 ** \file temp/tasks.hh
 ** \brief Declares the Temp tasks.
 */

#pragma once

#include <memory>

#include <temp/temp.hh>
#include <task/libtask.hh>

namespace temp
{

  namespace tasks
  {

    TASK_GROUP("Temporaries");

    /** \brief Allocated registers.

    Its value is changed by register allocation, and it is used
    whenever INSTR or ASM must be printed: it converts the
    temporary names.

    Implemented as a pointer, because we have a hierarchy of
    TempMap.*/
    extern std::unique_ptr<TempMap> tempmap;

    TASK_DECLARE("tempmap-display", "display the temporary table",
                 tempmap_display, "targeted");

  } // namespace tasks

} // namespace temp
