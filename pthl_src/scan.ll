%{ /* -*- C++ -*- */

/* Includes, prototypes, typedefs, etc. required */
#include <iostream>
#include <sstream>
#include "parse.hh"

/* Code for Bison/Flex Synchronization */
#define YY_DECL                                 \
  yy::parser::symbol_type yylex(/* OPT FIXME for locations */)

/* Useful typedef */
using token = yy::parser::token;

/* Useful macro */
#define TOKEN(type) \
  yy::parser::make_ ## type()

// Management of the location... OPT FIXME
// Action done at each token match
//# define YY_USER_ACTION

/* Management of the EOF automatically managed by the scanner and the parser */
#define yyterminate() return TOKEN(END_OF_FILE)
int count = 0;
%}

 /* Flex options */
%option noyywrap
%option	nounput

 /* Declaration of a new state : FIXME*/
%x COMMENT_STATE
%x STRING_STATE

 /* Regex Definition : FIXME */
ID              [A-Za-z][A-Za-z0-9_]*|_main
SPACE           [ \t]
LETTER          [a-zA-Z]
DIGIT           [0-9]
 /*OP              [\*|\/|+|-|<>|<=|>=|=|>|<|&|\|]*/
INTEGER         [0-9]+
COMMENT "/*"
STRING  \"
/* Rules */
%%


<STRING_STATE>
{
  \\[abfnrtv] { continue; }
  \\[0-3][0-7][0-7] {continue;}
  \\x[0-9a-fA-F][0-9a-fA-F] {continue;}
  "\\" { continue;}
  "\\\"" {continue; }
  "\"" { 
  BEGIN(INITIAL);
  return TOKEN(STRING);
  }
  \\. {  std::cerr << "scan error, unexpected ";
    std::cerr << yytext << std::endl;
    exit(2); }
  <<EOF>> {
    std::cerr << "scan error, unexpected ";
    std::cerr << yytext << std::endl;
    exit(2);
  }
  . { }
}


<COMMENT_STATE>
{
  "/*" count++;
  "*/" {count--;
    if (count == 0)
      BEGIN(INITIAL);
  }
  <<EOF>> {
    std::cerr << "scan error, unexpected ";
    std::cerr << yytext << std::endl;
    exit(2);
  }
  

}
 /* FIXME: Complete lexing rules */
<INITIAL>
{
  {SPACE}         { }

  "array"         { return TOKEN(ARRAY);     }
  "if"            { return TOKEN(IF);        }
  "then"          { return TOKEN(THEN);      }
  "else"          { return TOKEN(ELSE);      }
  "while"         { return TOKEN(WHILE);     }
  "for"           { return TOKEN(FOR);       }
  "to"            { return TOKEN(TO);        }
  "do"            { return TOKEN(DO);        }
  "let"           { return TOKEN(LET);       }
  "in"            { return TOKEN(IN);        }
  "end"           { return TOKEN(END);       }
  "of"            { return TOKEN(OF);        }
  "break"         { return TOKEN(BREAK);     }
  "nil"           { return TOKEN(NIL);       }
  "function"      { return TOKEN(FUNCTION);  }
  "var"           { return TOKEN(VAR);       }
  "type"          { return TOKEN(TYPE);      }
  "import"        { return TOKEN(IMPORT);    }
  "primitive"     { return TOKEN(PRIMITIVE); }

  "class"         { return TOKEN(CLASS);     }
  "extends"       { return TOKEN(EXTENDS);   }
  "method"        { return TOKEN(METHOD);    }
  "new"           { return TOKEN(NEW);       }

  ","             { return TOKEN(COMA);      }
  ":="            { return TOKEN(ASSIGN); }
  ":"             { return TOKEN(COLON);     }
  ";"             { return TOKEN(SEMICOLON); }
  "("             { return TOKEN(LBRACE);    }
  ")"             { return TOKEN(RBRACE);    }
  "["             { return TOKEN(LBRACKET);  }
  "]"             { return TOKEN(RBRACKET);  }
  "{"             { return TOKEN(LEMBRACE);  }
  "}"             { return TOKEN(REMBRACE);  }
  "."             { return TOKEN(DOT);       }
  "+" { return TOKEN(ADD); }
  "-" { return TOKEN(SUB); }
  "*" { return TOKEN(MUL); }
  "/" { return TOKEN(DIV); }
  "<=" { return TOKEN(INFE); }
  ">=" { return TOKEN(SUPE); }
  "=" { return TOKEN(EQUAL); }
  "<>" { return TOKEN(DIFF); }
  "<" { return TOKEN(INF); }
  ">" { return TOKEN(SUP); }
  "&" { return TOKEN(AND); }
  "|" { return TOKEN(OR); }
  "\"" {BEGIN(STRING_STATE);}

  {ID}            { return TOKEN(ID);        }
  {INTEGER}       { return TOKEN(INTEGER);   }
  "/*" { count++;
    BEGIN(COMMENT_STATE);}
  <<EOF>>         { yyterminate();    }
  .               {
    std::cerr << "scan error, unexpected ";
    std::cerr << yytext << std::endl;
    exit(2);
  }
}
%%
