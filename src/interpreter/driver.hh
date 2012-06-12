
#ifndef DRIVER_HH_
# define DRIVER_HH_

# include <string>
# include <iostream>
# include <fstream>

namespace parsepit
{
  /// Forward declarations of classes
  class Parser;
  class Scanner;
  class location;

  class Driver
  {
    public:
      Driver ();
      ~Driver ();

      void parse ();
      void parse_file (std::string& path);

      void reset ();
      int error_get () const;

    private:
      Scanner*      scanner_;
      Parser*       parser_;
      int           error_;
      location*     location_;

      /// Allows Parser and Scanner to access private attributes
      /// of the Driver class
      friend class  Parser;
      friend class  Scanner;
  };
}

# include "driver.hxx"

#endif /* !DRIVER_HH_ */

