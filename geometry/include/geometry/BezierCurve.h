#ifndef _BEZIER_CURVE_H_
#define _BEZIER_CURVE_H_

#include "BezierUtils.h"

#include "blaze/math/DynamicVector.h"
#include "blaze/math/StaticVector.h"

template<typename T, size_t Dim>
class BezierCurve
{
public:
  using CptRat    = blaze::StaticVector<T, Dim>;
  using CptNonRat = blaze::StaticVector<T, Dim + 1>;

  template<typename Type>
  using DynVec = blaze::DynamicVector<Type>;

  BezierCurve(DynVec<CptRat> const &cpts, DynVec<T> const &wts)
    : _cpts(cpts.size(), CptNonRat{ 0 })
  {
    using BezierUtils::transformToHomog;
    transformToHomog(begin(cpts), end(cpts), begin(wts), begin(_cpts));
  }

  explicit BezierCurve(DynVec<CptRat> const &cpts)
    : BezierCurve(cpts, DynVec<T>(cpts.size(), T(1)))
  {
  }

  CptRat operator()(T const &u) const
  {
    using namespace BezierUtils;
    return reduceDim(evaluateCurvePoint(_cpts, u));
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