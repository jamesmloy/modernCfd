#include <string>

template <typename T>
struct NumericTraits;


template <>
struct NumericTraits<int>
{
  static std::string tag()
  {
    return "int";
  }
};


template <>
struct NumericTraits<float>
{
  static std::string tag()
  {
    return "float";
  }
};


template <>
struct NumericTraits<double>
{
  static std::string tag()
  {
    return "double";
  }
};