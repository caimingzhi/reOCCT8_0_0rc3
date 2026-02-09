

#include <gtest/gtest.h>

#include <BVH_QuickSorter.hpp>
#include <BVH_Triangulation.hpp>

TEST(BVH_QuickSorterTest, Constructor)
{
  BVH_QuickSorter<double, 3> aSorterX(0);
  BVH_QuickSorter<double, 3> aSorterY(1);
  BVH_QuickSorter<double, 3> aSorterZ(2);

  EXPECT_TRUE(true);
}

TEST(BVH_QuickSorterTest, SortEmptySet)
{
  BVH_Triangulation<double, 3> aTriangulation;
  BVH_QuickSorter<double, 3>   aSorter(0);

  aSorter.Perform(&aTriangulation);
  EXPECT_EQ(aTriangulation.Size(), 0);
}

TEST(BVH_QuickSorterTest, SortSingleElement)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 1.0, 0.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  BVH_QuickSorter<double, 3> aSorter(0);
  aSorter.Perform(&aTriangulation);

  EXPECT_EQ(aTriangulation.Size(), 1);
}

TEST(BVH_QuickSorterTest, SortAlongXAxis)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(4.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(5.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(6.0, 1.0, 0.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(2.0, 1.0, 0.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(3, 4, 5, 0));

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(2.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(3.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(4.0, 1.0, 0.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(6, 7, 8, 0));

  BVH_QuickSorter<double, 3> aSorter(0);
  aSorter.Perform(&aTriangulation);

  EXPECT_LT(aTriangulation.Center(0, 0), aTriangulation.Center(1, 0));
  EXPECT_LT(aTriangulation.Center(1, 0), aTriangulation.Center(2, 0));

  EXPECT_NEAR(aTriangulation.Center(0, 0), 1.0, 1e-10);
  EXPECT_NEAR(aTriangulation.Center(1, 0), 3.0, 1e-10);
  EXPECT_NEAR(aTriangulation.Center(2, 0), 5.0, 1e-10);
}

TEST(BVH_QuickSorterTest, SortAlongYAxis)
{
  BVH_Triangulation<double, 3> aTriangulation;

  for (int i = 0; i < 3; ++i)
  {
    double y = (i == 0 ? 3.0 : (i == 1 ? 1.0 : 2.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, y - 0.5, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, y, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.5, y + 0.5, 0.0));
    BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  BVH_QuickSorter<double, 3> aSorter(1);
  aSorter.Perform(&aTriangulation);

  EXPECT_LT(aTriangulation.Center(0, 1), aTriangulation.Center(1, 1));
  EXPECT_LT(aTriangulation.Center(1, 1), aTriangulation.Center(2, 1));
}

TEST(BVH_QuickSorterTest, SortAlongZAxis)
{
  BVH_Triangulation<double, 3> aTriangulation;

  for (int i = 0; i < 3; ++i)
  {
    double z = (i == 0 ? 2.0 : (i == 1 ? 0.0 : 1.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, z));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 0.0, z));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.5, 1.0, z));
    BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  BVH_QuickSorter<double, 3> aSorter(2);
  aSorter.Perform(&aTriangulation);

  EXPECT_LT(aTriangulation.Center(0, 2), aTriangulation.Center(1, 2));
  EXPECT_LT(aTriangulation.Center(1, 2), aTriangulation.Center(2, 2));
}

TEST(BVH_QuickSorterTest, SortRangeInSet)
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

  aTriangulation.Swap(1, 3);

  EXPECT_NEAR(aTriangulation.Center(1, 0), 3.5, 1e-10);
  EXPECT_NEAR(aTriangulation.Center(2, 0), 2.5, 1e-10);
  EXPECT_NEAR(aTriangulation.Center(3, 0), 1.5, 1e-10);

  BVH_QuickSorter<double, 3> aSorter(0);
  aSorter.Perform(&aTriangulation, 1, 3);

  EXPECT_NEAR(aTriangulation.Center(0, 0), 0.5, 1e-10);
  EXPECT_NEAR(aTriangulation.Center(4, 0), 4.5, 1e-10);

  EXPECT_NEAR(aTriangulation.Center(1, 0), 1.5, 1e-10);
  EXPECT_NEAR(aTriangulation.Center(2, 0), 2.5, 1e-10);
  EXPECT_NEAR(aTriangulation.Center(3, 0), 3.5, 1e-10);
}

TEST(BVH_QuickSorterTest, AlreadySorted)
{
  BVH_Triangulation<double, 3> aTriangulation;

  for (int i = 0; i < 10; ++i)
  {
    double x = static_cast<double>(i);
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.9, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.5, 0.9, 0.0));
    BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  BVH_QuickSorter<double, 3> aSorter(0);
  aSorter.Perform(&aTriangulation);

  for (int i = 0; i < 9; ++i)
  {
    EXPECT_LT(aTriangulation.Center(i, 0), aTriangulation.Center(i + 1, 0));
  }
}

TEST(BVH_QuickSorterTest, ReverseSorted)
{
  BVH_Triangulation<double, 3> aTriangulation;

  for (int i = 0; i < 10; ++i)
  {
    double x = static_cast<double>(9 - i);
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.9, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.5, 0.9, 0.0));
    BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  BVH_QuickSorter<double, 3> aSorter(0);
  aSorter.Perform(&aTriangulation);

  for (int i = 0; i < 9; ++i)
  {
    EXPECT_LT(aTriangulation.Center(i, 0), aTriangulation.Center(i + 1, 0));
  }
}

TEST(BVH_QuickSorterTest, DuplicateValues)
{
  BVH_Triangulation<double, 3> aTriangulation;

  for (int i = 0; i < 5; ++i)
  {
    double x = (i == 0 ? 1.0 : (i <= 3 ? 2.0 : 3.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.9, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.5, 0.9, 0.0));
    BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  BVH_QuickSorter<double, 3> aSorter(0);
  aSorter.Perform(&aTriangulation);

  for (int i = 0; i < 4; ++i)
  {
    EXPECT_LE(aTriangulation.Center(i, 0), aTriangulation.Center(i + 1, 0));
  }
}

TEST(BVH_QuickSorterTest, AllSameValue)
{
  BVH_Triangulation<double, 3> aTriangulation;

  for (int i = 0; i < 5; ++i)
  {
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.9, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.5, 0.9, 0.0));
    BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  BVH_QuickSorter<double, 3> aSorter(0);
  aSorter.Perform(&aTriangulation);

  for (int i = 0; i < 5; ++i)
  {
    EXPECT_NEAR(aTriangulation.Center(i, 0), 1.467, 1e-2);
  }
}

TEST(BVH_QuickSorterTest, LargeDataSet)
{
  BVH_Triangulation<double, 3> aTriangulation;

  for (int i = 0; i < 1000; ++i)
  {

    double x = static_cast<double>((i * 37) % 1000);
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.9, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.5, 0.9, 0.0));
    BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  BVH_QuickSorter<double, 3> aSorter(0);
  aSorter.Perform(&aTriangulation);

  for (int i = 0; i < 999; ++i)
  {
    EXPECT_LE(aTriangulation.Center(i, 0), aTriangulation.Center(i + 1, 0));
  }
}

TEST(BVH_QuickSorterTest, TwoElements)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(2.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(3.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(2.5, 1.0, 0.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.5, 1.0, 0.0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(3, 4, 5, 0));

  BVH_QuickSorter<double, 3> aSorter(0);
  aSorter.Perform(&aTriangulation);

  EXPECT_LT(aTriangulation.Center(0, 0), aTriangulation.Center(1, 0));
}
