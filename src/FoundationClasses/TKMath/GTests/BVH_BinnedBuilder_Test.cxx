

#include <gtest/gtest.h>

#include <BVH_BinnedBuilder.hpp>
#include <BVH_BoxSet.hpp>
#include <Precision.hpp>

TEST(BVH_BinnedBuilderTest, DefaultConstructor)
{
  BVH_BinnedBuilder<double, 3> aBuilder;

  EXPECT_GT(aBuilder.LeafNodeSize(), 0);
  EXPECT_GT(aBuilder.MaxTreeDepth(), 0);
}

TEST(BVH_BinnedBuilderTest, CustomParameters)
{
  BVH_BinnedBuilder<double, 3> aBuilder(5, 20);

  EXPECT_EQ(aBuilder.LeafNodeSize(), 5);
  EXPECT_EQ(aBuilder.MaxTreeDepth(), 20);
}

TEST(BVH_BinnedBuilderTest, BuildEmptySet)
{
  opencascade::handle<BVH_BinnedBuilder<double, 3>> aBuilder = new BVH_BinnedBuilder<double, 3>();
  BVH_BoxSet<double, 3>                             aBoxSet(aBuilder);

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();
  EXPECT_EQ(aBVH->Length(), 0);
}

TEST(BVH_BinnedBuilderTest, BuildSingleElement)
{
  opencascade::handle<BVH_BinnedBuilder<double, 3>> aBuilder = new BVH_BinnedBuilder<double, 3>();
  BVH_BoxSet<double, 3>                             aBoxSet(aBuilder);

  aBoxSet.Add(0, BVH_Box<double, 3>(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(1.0, 1.0, 1.0)));
  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();
  EXPECT_EQ(aBVH->Length(), 1);
  EXPECT_TRUE(aBVH->IsOuter(0));
}

TEST(BVH_BinnedBuilderTest, BuildMultipleElements)
{
  opencascade::handle<BVH_BinnedBuilder<double, 3>> aBuilder =
    new BVH_BinnedBuilder<double, 3>(1, 32);
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

TEST(BVH_BinnedBuilderTest, SAHOptimization)
{
  opencascade::handle<BVH_BinnedBuilder<double, 3>> aBuilder =
    new BVH_BinnedBuilder<double, 3>(1, 32);
  BVH_BoxSet<double, 3> aBoxSet(aBuilder);

  for (int i = 0; i < 5; ++i)
  {
    BVH_Box<double, 3> aBox(BVH_Vec3d(i * 0.1, 0.0, 0.0), BVH_Vec3d(i * 0.1 + 0.1, 0.1, 0.1));
    aBoxSet.Add(i, aBox);
  }

  for (int i = 0; i < 5; ++i)
  {
    BVH_Box<double, 3> aBox(BVH_Vec3d(100.0 + i * 0.1, 0.0, 0.0),
                            BVH_Vec3d(100.0 + i * 0.1 + 0.1, 0.1, 0.1));
    aBoxSet.Add(i + 5, aBox);
  }

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();

  double aSAH = aBVH->EstimateSAH();
  EXPECT_GT(aSAH, 0.0);
}

TEST(BVH_BinnedBuilderTest, LeafNodeSizeRespected)
{
  const int                                         aLeafSize = 3;
  opencascade::handle<BVH_BinnedBuilder<double, 3>> aBuilder =
    new BVH_BinnedBuilder<double, 3>(aLeafSize, 32);
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

TEST(BVH_BinnedBuilderTest, BuildWithDifferentBinCounts)
{

  opencascade::handle<BVH_BinnedBuilder<double, 3, 16>> aBuilder16 =
    new BVH_BinnedBuilder<double, 3, 16>(1, 32);
  BVH_BoxSet<double, 3> aBoxSet(aBuilder16);

  for (int i = 0; i < 20; ++i)
  {
    BVH_Box<double, 3> aBox(BVH_Vec3d(i * 1.0, 0.0, 0.0), BVH_Vec3d(i * 1.0 + 0.5, 0.5, 0.5));
    aBoxSet.Add(i, aBox);
  }

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();
  EXPECT_GT(aBVH->Length(), 1);
}

TEST(BVH_BinnedBuilderTest, Build2D)
{
  opencascade::handle<BVH_BinnedBuilder<double, 2>> aBuilder =
    new BVH_BinnedBuilder<double, 2>(1, 32);
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

TEST(BVH_BinnedBuilderTest, RandomDistribution)
{
  opencascade::handle<BVH_BinnedBuilder<double, 3>> aBuilder =
    new BVH_BinnedBuilder<double, 3>(1, 32);
  BVH_BoxSet<double, 3> aBoxSet(aBuilder);

  int aCount = 0;
  for (int x = 0; x < 5; ++x)
  {
    for (int y = 0; y < 5; ++y)
    {
      for (int z = 0; z < 5; ++z)
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
  EXPECT_EQ(aTotalPrims, 125);
}

TEST(BVH_BinnedBuilderTest, CompareTreeQuality)
{

  opencascade::handle<BVH_BinnedBuilder<double, 3>> aBuilder1 =
    new BVH_BinnedBuilder<double, 3>(1, 32);
  opencascade::handle<BVH_BinnedBuilder<double, 3>> aBuilder4 =
    new BVH_BinnedBuilder<double, 3>(4, 32);

  BVH_BoxSet<double, 3> aBoxSet1(aBuilder1);
  BVH_BoxSet<double, 3> aBoxSet4(aBuilder4);

  for (int i = 0; i < 50; ++i)
  {
    BVH_Box<double, 3> aBox(BVH_Vec3d(i * 2.0, 0.0, 0.0), BVH_Vec3d(i * 2.0 + 1.0, 1.0, 1.0));
    aBoxSet1.Add(i, aBox);
    aBoxSet4.Add(i, aBox);
  }

  aBoxSet1.Build();
  aBoxSet4.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH1 = aBoxSet1.BVH();
  const opencascade::handle<BVH_Tree<double, 3>>& aBVH4 = aBoxSet4.BVH();

  EXPECT_GE(aBVH1->Depth(), aBVH4->Depth());
}

TEST(BVH_BinnedBuilderTest, MaxDepthRespected)
{
  const int                                         aMaxDepth = 5;
  opencascade::handle<BVH_BinnedBuilder<double, 3>> aBuilder =
    new BVH_BinnedBuilder<double, 3>(1, aMaxDepth);
  BVH_BoxSet<double, 3> aBoxSet(aBuilder);

  for (int i = 0; i < 100; ++i)
  {
    BVH_Box<double, 3> aBox(BVH_Vec3d(i * 2.0, 0.0, 0.0), BVH_Vec3d(i * 2.0 + 1.0, 1.0, 1.0));
    aBoxSet.Add(i, aBox);
  }

  aBoxSet.Build();

  const opencascade::handle<BVH_Tree<double, 3>>& aBVH = aBoxSet.BVH();
  EXPECT_LE(aBVH->Depth(), aMaxDepth);
}

TEST(BVH_BinnedBuilderTest, OverlappingBoxes)
{
  opencascade::handle<BVH_BinnedBuilder<double, 3>> aBuilder =
    new BVH_BinnedBuilder<double, 3>(1, 32);
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

TEST(BVH_BinnedBuilderTest, IdenticalBoxes)
{
  opencascade::handle<BVH_BinnedBuilder<double, 3>> aBuilder =
    new BVH_BinnedBuilder<double, 3>(1, 32);
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
