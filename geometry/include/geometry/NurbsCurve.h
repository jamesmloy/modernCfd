#ifndef _NURBS_CURVE_H_
#define _NURBS_CURVE_H_

#include "blaze/math/DynamicVector.h"
#include "blaze/math/StaticVector.h"

#include "BezierUtils.h"
#include "NurbsUtils.h"

template<typename T, size_t Dim>
class NurbsCurve
{
public:
  using CptRat    = blaze::StaticVector<T, Dim>;
  using CptNonRat = blaze::StaticVector<T, Dim + 1>;

  template<typename Type>
  using DynVec = blaze::DynamicVector<Type>;

  NurbsCurve(DynVec<CptRat> const &cpts,
             DynVec<T> const &wts,
             DynVec<T> const &&knots,
             size_t const p)
    : _cpts(cpts.size(), CptNonRat{ 0 })
    , _knots(knots)
    , _p(p)
  {
    using BezierUtils::transformToHomog;
    transformToHomog(begin(cpts), end(cpts), begin(wts), begin(_cpts));
  }

  NurbsCurve(DynVec<CptRat> const &cpts)
    : NurbsCurve(cpts,
                 DynVec<T>(cpts.size(), T(1)),
                 defaultKnots(cpts.size()),
                 cpts.size() - 1)
  {
  }

  CptRat operator()(T const &u) const
  {
    using namespace NurbsUtils;
    using BezierUtils::reduceDim;
    auto const bK  = begin(_knots);
    auto const eK  = end(_knots);
    auto const kIt = findSpan(bK, eK, _p, u);

    if (kIt == eK)
      throw std::runtime_error("Could not find knot span for u");

    size_t const span = std::distance(bK, kIt);
    auto const bf = basisFuns(span, _p, u, bK, eK);

    CptNonRat pw(0);

    for (size_t i = 0; i < _p + 1; ++i)
      pw += bf[i] * _cpts[span - _p + i];

    return reduceDim(pw);
  }

private:
  DynVec<T> defaultKnots(size_t const numCpts) const
  {
    size_t const m = 2 * (numCpts - 1) + 1;
    DynVec<T> knots(m + 1, T(0));
    std::fill(begin(knots) + (m + 1)/ 2, end(knots), T(1));
    return knots;
  }

  DynVec<CptNonRat> _cpts;
  DynVec<T> _knots;
  size_t _p;
};

#endif