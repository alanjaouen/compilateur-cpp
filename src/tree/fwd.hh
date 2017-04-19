/**
 ** \file tree/fwd.hh
 ** \brief Intermediate representation: all the forward declarations.
 **/

#pragma once

#include <vector>

#include <misc/fwd.hh>
#include <misc/ref.hh>

namespace tree
{
#define DECLARE(What)                           \
  class What;                                   \
  using r ## What = misc::ref< What >;

  DECLARE(Tree)
  DECLARE(Binop)
  DECLARE(Call)
  DECLARE(Cjump)
  DECLARE(Const)
  DECLARE(Eseq)
  DECLARE(Exp)
  DECLARE(Jump)
  DECLARE(Label)
  DECLARE(Mem)
  DECLARE(Move)
  DECLARE(Name)
  DECLARE(Seq)
  DECLARE(Stm)
  DECLARE(Sxp)
  DECLARE(Temp)

#undef DECLARE

  // Arguably we could include this typedef in the class Tree.
  using tree_list_type = std::vector<rTree>;

  // From fragment.hh.
  class Fragment;
  class ProcFrag;
  class DataFrag;

  // From fragments.hh.
  class Fragments;

  // From visitor.hh.
  template <template <typename> class Const>
  class GenVisitor;
  // FIXME: Ought to be _type.
  using ConstVisitor = GenVisitor<misc::constify_traits>;
  using Visitor = GenVisitor<misc::id_traits>;

} // namespace tree
