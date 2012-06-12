
#ifndef SCANPIT_HH_
# define SCANPIT_HH_

# include "parser.hh"


# ifndef YY_DECL
#  define YY_DECL parsepit::Parser::token_type                         \
     parsepit::Scanner::yylex(parsepit::Parser::semantic_type* yylval, \
                              parsepit::Parser::location_type*,        \
                              parsepit::Driver& driver)
# endif


# ifndef __FLEX_LEXER_H
#  define yyFlexLexer parsepitFlexLexer
#  include <FlexLexer.h>
#  undef yyFlexLexer
# endif


namespace parsepit
{
  class Scanner : public parsepitFlexLexer
  {
    public:
      Scanner ();

      virtual ~Scanner ();

      virtual Parser::token_type yylex (Parser::semantic_type* yylval,
                                        Parser::location_type* l,
                                        Driver& driver);

      void set_debug (bool b);
  };
}

#endif // SCANPIT_HH_
