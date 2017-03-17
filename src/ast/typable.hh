/**
 ** \file ast/typable.hh
 ** \brief Declaration of ast::Typable.
 */

#pragma once

#include <type/fwd.hh>
#include <ast/fwd.hh>

namespace ast
{


  /** \class ast::Typable
   ** \brief Hold a type information.
   **
   ** A Typable node holds a type information (type::Type) about
   ** this node.  This can be:
   ** \li the type of the node itself, if it is a Exp or a Ty, or
   ** \li the type of of the declared object, in case of a Dec.
   */

  class Typable
  {
  public:

    Typable() = default;
    Typable(const type::Type* type);
    ~Typable();

    void type_set (const type::Type*);
    const type::Type* type_get () const;

    virtual void accept (ConstVisitor& v) const = 0;
    virtual void accept (Visitor& v) = 0;
    
  private:
    const type::Type* type_;
  };

} // namespace ast

#include <ast/typable.hxx>

