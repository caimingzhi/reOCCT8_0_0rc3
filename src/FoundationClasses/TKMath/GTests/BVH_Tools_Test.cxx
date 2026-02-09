

#include <gtest/gtest.h>

#include <BVH_Box.hpp>
#include <BVH_Tools.hpp>
#include <Precision.hpp>

TEST(BVH_ToolsTest, PointBoxSquareDistance)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  double aDist1 = BVH_Tools<double, 3>::PointBoxSquareDistance(BVH_Vec3d(0.5, 0.5, 0.5), aBox);
  EXPECT_NEAR(aDist1, 0.0, Precision::Confusion());

  double aDist2 = BVH_Tools<double, 3>::PointBoxSquareDistance(BVH_Vec3d(0.5, 0.5, 1.0), aBox);
  EXPECT_NEAR(aDist2, 0.0, Precision::Confusion());

  double aDist3 = BVH_Tools<double, 3>::PointBoxSquareDistance(BVH_Vec3d(2.0, 0.5, 0.5), aBox);
  EXPECT_NEAR(aDist3, 1.0, Precision::Confusion());

  double aDist4 = BVH_Tools<double, 3>::PointBoxSquareDistance(BVH_Vec3d(2.0, 2.0, 2.0), aBox);
  EXPECT_NEAR(aDist4, 3.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, BoxBoxSquareDistance)
{
  BVH_Box<double, 3> aBox1(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));
  BVH_Box<double, 3> aBox2(BVH_Vec3d(2.0, 0.0, 0.0), BVH_Vec3d(3.0, 1.0, 1.0));
  BVH_Box<double, 3> aBox3(BVH_Vec3d(0.5, 0.5, 0.5), BVH_Vec3d(1.5, 1.5, 1.5));

  double aDist1 = BVH_Tools<double, 3>::BoxBoxSquareDistance(aBox1, aBox2);
  EXPECT_NEAR(aDist1, 1.0, Precision::Confusion());

  double aDist2 = BVH_Tools<double, 3>::BoxBoxSquareDistance(aBox1, aBox3);
  EXPECT_NEAR(aDist2, 0.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointBoxProjection)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  BVH_Vec3d aProj1 = BVH_Tools<double, 3>::PointBoxProjection(BVH_Vec3d(0.5, 0.5, 0.5), aBox);
  EXPECT_NEAR(aProj1.x(), 0.5, Precision::Confusion());
  EXPECT_NEAR(aProj1.y(), 0.5, Precision::Confusion());
  EXPECT_NEAR(aProj1.z(), 0.5, Precision::Confusion());

  BVH_Vec3d aProj2 = BVH_Tools<double, 3>::PointBoxProjection(BVH_Vec3d(2.0, 0.5, 0.5), aBox);
  EXPECT_NEAR(aProj2.x(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aProj2.y(), 0.5, Precision::Confusion());
  EXPECT_NEAR(aProj2.z(), 0.5, Precision::Confusion());
}

