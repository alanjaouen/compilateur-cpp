/**
 ** \file ast/record-ty.hh
 ** \brief Declaration of ast::RecordTy.
 */

#pragma once

#include <ast/field.hh>
#include <ast/ty.hh>

namespace ast
{

  /// RecordTy.
  class RecordTy : public Ty
  {
  public:
    using field_list = std::list<Field*>;

    RecordTy(const Location& location);
    virtual ~RecordTy();

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /// Prepend \a d.
    void push_front(Field* d);
    /// Append \a d.
    void emplace_back(Field* d);

    /// Splice the content of \a ds in front of this list.
    void splice_front(RecordTy& rs);
    /// Splice the content of \a ds at the back this list.
    void splice_back(RecordTy& rs);

    /** \name Accessors.
     ** \{ */
    /// Return declarations.
    const RecordTy::field_list& recs_get() const;
    /// Return declarations.
    RecordTy::field_list& recs_get();
    /** \} */

  protected:
    RecordTy::field_list recs_;
  };

} // namespace ast

#include <ast/record-ty.hxx>

