                                                                // -*- C++ -*-
%require "3.0"
%language "C++"
// Set the namespace name to `parse', instead of `yy'.
%name-prefix "parse"
%define api.value.type variant
%define api.token.constructor
%skeleton "lalr1.cc" // The grammar is lalr1
%expect 0            // No shift/reduce
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

%left "|"
%left "&"
%left "+" "-"
%left "*" "/"


%nonassoc ">=" "<=" "=" "<>" "<" ">"
%nonassoc THEN DO OF
%nonassoc  ELSE
%nonassoc ASSIGN

%start program

%%
program:
  /* Parsing a source program.  */
  exp   
| /* Parsing an imported file.  */
  decs  
;

exp:
INT
|  "nil"
| STRING
| ID "[" exp "]" "of" exp
| ID "{" array "}"
| "new" ID
| lvalue
| ID "(" function ")"

| lvalue_dot "(" function ")"
| "-" exp
| op_rule
| "(" exps ")"
| lvalue ":=" exp

| "if" exp "then" exp "else" exp
| "if" exp "then" exp
| "while" exp "do" exp
| "for" ID ":=" exp "to" exp "do" exp
| "break"
| "let" decs "in" exps  "end"
;

array: ID "=" exp arrayrec
| %empty
;
arrayrec: "," ID "=" exp arrayrec
| %empty
;
function: exp function_param
| %empty
;
function_param: %empty
|"," exp function_param
;

lvalue:
       ID
|       lvalue_dot
|       lvalue_bracket
;

lvalue_dot:
       lvalue_dot "." ID
|       lvalue_bracket "." ID
|       ID "." ID
;

lvalue_bracket:
       lvalue_dot "[" exp "]"
|       lvalue_bracket "[" exp "]"
|       ID "[" exp "]"
;

exps: exp exps_rec
| %empty
;

exps_rec: ";" exps
|       %empty
;


/*---------------.
| Declarations.  |
`---------------*/

%token DECS "_decs";
decs:
%empty
| dec decs
;
dec:
"type" ID "=" ty
| "class" ID dec_class_def "{" classfields "}"
| vardec
| "function" ID "(" tyfields ")" type_dec "="exp
| "primitive" ID "(" tyfields ")" type_dec
| "import" STRING
;
type_dec:
":" ID
| %empty
;
dec_class_def:
"extends" ID
| %empty
;
vardec:
"var" ID type_dec ":=" exp
;
classfields:
vardec
| "method" ID "(" tyfields ")" type_dec "=" exp
;
ty:
ID
| "{" tyfields "}"
| "array" "of" ID
| "class" dec_class_def "{" classfields "}"
;
tyfields:
ID ":" ID tyfilelds_rec
| %empty
;
tyfilelds_rec:
"," ID ":" ID tyfilelds_rec
| %empty
;
op_rule:
exp op
;
op:
"+" exp
| "-" exp
| "*" exp
| "/" exp
| "=" exp
| "<>" exp
| ">" exp
| "<" exp
| ">=" exp
| "<=" exp
| "&" exp
| "|" exp
;


%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
   tp.error_ << misc::error::parse
             << l
             << m << "\n";
}
