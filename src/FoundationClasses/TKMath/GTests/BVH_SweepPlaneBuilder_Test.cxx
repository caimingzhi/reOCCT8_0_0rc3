

#include <gtest/gtest.h>

#include <BVH_SweepPlaneBuilder.hpp>
#include <BVH_Triangulation.hpp>

template <class T, int N>
BVH_Box<T, N> ComputeSetBox(BVH_Set<T, N>* theSet)
{
  BVH_Box<T, N> aBox;
  const int     aSize = theSet->Size();
  for (int i = 0; i < aSize; ++i)
  {
    aBox.Combine(theSet->Box(i));
  }
  return aBox;
}

TEST(BVH_SweepPlaneBuilderTest, DefaultConstructor)
{
  BVH_SweepPlaneBuilder<double, 3> aBuilder;
  EXPECT_EQ(aBuilder.LeafNodeSize(), BVH_Constants_LeafNodeSizeDefault);
  EXPECT_EQ(aBuilder.MaxTreeDepth(), BVH_Constants_MaxTreeDepth);
}

TEST(BVH_SweepPlaneBuilderTest, CustomParameters)
{
  BVH_SweepPlaneBuilder<double, 3> aBuilder(5, 20, 1);
  EXPECT_EQ(aBuilder.LeafNodeSize(), 5);
  EXPECT_EQ(aBuilder.MaxTreeDepth(), 20);
}

TEST(BVH_SweepPlaneBuilderTest, BuildEmptyTriangulation)
{
  BVH_Triangulation<double, 3>     aTriangulation;
  BVH_SweepPlaneBuilder<double, 3> aBuilder;

  BVH_Tree<double, 3> aBVH;
  BVH_Box<double, 3>  aBox;

  aBuilder.Build(&aTriangulation, &aBVH, aBox);

  EXPECT_EQ(aBVH.Length(), 0);
}

TEST(BVH_SweepPlaneBuilderTest, BuildSingleTriangle)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 1.0, 0.0));

  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));

  BVH_SweepPlaneBuilder<double, 3> aBuilder(1, 32, 1);
  BVH_Tree<double, 3>              aBVH;
  BVH_Box<double, 3>               aBox = ComputeSetBox(&aTriangulation);

  aBuilder.Build(&aTriangulation, &aBVH, aBox);

  EXPECT_EQ(aBVH.Length(), 1);
  EXPECT_TRUE(aBVH.IsOuter(0));
  EXPECT_EQ(aBVH.BegPrimitive(0), 0);
  EXPECT_EQ(aBVH.EndPrimitive(0), 0);
}

TEST(BVH_SweepPlaneBuilderTest, BuildTwoTriangles)
{
  BVH_Triangulation<double, 3> aTriangulation;

  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 0.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(1.0, 1.0, 0.0));
  BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 1.0, 0.0));

  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 1, 2, 0));
  BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(0, 2, 3, 0));

  BVH_SweepPlaneBuilder<double, 3> aBuilder(1, 32, 1);
  BVH_Tree<double, 3>              aBVH;
  BVH_Box<double, 3>               aBox = ComputeSetBox(&aTriangulation);

  aBuilder.Build(&aTriangulation, &aBVH, aBox);

  EXPECT_GT(aBVH.Length(), 2);
  EXPECT_GE(aBVH.Depth(), 1);
}

TEST(BVH_SweepPlaneBuilderTest, BuildMultipleTriangles_Grid)
{
  BVH_Triangulation<double, 3> aTriangulation;

  const int aGridSize = 3;
  for (int i = 0; i < aGridSize; ++i)
  {
    for (int j = 0; j < aGridSize; ++j)
    {
      BVH::Array<double, 3>::Append(aTriangulation.Vertices,
                                    BVH_Vec3d(static_cast<double>(i), static_cast<double>(j), 0.0));
    }
  }

  for (int i = 0; i < aGridSize - 1; ++i)
  {
    for (int j = 0; j < aGridSize - 1; ++j)
    {
      int aV0 = i * aGridSize + j;
      int aV1 = i * aGridSize + (j + 1);
      int aV2 = (i + 1) * aGridSize + (j + 1);
      int aV3 = (i + 1) * aGridSize + j;

      BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(aV0, aV1, aV2, 0));
      BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(aV0, aV2, aV3, 0));
    }
  }

  BVH_SweepPlaneBuilder<double, 3> aBuilder(2, 32, 1);
  BVH_Tree<double, 3>              aBVH;
  BVH_Box<double, 3>               aBox = ComputeSetBox(&aTriangulation);

  aBuilder.Build(&aTriangulation, &aBVH, aBox);

  int aTotalTriangles = (aGridSize - 1) * (aGridSize - 1) * 2;
  EXPECT_GT(aBVH.Length(), 0);
  EXPECT_GE(aBVH.Depth(), 1);

  BVH_Box<double, 3> aRootBox(aBVH.MinPoint(0), aBVH.MaxPoint(0));
  for (int i = 0; i < aTotalTriangles; ++i)
  {
    BVH_Box<double, 3> aTriBox = aTriangulation.Box(i);
    EXPECT_FALSE(aRootBox.IsOut(aTriBox));
  }
}

