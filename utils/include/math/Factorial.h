#ifndef _FACTORIAL_H_
#define _FACTORIAL_H_

#include <type_traits>

namespace FacDetail
{

template <typename T, typename Enable = void>
struct Evaluate
{};


template <typename T>
struct Evaluate<T, typename std::enable_if<std::is_integral<T>::value>::type>
{
  static inline
  T call(T const t)
  {
    T ret{1};

    for (T i = t; i > 0; --i)
      ret *= i;

    return ret;
  }
};

}

namespace MathUtils
{

template <typename T>
T factorial(T const t)
{
  return FacDetail::Evaluate<T>::call(t);
}

}

#endif