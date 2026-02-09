

#include <Bnd_OBB.hpp>
#include <BRepBndLib.hpp>
#include <BRepPrimAPI_MakeBox.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

#include <gtest/gtest.h>

TEST(Bnd_OBB_Test, OCC33009_ReBuildWithPoints)
{
  Bnd_OBB aBndBox;

  NCollection_Array1<gp_Pnt> aPoints(1, 5);
  aPoints.ChangeValue(1) = gp_Pnt(1, 2, 3);
  aPoints.ChangeValue(2) = gp_Pnt(3, 2, 1);
  aPoints.ChangeValue(3) = gp_Pnt(2, 3, 1);
  aPoints.ChangeValue(4) = gp_Pnt(1, 3, 2);
  aPoints.ChangeValue(5) = gp_Pnt(2, 1, 3);

  EXPECT_NO_THROW(aBndBox.ReBuild(aPoints, (const NCollection_Array1<double>*)nullptr, true));
}

TEST(Bnd_OBB_Test, OCC30704_AddBoundingBoxToVoidBox)
{

  BRepPrimAPI_MakeBox aMkBox(gp_Pnt(100, 100, 100), 100, 100, 100);
  const TopoDS_Shape& aBox = aMkBox.Shape();

  Bnd_OBB aVoidBox, aOBB;
  BRepBndLib::AddOBB(aBox, aOBB, false, false, false);
  aVoidBox.Add(aOBB);

  const gp_XYZ& aCenter = aVoidBox.Center();
  EXPECT_DOUBLE_EQ(aCenter.X(), 150.0);
  EXPECT_DOUBLE_EQ(aCenter.Y(), 150.0);
  EXPECT_DOUBLE_EQ(aCenter.Z(), 150.0);
}

TEST(Bnd_OBB_Test, OCC30704_AddPointToVoidBox)
{

  gp_Pnt aP(100, 200, 300);

  Bnd_OBB aVoidBox;
  aVoidBox.Add(aP);

  const gp_XYZ& aCenter = aVoidBox.Center();
  EXPECT_DOUBLE_EQ(aCenter.X(), 100.0);
  EXPECT_DOUBLE_EQ(aCenter.Y(), 200.0);
  EXPECT_DOUBLE_EQ(aCenter.Z(), 300.0);
}
