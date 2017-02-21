/**
 ** \file bind/tasks.hh
 ** \brief Bind module related tasks.
 */
// FIXED by forest_b

#pragma once

#include <misc/fwd.hh>
#include <task/libtask.hh>

namespace bind
{
  namespace tasks
  {
    TASK_GROUP("3. Binding");

    TASK_DECLARE("bound", "Make sure bindings (regular or taking overloading or "
                 "objects constructs into account) are computed.",
                 bound, "");

    TASK_DECLARE("b|bindings-compute",
                 "Bind the name uses to their definitions (objects forbidden).",
                 bind, "parse");

    TASK_DECLARE("B|bindings-display",
                 "Enable the bindings display in the next --ast-display\
 invocation. This option does not imply --bindings-compute.",
                 bind_display, "");

    TASK_DECLARE(
      "object-bindings-compute",
      "Bind the name uses to their definitions, allowing objects. consistency.",
      object_bind, "");
  }
}
