/**
 ** \file bind/libbind.hh
 ** \brief Interface of the bind module.
 */

  // FIXED forest_b


#pragma once

#include <misc/error.hh>
#include <ast/fwd.hh>


namespace bind
{
  void bind_compute(ast::Ast& tree);
}
