#include "tools.hh"


int
convert (std::string& num)
{
  switch (num[0])
  {
    case 'x':
      return hexa_to_int (num);
    case '0':
      return oct_to_int (num);
    case '%':
      return bin_to_int (num);
  default:
    return string_to_int (num);
  }
}


int
string_to_int (std::string& num)
{
  int res = 0;

  for (unsigned i = 0; i < num.size (); i++)
  {
    if (num[i] == '_')
      continue;
    res *= 10;
    res += num[i] - '0';
  }

  return res;
}


int
hexa_to_int (std::string& num)
{
  int res = 0;
  int pow = 1;
  short tmp;

  for (unsigned i = num.size () - 1; i > 0 ; i--)
  {
    if (num[i] == '_')
      continue;
    if (num[i] >= 'A' && num[i] <= 'F')
      tmp = 55;
    else if (num[i] >= 'a' && num[i] <= 'f')
      tmp = 87;
    else
      tmp = 48;

    res += (num[i] - tmp) * pow;
    pow *= 16;
  }

  return res;
}


int
oct_to_int (std::string& num)
{
  int res = 0;
  int pow = 1;

  for (unsigned i = num.size () - 1; i > 0; i--)
  {
    if (num[i] == '_')
      continue;
    res += (num[i] - '0') * pow;
    pow *= 8;
  }

  return res;
}


int
bin_to_int (std::string& num)
{
  int res = 0;
  int pow = 1;

  for (unsigned i = num.size () - 1; i > 0; i--)
  {
    if (num[i] == '_')
      continue;
    res += (num[i] - '0') * pow;
    pow *= 2;
  }

  return res;
}
