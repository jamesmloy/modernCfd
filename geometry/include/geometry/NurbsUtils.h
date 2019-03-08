#ifndef _NURBS_UTILS_H_
#define _NURBS_UTILS_H_

#include "blaze/math/DynamicVector.h"

namespace NurbsUtils
{
  template<typename KnotIt, typename T>
  KnotIt findSpan(KnotIt b, KnotIt const e, size_t const p, T const& u)
  {
    if ((u < *b) || (b == e) || (u > *(e - 1)))
    {
      return e;
    }
    else
    {
      size_t const n = std::distance(b, e) - p - 2;

      if (u == *(b + n + 1))
        return b + n;

      return std::upper_bound(b + p, e, u) - 1;
    }
  }

  template<typename T, typename KnotIt>
  blaze::DynamicVector<T> basisFuns(
    size_t const i, size_t const p, T const& u, KnotIt const b, KnotIt const e)
  {
    blaze::DynamicVector<T> left(p + 1, T(0));
    blaze::DynamicVector<T> right(p + 1, T(0));
    blaze::DynamicVector<T> N(p + 1, T(0));
    N[0] = T(1);

    for (size_t j = 1; j != p + 1; ++j)
    {
      left[j]  = u - *(b + i - j + 1);
      right[j] = *(b + i + j) - u;
      T s(0);
      for (size_t r = 0; r < j; ++r)
      {
        T tmp = N[r] / (right[r + 1] + left[j - r]);
        N[r]  = s + right[r + 1] * tmp;
        s     = left[j - r] * tmp;
      }
      N[j] = s;
    }

    return N;
  }
}

#endif