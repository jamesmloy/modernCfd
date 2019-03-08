#ifndef _BEZIER_SURFACE_H_
#define _BEZIER_SURFACE_H_

#include "blaze/math/DynamicMatrix.h"
#include "blaze/math/DynamicVector.h"
#include "blaze/math/Row.h"
#include "blaze/math/StaticVector.h"

#include "BezierUtils.h"

#include "math/Assign.h"

template<typename T, size_t Dim>
class BezierSurface
{
public:
  template<typename Type, size_t N>
  using StatVec = blaze::StaticVector<Type, N>;

  using CptRat    = StatVec<T, Dim>;
  using CptNonRat = StatVec<T, Dim + 1>;

  template<typename Type>
  using DynVec = blaze::DynamicVector<Type>;

  template<typename Type>
  using DynMat = blaze::DynamicMatrix<Type>;

  BezierSurface(DynMat<CptRat> const &cpts, DynMat<T> const &wts)
    : _cpts(cpts.rows(), cpts.columns(), CptNonRat{ 0 })
  {
    using BezierUtils::transformToHomog;
    for (int i = 0; i != cpts.rows(); ++i)
    {
      transformToHomog(
        cpts.begin(i), cpts.end(i), wts.begin(i), _cpts.begin(i));
    }
  }

  explicit BezierSurface(DynMat<CptRat> const &cpts)
    : BezierSurface(cpts, DynMat<T>(cpts.rows(), cpts.columns(), T(1)))
  {
  }

  CptRat operator()(T const &u, T const &v) const
  {
    using namespace BezierUtils;
    DynVec<CptNonRat> q{ _cpts.rows(), CptNonRat{ 0 } };

    for (int i = 0; i != _cpts.rows(); ++i)
      q[i] = evaluateCurvePoint(blaze::row(_cpts, i), u);

    return reduceDim(evaluateCurvePoint(q, v));
  }

private:
  DynMat<CptNonRat> _cpts;
};

#endif