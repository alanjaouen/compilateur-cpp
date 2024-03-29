                                                                // -*- C++ -*-
%require "3.0"
%language "C++"
// Set the namespace name to `parse', instead of `yy'.
%name-prefix "parse"
%define api.value.type variant
%define api.token.constructor
%skeleton "glr.cc" // The grammar is lalr1
%glr-parser
%expect 2           // No shift/reduce
%expect-rr 0
%define parse.error verbose
%define parse.trace


 // FIXED by forest_b
%defines
%debug
// Prefix all the tokens with TOK_ to avoid colisions.
%define api.token.prefix {TOK_}

/* We use pointers to store the filename in the locations.  This saves
   space (pointers), time (no deep copy), but leaves the problem of
   deallocation.  This would be a perfect job for a misc::symbol
   object (passed by reference), however Bison locations require the
   filename to be passed as a pointer, thus forcing us to handle the
   allocation and deallocation of this object.

   Nevertheless, all is not lost: we can still use a misc::symbol
   object to allocate a flyweight (constant) string in the pool of
   symbols, extract it from the misc::symbol object, and use it to
   initialize the location.  The allocated data will be freed at the
   end of the program (see the documentation of misc::symbol and
   misc::unique).  */
%define filename_type {const std::string}
%locations

// The parsing context.
%param { ::parse::TigerParser& tp }

/*---------------------.
| Support for tokens.  |
`---------------------*/
%code requires
{
#include <string>
#include <misc/algorithm.hh>
#include <misc/separator.hh>
#include <misc/symbol.hh>
#include <parse/fwd.hh>

  // Pre-declare parse::parse to allow a ``reentrant'' parsing within
  // the parser.
  namespace parse
  {
    ast_type parse(Tweast& input);
  }
}

%code provides
{
  // Announce to Flex the prototype we want for lexing (member) function.
  # define YY_DECL_(Prefix)                               \
    ::parse::parser::symbol_type                          \
    (Prefix parselex)(::parse::TigerParser& tp)
  # define YY_DECL YY_DECL_(yyFlexLexer::)
}

%printer { yyo << $$; } <int> <std::string> <misc::symbol>;
%printer {
            if ($$ == nullptr)
                yyo << "nullptr";
            else
                yyo << $$;
         } <ast::Exp*><ast::Var*><ast::VarDecs*>
           <ast::DecsList*><ast::Ty*><ast::NameTy*>

%token <std::string>    STRING "string"
%token <misc::symbol>   ID     "identifier"
%token <int>            INT    "integer"


/*--------------------------------.
| Support for the non-terminals.  |
`--------------------------------*/

%code requires
{
# include <ast/fwd.hh>
// Provide the declarations of the following classes for the
// %destructor clauses below to work properly.
# include <ast/exp.hh>
# include <ast/var.hh>
# include <ast/ty.hh>
# include <ast/name-ty.hh>
# include <ast/field.hh>
# include <ast/field-init.hh>
# include <ast/function-dec.hh>
# include <ast/method-dec.hh>
# include <ast/type-dec.hh>
# include <ast/var-dec.hh>
# include <ast/any-decs.hh>
# include <ast/decs-list.hh>
}

  // FIXED by forest_b 


/*-----------------------------------------.
| Code output in the implementation file.  |
`-----------------------------------------*/

%code
{
# include <parse/tiger-parser.hh>
# include <parse/scantiger.hh>
# include <parse/tweast.hh>
# include <misc/separator.hh>
# include <misc/symbol.hh>
# include <ast/all.hh>
# include <ast/libast.hh>

  namespace
  {
    /// Get the metavar from the specified map.
    template <typename T>
    T*
    metavar(parse::TigerParser& tp, unsigned key)
    {
      parse::Tweast* input = tp.input_;
      return input->template take<T>(key);
    }

  }

  /// Use our local scanner object.
  inline
  ::parse::parser::symbol_type
  parselex(parse::TigerParser& tp)
  {
    return tp.scanner_->parselex(tp);
  }
}

// Definition of the tokens, and their pretty-printing.
%token AND          "&"
ARRAY        "array"
ASSIGN       ":="
BREAK        "break"
CAST         "_cast"
CLASS        "class"
COLON        ":"
COMMA        ","
DIVIDE       "/"
DO           "do"
DOT          "."
ELSE         "else"
END          "end"
EQ           "="
EXTENDS      "extends"
FOR          "for"
FUNCTION     "function"
GE           ">="
GT           ">"
IF           "if"
IMPORT       "import"
IN           "in"
LBRACE       "{"
LBRACK       "["
LE           "<="
LET          "let"
LPAREN       "("
LT           "<"
MINUS        "-"
METHOD       "method"
NE           "<>"
NEW          "new"
NIL          "nil"
OF           "of"
OR           "|"
PLUS         "+"
PRIMITIVE    "primitive"
RBRACE       "}"
RBRACK       "]"
RPAREN       ")"
SEMI         ";"
THEN         "then"
TIMES        "*"
TO           "to"
TYPE         "type"
VAR          "var"
WHILE        "while"
EOF 0        "end of file"
EXP "_exp"
LVALUE "_lvalue"
NAMETY "_namety"

