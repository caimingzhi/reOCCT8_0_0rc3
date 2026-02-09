

#include <gtest/gtest.h>

#include <BVH_BinnedBuilder.hpp>
#include <BVH_Traverse.hpp>
#include <BVH_Triangulation.hpp>

#include <vector>

class BVH_CountAllElements : public BVH_Traverse<double, 3, void, double>
{
public:
  BVH_CountAllElements()
      : myAcceptedCount(0)
  {
  }

  bool RejectNode(const BVH_VecNt&, const BVH_VecNt&, double& theMetric) const override
  {
    theMetric = 0.0;
    return false;
  }

  bool Accept(const int, const double&) override
  {
    ++myAcceptedCount;
    return true;
  }

  int AcceptedCount() const { return myAcceptedCount; }

  void Reset() { myAcceptedCount = 0; }

private:
  mutable int myAcceptedCount;
};

class BVH_BoxSelector : public BVH_Traverse<double, 3, void, double>
{
public:
  BVH_BoxSelector(const BVH_Box<double, 3>& theBox)
      : myBox(theBox),
        myAcceptedCount(0)
  {
  }

  bool RejectNode(const BVH_VecNt& theMin,
                  const BVH_VecNt& theMax,
                  double&          theMetric) const override
  {

    theMetric = 0.0;
    return myBox.IsOut(theMin, theMax);
  }

  bool Accept(const int, const double&) override
  {
    ++myAcceptedCount;
    return true;
  }

  int AcceptedCount() const { return myAcceptedCount; }

  void Reset() { myAcceptedCount = 0; }

private:
  BVH_Box<double, 3> myBox;
  mutable int        myAcceptedCount;
};

class BVH_DistanceSelector : public BVH_Traverse<double, 3, void, double>
{
public:
  BVH_DistanceSelector(const BVH_Vec3d& thePoint, double theMaxDist)
      : myPoint(thePoint),
        myMaxDistSq(theMaxDist * theMaxDist),
        myMinDistSq(std::numeric_limits<double>::max()),
        myAcceptedCount(0),
        myClosestIndex(-1)
  {
  }

  bool RejectNode(const BVH_VecNt& theMin,
                  const BVH_VecNt& theMax,
                  double&          theMetric) const override
  {

    theMetric = PointBoxSquareDistance(myPoint, theMin, theMax);
    return theMetric > myMaxDistSq;
  }

  bool Accept(const int theIndex, const double& theMetric) override
  {
    ++myAcceptedCount;
    if (theMetric < myMinDistSq)
    {
      myMinDistSq    = theMetric;
      myClosestIndex = theIndex;
    }
    return true;
  }

  bool IsMetricBetter(const double& theLeft, const double& theRight) const override
  {
    return theLeft < theRight;
  }

  bool RejectMetric(const double& theMetric) const override { return theMetric > myMaxDistSq; }

  int AcceptedCount() const { return myAcceptedCount; }

  int ClosestIndex() const { return myClosestIndex; }

  double MinDistance() const { return std::sqrt(myMinDistSq); }

private:
  static double PointBoxSquareDistance(const BVH_Vec3d& thePoint,
                                       const BVH_Vec3d& theMin,
                                       const BVH_Vec3d& theMax)
  {
    double aDist = 0.0;
    for (int i = 0; i < 3; ++i)
    {
      if (thePoint[i] < theMin[i])
      {
        double d = theMin[i] - thePoint[i];
        aDist += d * d;
      }
      else if (thePoint[i] > theMax[i])
      {
        double d = thePoint[i] - theMax[i];
        aDist += d * d;
      }
    }
    return aDist;
  }

  BVH_Vec3d myPoint;
  double    myMaxDistSq;
  double    myMinDistSq;
  int       myAcceptedCount;
  int       myClosestIndex;
};

class BVH_LimitedSelector : public BVH_Traverse<double, 3, void, double>
{
public:
  BVH_LimitedSelector(int theMaxCount)
      : myMaxCount(theMaxCount),
        myAcceptedCount(0)
  {
  }

  bool RejectNode(const BVH_VecNt&, const BVH_VecNt&, double& theMetric) const override
  {
    theMetric = 0.0;
    return false;
  }

