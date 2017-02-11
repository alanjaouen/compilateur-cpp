/**
 ** \file ast/object-exp.hh
 ** \brief Declaration of ast::ObjectExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{


    /**
     * \class ast::ObjectExp
     * \brief FIXME
     *
     * FIXME
     */

    /// ObjectExp.
    class ObjectExp : public Exp
    {
        public:
            /**
             * \name Ctor & dtor.
             * \{ */
            /// Construct an ObjectExp node.
            ObjectExp(const Location& location, NameTy* type);
            /// Destroy an ObjectExp node.
            virtual ~ObjectExp();
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
            /// Return the type of the expression.
            const NameTy& type_get() const;
            /// Return the type of the expression.
            NameTy& type_get();
            /** \} */

        protected:
            /// The type of the expression.
            NameTy* type_;
    };

} // namespace ast

#include <ast/object-exp.hxx>

