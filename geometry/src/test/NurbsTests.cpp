#include "gtest/gtest.h"

#include "geometry/BezierCurve.h"

#include "geometry/NurbsUtils.h"
#include "geometry/NurbsCurve.h"

#include "blaze/math/DynamicVector.h"

#include <algorithm>

namespace
{

  TEST(UNIT_TEST, FindSpan)
  {
    using blaze::DynamicVector;
    using NurbsUtils::findSpan;

    DynamicVector<double> U {{0, 0, 0, 1, 2, 3, 4, 4, 5, 5, 5}};

    {
      auto const it = findSpan(begin(U), end(U), 2, 1.5);
      EXPECT_EQ(3, std::distance(begin(U), it));
    }

    {
      auto const it = findSpan(begin(U), end(U), 2, 0.0);
      EXPECT_EQ(2, std::distance(begin(U), it));
    }

    {
      auto const it = findSpan(begin(U), end(U), 2, 4.0);
      EXPECT_EQ(7, std::distance(begin(U), it));
    }

    {
      auto const it = findSpan(begin(U), end(U), 2, 5.0);
      EXPECT_EQ(7, std::distance(begin(U), it));
    }
  }


  TEST(UNIT_TEST, BasisFunctions)
  {
    using namespace NurbsUtils;
    using blaze::DynamicVector;

    DynamicVector<double> U {{0, 0, 0, 1, 2, 3, 4, 4, 5, 5, 5}};

    {
      auto const n = basisFuns(3, 2, 1.5, begin(U), end(U));
      EXPECT_DOUBLE_EQ(1.0, std::accumulate(begin(n), end(n), 0.0));
    }

    {
      auto const n = basisFuns(3, 2, 2.1, begin(U), end(U));
      EXPECT_DOUBLE_EQ(1.0, std::accumulate(begin(n), end(n), 0.0));
    }

    {
      auto const n = basisFuns(3, 2, 4.15, begin(U), end(U));
      EXPECT_DOUBLE_EQ(1.0, std::accumulate(begin(n), end(n), 0.0));
    }

    {
      auto const n = basisFuns(3, 2, 0.0, begin(U), end(U));
      EXPECT_DOUBLE_EQ(1.0, std::accumulate(begin(n), end(n), 0.0));
    }

    {
      auto const n = basisFuns(3, 2, 5.0, begin(U), end(U));
      EXPECT_DOUBLE_EQ(1.0, std::accumulate(begin(n), end(n), 0.0));
    }
  }


  TEST(UNIT_TEST, NurbsCurve)
  {
    using blaze::DynamicVector;
    using StatVec3  = blaze::StaticVector<double, 3>;

    DynamicVector<StatVec3> cpts(4, StatVec3{0});
    cpts[1] = StatVec3 {1., 0.5, 0};
    cpts[2] = StatVec3 {2., 1.0, 0.25};
    cpts[3] = StatVec3 {1., 0.75, 0.5};

    NurbsCurve<double, 3> nurb(cpts);
    BezierCurve<double, 3> bc(cpts);

    for (double u = 0.0; u <= 1.0; u += 0.1)
    {
      auto const n = nurb(u);
      auto const b = bc(u);
      EXPECT_DOUBLE_EQ(n[0], b[0]);
      EXPECT_DOUBLE_EQ(n[1], b[1]);
      EXPECT_DOUBLE_EQ(n[2], b[2]);
    }
  }
}