  bool Accept(const int, const double&) override
  {
    ++myAcceptedCount;
    return true;
  }

  bool Stop() const override { return myAcceptedCount >= myMaxCount; }

  int AcceptedCount() const { return myAcceptedCount; }

private:
  int myMaxCount;
  int myAcceptedCount;
};

class BVH_CountAllPairs : public BVH_PairTraverse<double, 3, void, double>
{
public:
  BVH_CountAllPairs()
      : myAcceptedCount(0)
  {
  }

  bool RejectNode(const BVH_VecNt&,
                  const BVH_VecNt&,
                  const BVH_VecNt&,
                  const BVH_VecNt&,
                  double& theMetric) const override
  {
    theMetric = 0.0;
    return false;
  }

  bool Accept(const int, const int) override
  {
    ++myAcceptedCount;
    return true;
  }

  int AcceptedCount() const { return myAcceptedCount; }

private:
  mutable int myAcceptedCount;
};

class BVH_OverlapDetector : public BVH_PairTraverse<double, 3, void, double>
{
public:
  BVH_OverlapDetector()
      : myOverlapCount(0),
        myRejectCount(0)
  {
  }

  bool RejectNode(const BVH_VecNt& theMin1,
                  const BVH_VecNt& theMax1,
                  const BVH_VecNt& theMin2,
                  const BVH_VecNt& theMax2,
                  double&          theMetric) const override
  {
    ++myRejectCount;
    theMetric = 0.0;

    BVH_Box<double, 3> aBox1(theMin1, theMax1);
    bool               isOut = aBox1.IsOut(theMin2, theMax2);
    return isOut;
  }

  bool Accept(const int, const int) override
  {

    ++myOverlapCount;
    return true;
  }

  int OverlapCount() const { return myOverlapCount; }

  int RejectCount() const { return myRejectCount; }

private:
  mutable int myOverlapCount;
  mutable int myRejectCount;
};

opencascade::handle<BVH_Tree<double, 3>> CreateSimpleTriangulationBVH(int theNumTriangles)
{
  BVH_Triangulation<double, 3> aTriangulation;

  for (int i = 0; i < theNumTriangles; ++i)
  {
    double x = static_cast<double>(i * 2);
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 1.0, 1.0, 0.0));
    BVH::Array<double, 3>::Append(aTriangulation.Vertices, BVH_Vec3d(x + 2.0, 0.0, 0.0));
    BVH::Array<int, 4>::Append(aTriangulation.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  opencascade::handle<BVH_Tree<double, 3>> aBVH = new BVH_Tree<double, 3>;
  BVH_BinnedBuilder<double, 3>             aBuilder;
  aBuilder.Build(&aTriangulation, aBVH.get(), aTriangulation.Box());

  return aBVH;
}

TEST(BVH_TraverseTest, CountAllElements)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH = CreateSimpleTriangulationBVH(10);

  BVH_CountAllElements aSelector;
  int                  aCount = aSelector.Select(aBVH);

  EXPECT_EQ(aCount, 10);
  EXPECT_EQ(aSelector.AcceptedCount(), 10);
}

TEST(BVH_TraverseTest, EmptyTree)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH = new BVH_Tree<double, 3>;

  BVH_CountAllElements aSelector;
  int                  aCount = aSelector.Select(aBVH);

  EXPECT_EQ(aCount, 0);
}

TEST(BVH_TraverseTest, NullTree)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH;

  BVH_CountAllElements aSelector;
  int                  aCount = aSelector.Select(aBVH);

  EXPECT_EQ(aCount, 0);
}

TEST(BVH_TraverseTest, BoxSelection)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH = CreateSimpleTriangulationBVH(10);

  BVH_Box<double, 3> aBox(BVH_Vec3d(0.0, 0.0, -1.0), BVH_Vec3d(10.0, 2.0, 1.0));
  BVH_BoxSelector    aSelector(aBox);
  int                aCount = aSelector.Select(aBVH);

  EXPECT_GT(aCount, 0);
  EXPECT_LT(aCount, 10);
}

