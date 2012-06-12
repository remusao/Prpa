
#ifndef FWD_HH_
# define FWD_HH_

# include <iostream>


namespace parsepit
{
  // Forward declaration of the Driver class
  class Driver;

  inline void
  yyerror (const char* msg)
  {
    std::cerr << msg << std::endl;
  }
}


#endif /* !FWD_HH_ */
