
#ifndef DRIVER_HH_
# define DRIVER_HH_

# include <string>
# include <iostream>
# include <fstream>
# include <list>
# include <vector>
# include "tbb/pipeline.h"

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

      std::string* input_get () const;
      std::string* output_get () const;
      std::vector<std::string*> filters_get () const;

    private:
      Scanner*      scanner_;
      Parser*       parser_;
      int           error_;
      location*     location_;
      int           filter_flags_;

      //We want to store some informations from the parsing:
      std::string* output_;
      std::string* input_;
      std::vector<std::string*> filters_;

      /// Allows Parser and Scanner to access private attributes
      /// of the Driver class
      friend class  Parser;
      friend class  Scanner;
  };
}

# include "driver.hxx"

#endif /* !DRIVER_HH_ */

