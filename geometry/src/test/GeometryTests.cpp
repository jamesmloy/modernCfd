#include "gtest/gtest.h"

#include "geometry/BernsteinPolynomials.h"
#include "geometry/BezierCurve.h"

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

  TEST(GeometryTests, BernsteinEndPts)
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

  TEST(GeometryTests, BernsteinPartition)
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

  TEST(GeometryTests, BezierLinear)
  {
    {
      DynVec<double, 3> cpts {3, StatVec<double, 3>{0.0}};
      cpts[1] = StatVec<double, 3> {{1.0, 1.0, 1.0}};
      cpts[2] = StatVec<double, 3> {{2.0, 2.0, 2.0}};

      auto const half =
        BezierUtils::evaluatePoint(cpts, 0.5);

      auto const expected =
        StatVec<double, 3>{{1.0, 1.0, 1.0}};
      EXPECT_EQ(half, expected);

      BezierCurve<double, 3> bc {cpts};
      EXPECT_EQ(expected, bc(0.5));
    }
  }

  TEST(GeometryTest, BezierCircle)
  {
    using blaze::norm;
    DynVec<double, 2> cpts {{StatVec<double, 2>{1.0, 0.0},
                             StatVec<double, 2>{1.0, 1.0},
                             StatVec<double, 2>{0.0, 1.0}}};

    blaze::DynamicVector<double> wts {{1, 1, 2}};

    BezierCurve<double, 2> bc{cpts, wts};

    EXPECT_DOUBLE_EQ(1.0, norm(bc(0)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.1)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.2)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.3)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.4)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.5)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.6)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.7)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.8)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(0.9)));
    EXPECT_DOUBLE_EQ(1.0, norm(bc(1)));
  }
}