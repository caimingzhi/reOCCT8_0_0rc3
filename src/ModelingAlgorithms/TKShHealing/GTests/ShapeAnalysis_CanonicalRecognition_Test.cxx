

#include <gtest/gtest.h>

#include <memory>
#include <ShapeAnalysis_CanonicalRecognition.hpp>
#include <Precision.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepBuilderAPI_MakePolygon.hpp>
#include <BRepBuilderAPI_Sewing.hpp>
#include <BRepBuilderAPI_NurbsConvert.hpp>
#include <GC_MakeSegment.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shell.hpp>
#include <Geom_Plane.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_Line.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_BSplineCurve.hpp>
#include <GeomConvert.hpp>
#include <BRep_Tool.hpp>
#include <BRepAlgoAPI_Section.hpp>
#include <TopoDS.hpp>
#include <TopExp_Explorer.hpp>
#include <TopExp.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <GeomAPI_IntSS.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>
#include <gp_Vec.hpp>
#include <gp_Pln.hpp>
#include <gp_Lin.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Cone.hpp>
#include <gp_Sphere.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <NCollection_Array1.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <GeomAbs_CurveType.hpp>

class CanonicalRecognitionApproxTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    myRecognizer = std::make_unique<ShapeAnalysis_CanonicalRecognition>();
    myTolerance  = 1.0e-3;
  }

  std::unique_ptr<ShapeAnalysis_CanonicalRecognition> myRecognizer;
  double                                              myTolerance;
};

TEST_F(CanonicalRecognitionApproxTest, PolylineToPlaneRecognition_A1)
{

  BRepBuilderAPI_MakePolygon aPolygonMaker;
  aPolygonMaker.Add(gp_Pnt(0, 0, 0));
  aPolygonMaker.Add(gp_Pnt(1, 0, 0));
  aPolygonMaker.Add(gp_Pnt(1, 1, 0));
  aPolygonMaker.Add(gp_Pnt(0, 1, 0));
  aPolygonMaker.Close();

  ASSERT_TRUE(aPolygonMaker.IsDone()) << "Failed to create polyline";
  const TopoDS_Wire aWire = aPolygonMaker.Wire();

  myRecognizer->SetShape(aWire);
  gp_Pln     aResultPlane;
  const bool aResult = myRecognizer->IsPlane(myTolerance, aResultPlane);

  EXPECT_TRUE(aResult) << "Polyline should be recognized as planar";

  const gp_Pnt aOrigin = aResultPlane.Location();
  const gp_Dir aNormal = aResultPlane.Axis().Direction();

  EXPECT_NEAR(std::abs(aNormal.Z()), 1.0, myTolerance)
    << "Plane normal should be close to Z direction";
  EXPECT_NEAR(aOrigin.Z(), 0.0, myTolerance) << "Plane should pass through Z=0";
}

TEST_F(CanonicalRecognitionApproxTest, CylinderRecognition_A2)
{

  gp_Ax2                               aAxis(gp_Pnt(0, 0, 0), gp_Dir(1, 1, 1));
  occ::handle<Geom_CylindricalSurface> aCylSurf = new Geom_CylindricalSurface(aAxis, 1.0);
  BRepBuilderAPI_MakeFace aFaceMaker(aCylSurf, 0, 2 * M_PI, 0, 1, Precision::Confusion());

  ASSERT_TRUE(aFaceMaker.IsDone()) << "Failed to create cylindrical face";
  const TopoDS_Face aFace = aFaceMaker.Face();

  BRepBuilderAPI_NurbsConvert aNurbsConvert(aFace);
  ASSERT_TRUE(aNurbsConvert.IsDone()) << "Failed to convert face to NURBS";
  const TopoDS_Shape aNurbsShape = aNurbsConvert.Shape();
  const TopoDS_Face  aNurbsFace  = TopoDS::Face(aNurbsShape);

  myRecognizer->SetShape(aNurbsFace);
  gp_Cylinder aResultCylinder;
  const bool  aResult = myRecognizer->IsCylinder(myTolerance, aResultCylinder);

  EXPECT_TRUE(aResult) << "NURBS face should be recognized as cylinder";
  EXPECT_NEAR(aResultCylinder.Radius(), 1.0, myTolerance) << "Cylinder radius should match";
}

