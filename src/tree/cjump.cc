/**
 ** \file tree/cjump.cc
 ** \brief Implementation of tree::Cjump.
 **/

#include <ostream>
#include <tree/cjump.hh>

namespace tree
{

  Cjump::Cjump(Relop relop,
               const rExp& left, const rExp& right,
               const rName& iftrue, const rName& iffalse)
    : Stm()
    , relop_(relop)
  {
    child_emplace_back(left);
    child_emplace_back(right);
    child_emplace_back(iftrue);
    child_emplace_back(iffalse);
  }

  std::ostream&
  Cjump::tag_print(std::ostream& ostr) const
  {
    ostr << "cjump " << relop_;
    return ostr;
  }

  Tree::kind_tree_type
  Cjump::kind_get() const
  {
    return cjump_kind;
  }

  Cjump::Relop
  symmetrize(const Cjump::Relop& r)
  {
    switch (r)
      {
      case Cjump::eq:  return Cjump::eq;
      case Cjump::ne:  return Cjump::ne;

      case Cjump::lt:  return Cjump::gt;
      case Cjump::gt:  return Cjump::lt;

      case Cjump::le:  return Cjump::ge;
      case Cjump::ge:  return Cjump::le;

      case Cjump::ult: return Cjump::ugt;
      case Cjump::ugt: return Cjump::ult;

      case Cjump::ule: return Cjump::uge;
      case Cjump::uge: return Cjump::ule;

      default:
        die("Should not be here.");
      };
  }

  std::ostream&
  operator<<(std::ostream& ostr, const Cjump::Relop& r)
  {
    switch (r)
      {
      case Cjump::eq:  ostr << "eq";  break;
      case Cjump::ne:  ostr << "ne";  break;
      case Cjump::lt:  ostr << "lt";  break;
      case Cjump::gt:  ostr << "gt";  break;
      case Cjump::le:  ostr << "le";  break;
      case Cjump::ge:  ostr << "ge";  break;
      case Cjump::ult: ostr << "ult"; break;
      case Cjump::ugt: ostr << "ugt"; break;
      case Cjump::ule: ostr << "ule"; break;
      case Cjump::uge: ostr << "uge"; break;
      }
    return ostr;
  }

} // namespace tree
