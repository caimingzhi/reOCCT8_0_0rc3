

#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepMesh_GeomTool.hpp>
#include <Geom_Circle.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <Precision.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pln.hpp>

#include <gtest/gtest.h>

TEST(BRepMesh_GeomTool_Test, OCC25547_StaticMethodsExportAndFunctionality)
{

  const double                   aFirstP = 0., aLastP = M_PI;
  occ::handle<Geom_Circle>       aCircle = new Geom_Circle(gp_Ax2(gp::Origin(), gp::DZ()), 10);
  occ::handle<Geom_TrimmedCurve> aHalf   = new Geom_TrimmedCurve(aCircle, aFirstP, aLastP);
  TopoDS_Edge                    anEdge  = BRepBuilderAPI_MakeEdge(aHalf);
  BRepAdaptor_Curve              anAdaptor(anEdge);
  BRepMesh_GeomTool              aGeomTool(anAdaptor, aFirstP, aLastP, 0.1, 0.5);

  EXPECT_GT(aGeomTool.NbPoints(), 0) << "BRepMesh_GeomTool failed to discretize an arc";

  TopoDS_Face                      aFace = BRepBuilderAPI_MakeFace(gp_Pln(gp::Origin(), gp::DZ()));
  BRepAdaptor_Surface              aSurf(aFace);
  occ::handle<BRepAdaptor_Surface> aHSurf = new BRepAdaptor_Surface(aSurf);

  gp_Pnt aPnt;
  gp_Dir aNormal;
  bool   isNormalComputed = BRepMesh_GeomTool::Normal(aHSurf, 10., 10., aPnt, aNormal);

  EXPECT_TRUE(isNormalComputed) << "BRepMesh_GeomTool failed to compute a normal of surface";

  gp_XY aRefPnts[4] = {gp_XY(-10., -10.), gp_XY(10., 10.), gp_XY(-10., 10.), gp_XY(10., -10.)};

  gp_Pnt2d                   anIntPnt;
  double                     aParams[2];
  BRepMesh_GeomTool::IntFlag anIntFlag = BRepMesh_GeomTool::IntLinLin(aRefPnts[0],
                                                                      aRefPnts[1],
                                                                      aRefPnts[2],
                                                                      aRefPnts[3],
                                                                      anIntPnt.ChangeCoord(),
                                                                      aParams);

  double aDiff = anIntPnt.Distance(gp::Origin2d());
  EXPECT_EQ(anIntFlag, BRepMesh_GeomTool::Cross)
    << "BRepMesh_GeomTool::IntLinLin should return Cross flag";
  EXPECT_LE(aDiff, Precision::PConfusion())
    << "BRepMesh_GeomTool failed to intersect two lines at origin";

  anIntFlag = BRepMesh_GeomTool::IntSegSeg(aRefPnts[0],
                                           aRefPnts[1],
                                           aRefPnts[2],
                                           aRefPnts[3],
                                           false,
                                           false,
                                           anIntPnt);

  aDiff = anIntPnt.Distance(gp::Origin2d());
  EXPECT_EQ(anIntFlag, BRepMesh_GeomTool::Cross)
    << "BRepMesh_GeomTool::IntSegSeg should return Cross flag";
  EXPECT_LE(aDiff, Precision::PConfusion())
    << "BRepMesh_GeomTool failed to intersect two segments at origin";
}
