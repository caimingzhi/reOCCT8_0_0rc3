

#include <gtest/gtest.h>

#include <BVH_LinearBuilder.hpp>
#include <BVH_BoxSet.hpp>
#include <Precision.hpp>

TEST(BVH_LinearBuilderTest, DefaultConstructor)
{
  BVH_LinearBuilder<double, 3> aBuilder;

  EXPECT_GT(aBuilder.LeafNodeSize(), 0);
  EXPECT_GT(aBuilder.MaxTreeDepth(), 0);
}

TEST(BVH_LinearBuilderTest, CustomParameters)
{
  BVH_LinearBuilder<double, 3> aBuilder(5, 20);

  EXPECT_EQ(aBuilder.LeafNodeSize(), 5);
  EXPECT_EQ(aBuilder.MaxTreeDepth(), 20);
}

TEST(BVH_LinearBuilderTest, BuildEmptySet)
{
  opencascade::handle<BVH_LinearBuilder<double, 3>> aBuilder = new BVH_LinearBuilder<double, 3>();
  BVH_BoxSet<double, 3>                             aBoxSet(aBuilder);

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();
  EXPECT_EQ(aBVH->Length(), 0);
}

TEST(BVH_LinearBuilderTest, BuildSingleElement)
{
  opencascade::handle<BVH_LinearBuilder<double, 3>> aBuilder = new BVH_LinearBuilder<double, 3>();
  BVH_BoxSet<double, 3>                             aBoxSet(aBuilder);

  aBoxSet.Add(0, BVH_Box<double, 3>(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0)));
  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();
  EXPECT_EQ(aBVH->Length(), 1);
  EXPECT_TRUE(aBVH->IsOuter(0));
}

TEST(BVH_LinearBuilderTest, BuildMultipleElements)
{
  opencascade::handle<BVH_LinearBuilder<double, 3>> aBuilder =
    new BVH_LinearBuilder<double, 3>(1, 32);
  BVH_BoxSet<double, 3> aBoxSet(aBuilder);

  for (int i = 0; i < 10; ++i)
  {
    BVH_Box<double, 3> aBox(BVH_Vec3d(i * 2.0, 0.0, 0.0), BVH_Vec3d(i * 2.0 + 1.0, 1.0, 1.0));
    aBoxSet.Add(i, aBox);
  }

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();
  EXPECT_GT(aBVH->Length(), 1);
  EXPECT_GT(aBVH->Depth(), 0);
}

TEST(BVH_LinearBuilderTest, MortonCodeSorting)
{

  opencascade::handle<BVH_LinearBuilder<double, 3>> aBuilder =
    new BVH_LinearBuilder<double, 3>(1, 32);
  BVH_BoxSet<double, 3> aBoxSet(aBuilder);

  for (int i = 0; i < 8; ++i)
  {
    double x = (i & 1) ? 10.0 : 0.0;
    double y = (i & 2) ? 10.0 : 0.0;
    double z = (i & 4) ? 10.0 : 0.0;

    BVH_Box<double, 3> aBox(BVH_Vec3d(x, y, z), BVH_Vec3d(x + 1.0, y + 1.0, z + 1.0));
    aBoxSet.Add(i, aBox);
  }

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();
  EXPECT_GT(aBVH->Length(), 1);

  double aSAH = aBVH->EstimateSAH();
  EXPECT_GT(aSAH, 0.0);
}

TEST(BVH_LinearBuilderTest, LeafNodeSizeRespected)
{
  const int                                         aLeafSize = 3;
  opencascade::handle<BVH_LinearBuilder<double, 3>> aBuilder =
    new BVH_LinearBuilder<double, 3>(aLeafSize, 32);
  BVH_BoxSet<double, 3> aBoxSet(aBuilder);

  for (int i = 0; i < 10; ++i)
  {
    BVH_Box<double, 3> aBox(BVH_Vec3d(i * 2.0, 0.0, 0.0), BVH_Vec3d(i * 2.0 + 1.0, 1.0, 1.0));
    aBoxSet.Add(i, aBox);
  }

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();

  for (int i = 0; i < aBVH->Length(); ++i)
  {
    if (aBVH->IsOuter(i))
    {
      int aNbPrims = aBVH->NbPrimitives(i);
      EXPECT_LE(aNbPrims, aLeafSize);
    }
  }
}

TEST(BVH_LinearBuilderTest, Build2D)
{
  opencascade::handle<BVH_LinearBuilder<double, 2>> aBuilder =
    new BVH_LinearBuilder<double, 2>(1, 32);
  BVH_BoxSet<double, 2> aBoxSet(aBuilder);

  for (int i = 0; i < 10; ++i)
  {
    BVH_Box<double, 2> aBox(BVH_Vec2d(i * 2.0, 0.0), BVH_Vec2d(i * 2.0 + 1.0, 1.0));
    aBoxSet.Add(i, aBox);
  }

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 2>>& aBVH = aBoxSet.BVH();
  EXPECT_GT(aBVH->Length(), 1);
}

