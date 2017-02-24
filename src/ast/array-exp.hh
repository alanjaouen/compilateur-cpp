/**
 ** \file ast/array-exp.hh
 ** \brief Declaration of ast::ArrayExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{


    /**
     * \class ast::ArrayExp.
     * \brief FIXME
     *
     * FIXME
     */

    /// ArrayExp.
    class ArrayExp : public Exp
    {
        public:
            /**
             * \name Ctor & dtor.
             * \{ */
            /// Construct a ArrayExp node.
            ArrayExp(const Location& location, NameTy* type,
                     Exp* l_exp, Exp* r_exp);
            /// Destroy a ArrayExp node.
            virtual ~ArrayExp();
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
            /// Return the name of the type.
            const NameTy& type_get() const;
            /// Return the name of the type.
            NameTy& type_get();
            /// Return the left expression.
            const Exp& l_exp_get() const;
            /// Return the left expression.
            Exp& l_exp_get();
            /// Return the right expression.
            const Exp& r_exp_get() const;
            /// Return the right expression.
            Exp& r_exp_get();
            const VarDec* def_get() const;
            /// Return definition site.
            VarDec* def_get();
            /// Set definition site.
            void def_set(VarDec*);
            /** \} */

        protected:
            /// The name of the type.
            NameTy* type_;
            /// The left expression.
            Exp* l_exp_;
            /// The right expression.
            Exp* r_exp_;

            /// Definition site.
            VarDec* def_ = nullptr;
    };

} // namespace ast

#include <ast/array-exp.hxx>

