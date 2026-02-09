

#include <gtest/gtest.h>

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <BRepBuilderAPI_Sewing.hpp>
#include <BRepPrimAPI_MakeBox.hpp>
#include <Geom_Plane.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <ShapeUpgrade_UnifySameDomain.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Wire.hpp>

TEST(ShapeUpgrade_UnifySameDomainTest, InternalEdgesTermination_Issue925)
{

  BRep_Builder aBuilder;

  gp_Pnt aP1(0, 0, 0);
  gp_Pnt aP2(10, 0, 0);
  gp_Pnt aP3(10, 10, 0);
  gp_Pnt aP4(0, 10, 0);

  BRepBuilderAPI_MakeEdge aME1(aP1, aP2);
  BRepBuilderAPI_MakeEdge aME2(aP2, aP3);
  BRepBuilderAPI_MakeEdge aME3(aP3, aP4);
  BRepBuilderAPI_MakeEdge aME4(aP4, aP1);

  BRepBuilderAPI_MakeWire aMW;
  aMW.Add(aME1.Edge());
  aMW.Add(aME2.Edge());
  aMW.Add(aME3.Edge());
  aMW.Add(aME4.Edge());

  ASSERT_TRUE(aMW.IsDone()) << "Failed to create outer wire";
  TopoDS_Wire anOuterWire = aMW.Wire();

  gp_Pln                  aPlane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  BRepBuilderAPI_MakeFace aMF(aPlane, anOuterWire);
  ASSERT_TRUE(aMF.IsDone()) << "Failed to create face";

  TopoDS_Face aFace = aMF.Face();

  gp_Pnt aIP1(2, 2, 0);
  gp_Pnt aIP2(5, 5, 0);
  gp_Pnt aIP3(8, 2, 0);

  BRepBuilderAPI_MakeEdge aMIE1(aIP1, aIP2);
  BRepBuilderAPI_MakeEdge aMIE2(aIP2, aIP3);

  ASSERT_TRUE(aMIE1.IsDone()) << "Failed to create internal edge 1";
  ASSERT_TRUE(aMIE2.IsDone()) << "Failed to create internal edge 2";

  BRepBuilderAPI_MakeWire aMIW;
  aMIW.Add(aMIE1.Edge());
  aMIW.Add(aMIE2.Edge());
  ASSERT_TRUE(aMIW.IsDone()) << "Failed to create internal wire";

  TopoDS_Wire anInternalWire = aMIW.Wire();

  anInternalWire.Orientation(TopAbs_INTERNAL);
  aBuilder.Add(aFace, anInternalWire);

  TopoDS_Shell aShell;
  aBuilder.MakeShell(aShell);
  aBuilder.Add(aShell, aFace);

  ShapeUpgrade_UnifySameDomain aUnifier(aShell);
  aUnifier.SetAngularTolerance(1e-6);
  aUnifier.SetLinearTolerance(1e-5);
  aUnifier.AllowInternalEdges(true);

  aUnifier.Build();

  const TopoDS_Shape& aResult = aUnifier.Shape();
  EXPECT_FALSE(aResult.IsNull()) << "UnifySameDomain result should not be null";

  int aFaceCount = 0;
  for (TopExp_Explorer anExp(aResult, TopAbs_FACE); anExp.More(); anExp.Next())
  {
    aFaceCount++;
  }
  EXPECT_GE(aFaceCount, 1) << "Result should contain at least one face";
}

TEST(ShapeUpgrade_UnifySameDomainTest, MultipleCoplanarFacesWithInternalWires)
{
  BRep_Builder aBuilder;

  gp_Pln aPlane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));

  gp_Pnt aP1(0, 0, 0);
  gp_Pnt aP2(5, 0, 0);
  gp_Pnt aP3(5, 10, 0);
  gp_Pnt aP4(0, 10, 0);

  BRepBuilderAPI_MakeWire aMW1;
  aMW1.Add(BRepBuilderAPI_MakeEdge(aP1, aP2).Edge());
  aMW1.Add(BRepBuilderAPI_MakeEdge(aP2, aP3).Edge());
  aMW1.Add(BRepBuilderAPI_MakeEdge(aP3, aP4).Edge());
  aMW1.Add(BRepBuilderAPI_MakeEdge(aP4, aP1).Edge());

  ASSERT_TRUE(aMW1.IsDone()) << "Failed to create wire 1";

  BRepBuilderAPI_MakeFace aMF1(aPlane, aMW1.Wire());
  ASSERT_TRUE(aMF1.IsDone()) << "Failed to create face 1";
  TopoDS_Face aFace1 = aMF1.Face();

  gp_Pnt aP5(5, 0, 0);
  gp_Pnt aP6(10, 0, 0);
  gp_Pnt aP7(10, 10, 0);
  gp_Pnt aP8(5, 10, 0);

  BRepBuilderAPI_MakeWire aMW2;
  aMW2.Add(BRepBuilderAPI_MakeEdge(aP5, aP6).Edge());
  aMW2.Add(BRepBuilderAPI_MakeEdge(aP6, aP7).Edge());
  aMW2.Add(BRepBuilderAPI_MakeEdge(aP7, aP8).Edge());
  aMW2.Add(BRepBuilderAPI_MakeEdge(aP8, aP5).Edge());

  ASSERT_TRUE(aMW2.IsDone()) << "Failed to create wire 2";

  BRepBuilderAPI_MakeFace aMF2(aPlane, aMW2.Wire());
  ASSERT_TRUE(aMF2.IsDone()) << "Failed to create face 2";
  TopoDS_Face aFace2 = aMF2.Face();

  gp_Pnt                  aIP1(1, 5, 0);
  gp_Pnt                  aIP2(4, 5, 0);
  BRepBuilderAPI_MakeWire aMIW1;
  aMIW1.Add(BRepBuilderAPI_MakeEdge(aIP1, aIP2).Edge());
  ASSERT_TRUE(aMIW1.IsDone()) << "Failed to create internal wire 1";
  TopoDS_Wire anInternalWire1 = aMIW1.Wire();
  anInternalWire1.Orientation(TopAbs_INTERNAL);
  aBuilder.Add(aFace1, anInternalWire1);

  gp_Pnt                  aIP3(6, 5, 0);
  gp_Pnt                  aIP4(9, 5, 0);
  BRepBuilderAPI_MakeWire aMIW2;
  aMIW2.Add(BRepBuilderAPI_MakeEdge(aIP3, aIP4).Edge());
  ASSERT_TRUE(aMIW2.IsDone()) << "Failed to create internal wire 2";
  TopoDS_Wire anInternalWire2 = aMIW2.Wire();
  anInternalWire2.Orientation(TopAbs_INTERNAL);
  aBuilder.Add(aFace2, anInternalWire2);

  BRepBuilderAPI_Sewing aSewer(1e-6);
  aSewer.Add(aFace1);
  aSewer.Add(aFace2);
  aSewer.Perform();

  TopoDS_Shape aSewedShape = aSewer.SewedShape();
  ASSERT_FALSE(aSewedShape.IsNull()) << "Sewing failed";

  ShapeUpgrade_UnifySameDomain aUnifier(aSewedShape);
  aUnifier.SetAngularTolerance(1e-6);
  aUnifier.SetLinearTolerance(1e-5);
  aUnifier.AllowInternalEdges(true);

  aUnifier.Build();

  const TopoDS_Shape& aResult = aUnifier.Shape();
  EXPECT_FALSE(aResult.IsNull()) << "UnifySameDomain result should not be null";

  int aFaceCount = 0;
  for (TopExp_Explorer anExp(aResult, TopAbs_FACE); anExp.More(); anExp.Next())
  {
    aFaceCount++;
  }

  EXPECT_EQ(aFaceCount, 1) << "Coplanar faces should be merged into one";
}