TEST_F(CanonicalRecognitionApproxTest, ConicalSurfaceRecognition_A3)
{

  const double                     aHalfAngle = M_PI / 6.0;
  gp_Ax2                           aAxis(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  occ::handle<Geom_ConicalSurface> aConeSurf = new Geom_ConicalSurface(aAxis, aHalfAngle, 2.0);
  BRepBuilderAPI_MakeFace          aFaceMaker(aConeSurf, 0, 2 * M_PI, 0, 3, Precision::Confusion());

  ASSERT_TRUE(aFaceMaker.IsDone()) << "Failed to create conical face";
  const TopoDS_Face aFace = aFaceMaker.Face();

  BRepBuilderAPI_NurbsConvert aNurbsConvert(aFace);
  ASSERT_TRUE(aNurbsConvert.IsDone()) << "Failed to convert face to NURBS";
  const TopoDS_Shape aNurbsShape = aNurbsConvert.Shape();
  const TopoDS_Face  aNurbsFace  = TopoDS::Face(aNurbsShape);

  myRecognizer->SetShape(aNurbsFace);
  gp_Cone    aResultCone;
  const bool aResult = myRecognizer->IsCone(myTolerance, aResultCone);

  EXPECT_TRUE(aResult) << "NURBS face should be recognized as cone";
  EXPECT_NEAR(aResultCone.SemiAngle(), aHalfAngle, myTolerance) << "Cone semi-angle should match";
}

TEST_F(CanonicalRecognitionApproxTest, SphericalSurfaceRecognition_A4)
{

  gp_Ax2                             aAxis(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  occ::handle<Geom_SphericalSurface> aSphereSurf = new Geom_SphericalSurface(aAxis, 1.0);
  BRepBuilderAPI_MakeFace aFaceMaker(aSphereSurf, 0, 2 * M_PI, 0, M_PI / 2, Precision::Confusion());

  ASSERT_TRUE(aFaceMaker.IsDone()) << "Failed to create spherical face";
  const TopoDS_Face aFace = aFaceMaker.Face();

  BRepBuilderAPI_NurbsConvert aNurbsConvert(aFace);
  ASSERT_TRUE(aNurbsConvert.IsDone()) << "Failed to convert face to NURBS";
  const TopoDS_Shape aNurbsShape = aNurbsConvert.Shape();
  const TopoDS_Face  aNurbsFace  = TopoDS::Face(aNurbsShape);

  myRecognizer->SetShape(aNurbsFace);
  gp_Sphere  aResultSphere;
  const bool aResult = myRecognizer->IsSphere(myTolerance, aResultSphere);

  EXPECT_TRUE(aResult) << "NURBS face should be recognized as sphere";
  EXPECT_NEAR(aResultSphere.Radius(), 1.0, myTolerance) << "Sphere radius should match";
}

class CanonicalRecognitionBaseCurveTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    myRecognizer = std::make_unique<ShapeAnalysis_CanonicalRecognition>();
    myTolerance  = 1.0e-3;
  }

  std::unique_ptr<ShapeAnalysis_CanonicalRecognition> myRecognizer;
  double                                              myTolerance;
};

TEST_F(CanonicalRecognitionBaseCurveTest, BezierToLineRecognition_A1)
{

  NCollection_Array1<gp_Pnt> aControlPoints(1, 3);
  aControlPoints(1) = gp_Pnt(0, 0, 0);
  aControlPoints(2) = gp_Pnt(0.5, 0.0005, 0);
  aControlPoints(3) = gp_Pnt(1, 0, 0);

  occ::handle<Geom_BezierCurve> aBezier = new Geom_BezierCurve(aControlPoints);
  BRepBuilderAPI_MakeEdge       aEdgeMaker(aBezier);

  ASSERT_TRUE(aEdgeMaker.IsDone()) << "Failed to create Bezier edge";
  const TopoDS_Edge anEdge = aEdgeMaker.Edge();

  myRecognizer->SetShape(anEdge);
  gp_Lin     aResultLine;
  const bool aResult = myRecognizer->IsLine(myTolerance, aResultLine);

  EXPECT_TRUE(aResult) << "Nearly linear Bezier should be recognized as line";

  const gp_Dir aLineDir = aResultLine.Direction();
  EXPECT_NEAR(std::abs(aLineDir.X()), 1.0, myTolerance) << "Line should be along X direction";
}

