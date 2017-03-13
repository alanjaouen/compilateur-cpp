/**
 ** \file ast/function-dec.hh
 ** \brief Declaration of ast::FunctionDec.
 */

#pragma once

#include <ast/dec.hh>
#include <ast/exp.hh>
#include <ast/name-ty.hh>
#include <ast/type-constructor.hh>
#include <ast/var-dec.hh>
#include <ast/any-decs.hh>

namespace ast
{
    /**
     * \class ast::FunctionDec
     * \brief FIXME
     *
     * FIXED
     */

    /// FunctionDec.
    class FunctionDec : public Dec
    {
        public:
            /** \name Ctor & dtor.
             ** \{ */
            /// Construct a FunctionDec node.
            FunctionDec(const Location& location, const misc::symbol& name,
                    VarDecs* formals, NameTy* result, Exp* body);
            /// Destroy a FunctionDec node.
            virtual ~FunctionDec();
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
            /// Return formal arguments.
            const VarDecs& formals_get() const;
            /// Return formal arguments.
            VarDecs& formals_get();
            /// Return result type.
            const NameTy* result_get() const;
            /// Return result type.
            NameTy* result_get();
            /// Return instructions.
            const Exp* body_get() const;
            /// Return instructions.
            Exp* body_get();
            /// Set instructions.
            void body_set(Exp*);
            /** \} */

        protected:
            /// The formal arguments.
            VarDecs* formals_;
            /// The result type.
            NameTy* result_;
            /// The instructions.
            Exp* body_;
    };

} // namespace ast

#include <ast/function-dec.hxx>

