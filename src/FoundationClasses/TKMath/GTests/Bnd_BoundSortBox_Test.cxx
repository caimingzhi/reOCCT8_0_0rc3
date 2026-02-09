

#include <gtest/gtest.h>

#include <Bnd_BoundSortBox.hpp>
#include <Bnd_Box.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <BRepBndLib.hpp>
#include <BRepPrimAPI_MakeBox.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <TopoDS_Shape.hpp>
#include <TopExp_Explorer.hpp>

#include <random>
#include <chrono>

static Bnd_Box CreateBox(const double xmin,
                         const double ymin,
                         const double zmin,
                         const double xmax,
                         const double ymax,
                         const double zmax)
{
  Bnd_Box box;
  box.Update(xmin, ymin, zmin, xmax, ymax, zmax);
  return box;
}

class Bnd_BoundSortBoxTest : public ::testing::Test
{
protected:
  void SetUp() override
  {

    mySmallBox           = CreateBox(0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    myLargeBox           = CreateBox(-10.0, -10.0, -10.0, 10.0, 10.0, 10.0);
    myOffsetBox          = CreateBox(5.0, 5.0, 5.0, 7.0, 7.0, 7.0);
    myNonIntersectingBox = CreateBox(20.0, 20.0, 20.0, 30.0, 30.0, 30.0);

    myBoxes = new NCollection_HArray1<Bnd_Box>(1, 4);
    myBoxes->SetValue(1, mySmallBox);
    myBoxes->SetValue(2, myLargeBox);
    myBoxes->SetValue(3, myOffsetBox);
    myBoxes->SetValue(4, myNonIntersectingBox);

    myGlobalBox = CreateBox(-20.0, -20.0, -20.0, 40.0, 40.0, 40.0);
  }

  Bnd_Box                                   mySmallBox;
  Bnd_Box                                   myLargeBox;
  Bnd_Box                                   myOffsetBox;
  Bnd_Box                                   myNonIntersectingBox;
  Bnd_Box                                   myGlobalBox;
  occ::handle<NCollection_HArray1<Bnd_Box>> myBoxes;
};

TEST_F(Bnd_BoundSortBoxTest, InitializeWithBoxes)
{
  Bnd_BoundSortBox sortBox;
  sortBox.Initialize(myBoxes);

  Bnd_Box                      testBox = CreateBox(0.5, 0.5, 0.5, 1.5, 1.5, 1.5);
  const NCollection_List<int>& result  = sortBox.Compare(testBox);

  EXPECT_EQ(2, result.Extent()) << "Expected to find 2 intersections";

  bool foundSmall = false;
  bool foundLarge = false;
  for (NCollection_List<int>::Iterator it(result); it.More(); it.Next())
  {
    if (it.Value() == 1)
      foundSmall = true;
    if (it.Value() == 2)
      foundLarge = true;
  }
  EXPECT_TRUE(foundSmall) << "Small box (index 1) should be in the result";
  EXPECT_TRUE(foundLarge) << "Large box (index 2) should be in the result";
}

TEST_F(Bnd_BoundSortBoxTest, InitializeWithEnclosingBox)
{
  Bnd_BoundSortBox sortBox;
  sortBox.Initialize(myGlobalBox, myBoxes);

  const NCollection_List<int>& result = sortBox.Compare(myOffsetBox);

  EXPECT_EQ(2, result.Extent()) << "Expected to find 2 intersections";

  bool foundLarge  = false;
  bool foundOffset = false;
  for (NCollection_List<int>::Iterator it(result); it.More(); it.Next())
  {
    if (it.Value() == 2)
      foundLarge = true;
    if (it.Value() == 3)
      foundOffset = true;
  }
  EXPECT_TRUE(foundLarge) << "Large box (index 2) should be in the result";
  EXPECT_TRUE(foundOffset) << "Offset box (index 3) should be in the result";
}

TEST_F(Bnd_BoundSortBoxTest, InitializeWithCount)
{
  Bnd_BoundSortBox sortBox;
  sortBox.Initialize(myGlobalBox, 3);

  sortBox.Add(mySmallBox, 1);
  sortBox.Add(myLargeBox, 2);
  sortBox.Add(myNonIntersectingBox, 3);

  Bnd_Box                      testBox = CreateBox(-5.0, -5.0, -5.0, -2.0, -2.0, -2.0);
  const NCollection_List<int>& result  = sortBox.Compare(testBox);

  EXPECT_EQ(1, result.Extent()) << "Expected to find 1 intersection";

  EXPECT_EQ(2, result.First()) << "Large box (index 2) should be the only result";
}

TEST_F(Bnd_BoundSortBoxTest, CompareWithPlane)
{
  Bnd_BoundSortBox sortBox;
  sortBox.Initialize(myBoxes);

  gp_Pnt point(0.0, 0.0, 9.0);
  gp_Dir direction(gp_Dir::D::Z);
  gp_Pln plane(point, direction);

  const NCollection_List<int>& result = sortBox.Compare(plane);

  EXPECT_EQ(1, result.Extent()) << "Expected to find 1 intersection";
  EXPECT_EQ(2, result.First()) << "Large box (index 2) should be the only result";
}

TEST_F(Bnd_BoundSortBoxTest, VoidBoxes)
{
  occ::handle<NCollection_HArray1<Bnd_Box>> boxes = new NCollection_HArray1<Bnd_Box>(1, 2);
  Bnd_Box                                   void_box;
  boxes->SetValue(1, void_box);
  boxes->SetValue(2, mySmallBox);

  Bnd_BoundSortBox sortBox;
  sortBox.Initialize(boxes);

  const NCollection_List<int>& result = sortBox.Compare(mySmallBox);

  EXPECT_EQ(1, result.Extent()) << "Expected to find 1 intersection";
  EXPECT_EQ(2, result.First()) << "Small box (index 2) should be the only result";

  const NCollection_List<int>& void_result = sortBox.Compare(void_box);
  EXPECT_EQ(0, void_result.Extent()) << "Expected to find 0 intersections with void box";
}

TEST_F(Bnd_BoundSortBoxTest, TouchingBoxes)
{

  Bnd_Box box1 = CreateBox(0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
  Bnd_Box box2 = CreateBox(1.0, 1.0, 1.0, 2.0, 2.0, 2.0);

  occ::handle<NCollection_HArray1<Bnd_Box>> boxes = new NCollection_HArray1<Bnd_Box>(1, 2);
  boxes->SetValue(1, box1);
  boxes->SetValue(2, box2);

  Bnd_BoundSortBox sortBox;
  sortBox.Initialize(boxes);

  const NCollection_List<int>& result1 = sortBox.Compare(box1);
  EXPECT_EQ(2, result1.Extent()) << "Expected to find 2 intersections";

  const NCollection_List<int>& result2 = sortBox.Compare(box2);
  EXPECT_EQ(2, result2.Extent()) << "Expected to find 2 intersections";
}

TEST_F(Bnd_BoundSortBoxTest, DisjointBoxes)
{
  Bnd_Box farBox = CreateBox(100.0, 100.0, 100.0, 110.0, 110.0, 110.0);

  occ::handle<NCollection_HArray1<Bnd_Box>> boxes = new NCollection_HArray1<Bnd_Box>(1, 2);
  boxes->SetValue(1, mySmallBox);
  boxes->SetValue(2, farBox);

  Bnd_Box enclosingBox = CreateBox(-10.0, -10.0, -10.0, 120.0, 120.0, 120.0);

  Bnd_BoundSortBox sortBox;
  sortBox.Initialize(enclosingBox, boxes);

  Bnd_Box                      testBox = CreateBox(0.5, 0.5, 0.5, 1.5, 1.5, 1.5);
  const NCollection_List<int>& result  = sortBox.Compare(testBox);

  EXPECT_EQ(1, result.Extent()) << "Expected to find 1 intersection";
  EXPECT_EQ(1, result.First()) << "Small box (index 1) should be the only result";
}

TEST_F(Bnd_BoundSortBoxTest, DegenerateBoxes)
{

  Bnd_Box pointBox;
  pointBox.Update(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

  Bnd_Box lineBox;
  lineBox.Update(2.0, 0.0, 0.0, 5.0, 0.0, 0.0);

  Bnd_Box planeBox;
  planeBox.Update(0.0, 0.0, 3.0, 3.0, 3.0, 3.0);

  occ::handle<NCollection_HArray1<Bnd_Box>> boxes = new NCollection_HArray1<Bnd_Box>(1, 3);
  boxes->SetValue(1, pointBox);
  boxes->SetValue(2, lineBox);
  boxes->SetValue(3, planeBox);

  Bnd_BoundSortBox sortBox;
  sortBox.Initialize(boxes);

  Bnd_Box                      testBox = CreateBox(0.0, 0.0, 0.0, 6.0, 6.0, 6.0);
  const NCollection_List<int>& result  = sortBox.Compare(testBox);

  EXPECT_EQ(3, result.Extent()) << "Expected to find 3 intersections with degenerate boxes";

  Bnd_Box                      pointTestBox = CreateBox(0.5, 0.5, 0.5, 1.5, 1.5, 1.5);
  const NCollection_List<int>& pointResult  = sortBox.Compare(pointTestBox);

  EXPECT_EQ(1, pointResult.Extent()) << "Expected to find only the point box";
  EXPECT_EQ(1, pointResult.First()) << "Point box (index 1) should be the only result";
}

TEST(Bnd_BoundSortBox_Test, BUC60729_InitializeWithFaceBoxes)
{

  TopoDS_Shape aShape = BRepPrimAPI_MakeBox(1.0, 1.0, 1.0).Solid();

  Bnd_Box aMainBox;
  BRepBndLib::Add(aShape, aMainBox);

  const int        aMaxNbrBox = 6;
  Bnd_BoundSortBox aBoundSortBox;
  aBoundSortBox.Initialize(aMainBox, aMaxNbrBox);

  TopExp_Explorer aExplorer(aShape, TopAbs_FACE);
  int             i;

  for (i = 1, aExplorer.ReInit(); aExplorer.More(); aExplorer.Next(), i++)
  {
    const TopoDS_Shape& aFace = aExplorer.Current();
    Bnd_Box             aBox;
    BRepBndLib::Add(aFace, aBox);
    aBoundSortBox.Add(aBox, i);
  }

  EXPECT_EQ(7, i) << "Expected to process 6 faces (i should be 7 after loop)";
}