TEST_F(CanonicalRecognitionBaseCurveTest, BezierToCircleRecognition_A2)
{

  NCollection_Array1<gp_Pnt> aControlPoints(1, 3);
  aControlPoints(1) = gp_Pnt(0, 0, 0);
  aControlPoints(2) = gp_Pnt(0.5, 0.0005, 0);
  aControlPoints(3) = gp_Pnt(1, 0, 0);

  occ::handle<Geom_BezierCurve> aBezier = new Geom_BezierCurve(aControlPoints);
  BRepBuilderAPI_MakeEdge       aEdgeMaker(aBezier);

  ASSERT_TRUE(aEdgeMaker.IsDone()) << "Failed to create Bezier edge";
  const TopoDS_Edge anEdge = aEdgeMaker.Edge();

  myRecognizer->SetShape(anEdge);
  gp_Circ    aResultCircle;
  const bool aResult = myRecognizer->IsCircle(myTolerance, aResultCircle);

  EXPECT_TRUE(aResult)
    << "Bezier curve should be recognized as circle (matching original TCL test)";
  EXPECT_GT(aResultCircle.Radius(), 0.0) << "Circle radius should be positive";
}

TEST_F(CanonicalRecognitionBaseCurveTest, EllipseToEllipseRecognition_A3)
{

  gp_Ax2                    aAxis(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X));
  occ::handle<Geom_Ellipse> aEllipse = new Geom_Ellipse(aAxis, 1.0, 0.5);

  occ::handle<Geom_BSplineCurve> aBSplineCurve = GeomConvert::CurveToBSplineCurve(aEllipse);
  BRepBuilderAPI_MakeEdge        aEdgeMaker(aBSplineCurve);

  ASSERT_TRUE(aEdgeMaker.IsDone()) << "Failed to create ellipse edge";
  const TopoDS_Edge anEdge = aEdgeMaker.Edge();

  myRecognizer->SetShape(anEdge);
  gp_Elips   aResultEllipse;
  const bool aResult = myRecognizer->IsEllipse(1.0e-7, aResultEllipse);

  EXPECT_TRUE(aResult) << "Ellipse should be recognized as ellipse";
  EXPECT_NEAR(aResultEllipse.MajorRadius(), 1.0, 1.0e-7) << "Major radius should match";
  EXPECT_NEAR(aResultEllipse.MinorRadius(), 0.5, 1.0e-7) << "Minor radius should match";
}

TEST_F(CanonicalRecognitionBaseCurveTest, MultiSegmentWireToLineRecognition_A4)
{

  NCollection_Array1<gp_Pnt> aControlPoints(1, 3);
  aControlPoints(1) = gp_Pnt(0, 0, 0);
  aControlPoints(2) = gp_Pnt(0.5, 0.0000005, 0);
  aControlPoints(3) = gp_Pnt(1, 0, 0);

  occ::handle<Geom_BezierCurve> aBezier = new Geom_BezierCurve(aControlPoints);

  BRepBuilderAPI_MakeEdge aEdgeMaker1(aBezier, 0.0, 0.3);
  BRepBuilderAPI_MakeEdge aEdgeMaker2(aBezier, 0.3, 0.7);
  BRepBuilderAPI_MakeEdge aEdgeMaker3(aBezier, 0.7, 1.0);

  ASSERT_TRUE(aEdgeMaker1.IsDone() && aEdgeMaker2.IsDone() && aEdgeMaker3.IsDone())
    << "Failed to create edges";

  BRepBuilderAPI_MakeWire aWireMaker;
  aWireMaker.Add(aEdgeMaker1.Edge());
  aWireMaker.Add(aEdgeMaker2.Edge());
  aWireMaker.Add(aEdgeMaker3.Edge());

  ASSERT_TRUE(aWireMaker.IsDone()) << "Failed to create wire";
  const TopoDS_Wire aWire = aWireMaker.Wire();

  myRecognizer->SetShape(aWire);
  gp_Lin     aResultLine;
  const bool aResult = myRecognizer->IsLine(myTolerance, aResultLine);

  EXPECT_TRUE(aResult) << "Multi-segment nearly linear wire should be recognized as line";
}