TEST(BVH_ToolsTest, RayBoxIntersection)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  double aTimeEnter, aTimeLeave;

  bool aHit1 = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(-1.0, 0.5, 0.5),
                                                        BVH_Vec3d(1.0, 0.0, 0.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_TRUE(aHit1);
  EXPECT_NEAR(aTimeEnter, 1.0, Precision::Confusion());
  EXPECT_NEAR(aTimeLeave, 2.0, Precision::Confusion());

  bool aHit2 = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(-1.0, 5.0, 0.5),
                                                        BVH_Vec3d(1.0, 0.0, 0.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_FALSE(aHit2);

  bool aHit3 = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(0.5, 0.5, 0.5),
                                                        BVH_Vec3d(1.0, 0.0, 0.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_TRUE(aHit3);
  EXPECT_LE(aTimeEnter, 0.0);
  EXPECT_NEAR(aTimeLeave, 0.5, Precision::Confusion());
}

TEST(BVH_ToolsTest, RayBoxIntersectionParallelRay)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  double aTimeEnter, aTimeLeave;

  bool aHit1 = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(-1.0, 0.5, 0.5),
                                                        BVH_Vec3d(1.0, 0.0, 0.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_TRUE(aHit1);

  bool aHit2 = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(-1.0, 2.0, 0.5),
                                                        BVH_Vec3d(1.0, 0.0, 0.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_FALSE(aHit2);
}

TEST(BVH_ToolsTest, PointTriangleProjection)
{
  BVH_Vec3d aNode0(0.0, 0.0, 0.0);
  BVH_Vec3d aNode1(1.0, 0.0, 0.0);
  BVH_Vec3d aNode2(0.0, 1.0, 0.0);

  BVH_Vec3d aProj1 = BVH_Tools<double, 3>::PointTriangleProjection(BVH_Vec3d(-1.0, -1.0, 0.0),
                                                                   aNode0,
                                                                   aNode1,
                                                                   aNode2);
  EXPECT_NEAR(aProj1.x(), 0.0, Precision::Confusion());
  EXPECT_NEAR(aProj1.y(), 0.0, Precision::Confusion());
  EXPECT_NEAR(aProj1.z(), 0.0, Precision::Confusion());

  BVH_Vec3d aProj2 = BVH_Tools<double, 3>::PointTriangleProjection(BVH_Vec3d(0.5, -1.0, 0.0),
                                                                   aNode0,
                                                                   aNode1,
                                                                   aNode2);
  EXPECT_NEAR(aProj2.x(), 0.5, Precision::Confusion());
  EXPECT_NEAR(aProj2.y(), 0.0, Precision::Confusion());
  EXPECT_NEAR(aProj2.z(), 0.0, Precision::Confusion());

  BVH_Vec3d aProj3 = BVH_Tools<double, 3>::PointTriangleProjection(BVH_Vec3d(0.25, 0.25, 1.0),
                                                                   aNode0,
                                                                   aNode1,
                                                                   aNode2);
  EXPECT_NEAR(aProj3.x(), 0.25, Precision::Confusion());
  EXPECT_NEAR(aProj3.y(), 0.25, Precision::Confusion());
  EXPECT_NEAR(aProj3.z(), 0.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointBoxSquareDistance2D)
{
  BVH_Box<double, 2> aBox(BVH_Vec2d(0.0, 0.0), BVH_Vec2d(1.0, 1.0));

  double aDist1 = BVH_Tools<double, 2>::PointBoxSquareDistance(BVH_Vec2d(0.5, 0.5), aBox);
  EXPECT_NEAR(aDist1, 0.0, Precision::Confusion());

  double aDist2 = BVH_Tools<double, 2>::PointBoxSquareDistance(BVH_Vec2d(2.0, 0.5), aBox);
  EXPECT_NEAR(aDist2, 1.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, RayBoxIntersectionDiagonalRay)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  double aTimeEnter, aTimeLeave;

  BVH_Vec3d aDir(1.0, 1.0, 1.0);
  double    aNorm = std::sqrt(3.0);
  aDir            = BVH_Vec3d(aDir.x() / aNorm, aDir.y() / aNorm, aDir.z() / aNorm);

  bool aHit = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(-1.0, -1.0, -1.0),
                                                       aDir,
                                                       aBox,
                                                       aTimeEnter,
                                                       aTimeLeave);
  EXPECT_TRUE(aHit);
  EXPECT_GT(aTimeEnter, 0.0);
  EXPECT_GT(aTimeLeave, aTimeEnter);
}

TEST(BVH_ToolsTest, RayBoxIntersectionNegativeDirection)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  double aTimeEnter, aTimeLeave;

  bool aHit = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(2.0, 0.5, 0.5),
                                                       BVH_Vec3d(-1.0, 0.0, 0.0),
                                                       aBox,
                                                       aTimeEnter,
                                                       aTimeLeave);
  EXPECT_TRUE(aHit);
  EXPECT_NEAR(aTimeEnter, 1.0, Precision::Confusion());
  EXPECT_NEAR(aTimeLeave, 2.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, RayBoxIntersectionTouchingEdge)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  double aTimeEnter, aTimeLeave;

  bool aHit = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(-1.0, 0.0, 0.0),
                                                       BVH_Vec3d(1.0, 0.0, 0.0),
                                                       aBox,
                                                       aTimeEnter,
                                                       aTimeLeave);
  EXPECT_TRUE(aHit);
}

