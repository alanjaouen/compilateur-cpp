/**
 ** \file ast/escapable.hh
 ** \brief Declaration of ast::Escapable.
 */

#pragma once

#include <ast/fwd.hh>

namespace ast
{

  /// Escapable.
  class Escapable
  {
  // FIXME: Some code was deleted here.
  public:
        Escapable();
    /// Destroy a Escapable node.
    virtual ~Escapable();

    /// Return a boolean for is_escaped.
    bool is_escaped_get() const;
    /// Return a boolean for is_escaped.
    bool is_escaped_get();
    /// set a boolean for is_escaped.
    void is_escaped_set(bool bo);
  private:
    ///the variable is escaped
    bool is_escaped_;
  };

} // namespace ast

#include <ast/escapable.hxx>

