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


 // FIXME: Some code was deleted here (Other directives: %skeleton "lalr1.cc" %expect 0 etc).
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
# include <ast/type-dec.hh>
# include <ast/var-dec.hh>
# include <ast/any-decs.hh>
# include <ast/decs-list.hh>
}

  // FIXME: Some code was deleted here (Printers and destructors).


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
%left "|"
%left "&"
%left "+" "-"
%left "*" "/"


%nonassoc ">=" "<=" "=" "<>" "<" ">"
%nonassoc THEN DO OF
%nonassoc  ELSE
%nonassoc ASSIGN
  // FIXME: Some code was deleted here (More %types).


%type <ast::Exp*> exp
%type <ast::DecsList*> decs
%type <ast::NameTy*> type_id
%type <ast::exps_type*> exps
%type <ast::Var*> lvalue
%type <ast::Decs*> dec
%type <ast::Ty*> ty
%type <ast::NameTy*> type_dec
%type <ast::VarDecs*> vardec
%type <ast::fieldinits_type*> array
%type <ast::exps_type*> function
%type <ast::VarDecs*> vardecs
%type <ast::fields_type*> tyfields
%type <ast::SubscriptVar*> lvalue_bracket
%type <ast::FieldVar*> lvalue_dot
%type <ast::DecsList*> classfields
%destructor {delete $$;} <ast::Exp*> <ast::DecsList*> <ast::NameTy*> <ast::exps_type*> <ast::Var*> <ast::Decs*> <ast::Ty*>  <ast::fieldinits_type*> <ast::VarDecs*> <ast::fields_type*>

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
| "new" type_id //{ $$ = new ast::ClassTy(@$, $2, nullptr);}
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
| exp "&" exp  {
  $$ = tp.parse(::parse::Tweast() << "if" << $1 << "then" << $3 << "else" << 0);
  }
| exp "|" exp { $$ = tp.parse(::parse::Tweast() << "if" << $1 << "then" << 1 << "else" << $3);}
| "(" exps ")" {$$ = new ast::SeqExp(@$, $2);}
| lvalue ":=" exp {$$ = new ast::AssignExp(@$, $1, $3);}

| "if" exp "then" exp "else" exp {$$ = new ast::IfExp(@$, $2, $4, $6); }
| "if" exp "then" exp {$$ = new ast::IfExp(@$, $2, $4, nullptr); }
| "while" exp "do" exp {$$ = new ast::WhileExp(@$, $2, $4);}
| "for" ID ":=" exp "to" exp "do" exp { $$ = new ast::ForExp
      (@$, new ast::VarDec(@2, $2, nullptr, $4), $6, $8);}
| "break" { $$ = new ast::BreakExp(@$);}
| "let" decs "in" exps  "end" {$$ = new ast::LetExp(@$, $2, new ast::SeqExp(@$,$4)); }

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
;

exps: exp {auto* tab  = new ast::exps_type(); tab->insert(tab->begin(), $1); $$ = tab;}
| exp ";" exps {$3->insert($3->begin(), $1); $$ = $3;}
| %empty   { $$ = new ast::exps_type(); }
;

  // FIXME: Some code was deleted here (More rules).

/*---------------.
| Declarations.  |
`---------------*/

%token DECS "_decs";
decs:
%empty   { $$ = new ast::DecsList(@$); }
| dec decs {$2->push_front($1); $$ = $2;}
| "_decs" "(" INT ")" decs {$$ = metavar<ast::DecsList>(tp, $3);}
| "import" STRING decs {auto a  = tp.parse_import($2, @2);
  $3->splice_front(*a);
  $$ = $3;
  }
;
dec:
"type" ID "=" ty {

  auto* a = new ast::TypeDecs(@$);
  auto* b = new ast::TypeDec(@$, $2, $4);
  a->push_front(*b);
  $$ = a;
}
| "class" ID dec_class_def "{" classfields "}"
| vardec {$$ = $1;}
| "function" ID "(" vardecs ")" type_dec "=" exp {
  auto* tab = new ast::FunctionDecs(@$);
  auto* b = new ast::FunctionDec(@$, $2, $4, $6, $8);
  tab->push_front(*b);
  $$ = tab;
  }
| "primitive" ID "(" vardecs ")" type_dec
{
  auto* tab = new ast::FunctionDecs(@$);
  auto* prim = new ast::FunctionDec(@$, $2, $4, $6, nullptr);
  tab->push_front(*prim);
  $$ = tab;
}
;
type_dec:
":" type_id { $$ = $2; }
| %empty    { $$ = nullptr; }
;
dec_class_def:
"extends" type_id
| %empty //{ $$ = nullptr; }
;
vardec:
"var" ID type_dec ":=" exp { auto* a = new ast::VarDecs(@$);
  auto* b = new ast::VarDec(@$, $2, $3, $5);
  a->push_front(*b);
  $$ = a;
}
;
classfields:
classfields vardec //{$1->emplace_back($2);}
| classfields "method" ID "(" vardecs ")" type_dec "=" exp
  //{}
| %empty//{ $$ = new ast::DecsList(@$); }
;
ty:
type_id {$$ = $1;}
| "{" tyfields "}" {$$ = new ast::RecordTy(@$, $2);}
| "array" "of" type_id {$$ = $3;}
| "class" dec_class_def "{" classfields "}"
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
| %empty  { $$ = new ast::fields_type(); }
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
| %empty  { $$ = new ast::VarDecs(@$); }
;


type_id:
ID {$$ = new ast::NameTy(@$, $1);}
| "_namety" "(" INT ")" {$$ = metavar<ast::NameTy>(tp, $3);}
;

  // FIXME: Some code was deleted here (More rules).

%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
   tp.error_ << misc::error::parse
             << l << " "
             << m << std::endl;
}
