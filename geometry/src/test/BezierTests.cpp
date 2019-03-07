#include "gtest/gtest.h"

#include "geometry/BernsteinPolynomials.h"
#include "geometry/BezierCurve.h"
#include "geometry/BezierSurface.h"

#include <vector>

namespace
{
  template <typename T, size_t N>
  void endPtsTest()
  {
    {
      T const b = bernsteinPoly<T>(1, N, N);
      EXPECT_EQ(b, 1.0);
    }

    {
      T const b = bernsteinPoly<T>(0, N, 0);
      EXPECT_EQ(b, 1.0);
    }
  }

  TEST(UNIT_TEST, BernsteinEndPts)
  {
    endPtsTest<double, 1>();
    endPtsTest<double, 2>();
    endPtsTest<double, 3>();
    endPtsTest<double, 4>();

    endPtsTest<float, 1>();
    endPtsTest<float, 2>();
    endPtsTest<float, 3>();
    endPtsTest<float, 4>();
  }


  template <typename T, size_t N>
  void partitionTest()
  {
    T s{0};
    for (int i = 0; i != N + 1; ++i)
      s += bernsteinPoly<T>(0.5, N, i);

    EXPECT_EQ(s, 1.0);
  }

  TEST(UNIT_TEST, BernsteinPartition)
  {
    partitionTest<double, 1>();
    partitionTest<double, 2>();
    partitionTest<double, 3>();
    partitionTest<double, 4>();

    partitionTest<float, 1>();
    partitionTest<float, 2>();
    partitionTest<float, 3>();
    partitionTest<float, 4>();
  }

  template <typename T, size_t N>
  using StatVec = blaze::StaticVector<T, N>;

  template <typename T, size_t N>
  using DynVec = blaze::DynamicVector<StatVec<T, N>>;

  template <typename T, size_t N>
  using DynMat = blaze::DynamicMatrix<StatVec<T, N>>;

  TEST(UNIT_TEST, BezierLinear)
  {
    {
      DynVec<double, 3> cpts {3, StatVec<double, 3>{0.0}};
      cpts[1] = StatVec<double, 3> {{1.0, 1.0, 1.0}};
      cpts[2] = StatVec<double, 3> {{2.0, 2.0, 2.0}};

      auto const half =
        BezierUtils::evaluateCurvePoint(cpts, 0.5);

      auto const expected =
        StatVec<double, 3>{{1.0, 1.0, 1.0}};
      EXPECT_EQ(half, expected);

      BezierCurve<double, 3> bc {cpts};
      EXPECT_EQ(expected, bc(0.5));
    }
  }

  TEST(UNIT_TEST, BezierCircle)
  {
    using blaze::norm;
    DynVec<double, 3> cpts {{StatVec<double, 3>{1.0, 0.0, 0.0},
                             StatVec<double, 3>{1.0, 1.0, 0.0},
                             StatVec<double, 3>{0.0, 1.0, 0.0}}};

    blaze::DynamicVector<double> wts {{1, 1, 2}};

    BezierCurve<double, 3> bc{cpts, wts};

    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.0)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.1)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.2)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.3)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.4)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.5)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.6)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.7)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.8)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.9)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(1.0)));
  }


  TEST(UNIT_TEST, BezierSurfaceLinear)
  {
    DynMat<double, 3> cpts(2, 2);

    cpts(0, 0) = StatVec<double, 3>{0., 0., 0.};
    cpts(0, 1) = StatVec<double, 3>{1., 0., 0.};
    cpts(1, 0) = StatVec<double, 3>{0., 1., 0.};
    cpts(1, 1) = StatVec<double, 3>{1., 1., 1.};

    BezierSurface<double, 3> bs {cpts};

    {
      auto const val = bs(1, 0.25);
      EXPECT_DOUBLE_EQ(1.0, val[0]);
      EXPECT_DOUBLE_EQ(0.25, val[1]);
      EXPECT_DOUBLE_EQ(0.25, val[2]);
    }

    {
      auto const val = bs(0.25, 1);
      EXPECT_DOUBLE_EQ(0.25, val[0]);
      EXPECT_DOUBLE_EQ(1.0, val[1]);
      EXPECT_DOUBLE_EQ(0.25, val[2]);
    }

    {
      auto const val = bs(1, 0.5);
      EXPECT_DOUBLE_EQ(1, val[0]);
      EXPECT_DOUBLE_EQ(0.5, val[1]);
      EXPECT_DOUBLE_EQ(0.5, val[2]);
    }

    {
      auto const val = bs(0.5, 1);
      EXPECT_DOUBLE_EQ(0.5, val[0]);
      EXPECT_DOUBLE_EQ(1.0, val[1]);
      EXPECT_DOUBLE_EQ(0.5, val[2]);
    }

    {
      auto const val = bs(0.5, 0.5);
      EXPECT_DOUBLE_EQ(0.5, val[0]);
      EXPECT_DOUBLE_EQ(0.5, val[1]);
      EXPECT_DOUBLE_EQ(0.25, val[2]);
    }
  }


  TEST(UNIT_TEST, BezierSurfaceCylinder)
  {
    using blaze::norm;
    DynMat<double, 3> cpts(2, 3);

    cpts(0, 0) = StatVec<double, 3>{1., 0., 0.};
    cpts(0, 1) = StatVec<double, 3>{1., 1., 0.};
    cpts(0, 2) = StatVec<double, 3>{0., 1., 0.};

    cpts(1, 0) = StatVec<double, 3>{1., 0., 1.};
    cpts(1, 1) = StatVec<double, 3>{1., 1., 1.};
    cpts(1, 2) = StatVec<double, 3>{0., 1., 1.};

    blaze::DynamicMatrix<double> wts(2, 3);

    wts(0, 0) = 1;
    wts(0, 1) = 1;
    wts(0, 2) = 2;

    wts(1, 0) = 1;
    wts(1, 1) = 1;
    wts(1, 2) = 2;

    BezierSurface<double, 3> bs{cpts, wts};

    EXPECT_DOUBLE_EQ(norm(bs(0.0, 0)), 1);
    EXPECT_DOUBLE_EQ(norm(bs(0.5, 0)), 1);
    EXPECT_DOUBLE_EQ(norm(bs(1.0, 0)), 1);

    {
      auto const zComp = StatVec<double, 3>{0, 0, .5};
      EXPECT_DOUBLE_EQ(norm(bs(0.0, .5) - zComp), 1);
      EXPECT_DOUBLE_EQ(norm(bs(0.5, .5) - zComp), 1);
      EXPECT_DOUBLE_EQ(norm(bs(1.0, .5) - zComp), 1);
    }

    {
      auto const zComp = StatVec<double, 3>{0, 0, 1};
      EXPECT_DOUBLE_EQ(norm(bs(0.0, 1) - zComp), 1);
      EXPECT_DOUBLE_EQ(norm(bs(0.5, 1) - zComp), 1);
      EXPECT_DOUBLE_EQ(norm(bs(1.0, 1) - zComp), 1);
    }
  }

}