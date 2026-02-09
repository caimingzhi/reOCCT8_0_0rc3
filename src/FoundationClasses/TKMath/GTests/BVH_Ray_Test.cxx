#include <BVH_Ray.hpp>

#include <gtest/gtest.h>

TEST(BVH_RayTest, ConstructorBasic)
{
  BVH_Vec3d aOrigin(1.0, 2.0, 3.0);
  BVH_Vec3d aDirection(0.0, 1.0, 0.0);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Origin.x(), 1.0);
  EXPECT_EQ(aRay.Origin.y(), 2.0);
  EXPECT_EQ(aRay.Origin.z(), 3.0);

  EXPECT_EQ(aRay.Direct.x(), 0.0);
  EXPECT_EQ(aRay.Direct.y(), 1.0);
  EXPECT_EQ(aRay.Direct.z(), 0.0);
}

TEST(BVH_RayTest, DirectionStorage)
{
  BVH_Vec3d aOrigin(0.0, 0.0, 0.0);
  BVH_Vec3d aDirection(2.0, 4.0, 8.0);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Direct.x(), 2.0);
  EXPECT_EQ(aRay.Direct.y(), 4.0);
  EXPECT_EQ(aRay.Direct.z(), 8.0);
}

TEST(BVH_RayTest, NegativeDirection)
{
  BVH_Vec3d aOrigin(0.0, 0.0, 0.0);
  BVH_Vec3d aDirection(-2.0, -4.0, -1.0);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Direct.x(), -2.0);
  EXPECT_EQ(aRay.Direct.y(), -4.0);
  EXPECT_EQ(aRay.Direct.z(), -1.0);
}

TEST(BVH_RayTest, ZeroComponent)
{
  BVH_Vec3d aOrigin(0.0, 0.0, 0.0);
  BVH_Vec3d aDirection(1.0, 0.0, 1.0);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Direct.x(), 1.0);
  EXPECT_EQ(aRay.Direct.y(), 0.0);
  EXPECT_EQ(aRay.Direct.z(), 1.0);
}

TEST(BVH_RayTest, AllZeroDirection)
{
  BVH_Vec3d aOrigin(0.0, 0.0, 0.0);
  BVH_Vec3d aDirection(0.0, 0.0, 0.0);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Direct.x(), 0.0);
  EXPECT_EQ(aRay.Direct.y(), 0.0);
  EXPECT_EQ(aRay.Direct.z(), 0.0);
}

TEST(BVH_RayTest, DefaultConstructor)
{
  BVH_Ray<double, 3> aRay;

  EXPECT_EQ(aRay.Origin.x(), 0.0);
  EXPECT_EQ(aRay.Origin.y(), 0.0);
  EXPECT_EQ(aRay.Origin.z(), 0.0);

  EXPECT_EQ(aRay.Direct.x(), 0.0);
  EXPECT_EQ(aRay.Direct.y(), 0.0);
  EXPECT_EQ(aRay.Direct.z(), 0.0);
}

TEST(BVH_RayTest, Ray2D)
{
  BVH_Vec2d aOrigin(1.0, 2.0);
  BVH_Vec2d aDirection(3.0, 4.0);

  BVH_Ray<double, 2> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Origin.x(), 1.0);
  EXPECT_EQ(aRay.Origin.y(), 2.0);

  EXPECT_EQ(aRay.Direct.x(), 3.0);
  EXPECT_EQ(aRay.Direct.y(), 4.0);
}

TEST(BVH_RayTest, NormalizedDirection)
{
  BVH_Vec3d aOrigin(0.0, 0.0, 0.0);
  BVH_Vec3d aDirection(1.0, 0.0, 0.0);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Direct.x(), 1.0);
  EXPECT_EQ(aRay.Direct.y(), 0.0);
  EXPECT_EQ(aRay.Direct.z(), 0.0);
}

TEST(BVH_RayTest, VerySmallDirection)
{
  BVH_Vec3d aOrigin(0.0, 0.0, 0.0);
  BVH_Vec3d aDirection(1e-20, 1e-20, 1e-20);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Direct.x(), 1e-20);
  EXPECT_EQ(aRay.Direct.y(), 1e-20);
  EXPECT_EQ(aRay.Direct.z(), 1e-20);
}

