/**
 ** \file translate/exp.hxx
 ** \brief Inline methods for translate/exp.hh.
 **/

#pragma once

#include <translate/exp.hh>

namespace translate
{
  inline
  Cx::Cx(tree::Cjump::Relop op,
         const tree::rExp& left, const tree::rExp& right)
    : op_(op)
    , left_(left)
    , right_(right)
  {}


  inline
  Ex::Ex(const tree::rExp& exp)
    : exp_(exp)
  {}

  inline
  Nx::Nx(const tree::rStm& stm)
    : stm_(stm)
  {}

  inline
  Ix::Ix(rExp& cond, rExp& iftrue, rExp& iffalse)
    : cond_(cond)
    , iftrue_(iftrue)
    , iffalse_(iffalse)
  {}


  inline std::ostream&
  operator<<(std::ostream& ostr, const Exp& exp)
  {
    return exp.dump(ostr);
  }

} // namespace translate
