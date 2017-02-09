/**
 ** \file ast/record-ty.hh
 ** \brief Declaration of ast::RecordTy.
 */

#pragma once

#include <ast/field.hh>
#include <ast/ty.hh>

namespace ast
{


    /**
     * \class ast::RecordTy
     * \brief FIXME
     *
     * FIXME
     */

    /// RecordTy.
    class RecordTy : public Ty
    {
        public:


            /**
             * \name Ctor & dtor.
             * \{ */
            /// Construct a RecordTy node.
      RecordTy(const Location& location, fields_type* vect);
            /// Destroy a RecordTy node.
            virtual ~RecordTy();
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
            /// Return declarations.
            const fields_type& recs_get() const;
            /// Return declarations.
            fields_type& recs_get();
            /** \} */

        protected:
            /// The declarations.
            fields_type* vect_;
    };

} // namespace ast

#include <ast/record-ty.hxx>

