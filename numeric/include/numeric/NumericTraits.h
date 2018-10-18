#include <string>

template <typename T>
struct NumericTraits;


template <>
struct NumericTraits<bool>
{
  static std::string name()
  {
    return "bool";
  }
};


template <>
struct NumericTraits<int>
{
  static std::string name()
  {
    return "int";
  }
};


template <>
struct NumericTraits<unsigned int>
{
  static std::string name()
  {
    return "unsigned int";
  }
};


template <>
struct NumericTraits<float>
{
  static std::string name()
  {
    return "float";
  }
};


template <>
struct NumericTraits<double>
{
  static std::string name()
  {
    return "double";
  }
};


#include "blaze/math/DynamicVector.h"

template <typename T>
struct NumericTraits<blaze::DynamicVector<T>>
{
  static std::string name()
  {
    return "DynamicVector_" + NumericTraits<T>::name();
  }
};


#include "blaze/math/StaticVector.h"
#include <sstream>


template <typename T, size_t N>
struct NumericTraits<blaze::StaticVector<T, N>>
{
  static std::string name()
  {
    std::ostringstream comp;
    comp << N;
    return "StaticVector" + comp.str() + "_" + NumericTraits<T>::name();
  }
};