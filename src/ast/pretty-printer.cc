/**
 ** \file ast/pretty-printer.cc
 ** \brief Implementation of ast::PrettyPrinter.
 */

#include <misc/escape.hh>
#include <misc/indent.hh>
#include <misc/separator.hh>
#include <misc/pair.hh>
#include <ast/all.hh>
#include <ast/pretty-printer.hh>
#include <ast/libast.hh>


namespace ast
{

    // Anonymous namespace: these functions are private to this file.
    namespace
    {

        /// \brief Output \a e on \a ostr.
        ///
        /// Used to factor the output of the name declared,
        /// and its possible additional attributes.
        inline
            std::ostream&
            operator<< (std::ostream& ostr, const Dec& e)
            {
                ostr << e.name_get();
                return ostr;
            }
    }



    PrettyPrinter::PrettyPrinter(std::ostream& ostr)
        : ostr_(ostr)
    {}


    void
        PrettyPrinter::operator()(const SimpleVar& e)
        {
            ostr_ << e.name_get();
        }

    void
        PrettyPrinter::operator()(const FieldVar& e)
        {
            // FIXME: Some code was deleted here.
        }

    /* Foo[10]. */
    void
        PrettyPrinter::operator()(const SubscriptVar& e)
        {
            ostr_ << e.var_get() << '[' << misc::incindent << e.index_get()
                << misc::decindent << ']';
        }

    void
        PrettyPrinter::operator()(const CastVar& e)
        {
            ostr_ << "_cast(" << e.var_get() << ", " << e.ty_get() << ')';
        }

    void
        PrettyPrinter::operator()(const CastExp& e)
        {
            ostr_ << "_cast(" << e.exp_get() << ", " << e.ty_get() << ')';
        }

    void
        PrettyPrinter::operator()(const IfExp& e)
        {
            ostr_ << "(if " << e.test_get() << misc::incindent
                << "then " << e.then_get();
            if (e.else_get() != nullptr)
                ostr_ << misc::incindent
                    << "else " << e.else_get() << ')' << misc::decindent;
            else
                ostr_ << ')' << misc::decindent;
        }

    void
        PrettyPrinter::operator()(const LetExp& e)
        {
            ostr_ << "let" << misc::incindent
                << e.decs_get() << misc::decindent
                << "in" << misc::incindent
                << e.seq_get() << misc::decindent
                << "end;" << misc::decindent;
        }

    void
        PrettyPrinter::operator()(const FunctionDec& e)
        {
            ostr_ << "function " << e.formals_get() << ':' << e.result_get()
                    << '=' << misc::incindent
                << '(' << e.body_get() << ')' << misc::decindent;
        }

    void
        PrettyPrinter::operator()(const Exp& e)
        {
            ostr_ << '(' << e << ')' << misc::decindent;
        }

    void
        PrettyPrinter::operator()(const ForExp& e)
        {
            ostr_ << "(for " << e.vardec_get() << " to " << e.hi_get() << " do"
                    << misc::incindent
                << e.body_get() << ");" << misc::decindent;
        }

    void
        PrettyPrinter::operator()(const VarDec& e)
        {
            ostr_ << e.type_name_get() << " : " << e.init_get();
        }

    void
        PrettyPrinter::operator()(const NameTy& e)
        {
            ostr_ << e.name_get();
        }

    // FIXME: Some code was deleted here.

} // namespace ast