TEST(BVH_SweepPlaneBuilderTest, SplitAlongDifferentAxes)
{
  BVH_Triangulation<double, 3> aTriangulation;

  for (int i = 0; i < 10; ++i)
  {
    double x = static_cast<double>(i) * 2.0;
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 1.0, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.5, 1.0, 0.0));

    BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  BVH_SweepPlaneBuilder<double, 3> aBuilder(1, 32, 1);
  BVH_Tree<double, 3>              aBVH;
  BVH_Box<double, 3>               aBox = ComputeSetBox(&aTriangulation);

  aBuilder.Build(&aTriangulation, &aBVH, aBox);

  EXPECT_GT(aBVH.Length(), 1);
  EXPECT_GE(aBVH.Depth(), 1);
}

TEST(BVH_SweepPlaneBuilderTest, DegenerateCase_AllSamePosition)
{
  BVH_Triangulation<double, 3> aTriangulation;

  for (int i = 0; i < 5; ++i)
  {
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.1, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(0.0, 0.1, 0.0));

    BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  BVH_SweepPlaneBuilder<double, 3> aBuilder(1, 32, 1);
  BVH_Tree<double, 3>              aBVH;
  BVH_Box<double, 3>               aBox = ComputeSetBox(&aTriangulation);

  aBuilder.Build(&aTriangulation, &aBVH, aBox);

  EXPECT_GT(aBVH.Length(), 0);
}

TEST(BVH_SweepPlaneBuilderTest, SAHQuality_VerifyBetter)
{
  BVH_Triangulation<double, 3> aTriangulation;

  for (int i = 0; i < 5; ++i)
  {
    double x = static_cast<double>(i) * 0.5;
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.4, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.2, 0.4, 0.0));
    BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  for (int i = 0; i < 5; ++i)
  {
    double x = 10.0 + static_cast<double>(i) * 0.5;
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.4, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.2, 0.4, 0.0));
    BVH::Array<int, 4>::Append(aTriangulation.Elements,
                               BVH_Vec4i((5 + i) * 3, (5 + i) * 3 + 1, (5 + i) * 3 + 2, 0));
  }

  BVH_SweepPlaneBuilder<double, 3> aBuilder(2, 32, 1);
  BVH_Tree<double, 3>              aBVH;
  BVH_Box<double, 3>               aBox = ComputeSetBox(&aTriangulation);

  aBuilder.Build(&aTriangulation, &aBVH, aBox);

  EXPECT_GE(aBVH.Depth(), 1);

  if (!aBVH.IsOuter(0))
  {
    int aLeftChild  = aBVH.template Child<0>(0);
    int aRightChild = aBVH.template Child<1>(0);

    BVH_Box<double, 3> aLeftBox(aBVH.MinPoint(aLeftChild), aBVH.MaxPoint(aLeftChild));
    BVH_Box<double, 3> aRightBox(aBVH.MinPoint(aRightChild), aBVH.MaxPoint(aRightChild));

    double aOverlap = 0.0;
    for (int i = 0; i < 3; ++i)
    {
      double aMin = std::max(aLeftBox.CornerMin()[i], aRightBox.CornerMin()[i]);
      double aMax = std::min(aLeftBox.CornerMax()[i], aRightBox.CornerMax()[i]);
      if (aMax > aMin)
      {
        aOverlap += (aMax - aMin);
      }
    }

    double aTotalSize = (aBox.CornerMax()[0] - aBox.CornerMin()[0]);
    EXPECT_LT(aOverlap, aTotalSize * 0.1);
  }
}

TEST(BVH_SweepPlaneBuilderTest, LeafSize_RespectMaxSize)
{
  BVH_Triangulation<double, 3> aTriangulation;

  for (int i = 0; i < 20; ++i)
  {
    double x = static_cast<double>(i);
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.9, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 0.5, 0.9, 0.0));
    BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  BVH_SweepPlaneBuilder<double, 3> aBuilder(5, 32, 1);
  BVH_Tree<double, 3>              aBVH;
  BVH_Box<double, 3>               aBox = ComputeSetBox(&aTriangulation);

  aBuilder.Build(&aTriangulation, &aBVH, aBox);

  for (int i = 0; i < aBVH.Length(); ++i)
  {
    if (aBVH.IsOuter(i))
    {
      int aLeafSize = aBVH.EndPrimitive(i) - aBVH.BegPrimitive(i) + 1;
      EXPECT_LE(aLeafSize, 5);
    }
  }
}
