/**
 ** \file ast/string-exp.hh
 ** \brief Declaration of ast::StringExp.
 */

#pragma once

#include <ast/exp.hh>
#include <string>

namespace ast
{

  /// StringExp.
  class StringExp : public Exp
  {
  public:
    /// construct a Stringexp node.
    StringExp(const Location& location, std::string str);
    /// destroy a StringExp node
    virtual ~StringExp() = default;

    /// Accept a const visitor \a v
    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;
    const std::string value_get() const;
    std::string value_get();

  protected:
    std::string str_;
  };

} // namespace ast

#include <ast/string-exp.hxx>

