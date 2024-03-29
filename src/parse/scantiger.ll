                                                            /* -*- C++ -*- */
%option c++
%option nounput
%option debug
%option batch

%{

# include <climits>

# include <regex>
# include <string>
# include <cerrno>
# include <stdexcept>
# include <boost/lexical_cast.hpp>

# include <misc/contract.hh>
# include <misc/symbol.hh>
  // Using misc::escape is very useful to quote non printable characters.
  // For instance
  //
  //    std::cerr << misc::escape('\n') << std::endl;
  //
  // reports about `\n' instead of an actual new-line character.
# include <misc/escape.hh>
# include <parse/tiger-parser.hh>
# include <parse/parsetiger.hh>

  // FIXED by forest_b.
  std::string str = "";
  int count  = 0;

 // Convenient shortcuts.
#define TOKEN_VAL(Type, Value)                  \
  parser::make_ ## Type(Value, tp.location_)

#define TOKEN(Type)                             \
  parser::make_ ## Type(tp.location_)

#define YY_USER_ACTION tp.location_.columns(yyleng);

 // Flex uses `0' for end of file.  0 is not a token_type.
#define yyterminate() return TOKEN(EOF)

# define CHECK_EXTENSION()                              \
  do {                                                  \
    if (!tp.enable_extensions_p_)                       \
      tp.error_ << misc::error::scan                    \
                << tp.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(yytext) << "'\n";       \
  } while (false)

# define CHECK_OBJECT_EXTENSION()                              \
  do {                                                  \
    if (!tp.enable_object_extensions_p_)                       \
      tp.error_ << misc::error::scan                    \
                << tp.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(yytext) << "'\n";       \
  } while (false)


YY_FLEX_NAMESPACE_BEGIN
%}

%x SC_COMMENT SC_STRING

/* Abbreviations.  */
int             [0-9]+
ID              [A-Za-z][A-Za-z0-9_]*|_main
SPACE           [ \t]
NEWLINE         [\n]|[\n\r]|[\r\n]
%%
%{


  //FIXME: Some code was deleted here (Local variables).

  // Each time yylex is called.
  tp.location_.step();
%}

<SC_STRING>
{
\\n {tp.location_.lines(1); tp.location_.step(); str += "\n";}
\\a { str += '\a' ;}
\\b { str += '\b';}
\\f { str += '\f';}
\\r { str += '\r';}
\\t { str += '\t';}
\\v { str += '\v';}
\\[0-3][0-7][0-7] {str += strtol(yytext + 1, 0, 8);}
\\x[0-9a-fA-F][0-9a-fA-F] {str += strtol(yytext + 2, 0, 16);}
"\\" { str += '\\';}
"\\\"" {str += '\"'; }
"\"" {
    BEGIN(INITIAL);
    return TOKEN_VAL(STRING, str);
  }
\\. { tp.error_ << misc::error::scan
            << tp.location_
            << ": invalid identifier: '"
            << misc::escape(yytext) << "'\n";
  BEGIN(INITIAL);
}
<<EOF>> { tp.error_ << misc::error::scan
            << tp.location_
            << ": invalid identifier: '"
            << misc::escape(yytext) << "'\n";
  BEGIN(INITIAL);
  }
. { str += yytext;}
}