TEST(BVH_TraverseTest, EmptyBoxSelection)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH = CreateSimpleTriangulationBVH(10);

  BVH_Box<double, 3> aBox(BVH_Vec3d(100.0, 100.0, 100.0), BVH_Vec3d(200.0, 200.0, 200.0));
  BVH_BoxSelector    aSelector(aBox);
  int                aCount = aSelector.Select(aBVH);

  EXPECT_EQ(aCount, 0);
}

TEST(BVH_TraverseTest, FullBoxSelection)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH = CreateSimpleTriangulationBVH(10);

  BVH_Box<double, 3> aBox(BVH_Vec3d(-100.0, -100.0, -100.0), BVH_Vec3d(100.0, 100.0, 100.0));
  BVH_BoxSelector    aSelector(aBox);
  int                aCount = aSelector.Select(aBVH);

  EXPECT_EQ(aCount, 10);
}

TEST(BVH_TraverseTest, DistanceBasedSelection)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH = CreateSimpleTriangulationBVH(10);

  BVH_Vec3d            aPoint(5.0, 0.5, 0.0);
  double               aMaxDist = 5.0;
  BVH_DistanceSelector aSelector(aPoint, aMaxDist);
  int                  aCount = aSelector.Select(aBVH);

  EXPECT_GT(aCount, 0);
  EXPECT_LE(aCount, 10);
  EXPECT_GE(aSelector.ClosestIndex(), 0);
  EXPECT_LT(aSelector.ClosestIndex(), 10);
}

TEST(BVH_TraverseTest, EarlyTermination)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH = CreateSimpleTriangulationBVH(100);

  BVH_LimitedSelector aSelector(5);
  int                 aCount = aSelector.Select(aBVH);

  EXPECT_EQ(aCount, 5);
  EXPECT_EQ(aSelector.AcceptedCount(), 5);
}

TEST(BVH_TraverseTest, LargeDataSet)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH = CreateSimpleTriangulationBVH(1000);

  BVH_CountAllElements aSelector;
  int                  aCount = aSelector.Select(aBVH);

  EXPECT_EQ(aCount, 1000);
}

TEST(BVH_TraverseTest, MetricBasedPruning)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH = CreateSimpleTriangulationBVH(50);

  BVH_Vec3d            aPoint(1000.0, 1000.0, 1000.0);
  double               aMaxDist = 1.0;
  BVH_DistanceSelector aSelector(aPoint, aMaxDist);
  int                  aCount = aSelector.Select(aBVH);

  EXPECT_EQ(aCount, 0);
}

TEST(BVH_PairTraverseTest, IsOutVerification)
{

  BVH_Box<double, 3> aBox1(BVH_Vec3d(0.0, 0.0, 0.0), BVH_Vec3d(3.0, 1.0, 0.0));
  BVH_Box<double, 3> aBox2(BVH_Vec3d(100.0, 0.0, 0.0), BVH_Vec3d(103.0, 1.0, 0.0));

  EXPECT_TRUE(aBox1.IsOut(aBox2.CornerMin(), aBox2.CornerMax()));
  EXPECT_TRUE(aBox2.IsOut(aBox1.CornerMin(), aBox1.CornerMax()));
}

