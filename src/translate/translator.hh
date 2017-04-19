/**
 ** \file translate/translator.hh
 ** \brief Declaration of translate::Translator.
 */

#pragma once

#include <list>
#include <map>
#include <stack>

#include <ast/default-visitor.hh>
#include <ast/non-object-visitor.hh>

#include <temp/fwd.hh>
#include <tree/fwd.hh>
#include <translate/fwd.hh>

namespace translate
{

  /// Translate an ast::Ast into High level tree::Tree code.
  class Translator
    : public ast::DefaultConstVisitor
    , public ast::NonObjectConstVisitor
  {
  public:
    /// Super class.
    using super_type = ast::DefaultConstVisitor;
    /// Import overloaded operator() methods.
    using super_type::operator();

    Translator();

    /// \name Forbid copying this visitor: do not implement the copy
    /// ctor nor the assignment operator.
    ///
    /// Copying is forbidden because deep-copy is not implemented,
    /// and the dtor deletes the level_ attribute, which is allocated
    /// by the ctor.
    /// \{
    Translator(const Translator&) = delete;
    Translator& operator=(const Translator&) = delete;
    /// \}

    virtual ~Translator();

    /// Run the translation.
    void operator()(const ast::Ast& e) override;

    /// \brief Return the translation.
    /// Ownership is transferred to the receiver.
    tree::Fragments* fragments_get();

    /// \brief Run this visitor on \a node, and return its translation.
    ///
    /// It is also guaranteed that \a exp_ is set to it.
    /// More generally, this routine saves from direct calls to \a accept.
    rExp translate(const ast::Ast& node);

    /// The list of translations of \a es members.
    template <typename T>
    std::vector<rExp> translate(const std::vector<T*>& es);

    /// \name Lvalues
    /// \{
    void operator()(const ast::SimpleVar& e) override;
    void operator()(const ast::FieldVar& e) override;
    void operator()(const ast::SubscriptVar& e) override;
    void operator()(const ast::CastVar& e) override;
    /// \}


    /// \name Expressions
    /// \{
    // Literals.
    void operator()(const ast::NilExp&) override;
    void operator()(const ast::IntExp& e) override;
    // Literal string: insert its definition in fragments_, and return
    // an exp which refers to this fragment.
    void operator()(const ast::StringExp& e) override;
    void operator()(const ast::RecordExp& e) override;
    void operator()(const ast::CallExp& e) override;
    void operator()(const ast::OpExp& e) override;
    void operator()(const ast::SeqExp& e) override;
    void operator()(const ast::AssignExp& e) override;
    void operator()(const ast::IfExp& e) override;
    void operator()(const ast::WhileExp& e) override;

    // Translating a ForExp is an EPITA.  It would be more pleasant to
    // build a pseudo AST which maps a for-loop into a while-loop.
    void operator()(const ast::ForExp& e) override;
    void operator()(const ast::BreakExp&) override;
    void operator()(const ast::LetExp& e) override;
    void operator()(const ast::ArrayExp& e) override;
    void operator()(const ast::CastExp& e) override;
    /// \}

    /// \name Chunks of declarations
    /// \{
    void operator()(const ast::VarDecs& e) override;
    void operator()(const ast::TypeDecs&) override;
    void operator()(const ast::FunctionDecs& e) override;
    /// \}

    /// \name Function Declaration
    /// \{
    void operator()(const ast::FunctionDec&) override;
    void visit_function_dec_header(const ast::FunctionDec& e);
    void visit_function_dec_body(const ast::FunctionDec& e);
    /// \}

    void operator()(const ast::VarDec& e) override;

  protected:
    /// The translation of the last visited node.
    rExp exp_;

    /// The translations of all the pending declarations.
    std::stack<std::vector<rExp>> exps_;

    /// The fragments translated so far (functions and string literals).
    tree::Fragments* fragments_;

    /// The current level (related to FunctionDec nestings).
    Level* level_;

    /// For each loop, the address immediately after it.
    std::map<const ast::Exp*, temp::Label> loop_end_label_;

    /// Access for each "variable" (VarDec, Field).
    std::map<const ast::Ast*, const Access*> var_access_;

    /// Level for each function.
    std::map<const ast::Ast*, const Level*> fun_level_;

    /// Label for each function.
    std::map<const ast::Ast*, temp::Label> fun_label_;


  };

} // namespace translate