<SC_COMMENT>
{
"/*" {count++;}
"*/" {
  count--;
  if (count == 0)
    BEGIN(INITIAL);
  }
\\n {tp.location_.lines(1); tp.location_.step();}
<<EOF>> { tp.error_ << misc::error::scan
            << tp.location_
            << ": invalid identifier: '"
            << misc::escape(yytext) << "'\n";
  BEGIN(INITIAL);
   }
{NEWLINE}       { tp.location_.lines(1); tp.location_.step();}
   
. { }
}

 /* The rules.  */
{NEWLINE}       { tp.location_.lines(1); tp.location_.step();}
{SPACE}         { tp.location_.step();}
"&"             { return TOKEN(AND); }
"array"         { return TOKEN(ARRAY);     }
":="            { return TOKEN(ASSIGN); }
"break"         { return TOKEN(BREAK);     }
"class"         { CHECK_OBJECT_EXTENSION(); return TOKEN(CLASS);     }
":"             { return TOKEN(COLON);     }
","             { return TOKEN(COMMA);      }
"/"             { return TOKEN(DIVIDE); }
"do"            { return TOKEN(DO);        }
"."             { return TOKEN(DOT);       }
"else"          { return TOKEN(ELSE);      }
"end"           { return TOKEN(END);       }
"="             { return TOKEN(EQ); }
"extends"       { CHECK_OBJECT_EXTENSION(); return TOKEN(EXTENDS);   }
"for"           { return TOKEN(FOR);       }
"function"      { return TOKEN(FUNCTION);  }
">="            { return TOKEN(GE); }
">"             { return TOKEN(GT); }
"if"            { return TOKEN(IF);        }
"import"        { return TOKEN(IMPORT);    }
"in"            { return TOKEN(IN);        }
"{"             { return TOKEN(LBRACE);    }
"["             { return TOKEN(LBRACK);    }
"<="            { return TOKEN(LE); }
"let"           { return TOKEN(LET);       }
"("             { return TOKEN(LPAREN);    }
"<"             { return TOKEN(LT); }
"-"             { return TOKEN(MINUS); }
"method"        { CHECK_OBJECT_EXTENSION(); return TOKEN(METHOD);    }
"<>"            { return TOKEN(NE); }
"new"           { CHECK_OBJECT_EXTENSION(); return TOKEN(NEW);       }
"nil"           { return TOKEN(NIL);       }
"of"            { return TOKEN(OF);        }
"|"             { return TOKEN(OR); }
"+"             { return TOKEN(PLUS); }
"primitive"     { return TOKEN(PRIMITIVE); }
"}"             { return TOKEN(RBRACE);    }
"]"             { return TOKEN(RBRACK);    }
")"             { return TOKEN(RPAREN);    }
";"             { return TOKEN(SEMI); }
"then"          { return TOKEN(THEN);      }
"*"             { return TOKEN(TIMES); }
"to"            { return TOKEN(TO);        }
"type"          { return TOKEN(TYPE);      }
"var"           { return TOKEN(VAR);       }
"while"         { return TOKEN(WHILE);     }
"\""            { str = ""; BEGIN(SC_STRING);}
"_cast"         { CHECK_EXTENSION(); return TOKEN(CAST); }
"_decs"         { CHECK_EXTENSION(); return TOKEN(DECS);}
"_exp"          { CHECK_EXTENSION(); return TOKEN(EXP);}
"_lvalue"       { CHECK_EXTENSION(); return TOKEN(LVALUE);}
"_namety"       { CHECK_EXTENSION(); return TOKEN(NAMETY);}

{int} {
  int res = 0;
  try{
    res = std::stol(yytext);
    }
    // if (res > INT_MAX)
    catch (...)
    {
      tp.error_ << misc::error::scan
                << tp.location_ << "overflowed int: " << yytext << std::endl;
    }
    return TOKEN_VAL(INT, res);
}
{ID}            {
  misc::symbol identifier = misc::symbol(yytext);
  return TOKEN_VAL(ID, identifier); }
"/*" { count++;
    BEGIN(SC_COMMENT);
}
<<EOF>>         { yyterminate();    }

. {
   tp.error_ << misc::error::scan
            << tp.location_
            << ": invalid identifier: `"
            << misc::escape(yytext) << "'\n";
  }
%%

// Do not use %option noyywrap, because then flex generates the same
// definition of yywrap, but outside the namespaces, so it defines it
// for ::yyFlexLexer instead of ::parse::yyFlexLexer.
int yyFlexLexer::yywrap() { return 1; }

void
yyFlexLexer::scan_open_(std::istream& f)
{
  yypush_buffer_state(YY_CURRENT_BUFFER);
  yy_switch_to_buffer(yy_create_buffer(&f, YY_BUF_SIZE));
}

void
yyFlexLexer::scan_close_()
{
  yypop_buffer_state();
}

YY_FLEX_NAMESPACE_END
