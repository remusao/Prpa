%{                                                            /* -*- C++ -*- */

#include <stdlib.h>
#include "fwd.hh"
#include "parser.hh"
#include "scanpit.hh"
#include "driver.hh"
#include "tools.hh"

std::string* growing = 0;

/*  Defines some macros to update locations */


#define STEP()                                      \
  do {                                              \
    driver.location_->step ();                      \
  } while (0)

#define COL(Col)				    \
  driver.location_->columns (Col)

#define LINE(Line)				    \
  do{						    \
    driver.location_->lines (Line);		    \
 } while (0)

#define YY_USER_ACTION				    \
  COL(yyleng);

/* Macros to store values of the tokens */

#define GET_STR()                                   \
        do {                                        \
          yylval->str = new std::string(yytext);    \
        } while (0)


#define GET_INT()                                   \
        do {                                        \
          growing = new std::string (yytext);       \
          yylval->ival = convert(*growing);         \
          delete growing;                           \
          growing = 0;                              \
        } while (0)

typedef parsepit::Parser::token token;
typedef parsepit::Parser::token_type token_type;

#define yyterminate() return token::TOK_EOF

%}

%option debug
%option c++
%option noyywrap
%option never-interactive
%option yylineno
%option nounput
%option batch
%option prefix="parsepit"

%option stack
%x SC_COMMENT SC_C_COMMENT

/* Abbreviations.  */

sep             [ \t\r]+
endofline       [\n\r|\r\n|\n|\r]+

id              [a-zA-Z0-9_.]+

%%

 /* The rules.  */
%{
  STEP();
%}


<SC_COMMENT>
{
  {endofline}   { yy_pop_state (); }

  <<EOF>>       { yy_pop_state (); }

  .             { STEP (); }
}

<SC_C_COMMENT>
{
  "*/"          {yy_pop_state ();}

  <<EOF>>       {yy_pop_state ();}

  .             { STEP(); }
}

"/*"            {yy_push_state (SC_C_COMMENT);}

"\#"           {yy_push_state (SC_COMMENT);}


(?i:source)     return token::SOURCE;

(?i:filter)     return token::FILTER;

(?i:overlay)    return token::OVERLAY;

(?i:mix)        return token::MIX;

(?i:output)     return token::OUTPUT;


"("             return token::LPAR;
")"             return token::RPAR;


{id}          {
                GET_STR();
                return token::ID;
              }

{sep}         {STEP();}

{endofline}   {LINE(1);}

.             {
                std::cerr << *driver.location_ << " Unexpected token : "
                                              << *yytext << std::endl;
                driver.error_ = (driver.error_ == 127 ? 127
                                : driver.error_ + 1);
                STEP ();
              }

%%
