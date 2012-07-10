
namespace parsepit
{
  inline int
  Driver::error_get () const
  {
    return error_;
  }
  inline std::string*
  Driver::input_get () const
  {
    return input_;
  }
  inline std::string*
  Driver::output_get () const
  {
    return output_;
  }
}
