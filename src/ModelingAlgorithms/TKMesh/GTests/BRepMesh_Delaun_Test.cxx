

#include <BRep_Builder.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <BRepMesh_IncrementalMesh.hpp>
#include <BRepPrimAPI_MakeBox.hpp>
#include <BRepPrimAPI_MakeCylinder.hpp>
#include <Geom_Plane.hpp>
#include <Poly_Triangulation.hpp>
#include <Precision.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <gp_Pln.hpp>
#include <gp_Vec2d.hpp>

#include <gtest/gtest.h>

TEST(BRepMesh_DelaunTest, Vec2dAngleSignConvention)
{

  gp_Vec2d aVecRight(1.0, 0.0);
  gp_Vec2d aVecUp(0.0, 1.0);

  const double anAngleCCW = aVecUp.Angle(aVecRight);
  EXPECT_LT(anAngleCCW, 0.0) << "CCW rotation should give negative angle in OCCT convention";
  EXPECT_NEAR(anAngleCCW, -M_PI_2, Precision::Angular());

  const double anAngleCW = aVecRight.Angle(aVecUp);
  EXPECT_GT(anAngleCW, 0.0) << "CW rotation should give positive angle in OCCT convention";
  EXPECT_NEAR(anAngleCW, M_PI_2, Precision::Angular());
}

TEST(BRepMesh_DelaunTest, WindingAngleCCWPolygon)
{

  gp_XY aCenter(0.0, 0.0);
  gp_XY aVertices[5] = {gp_XY(1.0, 0.0),
                        gp_XY(0.0, 1.0),
                        gp_XY(-1.0, 0.0),
                        gp_XY(0.0, -1.0),
                        gp_XY(1.0, 0.0)};

  gp_Vec2d aPrevDir(aVertices[0] - aCenter);
  double   aTotalAngle = 0.0;

  for (int i = 1; i < 5; ++i)
  {
    gp_Vec2d aCurDir(aVertices[i] - aCenter);
    aTotalAngle += aCurDir.Angle(aPrevDir);
    aPrevDir = aCurDir;
  }

  EXPECT_NEAR(std::abs(aTotalAngle), 2.0 * M_PI, Precision::Angular())
    << "Winding angle magnitude should be 2*PI for point inside polygon";

  const double Angle2PI       = 2.0 * M_PI;
  const bool   isInsideOldFix = std::abs(Angle2PI - aTotalAngle) <= Precision::Angular();
  const bool   isInsideNewFix = std::abs(std::abs(aTotalAngle) - Angle2PI) <= Precision::Angular();

  EXPECT_FALSE(isInsideOldFix) << "Old check fails for CCW polygon (angle is negative)";
  EXPECT_TRUE(isInsideNewFix) << "New check handles both CCW and CW polygons";
}

TEST(BRepMesh_DelaunTest, WindingAngleCWPolygon)
{

  gp_XY aCenter(0.0, 0.0);
  gp_XY aVertices[5] = {gp_XY(1.0, 0.0),
                        gp_XY(0.0, -1.0),
                        gp_XY(-1.0, 0.0),
                        gp_XY(0.0, 1.0),
                        gp_XY(1.0, 0.0)};

  gp_Vec2d aPrevDir(aVertices[0] - aCenter);
  double   aTotalAngle = 0.0;

  for (int i = 1; i < 5; ++i)
  {
    gp_Vec2d aCurDir(aVertices[i] - aCenter);
    aTotalAngle += aCurDir.Angle(aPrevDir);
    aPrevDir = aCurDir;
  }

  EXPECT_NEAR(aTotalAngle, 2.0 * M_PI, Precision::Angular())
    << "Winding angle should be +2*PI for CW polygon";

  const double Angle2PI       = 2.0 * M_PI;
  const bool   isInsideOldFix = std::abs(Angle2PI - aTotalAngle) <= Precision::Angular();
  const bool   isInsideNewFix = std::abs(std::abs(aTotalAngle) - Angle2PI) <= Precision::Angular();

  EXPECT_TRUE(isInsideOldFix) << "Old check works for CW polygon";
  EXPECT_TRUE(isInsideNewFix) << "New check also works for CW polygon";
}