CHUNK "chunk"


%nonassoc CHUNK
%nonassoc THEN OF //DO

%precedence ":=" "to" "in" "do" "else"
%nonassoc IF
%nonassoc CLASS METHOD EXTENDS FUNCTION PRIMITIVE TYPE VAR

%left "|"
%left "&"
%left "+" "-"
%left "*" "/"
%nonassoc ">=" "<=" "=" "<>" "<" ">"

%type <ast::Ast*> program
%type <ast::Exp*> exp
%type <ast::DecsList*> decs
%type <ast::NameTy*> type_id
%type <ast::exps_type*> exps
%type <ast::Var*> lvalue
 //%type <ast::Decs*> dec
%type <ast::Ty*> ty
%type <ast::NameTy*> return_type
%type <ast::VarDecs*> vardec
%type <ast::fieldinits_type*> array
%type <ast::exps_type*> function
%type <ast::VarDecs*> vardecs
%type <ast::fields_type*> tyfields
%type <ast::SubscriptVar*> lvalue_bracket
%type <ast::FieldVar*> lvalue_dot

%type <ast::FunctionDecs*> decs_functions
%type <ast::TypeDecs*> decs_types
%type <ast::FunctionDec*> dec_function
%type <ast::TypeDec*> dec_type


%type <ast::DecsList*> classfields
%type <ast::NameTy*> super_class
%type <ast::MethodDecs*> methoddecs
%type <ast::MethodDec*> methoddec


%destructor {delete $$;} <ast::Exp*> <ast::DecsList*> <ast::NameTy*> <ast::exps_type*> <ast::Var*>  <ast::Ty*>  <ast::fieldinits_type*> <ast::VarDecs*> <ast::fields_type*> <ast::TypeDecs*> <ast::FunctionDecs*> <ast::TypeDec*> <ast::FunctionDec*> <ast::MethodDec*> <ast::MethodDecs*>

%start program

%%
program:
  /* Parsing a source program.  */
  exp   { tp.ast_ = $1; }
| /* Parsing an imported file.  */
  decs  { tp.ast_ = $1; }
;

exp:

INT   { $$ = new ast::IntExp(@$, $1); }
|  "nil" { $$ = new ast::NilExp(@$); }
| STRING { $$ = new ast::StringExp(@$, $1); }
| type_id "[" exp "]" "of" exp { $$ = new ast::ArrayExp(@$, $1, $3, $6);}
| type_id "{" array "}" { $$ = new ast::RecordExp(@$, $1, $3);}
| "new" type_id { $$ = new ast::ObjectExp(@$, $2);}
| lvalue { $$ = $1;}
| ID "(" function ")" { $$ = new ast::CallExp(@$, $1, $3);}

| lvalue_dot "(" function ")" {
  ast::FieldVar* a = $1;
  $$ = new ast::MethodCallExp(@$, a->name_get(), $3, $1);}
| "-" exp      {$$ = new ast::OpExp(@$, new ast::IntExp(@$, 0), ast::OpExp::Oper::sub, $2);}
| exp "+" exp  {$$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::add, $3);}
| exp "-" exp  {$$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::sub, $3);}
| exp "*" exp  {$$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::mul, $3);}
| exp "/" exp  {$$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::div, $3);}
| exp "=" exp  {$$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::eq, $3);}
| exp "<>" exp {$$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::ne, $3);}
| exp ">" exp  {$$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::gt, $3);}
| exp "<" exp  {$$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::lt, $3);}
| exp ">=" exp {$$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::ge, $3);}
| exp "<=" exp {$$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::le, $3);}

| error "*" exp {$$ = new ast::OpExp(@$, new ast::IntExp(@1, -1), ast::OpExp::Oper::le, $3);}


| exp "&" exp { $$ = new ast::IfExp(@$, $1, new ast::OpExp(@$, $3, ast::OpExp::Oper::ne, new ast::IntExp(@$, 0)), new ast::IntExp(@$, 0));}

  //{ $$ = tp.parse(::parse::Tweast() << " if " << *$1 << " then " << *$3 << " <> 0 " << " else 0");}
