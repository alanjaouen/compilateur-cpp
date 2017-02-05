/**
 ** \file ast/assign-exp.hh
 ** \brief Declaration of ast::AssignExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/var.hh>

namespace ast
{


    /**
     * \class ast::AssignExp.
     * \brief FIXME
     *
     * FIXME
     */

    /// AssignExp.
    class AssignExp : public Exp
    {
        public:
            /**
             * \name Ctor & dtor.
             * \{ */
            /// Construct a AssignExp node.
            AssignExp(const Location& location, Var* lvalue, Exp* exp);
            /// Destroy a AssignExp node.
            virtual ~AssignExp();
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
            /// Return the variable value.
            const Var& var_get() const;
            /// Return the variable value.
            Var& var_get();
            /// Return the assigned expression.
            const Exp& exp_get() const;
            /// Return the assigned expression.
            Exp& exp_get();
            /** \} */

        protected:
            /// The variable value.
            Var* lvalue_;
            /// The assigned expression.
            Exp* exp_;
    };

} // namespace ast

#include <ast/assign-exp.hxx>

