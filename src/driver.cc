#include "driver.hh"
#include "parser.hh"
#include "fwd.hh"
#include "scanpit.hh"

namespace parsepit
{
  Driver::Driver ()
    : scanner_ (new Scanner ()),
      parser_ (new Parser (*this)),
      error_ (0),
      location_ (new location ()),
      input_ (new std::string()),
      output_ (new std::string()),
      filter_flags_ (0)
  {
  }

  Driver::~Driver ()
  {
    delete parser_;
    delete scanner_;
    delete location_;
    delete input_;
    delete output_;
  }

  void
  Driver::reset ()
  {
    delete location_;
    location_ = new location ();

    error_ = 0;
  }

  void
  Driver::parse ()
  {
    scanner_->switch_streams (&std::cin, &std::cerr);

    parser_->parse ();

    //return result_;
  }

  void
  Driver::parse_file (std::string& path)
  {
    std::ifstream s (path.c_str (), std::ifstream::in);
    scanner_->switch_streams (&s, &std::cerr);

    parser_->parse ();

    s.close ();

    //return result_;
  }
}