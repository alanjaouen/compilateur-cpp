/**
 ** \file ast/field-var.hh
 ** \brief Declaration of ast::FieldVar.
 */

#pragma once

#include <ast/var.hh>
#include <misc/symbol.hh>

namespace ast
{


    /**
     * \class ast::FieldVar
     * \brief FIXME
     *
     * FIXME
     */

    /// FieldVar.
    class FieldVar : public Var
    {
        public:
            /**
             * \name Ctor & dtor.
             * \{ */
            /// Construct a FieldVar node.
            FieldVar(const Location& location, Var* var, Field* field);
            /// Destroy a FieldVar node.
            virtual ~FieldVar();
            /** /} */

            /**
             * \name Visitors entry point.
             * \{ */
            /// Accept a const visitor \a v.
            void accept(ConstVisitor& v) const override;
            /// Accept a non-const visitor \a v.
            void accept(Visitor& v) override;
            /**  \} */

            /**
             * \name Accessors.
             * \{ */
            /// Return the field variable.
            const Var& var_get() const;
            /// Return the field variable.
            Var& var_get();
            /// Return the field of the variable.
            const Field& field_get() const;
            /// Return the field of the variable.
            Field& field_get();
            /** /} */

        protected:
            /// The field variable.
            Var* var_;
            /// The field of the variable.
            Field* field_;
    };

} // namespace ast

#include <ast/field-var.hxx>

