/**
 ** \file object/binder.hh
 ** \brief Declaration of object::OverloadBinder.
 **/

#pragma once

#include <overload/binder.hh>
#include <object/binder.hh>

namespace object
{

  /// \brief Compute bindings with support for objects and overload.
  class OverfunBinder : public Binder, public overload::Binder
  {
  // FIXME: Some code was deleted here.
  };

} // namespace object
