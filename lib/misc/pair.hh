/**
 ** \file misc/pair.hh
 ** \brief An std::pair with support for printing.
 */

#pragma once

#include <iosfwd>

namespace misc
{

  template <class Fst, typename Snd>
  struct pair : public std::pair<Fst, Snd>
  {
    pair(const Fst& fst, const Snd& snd);
  };

  // c++1z - template arguments deduction for constructors
  // make_pair function will become useless

  /// Shorthand to create pair (fst, snd).
  template <class Fst, typename Snd>
  pair<Fst, Snd>
  make_pair(Fst fst, Snd snd);

  /// Output the pair object \a s on \a ostr.
  template <class Fst, typename Snd>
  inline std::ostream&
  operator<<(std::ostream& ostr, const pair<Fst, Snd>& p);

} // namespace misc

#include <misc/pair.hxx>