TEST(ShapeUpgrade_UnifySameDomainTest, ClosedInternalWire)
{
  BRep_Builder aBuilder;

  gp_Pnt aP1(0, 0, 0);
  gp_Pnt aP2(20, 0, 0);
  gp_Pnt aP3(20, 20, 0);
  gp_Pnt aP4(0, 20, 0);

  BRepBuilderAPI_MakeWire aMW;
  aMW.Add(BRepBuilderAPI_MakeEdge(aP1, aP2).Edge());
  aMW.Add(BRepBuilderAPI_MakeEdge(aP2, aP3).Edge());
  aMW.Add(BRepBuilderAPI_MakeEdge(aP3, aP4).Edge());
  aMW.Add(BRepBuilderAPI_MakeEdge(aP4, aP1).Edge());

  ASSERT_TRUE(aMW.IsDone()) << "Failed to create outer wire";

  gp_Pln                  aPlane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  BRepBuilderAPI_MakeFace aMF(aPlane, aMW.Wire());
  ASSERT_TRUE(aMF.IsDone()) << "Failed to create face";
  TopoDS_Face aFace = aMF.Face();

  gp_Pnt aIP1(5, 5, 0);
  gp_Pnt aIP2(15, 5, 0);
  gp_Pnt aIP3(10, 15, 0);

  BRepBuilderAPI_MakeWire aMIW;
  aMIW.Add(BRepBuilderAPI_MakeEdge(aIP1, aIP2).Edge());
  aMIW.Add(BRepBuilderAPI_MakeEdge(aIP2, aIP3).Edge());
  aMIW.Add(BRepBuilderAPI_MakeEdge(aIP3, aIP1).Edge());

  ASSERT_TRUE(aMIW.IsDone()) << "Failed to create internal wire";

  TopoDS_Wire anInternalWire = aMIW.Wire();
  anInternalWire.Orientation(TopAbs_INTERNAL);
  aBuilder.Add(aFace, anInternalWire);

  TopoDS_Shell aShell;
  aBuilder.MakeShell(aShell);
  aBuilder.Add(aShell, aFace);

  ShapeUpgrade_UnifySameDomain aUnifier(aShell);
  aUnifier.SetAngularTolerance(1e-6);
  aUnifier.SetLinearTolerance(1e-5);
  aUnifier.AllowInternalEdges(true);

  aUnifier.Build();

  const TopoDS_Shape& aResult = aUnifier.Shape();
  EXPECT_FALSE(aResult.IsNull()) << "UnifySameDomain result should not be null";
}

TEST(ShapeUpgrade_UnifySameDomainTest, BasicBoxUnification)
{

  BRepPrimAPI_MakeBox aBoxMaker(gp_Pnt(0, 0, 0), gp_Pnt(10, 10, 10));
  aBoxMaker.Build();
  ASSERT_TRUE(aBoxMaker.IsDone()) << "Failed to create box";

  TopoDS_Shape aBox = aBoxMaker.Shape();

  ShapeUpgrade_UnifySameDomain aUnifier(aBox);
  aUnifier.Build();

  const TopoDS_Shape& aResult = aUnifier.Shape();
  EXPECT_FALSE(aResult.IsNull()) << "UnifySameDomain result should not be null";

  int aFaceCount = 0;
  for (TopExp_Explorer anExp(aResult, TopAbs_FACE); anExp.More(); anExp.Next())
  {
    aFaceCount++;
  }
  EXPECT_EQ(aFaceCount, 6) << "Box should have 6 faces";
}