TEST_F(CanonicalRecognitionBaseCurveTest, MultiSegmentCircleWireRecognition_A5)
{

  gp_Ax2                   aAxis(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  occ::handle<Geom_Circle> aCircle = new Geom_Circle(aAxis, 1.0);

  occ::handle<Geom_BSplineCurve> aBSplineCurve = GeomConvert::CurveToBSplineCurve(aCircle);

  BRepBuilderAPI_MakeEdge aEdgeMaker1(aBSplineCurve, 0.0, 1.0);
  BRepBuilderAPI_MakeEdge aEdgeMaker2(aBSplineCurve, 1.0, 2.5);
  BRepBuilderAPI_MakeEdge aEdgeMaker3(aBSplineCurve, 2.5, 6.0);

  ASSERT_TRUE(aEdgeMaker1.IsDone() && aEdgeMaker2.IsDone() && aEdgeMaker3.IsDone())
    << "Failed to create edges";

  BRepBuilderAPI_MakeWire aWireMaker;
  aWireMaker.Add(aEdgeMaker1.Edge());
  aWireMaker.Add(aEdgeMaker2.Edge());
  aWireMaker.Add(aEdgeMaker3.Edge());

  ASSERT_TRUE(aWireMaker.IsDone()) << "Failed to create wire";
  const TopoDS_Wire aWire = aWireMaker.Wire();

  myRecognizer->SetShape(aWire);
  gp_Circ    aResultCircle;
  const bool aResult = myRecognizer->IsCircle(1.0e-7, aResultCircle);

  EXPECT_TRUE(aResult) << "Multi-segment circle wire should be recognized as circle";
  EXPECT_NEAR(aResultCircle.Radius(), 1.0, 1.0e-7) << "Circle radius should match";
}

TEST_F(CanonicalRecognitionBaseCurveTest, MultiSegmentEllipseWireRecognition_A6)
{

  gp_Ax2                    aAxis(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X));
  occ::handle<Geom_Ellipse> aEllipse = new Geom_Ellipse(aAxis, 1.0, 0.5);

  occ::handle<Geom_BSplineCurve> aBSplineCurve = GeomConvert::CurveToBSplineCurve(aEllipse);

  BRepBuilderAPI_MakeEdge aEdgeMaker1(aBSplineCurve, 0.0, 1.0);
  BRepBuilderAPI_MakeEdge aEdgeMaker2(aBSplineCurve, 1.0, 2.5);
  BRepBuilderAPI_MakeEdge aEdgeMaker3(aBSplineCurve, 2.5, 6.0);

  ASSERT_TRUE(aEdgeMaker1.IsDone() && aEdgeMaker2.IsDone() && aEdgeMaker3.IsDone())
    << "Failed to create edges";

  BRepBuilderAPI_MakeWire aWireMaker;
  aWireMaker.Add(aEdgeMaker1.Edge());
  aWireMaker.Add(aEdgeMaker2.Edge());
  aWireMaker.Add(aEdgeMaker3.Edge());

  ASSERT_TRUE(aWireMaker.IsDone()) << "Failed to create wire";
  const TopoDS_Wire aWire = aWireMaker.Wire();

  myRecognizer->SetShape(aWire);
  gp_Elips   aResultEllipse;
  const bool aResult = myRecognizer->IsEllipse(1.0e-7, aResultEllipse);

  EXPECT_TRUE(aResult) << "Multi-segment ellipse wire should be recognized as ellipse";
  EXPECT_NEAR(aResultEllipse.MajorRadius(), 1.0, 1.0e-7) << "Major radius should match";
  EXPECT_NEAR(aResultEllipse.MinorRadius(), 0.5, 1.0e-7) << "Minor radius should match";
}

class CanonicalRecognitionBaseSurfaceTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    myRecognizer = std::make_unique<ShapeAnalysis_CanonicalRecognition>();
    myTolerance  = 1.0e-7;
  }

  std::unique_ptr<ShapeAnalysis_CanonicalRecognition> myRecognizer;
  double                                              myTolerance;
};

TEST_F(CanonicalRecognitionBaseSurfaceTest, TrimmedPlaneRecognition_B1)
{

  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pln());

  BRepBuilderAPI_MakeFace aFaceMaker(aPlane, -1, 1, -1, 1, Precision::Confusion());
  ASSERT_TRUE(aFaceMaker.IsDone()) << "Failed to create planar face";
  TopoDS_Face aFace = aFaceMaker.Face();

  BRepBuilderAPI_NurbsConvert aNurbsConvert(aFace);
  ASSERT_TRUE(aNurbsConvert.IsDone()) << "Failed to convert face to NURBS";
  TopoDS_Face aNurbsFace = TopoDS::Face(aNurbsConvert.Shape());

  myRecognizer->SetShape(aNurbsFace);
  gp_Pln     aResultPlane;
  const bool aResult = myRecognizer->IsPlane(myTolerance, aResultPlane);

  EXPECT_TRUE(aResult) << "Planar face should be recognized as plane";

  const gp_Dir aNormal = aResultPlane.Axis().Direction();
  EXPECT_NEAR(std::abs(aNormal.Z()), 1.0, myTolerance) << "Plane normal should be Z direction";
}

