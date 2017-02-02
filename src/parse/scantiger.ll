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

  // FIXME: Some code was deleted here.
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
\\n {tp.location_.lines(1); tp.location_.step();}
\\[abfrtv] { str += yytext;}
\\[0-3][0-7][0-7] {str += yytext;}
\\x[0-9a-fA-F][0-9a-fA-F] {str += yytext;}
"\\" { str += yytext;}
"\\\"" {str += yytext; }
"\"" {
    BEGIN(INITIAL);
    return TOKEN_VAL(STRING, str);
  }
\\. { tp.error_ << misc::error::scan
            << tp.location_
            << ": invalid identifier: `"
            << misc::escape(yytext) << "'\n";
  BEGIN(INITIAL);
}
<<EOF>> { tp.error_ << misc::error::scan
            << tp.location_
            << ": invalid identifier: `"
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
            << ": invalid identifier: `"
            << misc::escape(yytext) << "'\n";
  BEGIN(INITIAL);
   }
. { }
}

 /* The rules.  */
{NEWLINE}       { tp.location_.lines(1); tp.location_.step();}
{SPACE}         { tp.location_.step();}
"&"             { return TOKEN(AND); }
"array"         { return TOKEN(ARRAY);     }
":="            { return TOKEN(ASSIGN); }
"break"         { return TOKEN(BREAK);     }
"class"         { return TOKEN(CLASS);     }
":"             { return TOKEN(COLON);     }
","             { return TOKEN(COMMA);      }
"/"             { return TOKEN(DIVIDE); }
"do"            { return TOKEN(DO);        }
"."             { return TOKEN(DOT);       }
"else"          { return TOKEN(ELSE);      }
"end"           { return TOKEN(END);       }
"="             { return TOKEN(EQ); }
"extends"       { return TOKEN(EXTENDS);   }
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
"method"        { return TOKEN(METHOD);    }
"<>"            { return TOKEN(NE); }
"new"           { return TOKEN(NEW);       }
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
{int} {
    int val = 0;
    auto res = std::stol(yytext);
    if (res > INT_MAX)
      throw std::overflow_error(res + " is overfow max int");
    val = res;
    return TOKEN_VAL(INT, val);
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
