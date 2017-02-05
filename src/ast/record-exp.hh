/**
 ** \file ast/record-exp.hh
 ** \brief Declaration of ast::RecordExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/field-init.hh>
#include <ast/name-ty.hh>
#include <ast/any-decs.hh>
namespace ast
{

    /**
     * \class ast::RecordExp
     * \brief FIXME
     *
     * FIXME
     */

    /// RecordExp.
    class RecordExp : public Exp
    {
        public:
            /**
             * \name Ctor & dtor.
             * \{ */
            /// Construct a RecordExp node.
            RecordExp(const Location& location, Exp* exp, FieldInits* vect);
            /// Destroy a RecordExp node.
            virtual ~RecordExp();
            /** \} */

            /**
             * \name Visitors entry point.
             * \{ */
            /// Accept a const visitor \a v.
            void accept(ConstVisitor& v) const override;
            /// Accept a non-const visitor \a v.
            void accept(Visitor& v) override;
            /** \} */

            /**
             * \name Accessors.
             * \{ */
            /// Return the record expression.
            const Exp& exp_get() const;
            /// Return the record expression.
            Exp& exp_get();
            /// Return the initiated field.
            const FieldInits& fini_get() const;
            /// Return the initiated field.
            FieldInits& fini_get();
            /** \} */

        protected:
            /// The record expression.
            Exp* exp_;
            /// The initiated field.
            FieldInits *vect_;
    };

} // namespace ast

#include <ast/record-exp.hxx>

