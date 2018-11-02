#include "gtest/gtest.h"

#include "connectivity/CrConnectivity.h"
#include "connectivity/ConnectivityBuilder.h"


namespace
{
  using IArray = CrConnectivity::IndexArray;
  TEST(ConnectivityTests, Instantiate)
  {
      IArray offsets(4);
      IArray entries(8);

      CrConnectivity cr(offsets, entries);
  }

  TEST(ConnectivityTests, Build)
  {
    ConnectivityBuilder cb(5, 5);

    cb.addCount(0, 2);
    cb.addCount(1, 1);
    cb.addCount(3, 4);
    cb.addCount(4, 3);

    cb.finalizeCount();

    cb.addEntry(0, 1);
    cb.addEntry(0, 4);

    cb.addEntry(1, 0);

    cb.addEntry(3, 0);
    cb.addEntry(3, 1);
    cb.addEntry(3, 2);
    cb.addEntry(3, 4);

    cb.addEntry(4, 1);
    cb.addEntry(4, 2);
    cb.addEntry(4, 4);

    auto conn = cb.makeConnectivity();

    EXPECT_EQ(conn->count(0), 2);
    EXPECT_EQ(conn->neib(0, 0), 1);
    EXPECT_EQ(conn->neib(0, 1), 4);

    EXPECT_EQ(conn->count(1), 1);
    EXPECT_EQ(conn->neib(1, 0), 0);

    EXPECT_EQ(conn->count(2), 0);

    EXPECT_EQ(conn->count(3), 4);
    EXPECT_EQ(conn->neib(3, 0), 0);
    EXPECT_EQ(conn->neib(3, 1), 1);
    EXPECT_EQ(conn->neib(3, 2), 2);
    EXPECT_EQ(conn->neib(3, 3), 4);
  }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}