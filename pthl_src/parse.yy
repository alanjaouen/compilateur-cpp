/*
** BISON DIRECTIVES
*/
%require "3.0.2"     // The version of bison should be superior or egal to 3.0.2
%skeleton "lalr1.cc" // The grammar is lalr1
%expect 0            // No shift/reduce
       // Put a specific message in case of parse error
%defines             // Generate header files which can be used by the scanner

// Add a prefix "TOK_" to the token names to avoid colisions.
%define api.token.prefix {TOK_}
// Request that symbols be handled as a whole in the scanner.
%define api.token.constructor
// The type for semantic values set to variant
%define api.value.type variant
%define parse.error verbose
%define parse.trace

/*
** CODE FOR FLEX/BISON SYNCHORNIZATION
*/
%code
{
#include <stdio.h>
#include <string>
#include <iostream>
  // Prototype of the synchronization function
  yy::parser::symbol_type yylex(/* OPT FIXME for locations */);
    extern FILE* yyin;
}


/*
** TOKENS, TYPES AND PRIORITIES
*/
// Tokens
/* FIXME: Complete tokens list */
%token EOL         "\n"

%token END_OF_FILE 0 "<EOF>" // Token EOF, automaticaly managed by the parser
%token ARRAY       "array"
%token IF          "if"
%token THEN        "then"
%token ELSE        "else"
%token WHILE       "while"
%token FOR         "for"
%token TO          "to"
%token DO          "do"
%token LET         "let"
%token IN          "in"
%token END         "end"
%token OF          "of"
%token BREAK       "break"
%token NIL         "nil"
%token FUNCTION    "function"
%token VAR         "var"
%token TYPE        "type"
%token IMPORT      "import"
%token PRIMITIVE   "primitive"

%token CLASS       "class"
%token EXTENDS     "extends"



%token METHOD      "method"
%token NEW         "new"
%token COMA        ","
%token COLON       ":"
%token SEMICOLON   ";"
%token LBRACE      "("
%token RBRACE      ")"
%token LBRACKET    "["
%token RBRACKET    "]"
%token LEMBRACE    "{"
%token REMBRACE    "}"

%token ASSIGN      ":="
%token ADD         "+"
%token SUB         "-"
%token MUL         "*"
%token DIV         "/"
%token INFE        "<="
%token SUPE        ">="
%token EQUAL       "="
%token DIFF        "<>"
%token INF         "<"
%token SUP         ">"
%token AND         "&"
%token OR          "|"


%token DOT         "."
%token ID
%token INTEGER "n"
%token STRING

%left "|"                        
%left "&"
%left "+" "-"                        
%left "*" "/"


%nonassoc ">=" "<=" "=" "<>" "<" ">"
%nonassoc THEN DO OF 
%nonassoc  ELSE
%nonassoc ASSIGN                                         
//                      %nonassoc  ELSE                        
                        // Priorities
 /* FIXME: Define priorities */

// Entry point
%start program


/*
** RULES
*/
%%

program: exp
| decs
;
exp: "nil"
| INTEGER
| STRING
| ID "[" exp "]" "of" exp
| ID "{" array "}"
                
| "new" ID
                
| lvalue

|        ID "(" function ")"

|        lvalue_dot "(" function ")"
|       "-" exp
|       op_rule
|       "(" exps ")"
|       lvalue ":=" exp

|       "if" exp "then" exp "else" exp
|       "if" exp "then" exp
|       "while" exp "do" exp
|       "for" ID ":=" exp "to" exp "do" exp
|       "break"
|       "let" decs "in" exps  "end"
                
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

decs: dec decs
    |       %empty
    ;
dec: "type" ID "=" ty
        |       "class" ID dec_class_def "{" classfields "}"
        |       vardec
        |       "function" ID "(" tyfields ")" type_dec "="exp 
        |       "primitive" ID "(" tyfields ")" type_dec
        |       "import" STRING
                        ;
type_dec:        ":" ID
        |       %empty
        ;
dec_class_def: "extends" ID
        |       %empty
                ;
vardec: "var" ID type_dec ":=" exp
                ;
classfields: vardec
        |       "method" ID "(" tyfields ")" type_dec "=" exp
                ;
ty: ID
        | "{" tyfields "}"
        | "array" "of" ID
        |       "class" dec_class_def "{" classfields "}"
                ;
tyfields: ID ":" ID tyfilelds_rec
        |       %empty
                ;
tyfilelds_rec: "," ID ":" ID tyfilelds_rec
        |       %empty
                ;
op_rule:        exp op
        ;
op:             "+" exp
                |"-" exp
                |"*" exp
                |"/" exp
                |"=" exp
                |"<>" exp
                |">" exp
                |"<" exp
                | ">=" exp
                |"<=" exp
                |"&" exp
                |"|" exp
;                
      /* FIXME: Add grammar rules */
%%
/*
** FUNCTIONS
*/

// Parse error function, automaticaly call by the parser in case of parse error
void
yy::parser::error(const std::string& msg)
{
  std::cerr << msg << std::endl;
  exit(3);
}

// Main function
int main(int argc, char** argv)
{
  // The value of the last expression.
    if (argc == 2)
    {
        yyin = fopen(argv[1], "r");
    }
    yy::parser parser;

    auto lex = getenv("SCAN");
    // Scanner debug traces.
    if (lex == NULL)
    {
        extern int yy_flex_debug;
        yy_flex_debug = 1;
    }

    auto parse = getenv("PARSER");
    // Parser debug traces.
    if (parse != NULL)
        parser.set_debug_level(1);

    // 0 if success, 1 otherwise.
    auto status = parser.parse();
//    std::cerr << "Result: " << result << '\n';
    if (argc == 2)
    {
        fclose(yyin);
    }
    return status;
}
