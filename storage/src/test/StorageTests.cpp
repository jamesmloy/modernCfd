#include "gtest/gtest.h"

#include "storage/StorageSite.h"
#include "storage/SubsetStorageSite.h"

namespace
{
  TEST(StorageTests, InstantiateSite)
  {
    StorageSite ss(4, 12);

    EXPECT_EQ(ss.selfCount(), 4);
    EXPECT_EQ(ss.count(), 12);
  }


  TEST(StorageTests, InstantiateSubset)
  {
    StorageSite ss(12, 12);

    SubsetStorageSite sub(2, 4, ss);

    EXPECT_EQ(&sub.parent(), &ss);
  }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}