TEST(BVH_RayTest, MixedZeroNonZero)
{
  BVH_Vec3d aOrigin(1.0, 2.0, 3.0);
  BVH_Vec3d aDirection(0.0, 2.0, 0.0);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Direct.x(), 0.0);
  EXPECT_EQ(aRay.Direct.y(), 2.0);
  EXPECT_EQ(aRay.Direct.z(), 0.0);
}

TEST(BVH_RayTest, FloatPrecision)
{
  BVH_Vec3f aOrigin(1.0f, 2.0f, 3.0f);
  BVH_Vec3f aDirection(2.0f, 4.0f, 8.0f);

  BVH_Ray<float, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Direct.x(), 2.0f);
  EXPECT_EQ(aRay.Direct.y(), 4.0f);
  EXPECT_EQ(aRay.Direct.z(), 8.0f);
}

TEST(BVH_RayTest, ConstexprConstructor)
{

  constexpr BVH_Vec3d          aOrigin(1.0, 2.0, 3.0);
  constexpr BVH_Vec3d          aDirection(1.0, 1.0, 1.0);
  constexpr BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Origin.x(), 1.0);
}

TEST(BVH_RayTest, DiagonalRay)
{
  BVH_Vec3d aOrigin(0.0, 0.0, 0.0);
  BVH_Vec3d aDirection(1.0, 1.0, 1.0);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Direct.x(), 1.0);
  EXPECT_EQ(aRay.Direct.y(), 1.0);
  EXPECT_EQ(aRay.Direct.z(), 1.0);
}

TEST(BVH_RayTest, NegativeOrigin)
{
  BVH_Vec3d aOrigin(-10.0, -20.0, -30.0);
  BVH_Vec3d aDirection(1.0, 2.0, 3.0);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Origin.x(), -10.0);
  EXPECT_EQ(aRay.Origin.y(), -20.0);
  EXPECT_EQ(aRay.Origin.z(), -30.0);

  EXPECT_EQ(aRay.Direct.x(), 1.0);
  EXPECT_EQ(aRay.Direct.y(), 2.0);
  EXPECT_EQ(aRay.Direct.z(), 3.0);
}

TEST(BVH_RayTest, AxisAlignedX)
{
  BVH_Vec3d aOrigin(0.0, 0.0, 0.0);
  BVH_Vec3d aDirection(1.0, 0.0, 0.0);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Direct.x(), 1.0);
  EXPECT_EQ(aRay.Direct.y(), 0.0);
  EXPECT_EQ(aRay.Direct.z(), 0.0);
}

TEST(BVH_RayTest, AxisAlignedY)
{
  BVH_Vec3d aOrigin(0.0, 0.0, 0.0);
  BVH_Vec3d aDirection(0.0, 1.0, 0.0);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Direct.x(), 0.0);
  EXPECT_EQ(aRay.Direct.y(), 1.0);
  EXPECT_EQ(aRay.Direct.z(), 0.0);
}

TEST(BVH_RayTest, AxisAlignedZ)
{
  BVH_Vec3d aOrigin(0.0, 0.0, 0.0);
  BVH_Vec3d aDirection(0.0, 0.0, 1.0);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Direct.x(), 0.0);
  EXPECT_EQ(aRay.Direct.y(), 0.0);
  EXPECT_EQ(aRay.Direct.z(), 1.0);
}

TEST(BVH_RayTest, LargeValues)
{
  BVH_Vec3d aOrigin(1e6, 2e6, 3e6);
  BVH_Vec3d aDirection(1e3, 2e3, 4e3);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Direct.x(), 1e3);
  EXPECT_EQ(aRay.Direct.y(), 2e3);
  EXPECT_EQ(aRay.Direct.z(), 4e3);
}

TEST(BVH_RayTest, OriginAndDirectionPreservation)
{
  BVH_Vec3d aOrigin(1.0, 2.0, 3.0);
  BVH_Vec3d aDirection(2.0, 4.0, 8.0);

  BVH_Ray<double, 3> aRay(aOrigin, aDirection);

  EXPECT_EQ(aRay.Origin.x(), aOrigin.x());
  EXPECT_EQ(aRay.Origin.y(), aOrigin.y());
  EXPECT_EQ(aRay.Origin.z(), aOrigin.z());

  EXPECT_EQ(aRay.Direct.x(), aDirection.x());
  EXPECT_EQ(aRay.Direct.y(), aDirection.y());
  EXPECT_EQ(aRay.Direct.z(), aDirection.z());
}
