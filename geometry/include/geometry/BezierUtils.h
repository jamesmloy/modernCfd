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

  template <typename T, size_t N>
  using DynVec = blaze::DynamicVector<StatVec<T, N>>;

  namespace detail
  {
    template <typename ...Args>
    struct EvaluateCurvePoint {};

    template <typename T, size_t N>
    struct EvaluateCurvePoint<StatVec<T, N>, DynVec<T, N>, T>
    {
      static inline
      StatVec<T, N> call(DynVec<T, N> const &pts, T const &u)
      {
        // copy pts
        DynVec<T, N> q {pts};
        size_t const n = q.size();

        T const u1 {T(1) - u};
        for (size_t k = 1; k != n; ++k)
          for (size_t i = 0; i != (n - k); ++i)
            q[i] = u1 * q[i] + u * q[i + 1];

        return q[0];
      }
    };

    template <typename PtsIt, typename T>
    struct EvaluateCurvePoint<PtsIt, T>
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

        return EvaluateCurvePoint<Pts, PtsArray, T>::call(q, u);
      }

    };

    template <typename T, size_t N>
    struct ReduceDim
    {
      static inline
      StatVec<T, N - 1> call(StatVec<T, N> const &pw)
      {
        StatVec<T, N - 1> p{0};
        T const oneOverLast = T(1) / pw[N-1];
        for (int i = 0; i < N-1; ++i)
          p[i] = pw[i] * oneOverLast;
        return p;
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
    using Cpt = Utils::RemoveConstRef<decltype(*pts.begin())>;
    return detail::EvaluateCurvePoint<Cpt, Pts, T>::call(pts, u);
  }


  template <typename T, size_t N>
  StatVec<T, N-1> reduceDim(StatVec<T, N> const &pw)
  {
    return detail::ReduceDim<T, N>::call(pw);
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