/**
 ** \file ast/seq-exp.hh
 ** \brief Declaration of ast::SeqExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{

  /// SeqExp.
  class SeqExp : public Exp
  {
  public:
    using seq_type = std::list<Exp*>;

    /// Prepend \a d.
    void push_front(Exp* e);
    /// Append \a d.
    void emplace_back(Exp* e);

    /// Splice the content of \a ds in front of this list.
    void splice_front(SeqExp& es);
    /// Splice the content of \a ds at the back this list.
    void splice_back(SeqExp& es);

    /// Construct a SeqExp node.
    SeqExp(const Location& location);

  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a SeqExp node.
    SeqExp(const Location& location, const SeqExp::seq_type& seq);
    /// Destroy a SeqExp node.
    virtual ~SeqExp();
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return declarations.
    const SeqExp::seq_type& seq_get() const;
    /// Return declarations.
    SeqExp::seq_type& seq_get();
    /** \} */
  protected:
        /// Declarations.
    SeqExp::seq_type seq_;

  };

} // namespace ast

#include <ast/seq-exp.hxx>

