/**
 ** \file escapes/escapes-visitor.hh
 ** \brief Compute the escapes.
 **
 ** Variables and formals of a function may escape, i.e., be accessed
 ** by an inner function.
 **
 ** When the semantic analysis finds a declaration of variable or
 ** formal FOO, it needs to know whether it escapes or not.  This
 ** requires an additional pass, before the semantic analysis, just to
 ** spot the potential escapes of FOO.
 **
 ** In order to pass the result to the semantic analysis which walks
 ** across the ast, the most natural and easy solution consists in
 ** tagging the various VarDec and Field.
 **
 ** Now, how shall we compute the escapes?
 ** The answer is obvious: we need to walk the ast, searching for variables
 ** declared then accessed by an inner function.
 */

#pragma once

#include <map>

#include <ast/default-visitor.hh>
#include <ast/non-object-visitor.hh>
#include <misc/scoped-map.hh>
namespace escapes
{

  /** \brief Compute the escapes.
   **
   ** The EscapeVisitor is extremely similar to type::TypeChecker:
   ** in its course of operation it must relate uses to
   ** definitions.  Therefore it will be run after the bind::Binder.
   ** It also needs auxiliary information about the definitions (their
   ** depth): a simple map suffices, since scoping issues were handled
   ** by the bind::Binder.
   **
   ** Note that this EscapesVisitor is mainly doing nothing: it is just
   ** interested in declaration and uses of variables/formals (and, of
   ** course, function declaration...).  It would be somewhat stupid to
   ** write all the methods that `do nothing but walk'.  This is why we
   ** will inherit from the non const ast::DefaultVisitor.
   **/
  class EscapesVisitor
    : public ast::DefaultVisitor
    , public ast::NonObjectVisitor
  {
  public:
    //Fixed by caradi_c.
    /// Super class type.
    using super_type = ast::DefaultVisitor;
    /// Import all the overloaded visit methods.
    using super_type::operator();

//    using dmap = std::map<misc::symbol, std::pair<ast::VarDec*, int>>;

    EscapesVisitor()
      {
        scope_begin();
      }
    ~EscapesVisitor()
      {
        scope_end();
      }
    //commence par increment le compteur; visite le contenu; decremente
    // inline void Binder::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e);
    void operator()(ast::VarDec& e) override;
    void operator()(ast::FunctionDec& e) override;
    void operator()(ast::SimpleVar& e) override;
    //map de <symbol, std::pair<vardec*, depth(un int de count)>>;
    //compteur statique et fonction d'increment et de decrement;
        /** \name Handling the environment
     ** \{ */
    /// Open a new var, fun, and type scope.
    virtual void scope_begin();
    /// Close the latest var, fun, and type scope.
    virtual void scope_end();
    /** \} */    
    //reshearch in th map
    ast::VarDec* get(misc::symbol sym);
    //add an elemet to the map
    void put(ast::VarDec* var);
    //print the map on std::cout
    void dump();

  private:
    misc::scoped_map<misc::symbol, ast::VarDec*> var_scope_;
    // dmap depth_map_;
    // int depth_;
  };

} // namespace escapes
#include <escapes/escapes-visitor.hxx>
