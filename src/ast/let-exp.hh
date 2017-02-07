/**
 ** \file ast/let-exp.hh
 ** \brief Declaration of ast::LetExp.
 */

#pragma once

#include <misc/contract.hh>
#include <ast/seq-exp.hh>
#include <ast/exp.hh>
#include <ast/decs-list.hh>

namespace ast
{


    /**
     * class ast::LetExp.
     * \brief FIXME
     *
     * FIXME
     */

    /// LetExp.
    class LetExp : public Exp
    {
        public:
            /**
             * \name Ctor & dtor.
             * \{ */
            /// Construct a LetExp node.
            LetExp(const Location& location, DecsList* decs, exps_type* vect);
            /// Destroy a LetExp node.
            virtual ~LetExp();
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
            /// Return the list declaration.
            const DecsList& decs_get() const;
            /// Return the list declaration.
            DecsList& decs_get();
            /// Return the sequence of expression.
            const exps_type& seq_get() const;
            /// Return the sequence of expression.
            exps_type& seq_get();
            /** \} */

        protected:
            /// The list declaration.
            DecsList* decs_;
            /// The sequence of expression.
            exps_type* vect_;
    };

} // namespace ast

#include <ast/let-exp.hxx>