TEST_F(CanonicalRecognitionBaseSurfaceTest, TrimmedCylinderRecognition_B2)
{

  gp_Ax2                               aAxis(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  occ::handle<Geom_CylindricalSurface> aCylSurf = new Geom_CylindricalSurface(aAxis, 1.0);

  BRepBuilderAPI_MakeFace aFaceMaker(aCylSurf, 0, 2 * M_PI, -1, 1, Precision::Confusion());
  ASSERT_TRUE(aFaceMaker.IsDone()) << "Failed to create cylindrical face";
  TopoDS_Face aFace = aFaceMaker.Face();

  BRepBuilderAPI_NurbsConvert aNurbsConvert(aFace);
  ASSERT_TRUE(aNurbsConvert.IsDone()) << "Failed to convert face to NURBS";
  TopoDS_Face aNurbsFace = TopoDS::Face(aNurbsConvert.Shape());

  myRecognizer->SetShape(aNurbsFace);
  gp_Cylinder aResultCylinder;
  const bool  aResult = myRecognizer->IsCylinder(myTolerance, aResultCylinder);

  EXPECT_TRUE(aResult) << "Cylindrical surface should be recognized as cylinder";
  EXPECT_NEAR(aResultCylinder.Radius(), 1.0, myTolerance) << "Cylinder radius should match";
}

TEST_F(CanonicalRecognitionBaseSurfaceTest, TrimmedConeRecognition_B3)
{

  const double                     aSemiAngle = M_PI / 6.0;
  gp_Ax2                           aAxis(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  occ::handle<Geom_ConicalSurface> aConeSurf = new Geom_ConicalSurface(aAxis, aSemiAngle, 0);

  BRepBuilderAPI_MakeFace aFaceMaker(aConeSurf, 0, 2 * M_PI, -1, 0, Precision::Confusion());
  ASSERT_TRUE(aFaceMaker.IsDone()) << "Failed to create conical face";
  TopoDS_Face aFace = aFaceMaker.Face();

  BRepBuilderAPI_NurbsConvert aNurbsConvert(aFace);
  ASSERT_TRUE(aNurbsConvert.IsDone()) << "Failed to convert face to NURBS";
  TopoDS_Face aNurbsFace = TopoDS::Face(aNurbsConvert.Shape());

  myRecognizer->SetShape(aNurbsFace);
  gp_Cone    aResultCone;
  const bool aResult = myRecognizer->IsCone(myTolerance, aResultCone);

  EXPECT_TRUE(aResult) << "Conical surface should be recognized as cone";
  EXPECT_NEAR(aResultCone.SemiAngle(), aSemiAngle, myTolerance) << "Cone semi-angle should match";
}

TEST_F(CanonicalRecognitionBaseSurfaceTest, ConvertedSphereRecognition_B4)
{

  gp_Ax2                             aAxis(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  occ::handle<Geom_SphericalSurface> aSphereSurf = new Geom_SphericalSurface(aAxis, 1.0);

  occ::handle<Geom_BSplineSurface> aBSplineSurf = GeomConvert::SurfaceToBSplineSurface(aSphereSurf);
  BRepBuilderAPI_MakeFace          aFaceMaker(aBSplineSurf, Precision::Confusion());

  ASSERT_TRUE(aFaceMaker.IsDone()) << "Failed to create spherical face";
  const TopoDS_Face aFace = aFaceMaker.Face();

  myRecognizer->SetShape(aFace);
  gp_Sphere  aResultSphere;
  const bool aResult = myRecognizer->IsSphere(myTolerance, aResultSphere);

  EXPECT_TRUE(aResult) << "Spherical surface should be recognized as sphere";
  EXPECT_NEAR(aResultSphere.Radius(), 1.0, myTolerance) << "Sphere radius should match";
}

TEST_F(CanonicalRecognitionBaseSurfaceTest, SewnPlanarSurfaceRecognition_B5)
{

  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pln());

  BRepBuilderAPI_MakeFace aFaceMaker1(aPlane, -1, 0, -1, 0, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker2(aPlane, -1, 0, 0, 1, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker3(aPlane, 0, 1, 0, 1, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker4(aPlane, 0, 1, -1, 0, Precision::Confusion());

  ASSERT_TRUE(aFaceMaker1.IsDone() && aFaceMaker2.IsDone() && aFaceMaker3.IsDone()
              && aFaceMaker4.IsDone())
    << "Failed to create planar faces";

  BRepBuilderAPI_Sewing aSewing;
  aSewing.Add(aFaceMaker1.Face());
  aSewing.Add(aFaceMaker2.Face());
  aSewing.Add(aFaceMaker3.Face());
  aSewing.Add(aFaceMaker4.Face());
  aSewing.Perform();

  const TopoDS_Shape aSewnShape = aSewing.SewedShape();
  ASSERT_FALSE(aSewnShape.IsNull()) << "Failed to create sewn shape";

  BRepBuilderAPI_NurbsConvert aNurbsConvert(aSewnShape);
  ASSERT_TRUE(aNurbsConvert.IsDone()) << "Failed to convert sewn shape to NURBS";
  const TopoDS_Shape aNurbsShape = aNurbsConvert.Shape();

  myRecognizer->SetShape(aNurbsShape);
  gp_Pln     aResultPlane;
  const bool aResult = myRecognizer->IsPlane(myTolerance, aResultPlane);

  EXPECT_TRUE(aResult) << "Sewn planar surface should be recognized as plane";

  const gp_Dir aNormal = aResultPlane.Axis().Direction();
  EXPECT_NEAR(std::abs(aNormal.Z()), 1.0, myTolerance) << "Plane normal should be Z direction";
}

TEST_F(CanonicalRecognitionBaseSurfaceTest, SewnCylindricalSurfaceRecognition_B6)
{

  gp_Ax2                               aAxis(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  occ::handle<Geom_CylindricalSurface> aCylSurf = new Geom_CylindricalSurface(aAxis, 1.0);

  BRepBuilderAPI_MakeFace aFaceMaker1(aCylSurf, 0, 3, -1, 0, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker2(aCylSurf, 0, 3, 0, 1, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker3(aCylSurf, 3, 6, 0, 1, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker4(aCylSurf, 3, 6, -1, 0, Precision::Confusion());

  ASSERT_TRUE(aFaceMaker1.IsDone() && aFaceMaker2.IsDone() && aFaceMaker3.IsDone()
              && aFaceMaker4.IsDone())
    << "Failed to create cylindrical faces";

  BRepBuilderAPI_Sewing aSewing;
  aSewing.Add(aFaceMaker1.Face());
  aSewing.Add(aFaceMaker2.Face());
  aSewing.Add(aFaceMaker3.Face());
  aSewing.Add(aFaceMaker4.Face());
  aSewing.Perform();

  const TopoDS_Shape aSewnShape = aSewing.SewedShape();
  ASSERT_FALSE(aSewnShape.IsNull()) << "Failed to create sewn shape";

  BRepBuilderAPI_NurbsConvert aNurbsConvert(aSewnShape);
  ASSERT_TRUE(aNurbsConvert.IsDone()) << "Failed to convert sewn shape to NURBS";
  const TopoDS_Shape aNurbsShape = aNurbsConvert.Shape();

  myRecognizer->SetShape(aNurbsShape);
  gp_Cylinder aResultCylinder;
  const bool  aResult = myRecognizer->IsCylinder(myTolerance, aResultCylinder);

  EXPECT_TRUE(aResult) << "Sewn cylindrical surface should be recognized as cylinder";
  EXPECT_NEAR(aResultCylinder.Radius(), 1.0, myTolerance) << "Cylinder radius should match";
}

TEST_F(CanonicalRecognitionBaseSurfaceTest, SewnConicalSurfaceRecognition_B7)
{

  const double                     aSemiAngle = M_PI / 6.0;
  gp_Ax2                           aAxis(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  occ::handle<Geom_ConicalSurface> aConeSurf = new Geom_ConicalSurface(aAxis, aSemiAngle, 0);

  BRepBuilderAPI_MakeFace aFaceMaker1(aConeSurf, 0, 3, 0, 1, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker2(aConeSurf, 0, 3, 1, 2, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker3(aConeSurf, 3, 6, 1, 2, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker4(aConeSurf, 3, 6, 0, 1, Precision::Confusion());

  ASSERT_TRUE(aFaceMaker1.IsDone() && aFaceMaker2.IsDone() && aFaceMaker3.IsDone()
              && aFaceMaker4.IsDone())
    << "Failed to create conical faces";

  BRepBuilderAPI_Sewing aSewing;
  aSewing.Add(aFaceMaker1.Face());
  aSewing.Add(aFaceMaker2.Face());
  aSewing.Add(aFaceMaker3.Face());
  aSewing.Add(aFaceMaker4.Face());
  aSewing.Perform();

  const TopoDS_Shape aSewnShape = aSewing.SewedShape();
  ASSERT_FALSE(aSewnShape.IsNull()) << "Failed to create sewn shape";

  BRepBuilderAPI_NurbsConvert aNurbsConvert(aSewnShape);
  ASSERT_TRUE(aNurbsConvert.IsDone()) << "Failed to convert sewn shape to NURBS";
  const TopoDS_Shape aNurbsShape = aNurbsConvert.Shape();

  myRecognizer->SetShape(aNurbsShape);
  gp_Cone    aResultCone;
  const bool aResult = myRecognizer->IsCone(myTolerance, aResultCone);

  EXPECT_TRUE(aResult) << "Sewn conical surface should be recognized as cone";
  EXPECT_NEAR(aResultCone.SemiAngle(), aSemiAngle, myTolerance) << "Cone semi-angle should match";
}

TEST_F(CanonicalRecognitionBaseSurfaceTest, SewnSphericalSurfaceRecognition_B8)
{

  gp_Ax2                             aAxis(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  occ::handle<Geom_SphericalSurface> aSphereSurf = new Geom_SphericalSurface(aAxis, 1.0);

  occ::handle<Geom_BSplineSurface> aBSplineSurf = GeomConvert::SurfaceToBSplineSurface(aSphereSurf);

  BRepBuilderAPI_MakeFace aFaceMaker1(aBSplineSurf, 0, 3, -1.5, 0, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker2(aBSplineSurf, 0, 3, 0, 1.5, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker3(aBSplineSurf, 3, 6, 0, 1.5, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker4(aBSplineSurf, 3, 6, -1.5, 0, Precision::Confusion());

  ASSERT_TRUE(aFaceMaker1.IsDone() && aFaceMaker2.IsDone() && aFaceMaker3.IsDone()
              && aFaceMaker4.IsDone())
    << "Failed to create spherical faces";

  BRepBuilderAPI_Sewing aSewing;
  aSewing.Add(aFaceMaker1.Face());
  aSewing.Add(aFaceMaker2.Face());
  aSewing.Add(aFaceMaker3.Face());
  aSewing.Add(aFaceMaker4.Face());
  aSewing.Perform();

  const TopoDS_Shape aSewnShape = aSewing.SewedShape();
  ASSERT_FALSE(aSewnShape.IsNull()) << "Failed to create sewn shape";

  myRecognizer->SetShape(aSewnShape);
  gp_Sphere  aResultSphere;
  const bool aResult = myRecognizer->IsSphere(myTolerance, aResultSphere);

  EXPECT_TRUE(aResult) << "Sewn spherical surface should be recognized as sphere";
  EXPECT_NEAR(aResultSphere.Radius(), 1.0, myTolerance) << "Sphere radius should match";
}

TEST_F(CanonicalRecognitionBaseSurfaceTest, ComplexCylindricalRecognitionWithSection_B9)
{

  gp_Ax2                               aAxis(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  occ::handle<Geom_CylindricalSurface> aCylSurf = new Geom_CylindricalSurface(aAxis, 1.0);

  BRepBuilderAPI_MakeFace aFaceMaker1(aCylSurf, 0, 1, -1, 1, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker2(aCylSurf, 1, 2, -1, 1, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker3(aCylSurf, 2, 3, -1, 1, Precision::Confusion());
  BRepBuilderAPI_MakeFace aFaceMaker4(aCylSurf, 3, 4, -1, 1, Precision::Confusion());

  ASSERT_TRUE(aFaceMaker1.IsDone() && aFaceMaker2.IsDone() && aFaceMaker3.IsDone()
              && aFaceMaker4.IsDone())
    << "Failed to create cylindrical faces";

  BRepBuilderAPI_Sewing aSewing;
  aSewing.Add(aFaceMaker1.Face());
  aSewing.Add(aFaceMaker2.Face());
  aSewing.Add(aFaceMaker3.Face());
  aSewing.Add(aFaceMaker4.Face());
  aSewing.Perform();

  const TopoDS_Shape aSewnShape = aSewing.SewedShape();
  ASSERT_FALSE(aSewnShape.IsNull()) << "Failed to create sewn shape";

  BRepBuilderAPI_NurbsConvert aNurbsConvert(aSewnShape);
  ASSERT_TRUE(aNurbsConvert.IsDone()) << "Failed to convert sewn shape to NURBS";
  const TopoDS_Shape aNurbsShape = aNurbsConvert.Shape();

  myRecognizer->SetShape(aNurbsShape);
  gp_Cylinder aResultCylinder;
  const bool  aResult = myRecognizer->IsCylinder(myTolerance, aResultCylinder);

  EXPECT_TRUE(aResult) << "Sewn cylindrical shape should be recognized as cylinder";
  EXPECT_NEAR(aResultCylinder.Radius(), 1.0, myTolerance) << "Cylinder radius should match";
}

TEST_F(CanonicalRecognitionBaseSurfaceTest, ExtrudedCylindricalSurfaceRecognition_B10)
{

  gp_Ax2                               aAxis(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  occ::handle<Geom_CylindricalSurface> aCylSurf = new Geom_CylindricalSurface(aAxis, 1.0);

  gp_Dir                  aNormal(1, 0, 1);
  gp_Pln                  aPlane(gp_Pnt(0, 0, 0), aNormal);
  occ::handle<Geom_Plane> aGeomPlane = new Geom_Plane(aPlane);

  GeomAPI_IntSS anIntersector(aCylSurf, aGeomPlane, Precision::Confusion());

  ASSERT_TRUE(anIntersector.IsDone()) << "Surface-surface intersection failed";
  ASSERT_GT(anIntersector.NbLines(), 0) << "No intersection curves found";

  occ::handle<Geom_Curve> anIntCurve = anIntersector.Line(1);
  ASSERT_FALSE(anIntCurve.IsNull()) << "Intersection curve is null";

  gp_Dir                                     anExtrusionDir(gp_Dir::D::Z);
  occ::handle<Geom_SurfaceOfLinearExtrusion> anExtSurf =
    new Geom_SurfaceOfLinearExtrusion(anIntCurve, anExtrusionDir);

  double uMin, uMax, vMin, vMax;
  anExtSurf->Bounds(uMin, uMax, vMin, vMax);
  BRepBuilderAPI_MakeFace aFaceMaker(anExtSurf, uMin, uMax, -1, 1, Precision::Confusion());

  ASSERT_TRUE(aFaceMaker.IsDone()) << "Failed to create face from extruded surface";
  TopoDS_Face aFace = aFaceMaker.Face();

  BRepBuilderAPI_NurbsConvert aNurbsConvert(aFace);
  ASSERT_TRUE(aNurbsConvert.IsDone()) << "Failed to convert face to NURBS";
  TopoDS_Face aNurbsFace = TopoDS::Face(aNurbsConvert.Shape());

  myRecognizer->SetShape(aNurbsFace);
  gp_Cylinder aResultCylinder;
  const bool  aResult = myRecognizer->IsCylinder(myTolerance, aResultCylinder);

  EXPECT_TRUE(aResult) << "Extruded surface should be recognized as cylinder";
  EXPECT_NEAR(aResultCylinder.Radius(), 1.0, myTolerance) << "Cylinder radius should match";
}

TEST_F(CanonicalRecognitionBaseSurfaceTest, PlaneDetectionWithGapValidation_Bug33170)
{

  occ::handle<Geom_Plane> aBasePlane = new Geom_Plane(gp_Pln());
  BRepBuilderAPI_MakeFace aFaceMaker(aBasePlane, -1, 1, -1, 1, Precision::Confusion());

  ASSERT_TRUE(aFaceMaker.IsDone()) << "Failed to create base planar face";
  const TopoDS_Face aFace = aFaceMaker.Face();

  myRecognizer->SetShape(aFace);
  gp_Pln     aResultPlane1;
  const bool aResult1 = myRecognizer->IsPlane(0.006, aResultPlane1);

  EXPECT_TRUE(aResult1) << "Surface should be recognized as plane with tolerance 0.006";

  const double aGap1 = myRecognizer->GetGap();
  EXPECT_LT(aGap1, 0.006) << "Gap should be less than tolerance used";
  EXPECT_GE(aGap1, 0.0) << "Gap should be non-negative";

  myRecognizer->ClearStatus();
  gp_Pln     aResultPlane2;
  const bool aResult2 = myRecognizer->IsPlane(1.0, aResultPlane2);

  EXPECT_TRUE(aResult2) << "Surface should be recognized as plane with tolerance 1.0";

  const double aGap2 = myRecognizer->GetGap();
  EXPECT_LT(aGap2, 1.0) << "Gap should be less than tolerance used";
  EXPECT_GE(aGap2, 0.0) << "Gap should be non-negative";

  EXPECT_DOUBLE_EQ(aGap1, aGap2) << "Gap should be the same regardless of tolerance used";
}