| exp "|" exp { $$ = new ast::IfExp(@$, $1, new ast::IntExp(@$, 1), new ast::OpExp(@$, $3, ast::OpExp::Oper::ne, new ast::IntExp(@$, 0)));}

  //{ $$ = tp.parse(::parse::Tweast() << " if " << *$1 << " then 1 " << " else " << *$3 << " <> 0 ");}
| "(" exps ")" {$$ = new ast::SeqExp(@$, $2);}
| "("  ")" {$$ = new ast::SeqExp(@$, new ast::exps_type());}
| lvalue ":=" exp {$$ = new ast::AssignExp(@$, $1, $3);}
| error ":=" exp {$$ = new ast::AssignExp(@$, new ast::SimpleVar(@$, "err"), $3);}

| "if" exp "then" exp "else" exp {$$ = new ast::IfExp(@$, $2, $4, $6); }
| "if" exp "then" exp {$$ = new ast::IfExp(@$, $2, $4, nullptr); }
| "while" exp "do" exp {$$ = new ast::WhileExp(@$, $2, $4);}
| "while" error "do" exp {$$ = new ast::WhileExp(@$, new ast::SimpleVar(@$, "err"), $4);}
| "for" ID ":=" exp "to" exp "do" exp { $$ = new ast::ForExp
      (@$, new ast::VarDec(@2, $2, nullptr, $4), $6, $8);}
| "for" error ":=" exp "to" exp "do" exp { $$ = new ast::ForExp
      (@$, new ast::VarDec(@2, "err", nullptr, $4), $6, $8);}
| "break" { $$ = new ast::BreakExp(@$);}
| "let" decs "in" exps  "end" {$$ = new ast::LetExp(@$, $2, new ast::SeqExp(@$,$4)); }
| "let" decs "in"   "end" {$$ = new ast::LetExp(@$, $2, new ast::SeqExp(@$,new ast::exps_type())); }

| "_cast" "(" exp "," ty ")" { $$ = new ast::CastExp(@$, $3, $5);}
| "_exp" "(" INT ")" {$$ = metavar<ast::Exp>(tp, $3);}
;

array: ID "=" exp { $$ =  new ast::fieldinits_type(); $$->insert($$->begin(), new ast::FieldInit(@$, $1, $3));}
| ID "=" exp ","  array {$5->insert($5->begin(), new ast::FieldInit(@1, $1, $3));
  $$ = $5;}
| %empty   { $$ = new ast::fieldinits_type(); }
;

function: exp {$$ = new ast::exps_type(); $$->insert($$->begin(), $1);}
| exp "," function { $3->insert($3->begin(), $1); $$ = $3;}
| %empty  { $$ = new ast::exps_type(); }
;

lvalue:
ID {$$ = new ast::SimpleVar(@$, $1);}
| lvalue_dot {$$ = $1;}
| lvalue_bracket {$$ = $1;}
| "_cast" "(" lvalue "," ty ")" {$$ = new ast::CastVar(@$, $3, $5);}
| "_lvalue" "(" INT ")" {$$ = metavar<ast::Var>(tp, $3);}
;

//field-var
lvalue_dot:
lvalue_dot "." ID { auto* a = new ast::FieldVar(@$, $1, $3);
  $$ = a;}
|       lvalue_bracket "." ID { $$ = new ast::FieldVar(@$, $1, $3); }
|       ID "." ID { $$ = new ast::FieldVar(@$, new ast::SimpleVar(@1, $1), $3); }
;

//subscript-var
lvalue_bracket:
lvalue_dot "[" exp "]" { $$ = new ast::SubscriptVar(@$, $1, $3); }
|       lvalue_bracket "[" exp "]" { $$ = new ast::SubscriptVar(@$, $1, $3); }
|       ID "[" exp "]" { $$ = new ast::SubscriptVar(@$, new ast::SimpleVar(@1, $1), $3); }
|       ID "[" error "]" { $$ = new ast::SubscriptVar(@$, new ast::SimpleVar(@1, "err"), nullptr); }
;

exps: exp {auto* tab  = new ast::exps_type(); tab->insert(tab->begin(), $1); $$ = tab;}
| exp ";" exps {$3->insert($3->begin(), $1); $$ = $3;}
| exp error exps {$3->insert($3->begin(), $1); $$ = $3;}
;

/*---------------.
| Declarations.  |
`---------------*/

%token DECS "_decs";
decs:
%empty   { $$ = new ast::DecsList(@$); }
//| decs_type decs {$2->push_front($1); $$ = $2;}
| "_decs" "(" INT ")" decs {auto* a = metavar<ast::DecsList>(tp, $3);
  $5->splice_front(*a);
  $$ = $5;
  }
