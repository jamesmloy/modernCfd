#ifndef _BEZIER_CURVE_H_
#define _BEZIER_CURVE_H_

#include "blaze/math/DynamicVector.h"
#include "blaze/math/StaticVector.h"

#include "utils/RemoveConstRef.h"

namespace BezierUtils
{
  template <typename T, size_t N>
  using StatVec = blaze::StaticVector<T, N>;

  template <typename T, size_t N>
  using DynVec = blaze::DynamicVector<StatVec<T, N>>;

  namespace detail
  {
    template <typename ...Args>
    struct EvaluatePoint {};

    template <typename T, size_t N>
    struct EvaluatePoint<StatVec<T, N>, DynVec<T, N>, T>
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


  template <typename Pts, typename T>
  auto evaluatePoint(Pts const &pts, T const &u)
  {
    using Cpt = Utils::RemoveConstRef<decltype(*pts.begin())>;
    return detail::EvaluatePoint<Cpt, Pts, T>::call(pts, u);
  }


  template <typename T, size_t N>
  StatVec<T, N-1> reduceDim(StatVec<T, N> const &pw)
  {
    return detail::ReduceDim<T, N>::call(pw);
  }
}


template <typename T, size_t Dim>
class BezierCurve
{
public:

  using CptRat = blaze::StaticVector<T, Dim>;
  using CptNonRat = blaze::StaticVector<T, Dim + 1>;

  template <typename Type>
  using DynVec = blaze::DynamicVector<Type>;

  explicit BezierCurve(DynVec<CptRat> const &cpts)
  {
    _cpts.resize(cpts.size());
    for (int i = 0; i != cpts.size(); ++i)
    {
      std::copy(begin(cpts[i]), end(cpts[i]), begin(_cpts[i]));
      _cpts[i][Dim] = 1;
    }
  }

  BezierCurve(DynVec<CptRat> const &cpts, DynVec<T> const &wts)
  {
    _cpts.resize(cpts.size());
    for (int i = 0; i != cpts.size(); ++i)
    {
      std::copy(begin(cpts[i]), end(cpts[i]), begin(_cpts[i]));
      _cpts[i][Dim] = wts[i];

      std::for_each(begin(_cpts[i]), end(_cpts[i]) - 1,
                    [&] (T &c) { c *= wts[i]; });
    }
  }

  CptRat operator()(T const &u) const
  {
    using namespace BezierUtils;
    return reduceDim(evaluatePoint(_cpts, u));
  }

  void setWeight(size_t const i, T const &w)
  {
    if (i >= _cpts.size())
      throw std::runtime_error("Index exceeds control point size");
    _cpts[i][Dim] = w;
  }

private:
  DynVec<CptNonRat> _cpts;
};

#endif