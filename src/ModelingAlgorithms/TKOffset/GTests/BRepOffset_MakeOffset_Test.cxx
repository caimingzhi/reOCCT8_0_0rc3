

#include <gtest/gtest.h>

#include <BRepOffsetAPI_MakeThickSolid.hpp>
#include <BRepOffsetAPI_ThruSections.hpp>
#include <BRepOffset_MakeOffset.hpp>
#include <BRepOffset_Error.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <BRepBuilderAPI_MakePolygon.hpp>
#include <BRepPrimAPI_MakeBox.hpp>
#include <BRepPrimAPI_MakeCylinder.hpp>
#include <BRepPrimAPI_MakeSphere.hpp>
#include <BRepCheck_Analyzer.hpp>
#include <BRepAlgoAPI_Fuse.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAPI_PointsToBSpline.hpp>
#include <gp_Ax2.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Wire.hpp>
#include <TopExp_Explorer.hpp>
#include <NCollection_List.hpp>

static TopoDS_Wire MakeCircularWire(const gp_Pnt& theCenter,
                                    const gp_Dir& theNormal,
                                    double        theRadius)
{
  gp_Ax2  anAxis(theCenter, theNormal);
  gp_Circ aCirc(anAxis, theRadius);

  BRepBuilderAPI_MakeEdge anEdgeMaker(aCirc);
  if (!anEdgeMaker.IsDone())
  {
    return TopoDS_Wire();
  }

  BRepBuilderAPI_MakeWire aWireMaker(anEdgeMaker.Edge());
  if (!aWireMaker.IsDone())
  {
    return TopoDS_Wire();
  }

  return aWireMaker.Wire();
}

