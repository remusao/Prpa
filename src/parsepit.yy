%{     /* PARSER */

#include "parser.hh"
#include "scanpit.hh"

#define yylex driver.scanner_->yylex
%}

%code requires
{
#include "fwd.hh"
#include "driver.hh"
#include "location.hh"
#include "position.hh"
}

%require "2.4"
%language "C++"
%locations
%defines
%debug
%define namespace "parsepit"
%define parser_class_name "Parser"
%parse-param { Driver &driver }
%lex-param { Driver &driver }
%error-verbose
%expect 1

%union
{
  bool          ibool;
  std::string*  str;
  int           ival;
}

/* Arithmetic */
%token
  LPAR        "("
  RPAR        ")"


/* Treatment */
%token <str>
    SOURCE  "source"
    OUTPUT  "output"
    FILTER  "filter"
    OVERLAY "overlay"
    MIX     "mix"

/* Misc */
%token
  ASSIGN      "="
  COMA        ","
  TOK_EOF 0   "eof"

%token  <ival>
  INTEGER     "int"

%token  <str>
  ID          "id"
  FLAGS       "flag"
  COMMENT     "comment"
  STRING      "string"
  error

%start START

%destructor { delete $$; } <str>


%%

START:
    SCRIPT
  | "eof"       {}
;

SCRIPT:
      /* empty */
    | STATEMENT SCRIPT
;

STATEMENT:
        "source" "(" "id" ")"       { driver.input_ = $3; }
    |   "filter" "(" "id" ")"       { std::cout << *$3 << std::endl; driver.filters_.push_back($3); }
    |   "overlay" "(" "id" ")"      {}
    |   "mix" "(" "id" ")"          {}
    |   "output" "(" "id" ")"       { driver.output_ = $3; }
;


%%

namespace parsepit
{
  void
  Parser::error (const location&, const std::string& m)
  {
    std::cerr << *driver.location_ << ": " << m << std::endl;
    driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
  }
}
