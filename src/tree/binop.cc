/**
 ** \file tree/binop.cc
 ** \brief Implementation for tree/binop.hh.
 **/

#include <ostream>

#include <tree/binop.hh>

namespace tree
{

  Binop::Binop(const Oper oper, const rExp& left, const rExp& right)
    : Exp()
    , oper_(oper)
  {
    child_emplace_back(left);
    child_emplace_back(right);
  }

  std::ostream&
  Binop::tag_print(std::ostream& ostr) const
  {
    ostr << "binop ";
    switch (oper_)
      {
      case add:       ostr << "add";     break;
      case sub:       ostr << "sub";     break;
      case mul:       ostr << "mul";     break;
      case div:       ostr << "div";     break;
      case logic_and: ostr << "and";     break;
      case logic_or:  ostr << "or";      break;
      case lshift:    ostr << "lshift";  break;
      case rshift:    ostr << "rshift";  break;
      case arshift:   ostr << "arshift"; break;
      case logic_xor: ostr << "xor";     break;
      }
    return ostr;
  }

  Tree::kind_tree_type
  Binop::kind_get() const
  {
    return binop_kind;
  }
} // namespace tree
