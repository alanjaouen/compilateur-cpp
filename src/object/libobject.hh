/**
 ** \file object/libobject.hh
 ** \brief Declare functions and variables exported by object module.
 */

#pragma once

#include <misc/map.hh>
#include <misc/symbol.hh>
#include <misc/error.hh>

#include <ast/fwd.hh>



namespace object
{

  /*-------.
  | Bind.  |
  `-------*/

  // FIXED by forest_b

  misc::error bind(ast::Ast& e);
  misc::error bind_obj(ast::Ast& );
} // namespace object
