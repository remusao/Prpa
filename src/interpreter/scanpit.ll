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
%x SC_COMMENT SC_STRING

/* Abbreviations.  */

sep             [ \t\r]+
endofline       [\n\r|\r\n|\n|\r]+

integer         ([1-9]+[0-9]*)|"0"|([1-9]+[0-9_]*[0-9])
octal           "0"(([1-7]+[0-7]*)|"0"|([1-7]+[0-7_]*[0-7]))
hexa            "0x"(([0-9A-Fa-f]+)|([0-9A-Fa-f]+[0-9A-Fa-f_]*[0-9A-Fa-f]))
binary          "%"(([01]+)|[01][01_]*[01])
id              [a-zA-Z0-9]+
flag            [A-Z_]*

%%

 /* The rules.  */
%{
  STEP();
%}


<SC_STRING>
{
  "\""      {
              yy_pop_state ();
              yylval->str = growing;
              return token::STRING;
            }

  <<EOF>>   {
              std::cerr << driver.location_ << " Unterminated string" << std::endl;
              driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
              yy_pop_state ();
            }
[\a|\b|\f|\n|\r|\t|\v] growing->append(yytext);

  .         {
              growing->append(yytext);
            }

}


<SC_COMMENT>
{
  {endofline}   { yy_pop_state (); }

  <<EOF>>       { yy_pop_state (); }

  .             { STEP (); }
}


"\""          {
                yy_push_state (SC_STRING);
                growing = new std::string ();
              }


(?i:source)   {
                GET_STR ();
                return token::SOURCE;
              }

(?i:filter)   {
                GET_STR ();
                return token::FILTER;
              }

(?i:overlay)  {
                GET_STR ();
                return token::OVERLAY;
              }

(?i:mix)      {
                GET_STR ();
                return token::MIX;
              }

(?i:output)   {
                GET_STR();
                return token::OUTPUT;
              }


{binary}      {
                GET_INT();
                return token::INTEGER;
              }

","           return token::COMA;

"\#"           {yy_push_state (SC_COMMENT);}

"("           return token::LPAR;
")"           return token::RPAR;
"="           return token::ASSIGN;



{octal}       {
                GET_INT();
                return token::INTEGER;
              }

{integer}     {
                GET_INT();
                return token::INTEGER;
              }


{hexa}        {
                growing = new std::string (yytext + 1);
                yylval->ival = convert(*growing);
                delete growing;
                growing = 0;
                return token::INTEGER;
              }

{flag}        {
                GET_STR();
                return token::FLAGS;
              }


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
