

#include <gtest/gtest.h>

#include <BVH_Triangulation.hpp>

TEST(BVH_TriangulationTest, DefaultConstructor)
{
  BVH_Triangulation<double, 3> aTriangulation;

  EXPECT_EQ(aTriangulation.Size(), 0);
  EXPECT_EQ((BVH::Array<double, 3>::Size(aTriangulation.Vertices)), 0);
  EXPECT_EQ((BVH::Array<int, 4>::Size(aTriangulation.Elements)), 0);
}

TEST(BVH_TriangulationTest, AddSingleTriangle)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 1.0, 0.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  EXPECT_EQ(aTriangulation.Size(), 1);
  EXPECT_EQ((BVH::Array<double, 3>::Size(aTriangulation.Vertices)), 3);
}

TEST(BVH_TriangulationTest, AddMultipleTriangles)
{
  BVH_Triangulation<double, 3> aTriangulation;

  for (int i = 0; i < 5; ++i)
  {
    double x = static_cast<double>(i);
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 1.0, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.5, 1.0, 0.0));
    BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  EXPECT_EQ(aTriangulation.Size(), 5);
  EXPECT_EQ((BVH::Array<double, 3>::Size(aTriangulation.Vertices)), 15);
}

TEST(BVH_TriangulationTest, BoxForSingleTriangle)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 2.0, 3.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(4.0, 1.0, 2.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(2.0, 3.0, 1.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  BVH_Box<double, 3> aBox = aTriangulation.Box(0);

  EXPECT_NEAR(aBox.CornerMin().x(), 1.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMin().y(), 1.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMin().z(), 1.0, 1e-10);

  EXPECT_NEAR(aBox.CornerMax().x(), 4.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMax().y(), 3.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMax().z(), 3.0, 1e-10);
}

TEST(BVH_TriangulationTest, BoxForDegenerateTriangle)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 1.0, 1.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 1.0, 1.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 1.0, 1.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  BVH_Box<double, 3> aBox = aTriangulation.Box(0);

  EXPECT_NEAR(aBox.CornerMin().x(), 1.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMin().y(), 1.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMin().z(), 1.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMax().x(), 1.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMax().y(), 1.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMax().z(), 1.0, 1e-10);
}

TEST(BVH_TriangulationTest, BoxForFlatTriangle)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(2.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 3.0, 0.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  BVH_Box<double, 3> aBox = aTriangulation.Box(0);

  EXPECT_NEAR(aBox.CornerMin().z(), 0.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMax().z(), 0.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMax().x(), 2.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMax().y(), 3.0, 1e-10);
}

TEST(BVH_TriangulationTest, CenterComputation)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(3.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 3.0, 0.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  EXPECT_NEAR(aTriangulation.Center(0, 0), 1.0, 1e-10);
  EXPECT_NEAR(aTriangulation.Center(0, 1), 1.0, 1e-10);
  EXPECT_NEAR(aTriangulation.Center(0, 2), 0.0, 1e-10);
}

TEST(BVH_TriangulationTest, CenterAlongXAxis)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(2.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(3.0, 0.0, 0.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  EXPECT_NEAR(aTriangulation.Center(0, 0), 2.0, 1e-10);
}

TEST(BVH_TriangulationTest, CenterAlongYAxis)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 2.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 4.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 6.0, 0.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  EXPECT_NEAR(aTriangulation.Center(0, 1), 4.0, 1e-10);
}

TEST(BVH_TriangulationTest, CenterAlongZAxis)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, 1.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, 4.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, 7.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  EXPECT_NEAR(aTriangulation.Center(0, 2), 4.0, 1e-10);
}

