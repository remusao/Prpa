
#include "fwd.hh"
#include "scanpit.hh"

namespace parsepit
{

  Scanner::Scanner ()
    : parsepitFlexLexer ()
  {
  }

  Scanner::~Scanner ()
  {
  }

  void Scanner::set_debug (bool b)
  {
    yy_flex_debug = b;
  }
}

#ifdef yylex
# undef yylex
#endif

int parsepitFlexLexer::yylex ()
{
  std::cerr << "call parsepitFlexLexer::yylex()!" << std::endl;
  return 0;
}
