/**
 ** \file escapes/libescapes.hh
 ** \brief Declare functions and variables exported by escapes module.
 */

#pragma once

#include <misc/error.hh>
#include <ast/fwd.hh>

/// Computing escape and static link related information.
namespace escapes
{

  /// Compute the escaping variables.
  void escapes_compute(ast::Ast& tree);

} // namespace escapes