TEST(BVH_PairTraverseTest, TriangulationBoxVerification)
{

  BVH_Triangulation<double, 3> aTri1, aTri2;

  for (int i = 0; i < 3; ++i)
  {
    double x = static_cast<double>(i);
    BVH::Array<double, 3>::Append(aTri1.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTri1.Vertices, BVH_Vec3d(x + 0.5, 1.0, 0.0));
    BVH::Array<double, 3>::Append(aTri1.Vertices, BVH_Vec3d(x + 1.0, 0.0, 0.0));
    BVH::Array<int, 4>::Append(aTri1.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  for (int i = 0; i < 3; ++i)
  {
    double x = 100.0 + static_cast<double>(i);
    BVH::Array<double, 3>::Append(aTri2.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTri2.Vertices, BVH_Vec3d(x + 0.5, 1.0, 0.0));
    BVH::Array<double, 3>::Append(aTri2.Vertices, BVH_Vec3d(x + 1.0, 0.0, 0.0));
    BVH::Array<int, 4>::Append(aTri2.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  aTri1.MarkDirty();
  aTri2.MarkDirty();

  BVH_Box<double, 3> aBox1 = aTri1.Box();
  BVH_Box<double, 3> aBox2 = aTri2.Box();

  EXPECT_TRUE(aBox1.IsValid());
  EXPECT_TRUE(aBox2.IsValid());

  EXPECT_NEAR(aBox1.CornerMin().x(), 0.0, 0.01);
  EXPECT_NEAR(aBox1.CornerMax().x(), 3.0, 0.01);

  EXPECT_NEAR(aBox2.CornerMin().x(), 100.0, 0.01);
  EXPECT_NEAR(aBox2.CornerMax().x(), 103.0, 0.01);

  EXPECT_TRUE(aBox1.IsOut(aBox2));
  EXPECT_TRUE(aBox2.IsOut(aBox1));
}

TEST(BVH_PairTraverseTest, BVHRootBoxVerification)
{

  BVH_Triangulation<double, 3> aTri1, aTri2;

  for (int i = 0; i < 3; ++i)
  {
    double x = static_cast<double>(i);
    BVH::Array<double, 3>::Append(aTri1.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTri1.Vertices, BVH_Vec3d(x + 0.5, 1.0, 0.0));
    BVH::Array<double, 3>::Append(aTri1.Vertices, BVH_Vec3d(x + 1.0, 0.0, 0.0));
    BVH::Array<int, 4>::Append(aTri1.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  for (int i = 0; i < 3; ++i)
  {
    double x = 100.0 + static_cast<double>(i);
    BVH::Array<double, 3>::Append(aTri2.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTri2.Vertices, BVH_Vec3d(x + 0.5, 1.0, 0.0));
    BVH::Array<double, 3>::Append(aTri2.Vertices, BVH_Vec3d(x + 1.0, 0.0, 0.0));
    BVH::Array<int, 4>::Append(aTri2.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  aTri1.MarkDirty();
  aTri2.MarkDirty();

  opencascade::handle<BVH_Tree<double, 3>> aBVH1 = new BVH_Tree<double, 3>;
  opencascade::handle<BVH_Tree<double, 3>> aBVH2 = new BVH_Tree<double, 3>;

  BVH_BinnedBuilder<double, 3> aBuilder;
  aBuilder.Build(&aTri1, aBVH1.get(), aTri1.Box());
  aBuilder.Build(&aTri2, aBVH2.get(), aTri2.Box());

  BVH_Vec3d aMin1 = aBVH1->MinPoint(0);
  BVH_Vec3d aMax1 = aBVH1->MaxPoint(0);
  BVH_Vec3d aMin2 = aBVH2->MinPoint(0);
  BVH_Vec3d aMax2 = aBVH2->MaxPoint(0);

  EXPECT_NEAR(aMin1.x(), 0.0, 0.01);
  EXPECT_NEAR(aMax1.x(), 3.0, 0.01);
  EXPECT_NEAR(aMin2.x(), 100.0, 0.01);
  EXPECT_NEAR(aMax2.x(), 103.0, 0.01);

  BVH_Box<double, 3> aBox1(aMin1, aMax1);
  EXPECT_TRUE(aBox1.IsOut(aMin2, aMax2));

  const BVH_Vec4i& aData1 = aBVH1->NodeInfoBuffer()[0];
  const BVH_Vec4i& aData2 = aBVH2->NodeInfoBuffer()[0];

  EXPECT_EQ(aData1.x(), 1) << "Root of BVH1 should be a leaf node (3 elements)";
  EXPECT_EQ(aData2.x(), 1) << "Root of BVH2 should be a leaf node (3 elements)";
}

TEST(BVH_PairTraverseTest, CountAllPairs)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH1 = CreateSimpleTriangulationBVH(5);
  opencascade::handle<BVH_Tree<double, 3>> aBVH2 = CreateSimpleTriangulationBVH(5);

  BVH_CountAllPairs aSelector;
  int               aCount = aSelector.Select(aBVH1, aBVH2);

  EXPECT_EQ(aCount, 25);
}

TEST(BVH_PairTraverseTest, EmptyFirstTree)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH1 = new BVH_Tree<double, 3>;
  opencascade::handle<BVH_Tree<double, 3>> aBVH2 = CreateSimpleTriangulationBVH(5);

  BVH_CountAllPairs aSelector;
  int               aCount = aSelector.Select(aBVH1, aBVH2);

  EXPECT_EQ(aCount, 0);
}

TEST(BVH_PairTraverseTest, EmptySecondTree)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH1 = CreateSimpleTriangulationBVH(5);
  opencascade::handle<BVH_Tree<double, 3>> aBVH2 = new BVH_Tree<double, 3>;

  BVH_CountAllPairs aSelector;
  int               aCount = aSelector.Select(aBVH1, aBVH2);

  EXPECT_EQ(aCount, 0);
}

TEST(BVH_PairTraverseTest, NullTrees)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH1;
  opencascade::handle<BVH_Tree<double, 3>> aBVH2;

  BVH_CountAllPairs aSelector;
  int               aCount = aSelector.Select(aBVH1, aBVH2);

  EXPECT_EQ(aCount, 0);
}

TEST(BVH_PairTraverseTest, OverlapDetection_SameTrees)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH = CreateSimpleTriangulationBVH(10);

  BVH_OverlapDetector aSelector;
  int                 aCount = aSelector.Select(aBVH, aBVH);

  EXPECT_GE(aCount, 10);
}

TEST(BVH_PairTraverseTest, OverlapDetection_NonOverlapping)
{

  BVH_Triangulation<double, 3> aTri1, aTri2;

  for (int i = 0; i < 3; ++i)
  {
    double x = static_cast<double>(i);
    BVH::Array<double, 3>::Append(aTri1.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTri1.Vertices, BVH_Vec3d(x + 0.5, 1.0, 0.0));
    BVH::Array<double, 3>::Append(aTri1.Vertices, BVH_Vec3d(x + 1.0, 0.0, 0.0));
    BVH::Array<int, 4>::Append(aTri1.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  for (int i = 0; i < 3; ++i)
  {
    double x = 100.0 + static_cast<double>(i);
    BVH::Array<double, 3>::Append(aTri2.Vertices, BVH_Vec3d(x, 0.0, 0.0));
    BVH::Array<double, 3>::Append(aTri2.Vertices, BVH_Vec3d(x + 0.5, 1.0, 0.0));
    BVH::Array<double, 3>::Append(aTri2.Vertices, BVH_Vec3d(x + 1.0, 0.0, 0.0));
    BVH::Array<int, 4>::Append(aTri2.Elements, BVH_Vec4i(i * 3, i * 3 + 1, i * 3 + 2, 0));
  }

  aTri1.MarkDirty();
  aTri2.MarkDirty();

  opencascade::handle<BVH_Tree<double, 3>> aBVH1 = new BVH_Tree<double, 3>;
  opencascade::handle<BVH_Tree<double, 3>> aBVH2 = new BVH_Tree<double, 3>;

  BVH_BinnedBuilder<double, 3> aBuilder;
  aBuilder.Build(&aTri1, aBVH1.get(), aTri1.Box());
  aBuilder.Build(&aTri2, aBVH2.get(), aTri2.Box());

  BVH_OverlapDetector aSelector;
  int                 aCount = aSelector.Select(aBVH1, aBVH2);

  EXPECT_GT(aSelector.RejectCount(), 0) << "RejectNode should be called at least once";

  EXPECT_EQ(aCount, 0) << "Found " << aCount << " overlaps (RejectNode called "
                       << aSelector.RejectCount() << " times)";
}

TEST(BVH_PairTraverseTest, AsymmetricPairs)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH1 = CreateSimpleTriangulationBVH(3);
  opencascade::handle<BVH_Tree<double, 3>> aBVH2 = CreateSimpleTriangulationBVH(7);

  BVH_CountAllPairs aSelector;
  int               aCount = aSelector.Select(aBVH1, aBVH2);

  EXPECT_EQ(aCount, 21);
}

TEST(BVH_PairTraverseTest, LargeDataSets)
{
  opencascade::handle<BVH_Tree<double, 3>> aBVH1 = CreateSimpleTriangulationBVH(50);
  opencascade::handle<BVH_Tree<double, 3>> aBVH2 = CreateSimpleTriangulationBVH(50);

  BVH_CountAllPairs aSelector;
  int               aCount = aSelector.Select(aBVH1, aBVH2);

  EXPECT_EQ(aCount, 2500);
}
