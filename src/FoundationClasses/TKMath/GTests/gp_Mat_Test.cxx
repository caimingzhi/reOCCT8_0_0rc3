

#include <gp_Mat.hpp>

#include <gtest/gtest.h>

TEST(gp_MatTest, OCC22595_DefaultConstructor)
{
  gp_Mat aM0;

  EXPECT_DOUBLE_EQ(0.0, aM0(1, 1));
  EXPECT_DOUBLE_EQ(0.0, aM0(1, 2));
  EXPECT_DOUBLE_EQ(0.0, aM0(1, 3));

  EXPECT_DOUBLE_EQ(0.0, aM0(2, 1));
  EXPECT_DOUBLE_EQ(0.0, aM0(2, 2));
  EXPECT_DOUBLE_EQ(0.0, aM0(2, 3));

  EXPECT_DOUBLE_EQ(0.0, aM0(3, 1));
  EXPECT_DOUBLE_EQ(0.0, aM0(3, 2));
  EXPECT_DOUBLE_EQ(0.0, aM0(3, 3));
}
