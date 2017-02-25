/**
 ** \file bind/renamer.hxx
 ** \brief Template methods of bind::Renamer.
 */

#pragma once

#include <bind/renamer.hh>

namespace bind
{
  //fixed by caradi_c

  template <typename Def>
  misc::symbol Renamer::new_name_compute(const Def& e)
  {
    return e.name_get().fresh(e.name_get());
  }

  template <typename Def>
  misc::symbol Renamer::new_name(const Def& e)
  {
    return new_name_compute(e);
  }

  // template <class E, class Def>
  // void
  // Renamer::visit(E& e, const Def* def)
  // {
    
  // }


} // namespace bind
