#ifndef _BERNSTEIN_POLYNOMIALS_H_
#define _BERNSTEIN_POLYNOMIALS_H_

#include "blaze/math/DynamicVector.h"

namespace BP_detail
{

template <typename T>
struct Evaluate
{
  using Vec = blaze::DynamicVector<T>;

  static inline
  T call(T const &u, size_t const n, size_t const i)
  {
    Vec tmp(n + 1, 0.0);
    tmp[n - i] = T(1);
    T const u1 {T(1) - u};

    for (size_t k = 1; k != n+1; ++k)
      for (size_t j = n; j >= k; --j)
        tmp[j] = u1 * tmp[j] + u * tmp[j - 1];

    return tmp[n];
  }
};

}

template <typename T>
T bernsteinPoly(T const &u, size_t const n, size_t const i)
{
  return BP_detail::Evaluate<T>::call(u, n, i);
}

#endif