/**
 ** \file object/libobject.cc
 ** \brief Define exported object functions.
 */

#include <memory>

#include <object/libobject.hh>
#include <ast/libast.hh>
#include <object/binder.hh>
  // FIXME: Some code was deleted here.
#include <object/type-checker.hh>
#include <desugar/libdesugar.hh>
#include <object/renamer.hh>
#include <object/desugar-visitor.hh>

namespace object
{
  /*-------.
  | Bind.  |
  `-------*/

  misc::error bind(ast::Ast& e)
  {
  }
  misc::error bind_obj(ast::Ast& e)
  {
    Binder bind_compute;
    bind_compute(e);
    return bind_compute.error_get();
  }
  /*----------------.
  | Compute types.  |
  `----------------*/

  misc::error
  types_check(ast::Ast& tree)
  {
    TypeChecker type;
    type(tree);
    return type.error_get();
  }


  /*---------.
  | Rename.  |
  `---------*/

  class_names_type*
  rename(ast::Ast& tree)
  {
    // Rename.
    Renamer rename;
    rename(tree);
    return rename.class_names_get();
  }


  /*------------------.
  | Desugar objects.  |
  `------------------*/

  template <typename A>
  A*
  raw_desugar(const A& tree, const class_names_type& class_names)
  {
    // Desugar.
    DesugarVisitor desugar(class_names);
    desugar(tree);
    return dynamic_cast<A*>(desugar.result_get());
  }

  template <typename A>
  A*
  desugar(const A& tree, const class_names_type& class_names)
  {
    // Desugar.
    A* desugared = raw_desugar(tree, class_names);
    assertion(desugared);
    std::unique_ptr<A> desugared_ptr(desugared);
    // Recompute the bindings and the types.
    ::desugar::bind_and_types_check(*desugared_ptr);
    return desugared_ptr.release();
  }

  /// Explicit instantiations.
  template ast::DecsList* raw_desugar(const ast::DecsList&,
                                      const class_names_type&);
  template ast::DecsList* desugar(const ast::DecsList&,
                                  const class_names_type&);


} // namespace object
