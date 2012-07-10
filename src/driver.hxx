
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
  inline std::vector<std::string*>&
  Driver::filters_get () const
  {
      return filters_;
  }
}