static TopoDS_Wire MakeRectangularWire(const gp_Pnt& theCenter,
                                       const gp_Dir& theNormal,
                                       double        theWidth,
                                       double        theHeight)
{

  gp_Ax2 anAxis(theCenter, theNormal);
  gp_Dir aXDir = anAxis.XDirection();
  gp_Dir aYDir = anAxis.YDirection();

  double aHalfW = theWidth / 2.0;
  double aHalfH = theHeight / 2.0;

  gp_Pnt aP1 = theCenter.Translated(gp_Vec(aXDir) * (-aHalfW) + gp_Vec(aYDir) * (-aHalfH));
  gp_Pnt aP2 = theCenter.Translated(gp_Vec(aXDir) * (aHalfW) + gp_Vec(aYDir) * (-aHalfH));
  gp_Pnt aP3 = theCenter.Translated(gp_Vec(aXDir) * (aHalfW) + gp_Vec(aYDir) * (aHalfH));
  gp_Pnt aP4 = theCenter.Translated(gp_Vec(aXDir) * (-aHalfW) + gp_Vec(aYDir) * (aHalfH));

  BRepBuilderAPI_MakeWire aWireMaker;
  aWireMaker.Add(BRepBuilderAPI_MakeEdge(aP1, aP2).Edge());
  aWireMaker.Add(BRepBuilderAPI_MakeEdge(aP2, aP3).Edge());
  aWireMaker.Add(BRepBuilderAPI_MakeEdge(aP3, aP4).Edge());
  aWireMaker.Add(BRepBuilderAPI_MakeEdge(aP4, aP1).Edge());

  if (!aWireMaker.IsDone())
  {
    return TopoDS_Wire();
  }

  return aWireMaker.Wire();
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_CircleToRectangleLoft)
{

  gp_Pnt aCircleCenter(0, 0, 0);
  gp_Dir aNormal(0, 0, 1);
  double aRadius = 50.0;

  TopoDS_Wire aCircleWire = MakeCircularWire(aCircleCenter, aNormal, aRadius);
  ASSERT_FALSE(aCircleWire.IsNull()) << "Failed to create circular wire";

  gp_Pnt aRectCenter(0, 0, 100);
  double aWidth  = 80.0;
  double aHeight = 60.0;

  TopoDS_Wire aRectWire = MakeRectangularWire(aRectCenter, aNormal, aWidth, aHeight);
  ASSERT_FALSE(aRectWire.IsNull()) << "Failed to create rectangular wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, false);
  aLoftMaker.AddWire(aCircleWire);
  aLoftMaker.AddWire(aRectWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();
  ASSERT_FALSE(aLoftShape.IsNull()) << "Loft shape is null";

  BRepCheck_Analyzer aChecker(aLoftShape);
  EXPECT_TRUE(aChecker.IsValid()) << "Loft shape is not valid";

  double                         anOffset = 2.0;
  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   anOffset,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone())
    << "ThickSolid operation failed. This may be a regression from commit 44be1230391 "
    << "where CheckMixedContinuity incorrectly flags valid loft geometry as having "
    << "mixed connectivity.";

  if (aThickMaker.IsDone())
  {
    TopoDS_Shape aThickShape = aThickMaker.Shape();

    if (!aThickShape.IsNull())
    {
      BRepCheck_Analyzer aThickChecker(aThickShape);
      EXPECT_TRUE(aThickChecker.IsValid()) << "Thick solid shape is not valid";
    }
  }
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_CircleToRectangleLoft_IntersectionMode)
{

  gp_Pnt aCircleCenter(0, 0, 0);
  gp_Dir aNormal(0, 0, 1);
  double aRadius = 50.0;

  TopoDS_Wire aCircleWire = MakeCircularWire(aCircleCenter, aNormal, aRadius);
  ASSERT_FALSE(aCircleWire.IsNull()) << "Failed to create circular wire";

  gp_Pnt aRectCenter(0, 0, 100);
  double aWidth  = 80.0;
  double aHeight = 60.0;

  TopoDS_Wire aRectWire = MakeRectangularWire(aRectCenter, aNormal, aWidth, aHeight);
  ASSERT_FALSE(aRectWire.IsNull()) << "Failed to create rectangular wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, false);
  aLoftMaker.AddWire(aCircleWire);
  aLoftMaker.AddWire(aRectWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();
  ASSERT_FALSE(aLoftShape.IsNull()) << "Loft shape is null";

  double                         anOffset = 2.0;
  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   anOffset,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   true,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone()) << "ThickSolid operation with intersection mode failed. "
                                    << "This may be a regression from commit 44be1230391.";

  if (aThickMaker.IsDone())
  {
    TopoDS_Shape aThickShape = aThickMaker.Shape();

    if (!aThickShape.IsNull())
    {
      BRepCheck_Analyzer aThickChecker(aThickShape);
      EXPECT_TRUE(aThickChecker.IsValid()) << "Thick solid shape is not valid";
    }
  }
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_SimpleBox_Baseline)
{

  gp_Pnt aCenter(0, 0, 0);
  gp_Dir aNormal(0, 0, 1);

  TopoDS_Wire aWire = MakeRectangularWire(aCenter, aNormal, 100.0, 100.0);
  ASSERT_FALSE(aWire.IsNull()) << "Failed to create rectangular wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, true);

  gp_Pnt      aTopCenter(0, 0, 50);
  TopoDS_Wire aTopWire = MakeRectangularWire(aTopCenter, aNormal, 100.0, 100.0);
  ASSERT_FALSE(aTopWire.IsNull()) << "Failed to create top wire";

  aLoftMaker.AddWire(aWire);
  aLoftMaker.AddWire(aTopWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create ruled solid";

  TopoDS_Shape aShape = aLoftMaker.Shape();

  double                         anOffset = 2.0;
  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aShape,
                                   aFacesToRemove,
                                   anOffset,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone()) << "ThickSolid on simple ruled solid failed";

  if (aThickMaker.IsDone())
  {
    TopoDS_Shape aThickShape = aThickMaker.Shape();
    EXPECT_FALSE(aThickShape.IsNull()) << "Thick solid shape is null";
  }
}

static TopoDS_Wire MakeEllipticalWire(const gp_Pnt& theCenter,
                                      const gp_Dir& theNormal,
                                      double        theMajorRadius,
                                      double        theMinorRadius)
{
  gp_Ax2   anAxis(theCenter, theNormal);
  gp_Elips anEllipse(anAxis, theMajorRadius, theMinorRadius);

  BRepBuilderAPI_MakeEdge anEdgeMaker(anEllipse);
  if (!anEdgeMaker.IsDone())
  {
    return TopoDS_Wire();
  }

  BRepBuilderAPI_MakeWire aWireMaker(anEdgeMaker.Edge());
  if (!aWireMaker.IsDone())
  {
    return TopoDS_Wire();
  }

  return aWireMaker.Wire();
}