| "import" STRING decs {auto* a  = tp.parse_import($2, @2);
  if (a != nullptr)
    $3->splice_front(*a);
  $$ = $3;
  }
| vardec decs {$2->push_front($1); $$ = $2;}
| decs_functions decs {$2->push_front($1); $$ = $2;}
| decs_types decs {$2->push_front($1); $$ = $2;}
;

decs_types:
 dec_type %prec CHUNK  { $$ = new ast::TypeDecs(@$); $$->push_front(*$1);}
| dec_type decs_types { $2->push_front(*$1); $$ = $2;}
;

dec_type:
  "type" ID "=" ty  { $$ = new ast::TypeDec(@$, $2, $4);}
| "class" ID super_class "{" classfields "}" { auto* a = new ast::ClassTy(@$, $3, $5);
  $$ = new ast::TypeDec(@$, $2, a); }
;


decs_functions:
dec_function %prec CHUNK {$$ = new ast::FunctionDecs(@$); $$->push_front(*$1);}
| dec_function decs_functions { $2->push_front(*$1); $$ = $2;}
;


dec_function:
 "function" ID "(" vardecs ")" return_type "=" exp { $$ = new ast::FunctionDec(@$, $2, $4, $6, $8); }
| "function" ID "(" ")" return_type "=" exp {  $$ = new ast::FunctionDec(@$, $2, new ast::VarDecs(@$), $5, $7); }
| "primitive" ID "(" vardecs ")" return_type { $$ = new ast::FunctionDec(@$, $2, $4, $6, nullptr); }
| "primitive" ID "(" ")" return_type {$$ = new ast::FunctionDec(@$, $2, new ast::VarDecs(@$), $5, nullptr); }
;

vardec:
"var" ID return_type ":=" exp { auto* a = new ast::VarDecs(@$);
  auto* b = new ast::VarDec(@$, $2, $3, $5);
  a->push_front(*b);
  $$ = a;
}
;

return_type:
":" type_id { $$ = $2; }
| %empty    { $$ = nullptr; }
;
super_class:
"extends" type_id { $$ = $2; }
| %empty { $$ = new ast::NameTy(@$, misc::symbol("Object")); }
;

classfields:
vardec classfields {$2->push_front($1); $$ = $2;}
| methoddecs classfields {$2->push_front($1); $$ = $2;}
| %empty { $$ = new ast::DecsList(@$); }

;

methoddecs:
methoddec %prec CHUNK {$$ = new ast::MethodDecs(@$); $$->push_front(*$1);}
| methoddec methoddecs {$2->push_front(*$1); $$ = $2; }
;
methoddec:
 "method" ID "(" vardecs ")" return_type "=" exp { $$ = new ast::MethodDec(@$, $2, $4, $6, $8); }
| "method" ID "(" ")" return_type "=" exp {$$ = new ast::MethodDec(@$, $2, new ast::VarDecs(@$), $5, $7); }
;


ty:
type_id {$$ = $1;}
| "{" tyfields "}" {$$ = new ast::RecordTy(@$, $2);}
| "{"  "}" {$$ = new ast::RecordTy(@$, new ast::fields_type());}
| "array" "of" type_id { $$ = new ast::ArrayTy(@$, $3);}
| "class" super_class "{" classfields "}" { $$ = new ast::ClassTy(@$, $2, $4); }
;

//use field
tyfields:
ID ":" type_id {
  auto* tab = new ast::fields_type();
  auto* res = new ast::Field(@$, $1, $3);
  tab->insert(tab->begin(), res);
  $$ = tab;
}
|ID ":" type_id "," tyfields
{
  auto* res = new ast::Field(@$, $1, $3);
  $5->insert($5->begin(), res);
  $$ = $5;
}
;
// use vardec
vardecs:
ID ":" type_id {auto* tab = new ast::VarDecs(@$);
  auto* a =  new ast::VarDec(@$, $1, $3, nullptr);
  tab->push_front(*a);
  $$ = tab;}
|ID ":" type_id "," vardecs
{
  auto* a =  new ast::VarDec(@$, $1, $3, nullptr);
  $5->push_front(*a);
  $$ = $5;
}
//| %empty  { $$ = new ast::VarDecs(@$); }
;



type_id:
ID {$$ = new ast::NameTy(@$, $1);}
| "_namety" "(" INT ")" {$$ = metavar<ast::NameTy>(tp, $3);}
;

%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
   tp.error_ << misc::error::parse
             << l << " "
             << m << std::endl;
}