TEST(BRepMesh_DelaunTest, MeshPlanarFaceWithHole)
{

  gp_Pnt aP1(-5.0, -5.0, 0.0);
  gp_Pnt aP2(5.0, -5.0, 0.0);
  gp_Pnt aP3(5.0, 5.0, 0.0);
  gp_Pnt aP4(-5.0, 5.0, 0.0);

  BRepBuilderAPI_MakeWire anOuterWireMaker;
  anOuterWireMaker.Add(BRepBuilderAPI_MakeEdge(aP1, aP2));
  anOuterWireMaker.Add(BRepBuilderAPI_MakeEdge(aP2, aP3));
  anOuterWireMaker.Add(BRepBuilderAPI_MakeEdge(aP3, aP4));
  anOuterWireMaker.Add(BRepBuilderAPI_MakeEdge(aP4, aP1));
  ASSERT_TRUE(anOuterWireMaker.IsDone());

  gp_Pnt aH1(-1.0, -1.0, 0.0);
  gp_Pnt aH2(1.0, -1.0, 0.0);
  gp_Pnt aH3(1.0, 1.0, 0.0);
  gp_Pnt aH4(-1.0, 1.0, 0.0);

  BRepBuilderAPI_MakeWire anInnerWireMaker;
  anInnerWireMaker.Add(BRepBuilderAPI_MakeEdge(aH1, aH2));
  anInnerWireMaker.Add(BRepBuilderAPI_MakeEdge(aH2, aH3));
  anInnerWireMaker.Add(BRepBuilderAPI_MakeEdge(aH3, aH4));
  anInnerWireMaker.Add(BRepBuilderAPI_MakeEdge(aH4, aH1));
  ASSERT_TRUE(anInnerWireMaker.IsDone());

  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pln(gp::Origin(), gp::DZ()));
  BRepBuilderAPI_MakeFace aFaceMaker(aPlane, anOuterWireMaker.Wire());
  aFaceMaker.Add(anInnerWireMaker.Wire());
  ASSERT_TRUE(aFaceMaker.IsDone());

  TopoDS_Face aFace = aFaceMaker.Face();

  BRepMesh_IncrementalMesh aMesher(aFace, 0.1);
  EXPECT_TRUE(aMesher.IsDone()) << "Meshing should succeed";

  TopLoc_Location                       aLoc;
  const occ::handle<Poly_Triangulation> aTri = BRep_Tool::Triangulation(aFace, aLoc);
  ASSERT_FALSE(aTri.IsNull()) << "Triangulation should be created";
  EXPECT_GT(aTri->NbTriangles(), 0) << "Should have triangles";
  EXPECT_GT(aTri->NbNodes(), 0) << "Should have nodes";
}

TEST(BRepMesh_DelaunTest, MeshBoxAllFaces)
{

  TopoDS_Shape aBox = BRepPrimAPI_MakeBox(10.0, 10.0, 10.0).Shape();

  BRepMesh_IncrementalMesh aMesher(aBox, 0.5);
  EXPECT_TRUE(aMesher.IsDone()) << "Meshing should succeed";

  int aFaceCount = 0;
  for (TopExp_Explorer anExp(aBox, TopAbs_FACE); anExp.More(); anExp.Next())
  {
    const TopoDS_Face&                    aFace = TopoDS::Face(anExp.Current());
    TopLoc_Location                       aLoc;
    const occ::handle<Poly_Triangulation> aTri = BRep_Tool::Triangulation(aFace, aLoc);

    EXPECT_FALSE(aTri.IsNull()) << "Face " << aFaceCount << " should have triangulation";
    if (!aTri.IsNull())
    {
      EXPECT_GT(aTri->NbTriangles(), 0) << "Face " << aFaceCount << " should have triangles";
    }
    ++aFaceCount;
  }

  EXPECT_EQ(aFaceCount, 6) << "Box should have 6 faces";
}

TEST(BRepMesh_DelaunTest, MeshCylinderCurvedFaces)
{

  TopoDS_Shape aCylinder = BRepPrimAPI_MakeCylinder(5.0, 10.0).Shape();

  BRepMesh_IncrementalMesh aMesher(aCylinder, 0.5);
  EXPECT_TRUE(aMesher.IsDone()) << "Meshing should succeed";

  int aTotalTriangles = 0;
  for (TopExp_Explorer anExp(aCylinder, TopAbs_FACE); anExp.More(); anExp.Next())
  {
    const TopoDS_Face&                    aFace = TopoDS::Face(anExp.Current());
    TopLoc_Location                       aLoc;
    const occ::handle<Poly_Triangulation> aTri = BRep_Tool::Triangulation(aFace, aLoc);

    EXPECT_FALSE(aTri.IsNull()) << "Face should have triangulation";
    if (!aTri.IsNull())
    {
      aTotalTriangles += aTri->NbTriangles();
    }
  }

  EXPECT_GT(aTotalTriangles, 0) << "Cylinder should have triangles";
}
