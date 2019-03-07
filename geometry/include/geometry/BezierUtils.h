#ifndef _BEZIER_UTILS_H_
#define _BEZIER_UTILS_H_

#include "blaze/math/DynamicVector.h"
#include "blaze/math/StaticVector.h"

#include "utils/RemoveConstRef.h"

#include "math/Assign.h"

#include <utility>

namespace BezierUtils
{
  template <typename T, size_t N>
  using StatVec = blaze::StaticVector<T, N>;

  namespace detail
  {
    template <typename PtsIt, typename T>
    struct EvaluateCurvePoint
    {
      using Pts = Utils::RemoveConstRef<decltype(*std::declval<PtsIt>())>;
      using PtsArray = blaze::DynamicVector<Pts>;

      static inline
      Pts call(PtsIt const beg, PtsIt const fin, T const & u)
      {
        size_t const n = std::distance(beg, fin);
        PtsArray q {n, Pts{0}};
        {
          auto it = beg;
          auto outIt = q.begin();
          while (it != fin)
          {
            MathUtils::assign(*outIt, *it);
            ++it;
            ++outIt;
          }
        }

        {
          T const u1 {T(1) - u};
          auto const bq = begin(q);
          auto const eq = end(q);
          for (size_t k = 1; k != n; ++k)
            for (auto i = bq; i !=  (eq - k); ++i)
              *i = *i * u1 + *(i + 1) * u;
        }

        return q[0];
      }

    };
  }

  template <typename PtsIt, typename T>
  auto evaluateCurvePoint(PtsIt const beg, PtsIt const fin, T const &u)
  {
    return detail::EvaluateCurvePoint<PtsIt, T>::call(beg, fin, u);
  }


  template <typename Pts, typename T>
  auto evaluateCurvePoint(Pts const &pts, T const &u)
  {
    return evaluateCurvePoint(begin(pts), end(pts), u);
  }


  template <typename T, size_t N>
  StatVec<T, N-1> reduceDim(StatVec<T, N> const &pw)
  {
    StatVec<T, N - 1> p{0};
    T const oneOverLast = T(1) / pw[N-1];
    for (int i = 0; i < N-1; ++i)
      p[i] = pw[i] * oneOverLast;
    return p;
  }

  template <typename PtsIt,
            typename WtsIt,
            typename NonRatIt>
  void transformToHomog(PtsIt begP, PtsIt const endP,
                        WtsIt begW, NonRatIt begO)
  {
    using T = Utils::RemoveConstRef<decltype(*begW)>;
    while (begP != endP)
    {
      MathUtils::assign(*begO, *begP);
      *(begO->end() - 1) = *begW;

      std::for_each(begin(*begO), end(*begO) - 1,
                    [&begW] (T &c) { c *= *begW; });

      ++begP; ++begW; ++begO;
    }
  }
}

#endif