TEST(BVH_TriangulationTest, SwapTwoTriangles)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 1.0, 0.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(5.0, 5.0, 5.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(6.0, 5.0, 5.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(5.0, 6.0, 5.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(3, 4, 5, 0));

  double aCentroid0Before = aTriangulation.Center(0, 0);
  double aCentroid1Before = aTriangulation.Center(1, 0);

  aTriangulation.Swap(0, 1);

  EXPECT_NEAR(aTriangulation.Center(0, 0), aCentroid1Before, 1e-10);
  EXPECT_NEAR(aTriangulation.Center(1, 0), aCentroid0Before, 1e-10);
}

TEST(BVH_TriangulationTest, SwapPreservesVertices)
{
  BVH_Triangulation<double, 3> aTriangulation;

  for (int i = 0; i < 3; ++i)
  {
    double x = static_cast<double>(i) * 10.0;
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 1.0, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.5, 1.0, 0.0));
    BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  int aVertexCount = BVH::Array<double, 3>::Size(aTriangulation.Vertices);

  aTriangulation.Swap(0, 2);

  EXPECT_EQ((BVH::Array<double, 3>::Size(aTriangulation.Vertices)), aVertexCount);
}

TEST(BVH_TriangulationTest, Triangulation2D)
{
  BVH_Triangulation<double, 2> aTriangulation2D;

  BVH::Array<double, 2>::Append(aTriangulation2D.Vertices, BVH_Vec2d(0.0, 0.0));
  BVH::Array<double, 2>::Append(aTriangulation2D.Vertices, BVH_Vec2d(1.0, 0.0));
  BVH::Array<double, 2>::Append(aTriangulation2D.Vertices, BVH_Vec2d(0.5, 1.0));
  BVH::Array<int, 4>::Append(aTriangulation2D.Elements, BVH_Vec4i(0, 1, 2, 0));

  EXPECT_EQ(aTriangulation2D.Size(), 1);

  BVH_Box<double, 2> aBox = aTriangulation2D.Box(0);
  EXPECT_NEAR(aBox.CornerMin().x(), 0.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMin().y(), 0.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMax().x(), 1.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMax().y(), 1.0, 1e-10);
}

TEST(BVH_TriangulationTest, SharedVertices)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 1.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 1.0, 0.0));

  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 2, 3, 0));

  EXPECT_EQ(aTriangulation.Size(), 2);
  EXPECT_EQ((BVH::Array<double, 3>::Size(aTriangulation.Vertices)), 4);

  BVH_Box<double, 3> aBox0 = aTriangulation.Box(0);
  BVH_Box<double, 3> aBox1 = aTriangulation.Box(1);

  EXPECT_FALSE(aBox0.IsOut(aBox1));
}

TEST(BVH_TriangulationTest, FloatPrecision)
{
  BVH_Triangulation<float, 3> aTriangulation;

  BVH::Array<float, 3>::Append(aTriangulation.Vertices, BVH_Vec3f(0.0f, 0.0f, 0.0f));
  BVH::Array<float, 3>::Append(aTriangulation.Vertices, BVH_Vec3f(1.0f, 0.0f, 0.0f));
  BVH::Array<float, 3>::Append(aTriangulation.Vertices, BVH_Vec3f(0.0f, 1.0f, 0.0f));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  EXPECT_EQ(aTriangulation.Size(), 1);

  BVH_Box<float, 3> aBox = aTriangulation.Box(0);
  EXPECT_NEAR(aBox.CornerMax().x(), 1.0f, 1e-6f);
  EXPECT_NEAR(aBox.CornerMax().y(), 1.0f, 1e-6f);
}

TEST(BVH_TriangulationTest, NegativeCoordinates)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(-1.0, -2.0, -3.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, -1.0, -2.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, -1.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  BVH_Box<double, 3> aBox = aTriangulation.Box(0);

  EXPECT_NEAR(aBox.CornerMin().x(), -1.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMin().y(), -2.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMin().z(), -3.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMax().x(), 1.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMax().y(), 0.0, 1e-10);
  EXPECT_NEAR(aBox.CornerMax().z(), -1.0, 1e-10);
}
