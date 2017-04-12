/**
 ** \file tree/visitor.hh
 ** \brief Allow to visit intermediate representation fragments.
 */

#pragma once

#include <misc/select-const.hh>
#include <tree/fwd.hh>

namespace tree
{

  template <template <typename> class Const>
  class GenVisitor
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Convenient abbreviation.
    template <typename Type>
    using const_t = typename Const<Type>::type;

    /// Destroy an Visitor
    virtual ~GenVisitor() = default;
    /** \} */

    /// Visit an intermediate representation procedure fragment.
    virtual void operator()(const_t<ProcFrag>& a);
    /// Visit an intermediate representation data fragment.
    virtual void operator()(const_t<DataFrag>& a);
    /// To enable the use of standard algorithm on containers of pointers.
    template <class E> void operator()(E* e);

    /// Visit a list of intermediate representation fragments.
    virtual void operator()(const_t<Fragments>& fs);
  };

  /// Readonly visitor.
  using ConstVisitor = GenVisitor<misc::constify_traits>;
  /// Read-write visitor.
  using Visitor = GenVisitor<misc::id_traits>;

} // namespace tree

#include <tree/visitor.hxx>
