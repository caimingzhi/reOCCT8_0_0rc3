

#include <GeomPlate_BuildPlateSurface.hpp>

#include <gtest/gtest.h>

TEST(GeomPlate_BuildPlateSurface, OCC525_PerformWithoutConstraints)
{
  GeomPlate_BuildPlateSurface aBuilder;
  aBuilder.Perform();

  EXPECT_TRUE(aBuilder.IsDone());
  EXPECT_TRUE(aBuilder.Surface().IsNull())
    << "Surface should be null when Perform() is called without constraints";
}
