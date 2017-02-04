/**
 ** \file ast/call-exp.hh
 ** \brief Declaration of ast::CallExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/function-dec.hh>
#include <misc/symbol.hh>

namespace ast
{

    /**
     * \class ast::CallExp
     * \brief FIXME
     *
     * FIXME
     */

    /// CallExp.
    class CallExp : public Exp
    {
        public:
            /**
             * \name Ctor & dtor.
             * \{ */
            /// Construct a CallExp node.
            CallExp(const Location& location, Exp* exp); //FIXME
            /// Destroy a CallExp node.
            virtual ~CallExp();
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
            /// Return the call expression.
            const Exp& exp_get() const;
            /// Return the call expression.
            Exp& exp_get();
            /** \} */

        protected:
            /// The call expression.
            Exp* exp_;
    };

} // namespace ast

#include <ast/call-exp.hxx>