TEST(BVH_ToolsTest, RayBoxIntersectionTouchingCorner)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  double aTimeEnter, aTimeLeave;

  BVH_Vec3d aDir(1.0, 1.0, 1.0);
  double    aNorm = std::sqrt(3.0);
  aDir            = BVH_Vec3d(aDir.x() / aNorm, aDir.y() / aNorm, aDir.z() / aNorm);

  bool aHit = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(-1.0, -1.0, -1.0),
                                                       aDir,
                                                       aBox,
                                                       aTimeEnter,
                                                       aTimeLeave);
  EXPECT_TRUE(aHit);
}

TEST(BVH_ToolsTest, BoxBoxSquareDistanceTouching)
{
  BVH_Box<double, 3> aBox1(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));
  BVH_Box<double, 3> aBox2(BVH_Vec3d(1.0, 0.0, 0.0), BVH_Vec3d(2.0, 1.0, 1.0));

  double aDist = BVH_Tools<double, 3>::BoxBoxSquareDistance(aBox1, aBox2);
  EXPECT_NEAR(aDist, 0.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, BoxBoxSquareDistanceOneInsideOther)
{
  BVH_Box<double, 3> aBox1(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(10.0, 10.0, 10.0));
  BVH_Box<double, 3> aBox2(BVH_Vec3d(2.0, 2.0, 2.0), BVH_Vec3d(3.0, 3.0, 3.0));

  double aDist = BVH_Tools<double, 3>::BoxBoxSquareDistance(aBox1, aBox2);
  EXPECT_NEAR(aDist, 0.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, BoxBoxSquareDistanceCornerToCorner)
{
  BVH_Box<double, 3> aBox1(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));
  BVH_Box<double, 3> aBox2(BVH_Vec3d(2.0, 2.0, 2.0), BVH_Vec3d(3.0, 3.0, 3.0));

  double aDist = BVH_Tools<double, 3>::BoxBoxSquareDistance(aBox1, aBox2);
  EXPECT_NEAR(aDist, 3.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointBoxProjectionNegativeCoords)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(-1.0, -1.0, -1.0), BVH_Vec3d(1.0, 1.0, 1.0));

  BVH_Vec3d aProj = BVH_Tools<double, 3>::PointBoxProjection(BVH_Vec3d(-5.0, -5.0, -5.0), aBox);
  EXPECT_NEAR(aProj.x(), -1.0, Precision::Confusion());
  EXPECT_NEAR(aProj.y(), -1.0, Precision::Confusion());
  EXPECT_NEAR(aProj.z(), -1.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointTriangleProjectionOnEdge01)
{
  BVH_Vec3d aNode0(0.0, 0.0, 0.0);
  BVH_Vec3d aNode1(2.0, 0.0, 0.0);
  BVH_Vec3d aNode2(0.0, 2.0, 0.0);

  BVH_Vec3d aProj = BVH_Tools<double, 3>::PointTriangleProjection(BVH_Vec3d(1.0, -1.0, 0.0),
                                                                  aNode0,
                                                                  aNode1,
                                                                  aNode2);
  EXPECT_NEAR(aProj.x(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aProj.y(), 0.0, Precision::Confusion());
  EXPECT_NEAR(aProj.z(), 0.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointTriangleProjectionOnEdge12)
{
  BVH_Vec3d aNode0(0.0, 0.0, 0.0);
  BVH_Vec3d aNode1(2.0, 0.0, 0.0);
  BVH_Vec3d aNode2(0.0, 2.0, 0.0);

  BVH_Vec3d aProj =
    BVH_Tools<double, 3>::PointTriangleProjection(BVH_Vec3d(2.0, 2.0, 0.0), aNode0, aNode1, aNode2);
  EXPECT_NEAR(aProj.x(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aProj.y(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aProj.z(), 0.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointTriangleProjectionOnEdge20)
{
  BVH_Vec3d aNode0(0.0, 0.0, 0.0);
  BVH_Vec3d aNode1(2.0, 0.0, 0.0);
  BVH_Vec3d aNode2(0.0, 2.0, 0.0);

  BVH_Vec3d aProj = BVH_Tools<double, 3>::PointTriangleProjection(BVH_Vec3d(-1.0, 1.0, 0.0),
                                                                  aNode0,
                                                                  aNode1,
                                                                  aNode2);
  EXPECT_NEAR(aProj.x(), 0.0, Precision::Confusion());
  EXPECT_NEAR(aProj.y(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aProj.z(), 0.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointTriangleProjectionVertex1)
{
  BVH_Vec3d aNode0(0.0, 0.0, 0.0);
  BVH_Vec3d aNode1(2.0, 0.0, 0.0);
  BVH_Vec3d aNode2(0.0, 2.0, 0.0);

  BVH_Vec3d aProj = BVH_Tools<double, 3>::PointTriangleProjection(BVH_Vec3d(3.0, -1.0, 0.0),
                                                                  aNode0,
                                                                  aNode1,
                                                                  aNode2);
  EXPECT_NEAR(aProj.x(), 2.0, Precision::Confusion());
  EXPECT_NEAR(aProj.y(), 0.0, Precision::Confusion());
  EXPECT_NEAR(aProj.z(), 0.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointTriangleProjectionVertex2)
{
  BVH_Vec3d aNode0(0.0, 0.0, 0.0);
  BVH_Vec3d aNode1(2.0, 0.0, 0.0);
  BVH_Vec3d aNode2(0.0, 2.0, 0.0);

  BVH_Vec3d aProj = BVH_Tools<double, 3>::PointTriangleProjection(BVH_Vec3d(-1.0, 3.0, 0.0),
                                                                  aNode0,
                                                                  aNode1,
                                                                  aNode2);
  EXPECT_NEAR(aProj.x(), 0.0, Precision::Confusion());
  EXPECT_NEAR(aProj.y(), 2.0, Precision::Confusion());
  EXPECT_NEAR(aProj.z(), 0.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointTriangleProjection3D)
{

  BVH_Vec3d aNode0(0.0, 0.0, 0.0);
  BVH_Vec3d aNode1(1.0, 0.0, 0.0);
  BVH_Vec3d aNode2(0.0, 1.0, 1.0);

  BVH_Vec3d aProj =
    BVH_Tools<double, 3>::PointTriangleProjection(BVH_Vec3d(0.3, 0.3, 0.8), aNode0, aNode1, aNode2);

  EXPECT_GE(aProj.x(), 0.0);
  EXPECT_GE(aProj.y(), 0.0);
  EXPECT_LE(aProj.x() + aProj.y(), 1.0 + Precision::Confusion());
}

TEST(BVH_ToolsTest, BoxBoxSquareDistance2D)
{
  BVH_Box<double, 2> aBox1(BVH_Vec2d(0.0, 0.0), BVH_Vec2d(1.0, 1.0));
  BVH_Box<double, 2> aBox2(BVH_Vec2d(3.0, 0.0), BVH_Vec2d(4.0, 1.0));

  double aDist = BVH_Tools<double, 2>::BoxBoxSquareDistance(aBox1, aBox2);
  EXPECT_NEAR(aDist, 4.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointBoxProjection2D)
{
  BVH_Box<double, 2> aBox(BVH_Vec2d(0.0, 0.0), BVH_Vec2d(1.0, 1.0));

  BVH_Vec2d aProj = BVH_Tools<double, 2>::PointBoxProjection(BVH_Vec2d(2.0, 2.0), aBox);
  EXPECT_NEAR(aProj.x(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aProj.y(), 1.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointBoxSquareDistanceAtVertex)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  double aDist = BVH_Tools<double, 3>::PointBoxSquareDistance(BVH_Vec3d(0.0, 0.0, 0.0), aBox);
  EXPECT_NEAR(aDist, 0.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointBoxSquareDistanceAtEdge)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  double aDist = BVH_Tools<double, 3>::PointBoxSquareDistance(BVH_Vec3d(0.5, 0.0, 0.0), aBox);
  EXPECT_NEAR(aDist, 0.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointBoxSquareDistanceFloat)
{
  BVH_Box<float, 3> aBox(BVH_Vec3f(0.0f, 0.0f, 0.0f), BVH_Vec3f(1.0f, 1.0f, 1.0f));

  float aDist1 = BVH_Tools<float, 3>::PointBoxSquareDistance(BVH_Vec3f(0.5f, 0.5f, 0.5f), aBox);
  EXPECT_NEAR(aDist1, 0.0f, 1e-5f);

  float aDist2 = BVH_Tools<float, 3>::PointBoxSquareDistance(BVH_Vec3f(2.0f, 0.5f, 0.5f), aBox);
  EXPECT_NEAR(aDist2, 1.0f, 1e-5f);
}

TEST(BVH_ToolsTest, RayBoxIntersectionFloat)
{
  BVH_Box<float, 3> aBox(BVH_Vec3f(0.0f, 0.0f, 0.0f), BVH_Vec3f(1.0f, 1.0f, 1.0f));

  float aTimeEnter, aTimeLeave;

  bool aHit = BVH_Tools<float, 3>::RayBoxIntersection(BVH_Vec3f(-1.0f, 0.5f, 0.5f),
                                                      BVH_Vec3f(1.0f, 0.0f, 0.0f),
                                                      aBox,
                                                      aTimeEnter,
                                                      aTimeLeave);
  EXPECT_TRUE(aHit);
  EXPECT_NEAR(aTimeEnter, 1.0f, 1e-5f);
  EXPECT_NEAR(aTimeLeave, 2.0f, 1e-5f);
}

TEST(BVH_ToolsTest, RayBoxIntersectionBehindRay)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  double aTimeEnter, aTimeLeave;

  bool aHit = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(2.0, 0.5, 0.5),
                                                       BVH_Vec3d(1.0, 0.0, 0.0),
                                                       aBox,
                                                       aTimeEnter,
                                                       aTimeLeave);

  EXPECT_TRUE(aTimeLeave < 0.0 || !aHit);
}

TEST(BVH_ToolsTest, RayBoxIntersectionYAxis)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  double aTimeEnter, aTimeLeave;

  bool aHit = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(0.5, -1.0, 0.5),
                                                       BVH_Vec3d(0.0, 1.0, 0.0),
                                                       aBox,
                                                       aTimeEnter,
                                                       aTimeLeave);
  EXPECT_TRUE(aHit);
  EXPECT_NEAR(aTimeEnter, 1.0, Precision::Confusion());
  EXPECT_NEAR(aTimeLeave, 2.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, RayBoxIntersectionZAxis)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  double aTimeEnter, aTimeLeave;

  bool aHit = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(0.5, 0.5, -1.0),
                                                       BVH_Vec3d(0.0, 0.0, 1.0),
                                                       aBox,
                                                       aTimeEnter,
                                                       aTimeLeave);
  EXPECT_TRUE(aHit);
  EXPECT_NEAR(aTimeEnter, 1.0, Precision::Confusion());
  EXPECT_NEAR(aTimeLeave, 2.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, BoxBoxSquareDistanceFloat)
{
  BVH_Box<float, 3> aBox1(BVH_Vec3f(0.0f, 0.0f, 0.0f), BVH_Vec3f(1.0f, 1.0f, 1.0f));
  BVH_Box<float, 3> aBox2(BVH_Vec3f(2.0f, 0.0f, 0.0f), BVH_Vec3f(3.0f, 1.0f, 1.0f));

  float aDist = BVH_Tools<float, 3>::BoxBoxSquareDistance(aBox1, aBox2);
  EXPECT_NEAR(aDist, 1.0f, 1e-5f);
}

TEST(BVH_ToolsTest, PointBoxProjectionFloat)
{
  BVH_Box<float, 3> aBox(BVH_Vec3f(0.0f, 0.0f, 0.0f), BVH_Vec3f(1.0f, 1.0f, 1.0f));

  BVH_Vec3f aProj = BVH_Tools<float, 3>::PointBoxProjection(BVH_Vec3f(2.0f, 0.5f, 0.5f), aBox);
  EXPECT_NEAR(aProj.x(), 1.0f, 1e-5f);
  EXPECT_NEAR(aProj.y(), 0.5f, 1e-5f);
  EXPECT_NEAR(aProj.z(), 0.5f, 1e-5f);
}

TEST(BVH_ToolsTest, PointBoxSquareDistanceNegativeBox)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(-2.0, -2.0, -2.0), BVH_Vec3d(-1.0, -1.0, -1.0));

  double aDist = BVH_Tools<double, 3>::PointBoxSquareDistance(BVH_Vec3d(0.0, 0.0, 0.0), aBox);

  EXPECT_NEAR(aDist, 3.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, BoxBoxSquareDistanceEdgeToEdge)
{
  BVH_Box<double, 3> aBox1(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));
  BVH_Box<double, 3> aBox2(BVH_Vec3d(2.0, 2.0, 0.0), BVH_Vec3d(3.0, 3.0, 1.0));

  double aDist = BVH_Tools<double, 3>::BoxBoxSquareDistance(aBox1, aBox2);
  EXPECT_NEAR(aDist, 2.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointTriangleProjectionFloat)
{
  BVH_Vec3f aNode0(0.0f, 0.0f, 0.0f);
  BVH_Vec3f aNode1(1.0f, 0.0f, 0.0f);
  BVH_Vec3f aNode2(0.0f, 1.0f, 0.0f);

  BVH_Vec3f aProj = BVH_Tools<float, 3>::PointTriangleProjection(BVH_Vec3f(0.25f, 0.25f, 1.0f),
                                                                 aNode0,
                                                                 aNode1,
                                                                 aNode2);
  EXPECT_NEAR(aProj.x(), 0.25f, 1e-5f);
  EXPECT_NEAR(aProj.y(), 0.25f, 1e-5f);
  EXPECT_NEAR(aProj.z(), 0.0f, 1e-5f);
}

TEST(BVH_ToolsTest, PointBoxSquareDistanceLargeBox)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1000.0, 1000.0, 1000.0));

  double aDist1 =
    BVH_Tools<double, 3>::PointBoxSquareDistance(BVH_Vec3d(500.0, 500.0, 500.0), aBox);
  EXPECT_NEAR(aDist1, 0.0, Precision::Confusion());

  double aDist2 =
    BVH_Tools<double, 3>::PointBoxSquareDistance(BVH_Vec3d(1001.0, 500.0, 500.0), aBox);
  EXPECT_NEAR(aDist2, 1.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, RayBoxIntersectionLargeBox)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1000.0, 1000.0, 1000.0));

  double aTimeEnter, aTimeLeave;

  bool aHit = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(-100.0, 500.0, 500.0),
                                                       BVH_Vec3d(1.0, 0.0, 0.0),
                                                       aBox,
                                                       aTimeEnter,
                                                       aTimeLeave);
  EXPECT_TRUE(aHit);
  EXPECT_NEAR(aTimeEnter, 100.0, Precision::Confusion());
  EXPECT_NEAR(aTimeLeave, 1100.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointTriangleProjectionCentroid)
{
  BVH_Vec3d aNode0(0.0, 0.0, 0.0);
  BVH_Vec3d aNode1(3.0, 0.0, 0.0);
  BVH_Vec3d aNode2(0.0, 3.0, 0.0);

  BVH_Vec3d aProj =
    BVH_Tools<double, 3>::PointTriangleProjection(BVH_Vec3d(1.0, 1.0, 5.0), aNode0, aNode1, aNode2);
  EXPECT_NEAR(aProj.x(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aProj.y(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aProj.z(), 0.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, BoxBoxSquareDistanceSameBox)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  double aDist = BVH_Tools<double, 3>::BoxBoxSquareDistance(aBox, aBox);
  EXPECT_NEAR(aDist, 0.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, PointBoxProjectionAllCorners)
{
  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));

  BVH_Vec3d aProj1 = BVH_Tools<double, 3>::PointBoxProjection(BVH_Vec3d(-1.0, -1.0, -1.0), aBox);
  EXPECT_NEAR(aProj1.x(), 0.0, Precision::Confusion());
  EXPECT_NEAR(aProj1.y(), 0.0, Precision::Confusion());
  EXPECT_NEAR(aProj1.z(), 0.0, Precision::Confusion());

  BVH_Vec3d aProj2 = BVH_Tools<double, 3>::PointBoxProjection(BVH_Vec3d(2.0, 2.0, 2.0), aBox);
  EXPECT_NEAR(aProj2.x(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aProj2.y(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aProj2.z(), 1.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, RayBoxIntersection2D)
{

  BVH_Box<double, 2> aBox(BVH_Vec2d(0.0, 0.0), BVH_Vec2d(1.0, 1.0));

  double aTimeEnter, aTimeLeave;

  bool aHit1 = BVH_Tools<double, 2>::RayBoxIntersection(BVH_Vec2d(-1.0, 0.5),
                                                        BVH_Vec2d(1.0, 0.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_TRUE(aHit1);
  EXPECT_NEAR(aTimeEnter, 1.0, Precision::Confusion());
  EXPECT_NEAR(aTimeLeave, 2.0, Precision::Confusion());

  bool aHit2 = BVH_Tools<double, 2>::RayBoxIntersection(BVH_Vec2d(-1.0, 2.0),
                                                        BVH_Vec2d(1.0, 0.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_FALSE(aHit2);

  bool aHit3 = BVH_Tools<double, 2>::RayBoxIntersection(BVH_Vec2d(-1.0, 0.5),
                                                        BVH_Vec2d(1.0, 0.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_TRUE(aHit3);

  bool aHit4 = BVH_Tools<double, 2>::RayBoxIntersection(BVH_Vec2d(0.5, -1.0),
                                                        BVH_Vec2d(0.0, 1.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_TRUE(aHit4);
  EXPECT_NEAR(aTimeEnter, 1.0, Precision::Confusion());
  EXPECT_NEAR(aTimeLeave, 2.0, Precision::Confusion());
}

TEST(BVH_ToolsTest, RayBoxIntersectionEarlyExit)
{

  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));
  double             aTimeEnter, aTimeLeave;

  bool aHit = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(-2.0, 0.5, 0.5),
                                                       BVH_Vec3d(-1.0, 0.0, 0.0),
                                                       aBox,
                                                       aTimeEnter,
                                                       aTimeLeave);
  EXPECT_FALSE(aHit);

  bool aHit2 = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(0.5, -2.0, 0.5),
                                                        BVH_Vec3d(0.0, -1.0, 0.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_FALSE(aHit2);
}

TEST(BVH_ToolsTest, RayBoxIntersectionParallelRayEarlyExit)
{

  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));
  double             aTimeEnter, aTimeLeave;

  bool aHit = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(-1.0, 2.0, 0.5),
                                                       BVH_Vec3d(1.0, 0.0, 0.0),
                                                       aBox,
                                                       aTimeEnter,
                                                       aTimeLeave);
  EXPECT_FALSE(aHit);

  bool aHit2 = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(2.0, -1.0, 0.5),
                                                        BVH_Vec3d(0.0, 1.0, 0.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_FALSE(aHit2);

  bool aHit3 = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(-1.0, -1.0, 0.5),
                                                        BVH_Vec3d(0.0, 0.0, 1.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_FALSE(aHit3);
}

TEST(BVH_ToolsTest, RayBoxIntersection2DParallelBothAxes)
{

  BVH_Box<double, 2> aBox(BVH_Vec2d(0.0, 0.0), BVH_Vec2d(1.0, 1.0));
  double             aTimeEnter, aTimeLeave;

  bool aHit1 = BVH_Tools<double, 2>::RayBoxIntersection(BVH_Vec2d(0.5, 0.5),
                                                        BVH_Vec2d(0.0, 0.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_TRUE(aHit1);

  bool aHit2 = BVH_Tools<double, 2>::RayBoxIntersection(BVH_Vec2d(2.0, 2.0),
                                                        BVH_Vec2d(0.0, 0.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_FALSE(aHit2);
}

TEST(BVH_ToolsTest, RayBoxIntersectionNegativeTime)
{

  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));
  double             aTimeEnter, aTimeLeave;

  bool aHit = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(2.0, 0.5, 0.5),
                                                       BVH_Vec3d(1.0, 0.0, 0.0),
                                                       aBox,
                                                       aTimeEnter,
                                                       aTimeLeave);
  EXPECT_FALSE(aHit);

  bool aHit2 = BVH_Tools<double, 3>::RayBoxIntersection(BVH_Vec3d(0.5, 0.5, 0.5),
                                                        BVH_Vec3d(1.0, 0.0, 0.0),
                                                        aBox,
                                                        aTimeEnter,
                                                        aTimeLeave);
  EXPECT_TRUE(aHit2);
  EXPECT_TRUE(aTimeLeave >= 0.0);
}