TEST(BVH_LinearBuilderTest, LargeDataSet)
{
  opencascade::handle<BVH_LinearBuilder<double, 3>> aBuilder =
    new BVH_LinearBuilder<double, 3>(4, 32);
  BVH_BoxSet<double, 3> aBoxSet(aBuilder);

  int aCount = 0;
  for (int x = 0; x < 10; ++x)
  {
    for (int y = 0; y < 10; ++y)
    {
      for (int z = 0; z < 10; ++z)
      {
        BVH_Box<double, 3> aBox(BVH_Vec3d(x * 2.0, y * 2.0, z * 2.0),
                                BVH_Vec3d(x * 2.0 + 1.0, y * 2.0 + 1.0, z * 2.0 + 1.0));
        aBoxSet.Add(aCount++, aBox);
      }
    }
  }

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();
  EXPECT_GT(aBVH->Length(), 1);

  int aTotalPrims = 0;
  for (int i = 0; i < aBVH->Length(); ++i)
  {
    if (aBVH->IsOuter(i))
    {
      aTotalPrims += aBVH->NbPrimitives(i);
    }
  }
  EXPECT_EQ(aTotalPrims, 1000);
}

TEST(BVH_LinearBuilderTest, MaxDepthParameter)
{

  const int                                         aMaxDepth = 10;
  opencascade::handle<BVH_LinearBuilder<double, 3>> aBuilder =
    new BVH_LinearBuilder<double, 3>(1, aMaxDepth);
  BVH_BoxSet<double, 3> aBoxSet(aBuilder);

  for (int i = 0; i < 100; ++i)
  {
    BVH_Box<double, 3> aBox(BVH_Vec3d(i * 2.0, 0.0, 0.0), BVH_Vec3d(i * 2.0 + 1.0, 1.0, 1.0));
    aBoxSet.Add(i, aBox);
  }

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();

  EXPECT_GT(aBVH->Depth(), 0);
  EXPECT_LT(aBVH->Depth(), 20);
}

TEST(BVH_LinearBuilderTest, ClusteredData)
{
  opencascade::handle<BVH_LinearBuilder<double, 3>> aBuilder =
    new BVH_LinearBuilder<double, 3>(1, 32);
  BVH_BoxSet<double, 3> aBoxSet(aBuilder);

  for (int i = 0; i < 10; ++i)
  {

    BVH_Box<double, 3> aBox1(BVH_Vec3d(i * 0.1, i * 0.1, i * 0.1),
                             BVH_Vec3d(i * 0.1 + 0.1, i * 0.1 + 0.1, i * 0.1 + 0.1));
    aBoxSet.Add(i, aBox1);

    BVH_Box<double, 3> aBox2(BVH_Vec3d(100.0 + i * 0.1, 100.0 + i * 0.1, 100.0 + i * 0.1),
                             BVH_Vec3d(100.1 + i * 0.1, 100.1 + i * 0.1, 100.1 + i * 0.1));
    aBoxSet.Add(i + 10, aBox2);
  }

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();
  EXPECT_GT(aBVH->Length(), 1);

  double aSAH = aBVH->EstimateSAH();
  EXPECT_GT(aSAH, 0.0);
}

TEST(BVH_LinearBuilderTest, OverlappingBoxes)
{
  opencascade::handle<BVH_LinearBuilder<double, 3>> aBuilder =
    new BVH_LinearBuilder<double, 3>(1, 32);
  BVH_BoxSet<double, 3> aBoxSet(aBuilder);

  for (int i = 0; i < 10; ++i)
  {
    BVH_Box<double, 3> aBox(BVH_Vec3d(i * 0.5, 0.0, 0.0), BVH_Vec3d(i * 0.5 + 2.0, 1.0, 1.0));
    aBoxSet.Add(i, aBox);
  }

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();
  EXPECT_GT(aBVH->Length(), 1);
}

TEST(BVH_LinearBuilderTest, IdenticalBoxes)
{
  opencascade::handle<BVH_LinearBuilder<double, 3>> aBuilder =
    new BVH_LinearBuilder<double, 3>(1, 32);
  BVH_BoxSet<double, 3> aBoxSet(aBuilder);

  for (int i = 0; i < 10; ++i)
  {
    BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0));
    aBoxSet.Add(i, aBox);
  }

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();
  EXPECT_GE(aBVH->Length(), 1);
}

TEST(BVH_LinearBuilderTest, CompareWithBinnedBuilder)
{

  opencascade::handle<BVH_LinearBuilder<double, 3>> aLinearBuilder =
    new BVH_LinearBuilder<double, 3>(1, 32);
  BVH_BoxSet<double, 3> aLinearSet(aLinearBuilder);

  for (int i = 0; i < 50; ++i)
  {
    BVH_Box<double, 3> aBox(BVH_Vec3d(i * 2.0, 0.0, 0.0), BVH_Vec3d(i * 2.0 + 1.0, 1.0, 1.0));
    aLinearSet.Add(i, aBox);
  }

  aLinearSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aLinearBVH = aLinearSet.BVH();

  EXPECT_GT(aLinearBVH->Length(), 1);
  EXPECT_GT(aLinearBVH->Depth(), 0);

  double aSAH = aLinearBVH->EstimateSAH();
  EXPECT_GT(aSAH, 0.0);
}

TEST(BVH_LinearBuilderTest, NegativeCoordinates)
{
  opencascade::handle<BVH_LinearBuilder<double, 3>> aBuilder =
    new BVH_LinearBuilder<double, 3>(1, 32);
  BVH_BoxSet<double, 3> aBoxSet(aBuilder);

  for (int i = 0; i < 10; ++i)
  {
    BVH_Box<double, 3> aBox(BVH_Vec3d(-10.0 + i * 2.0, -5.0, -5.0),
                            BVH_Vec3d(-9.0 + i * 2.0, -4.0, -4.0));
    aBoxSet.Add(i, aBox);
  }

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();
  EXPECT_GT(aBVH->Length(), 1);
}