static TopoDS_Wire MakePolygonalWire(const gp_Pnt& theCenter,
                                     const gp_Dir& theNormal,
                                     double        theRadius,
                                     int           theNbSides)
{
  gp_Ax2 anAxis(theCenter, theNormal);
  gp_Dir aXDir = anAxis.XDirection();
  gp_Dir aYDir = anAxis.YDirection();

  BRepBuilderAPI_MakePolygon aPolygon;

  for (int i = 0; i <= theNbSides; ++i)
  {
    double anAngle = 2.0 * M_PI * i / theNbSides;
    gp_Pnt aPnt    = theCenter.Translated(gp_Vec(aXDir) * theRadius * cos(anAngle)
                                       + gp_Vec(aYDir) * theRadius * sin(anAngle));
    aPolygon.Add(aPnt);
  }

  aPolygon.Close();

  if (!aPolygon.IsDone())
  {
    return TopoDS_Wire();
  }

  return aPolygon.Wire();
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_CircleToEllipseLoft)
{
  gp_Pnt aCircleCenter(0, 0, 0);
  gp_Dir aNormal(0, 0, 1);

  TopoDS_Wire aCircleWire = MakeCircularWire(aCircleCenter, aNormal, 50.0);
  ASSERT_FALSE(aCircleWire.IsNull()) << "Failed to create circular wire";

  gp_Pnt      anEllipseCenter(0, 0, 100);
  TopoDS_Wire anEllipseWire = MakeEllipticalWire(anEllipseCenter, aNormal, 60.0, 40.0);
  ASSERT_FALSE(anEllipseWire.IsNull()) << "Failed to create elliptical wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, false);
  aLoftMaker.AddWire(aCircleWire);
  aLoftMaker.AddWire(anEllipseWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();
  ASSERT_FALSE(aLoftShape.IsNull()) << "Loft shape is null";

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   2.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone())
    << "ThickSolid on circle-to-ellipse loft failed. "
    << "This is a smooth transition and should not trigger mixed connectivity.";
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_CircleToHexagonLoft)
{
  gp_Pnt aCircleCenter(0, 0, 0);
  gp_Dir aNormal(0, 0, 1);

  TopoDS_Wire aCircleWire = MakeCircularWire(aCircleCenter, aNormal, 50.0);
  ASSERT_FALSE(aCircleWire.IsNull()) << "Failed to create circular wire";

  gp_Pnt      aHexCenter(0, 0, 100);
  TopoDS_Wire aHexWire = MakePolygonalWire(aHexCenter, aNormal, 50.0, 6);
  ASSERT_FALSE(aHexWire.IsNull()) << "Failed to create hexagonal wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, false);
  aLoftMaker.AddWire(aCircleWire);
  aLoftMaker.AddWire(aHexWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();
  ASSERT_FALSE(aLoftShape.IsNull()) << "Loft shape is null";

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   2.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone()) << "ThickSolid on circle-to-hexagon loft failed. "
                                    << "This may be affected by the mixed connectivity regression.";
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_CircleToSquareLoft)
{
  gp_Pnt aCircleCenter(0, 0, 0);
  gp_Dir aNormal(0, 0, 1);

  TopoDS_Wire aCircleWire = MakeCircularWire(aCircleCenter, aNormal, 50.0);
  ASSERT_FALSE(aCircleWire.IsNull()) << "Failed to create circular wire";

  gp_Pnt      aSquareCenter(0, 0, 100);
  TopoDS_Wire aSquareWire = MakeRectangularWire(aSquareCenter, aNormal, 80.0, 80.0);
  ASSERT_FALSE(aSquareWire.IsNull()) << "Failed to create square wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, false);
  aLoftMaker.AddWire(aCircleWire);
  aLoftMaker.AddWire(aSquareWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();
  ASSERT_FALSE(aLoftShape.IsNull()) << "Loft shape is null";

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   2.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone()) << "ThickSolid on circle-to-square loft failed. "
                                    << "This is a regression from commit 44be1230391.";
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_EllipseToRectangleLoft)
{
  gp_Dir aNormal(0, 0, 1);

  gp_Pnt      anEllipseCenter(0, 0, 0);
  TopoDS_Wire anEllipseWire = MakeEllipticalWire(anEllipseCenter, aNormal, 60.0, 30.0);
  ASSERT_FALSE(anEllipseWire.IsNull()) << "Failed to create elliptical wire";

  gp_Pnt      aRectCenter(0, 0, 100);
  TopoDS_Wire aRectWire = MakeRectangularWire(aRectCenter, aNormal, 100.0, 50.0);
  ASSERT_FALSE(aRectWire.IsNull()) << "Failed to create rectangular wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, false);
  aLoftMaker.AddWire(anEllipseWire);
  aLoftMaker.AddWire(aRectWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();
  ASSERT_FALSE(aLoftShape.IsNull()) << "Loft shape is null";

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   2.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone()) << "ThickSolid on ellipse-to-rectangle loft failed. "
                                    << "This may be affected by the mixed connectivity regression.";
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_ThreeSectionLoft)
{
  gp_Dir aNormal(0, 0, 1);

  TopoDS_Wire aCircleWire = MakeCircularWire(gp_Pnt(0, 0, 0), aNormal, 40.0);
  ASSERT_FALSE(aCircleWire.IsNull()) << "Failed to create circular wire";

  TopoDS_Wire anEllipseWire = MakeEllipticalWire(gp_Pnt(0, 0, 50), aNormal, 50.0, 35.0);
  ASSERT_FALSE(anEllipseWire.IsNull()) << "Failed to create elliptical wire";

  TopoDS_Wire aRectWire = MakeRectangularWire(gp_Pnt(0, 0, 100), aNormal, 80.0, 60.0);
  ASSERT_FALSE(aRectWire.IsNull()) << "Failed to create rectangular wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, false);
  aLoftMaker.AddWire(aCircleWire);
  aLoftMaker.AddWire(anEllipseWire);
  aLoftMaker.AddWire(aRectWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();
  ASSERT_FALSE(aLoftShape.IsNull()) << "Loft shape is null";

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   2.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone())
    << "ThickSolid on three-section loft failed. "
    << "Complex multi-section lofts are prone to mixed connectivity issues.";
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_CircleToRectangleLoft_Ruled)
{
  gp_Pnt aCircleCenter(0, 0, 0);
  gp_Dir aNormal(0, 0, 1);

  TopoDS_Wire aCircleWire = MakeCircularWire(aCircleCenter, aNormal, 50.0);
  ASSERT_FALSE(aCircleWire.IsNull()) << "Failed to create circular wire";

  gp_Pnt      aRectCenter(0, 0, 100);
  TopoDS_Wire aRectWire = MakeRectangularWire(aRectCenter, aNormal, 80.0, 60.0);
  ASSERT_FALSE(aRectWire.IsNull()) << "Failed to create rectangular wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, true);
  aLoftMaker.AddWire(aCircleWire);
  aLoftMaker.AddWire(aRectWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create ruled loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();
  ASSERT_FALSE(aLoftShape.IsNull()) << "Loft shape is null";

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   2.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone()) << "ThickSolid on ruled circle-to-rectangle loft failed.";
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_CircleToRectangleLoft_SmallOffset)
{
  gp_Pnt aCircleCenter(0, 0, 0);
  gp_Dir aNormal(0, 0, 1);

  TopoDS_Wire aCircleWire = MakeCircularWire(aCircleCenter, aNormal, 50.0);
  ASSERT_FALSE(aCircleWire.IsNull()) << "Failed to create circular wire";

  gp_Pnt      aRectCenter(0, 0, 100);
  TopoDS_Wire aRectWire = MakeRectangularWire(aRectCenter, aNormal, 80.0, 60.0);
  ASSERT_FALSE(aRectWire.IsNull()) << "Failed to create rectangular wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, false);
  aLoftMaker.AddWire(aCircleWire);
  aLoftMaker.AddWire(aRectWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   0.5,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone())
    << "ThickSolid with small offset failed on circle-to-rectangle loft.";
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_CircleToRectangleLoft_LargeOffset)
{
  gp_Pnt aCircleCenter(0, 0, 0);
  gp_Dir aNormal(0, 0, 1);

  TopoDS_Wire aCircleWire = MakeCircularWire(aCircleCenter, aNormal, 50.0);
  ASSERT_FALSE(aCircleWire.IsNull()) << "Failed to create circular wire";

  gp_Pnt      aRectCenter(0, 0, 100);
  TopoDS_Wire aRectWire = MakeRectangularWire(aRectCenter, aNormal, 80.0, 60.0);
  ASSERT_FALSE(aRectWire.IsNull()) << "Failed to create rectangular wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, false);
  aLoftMaker.AddWire(aCircleWire);
  aLoftMaker.AddWire(aRectWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   10.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone())
    << "ThickSolid with large offset failed on circle-to-rectangle loft.";
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_CircleToRectangleLoft_NegativeOffset)
{
  gp_Pnt aCircleCenter(0, 0, 0);
  gp_Dir aNormal(0, 0, 1);

  TopoDS_Wire aCircleWire = MakeCircularWire(aCircleCenter, aNormal, 50.0);
  ASSERT_FALSE(aCircleWire.IsNull()) << "Failed to create circular wire";

  gp_Pnt      aRectCenter(0, 0, 100);
  TopoDS_Wire aRectWire = MakeRectangularWire(aRectCenter, aNormal, 80.0, 60.0);
  ASSERT_FALSE(aRectWire.IsNull()) << "Failed to create rectangular wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, false);
  aLoftMaker.AddWire(aCircleWire);
  aLoftMaker.AddWire(aRectWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   -2.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone())
    << "ThickSolid with negative offset failed on circle-to-rectangle loft.";
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_Cylinder_Baseline)
{
  BRepPrimAPI_MakeCylinder aCylMaker(50.0, 100.0);
  TopoDS_Shape             aCylinder = aCylMaker.Shape();
  ASSERT_FALSE(aCylinder.IsNull()) << "Failed to create cylinder";

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aCylinder,
                                   aFacesToRemove,
                                   2.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone()) << "ThickSolid on cylinder failed - this is unexpected.";

  if (aThickMaker.IsDone())
  {
    BRepCheck_Analyzer aChecker(aThickMaker.Shape());
    EXPECT_TRUE(aChecker.IsValid()) << "Thick cylinder is not valid";
  }
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_Sphere_Baseline)
{
  BRepPrimAPI_MakeSphere aSphereMaker(50.0);
  TopoDS_Shape           aSphere = aSphereMaker.Shape();
  ASSERT_FALSE(aSphere.IsNull()) << "Failed to create sphere";

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aSphere,
                                   aFacesToRemove,
                                   2.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone()) << "ThickSolid on sphere failed - this is unexpected.";

  if (aThickMaker.IsDone())
  {
    BRepCheck_Analyzer aChecker(aThickMaker.Shape());
    EXPECT_TRUE(aChecker.IsValid()) << "Thick sphere is not valid";
  }
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_FusedBoxCylinder)
{
  BRepPrimAPI_MakeBox aBoxMaker(100.0, 100.0, 50.0);
  TopoDS_Shape        aBox = aBoxMaker.Shape();
  ASSERT_FALSE(aBox.IsNull()) << "Failed to create box";

  BRepPrimAPI_MakeCylinder aCylMaker(gp_Ax2(gp_Pnt(50, 50, 50), gp_Dir(0, 0, 1)), 30.0, 50.0);
  TopoDS_Shape             aCyl = aCylMaker.Shape();
  ASSERT_FALSE(aCyl.IsNull()) << "Failed to create cylinder";

  BRepAlgoAPI_Fuse aFuser(aBox, aCyl);
  ASSERT_TRUE(aFuser.IsDone()) << "Failed to fuse shapes";

  TopoDS_Shape aFusedShape = aFuser.Shape();

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aFusedShape,
                                   aFacesToRemove,
                                   2.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone()) << "ThickSolid on fused box+cylinder failed.";
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_CircleToRectangle_ThinLoft)
{
  gp_Pnt aCircleCenter(0, 0, 0);
  gp_Dir aNormal(0, 0, 1);

  TopoDS_Wire aCircleWire = MakeCircularWire(aCircleCenter, aNormal, 50.0);
  ASSERT_FALSE(aCircleWire.IsNull()) << "Failed to create circular wire";

  gp_Pnt      aRectCenter(0, 0, 10);
  TopoDS_Wire aRectWire = MakeRectangularWire(aRectCenter, aNormal, 80.0, 60.0);
  ASSERT_FALSE(aRectWire.IsNull()) << "Failed to create rectangular wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, false);
  aLoftMaker.AddWire(aCircleWire);
  aLoftMaker.AddWire(aRectWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create thin loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   1.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  (void)aThickMaker.IsDone();
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_CircleToRectangle_TallLoft)
{
  gp_Pnt aCircleCenter(0, 0, 0);
  gp_Dir aNormal(0, 0, 1);

  TopoDS_Wire aCircleWire = MakeCircularWire(aCircleCenter, aNormal, 50.0);
  ASSERT_FALSE(aCircleWire.IsNull()) << "Failed to create circular wire";

  gp_Pnt      aRectCenter(0, 0, 500);
  TopoDS_Wire aRectWire = MakeRectangularWire(aRectCenter, aNormal, 80.0, 60.0);
  ASSERT_FALSE(aRectWire.IsNull()) << "Failed to create rectangular wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, false);
  aLoftMaker.AddWire(aCircleWire);
  aLoftMaker.AddWire(aRectWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create tall loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   2.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone()) << "ThickSolid on tall circle-to-rectangle loft failed.";
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_CircleToTriangleLoft)
{
  gp_Pnt aCircleCenter(0, 0, 0);
  gp_Dir aNormal(0, 0, 1);

  TopoDS_Wire aCircleWire = MakeCircularWire(aCircleCenter, aNormal, 50.0);
  ASSERT_FALSE(aCircleWire.IsNull()) << "Failed to create circular wire";

  gp_Pnt      aTriCenter(0, 0, 100);
  TopoDS_Wire aTriWire = MakePolygonalWire(aTriCenter, aNormal, 60.0, 3);
  ASSERT_FALSE(aTriWire.IsNull()) << "Failed to create triangular wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, false);
  aLoftMaker.AddWire(aCircleWire);
  aLoftMaker.AddWire(aTriWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   2.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone()) << "ThickSolid on circle-to-triangle loft failed. "
                                    << "Triangle corners create extreme curvature transitions.";
}

TEST(BRepOffset_MakeOffsetTest, ThickSolid_CircleToOctagonLoft)
{
  gp_Pnt aCircleCenter(0, 0, 0);
  gp_Dir aNormal(0, 0, 1);

  TopoDS_Wire aCircleWire = MakeCircularWire(aCircleCenter, aNormal, 50.0);
  ASSERT_FALSE(aCircleWire.IsNull()) << "Failed to create circular wire";

  gp_Pnt      anOctCenter(0, 0, 100);
  TopoDS_Wire anOctWire = MakePolygonalWire(anOctCenter, aNormal, 55.0, 8);
  ASSERT_FALSE(anOctWire.IsNull()) << "Failed to create octagonal wire";

  BRepOffsetAPI_ThruSections aLoftMaker(true, false);
  aLoftMaker.AddWire(aCircleWire);
  aLoftMaker.AddWire(anOctWire);
  aLoftMaker.Build();

  ASSERT_TRUE(aLoftMaker.IsDone()) << "Failed to create loft";

  TopoDS_Shape aLoftShape = aLoftMaker.Shape();

  NCollection_List<TopoDS_Shape> aFacesToRemove;
  BRepOffsetAPI_MakeThickSolid   aThickMaker;

  aThickMaker.MakeThickSolidByJoin(aLoftShape,
                                   aFacesToRemove,
                                   2.0,
                                   1.0e-3,
                                   BRepOffset_Skin,
                                   false,
                                   false,
                                   GeomAbs_Intersection);
  aThickMaker.Build();

  EXPECT_TRUE(aThickMaker.IsDone()) << "ThickSolid on circle-to-octagon loft failed.";
}
