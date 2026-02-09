

#include <gtest/gtest.h>

#include <Geom_BezierSurface.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomGridEval_BezierSurface.hpp>
#include <GeomGridEval_BSplineSurface.hpp>
#include <GeomGridEval_Cone.hpp>
#include <GeomGridEval_Cylinder.hpp>
#include <GeomGridEval_OtherSurface.hpp>
#include <GeomGridEval_Plane.hpp>
#include <GeomGridEval_Sphere.hpp>
#include <GeomGridEval_Surface.hpp>
#include <GeomGridEval_Torus.hpp>
#include <gp_Ax3.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Sphere.hpp>
#include <NCollection_Array2.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

#include <cmath>

namespace
{
  const double THE_TOLERANCE = 1e-10;

  NCollection_Array1<double> CreateUniformParams(double theFirst, double theLast, int theNbPoints)
  {
    NCollection_Array1<double> aParams(1, theNbPoints);
    const double               aStep = (theLast - theFirst) / (theNbPoints - 1);
    for (int i = 1; i <= theNbPoints; ++i)
    {
      aParams.SetValue(i, theFirst + (i - 1) * aStep);
    }
    return aParams;
  }

  occ::handle<Geom_BSplineSurface> CreateSimpleBSplineSurface()
  {
    NCollection_Array2<gp_Pnt> aPoles(1, 2, 1, 2);
    aPoles.SetValue(1, 1, gp_Pnt(0, 0, 0));
    aPoles.SetValue(2, 1, gp_Pnt(1, 0, 0));
    aPoles.SetValue(1, 2, gp_Pnt(0, 1, 0));
    aPoles.SetValue(2, 2, gp_Pnt(1, 1, 1));

    NCollection_Array1<double> aUKnots(1, 2);
    NCollection_Array1<double> aVKnots(1, 2);
    NCollection_Array1<int>    aUMults(1, 2);
    NCollection_Array1<int>    aVMults(1, 2);

    aUKnots.SetValue(1, 0.0);
    aUKnots.SetValue(2, 1.0);
    aVKnots.SetValue(1, 0.0);
    aVKnots.SetValue(2, 1.0);
    aUMults.SetValue(1, 2);
    aUMults.SetValue(2, 2);
    aVMults.SetValue(1, 2);
    aVMults.SetValue(2, 2);

    return new Geom_BSplineSurface(aPoles, aUKnots, aVKnots, aUMults, aVMults, 1, 1);
  }
} // namespace

TEST(GeomGridEval_PlaneTest, BasicEvaluation)
{

  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));

  GeomGridEval_Plane anEval(aPlane);
  EXPECT_FALSE(anEval.Geometry().IsNull());

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 5.0, 6);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 3.0, 4);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);
  EXPECT_EQ(aGrid.RowLength(), 4);
  EXPECT_EQ(aGrid.ColLength(), 6);

  for (int iU = 1; iU <= 6; ++iU)
  {
    for (int iV = 1; iV <= 4; ++iV)
    {
      const gp_Pnt& aPnt = aGrid.Value(iU, iV);
      EXPECT_NEAR(aPnt.Z(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR(aPnt.X(), aUParams.Value(iU), THE_TOLERANCE);
      EXPECT_NEAR(aPnt.Y(), aVParams.Value(iV), THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_PlaneTest, NonOriginPlane)
{

  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pnt(1, 2, 3), gp_Dir(0, 0, 1));

  GeomGridEval_Plane anEval(aPlane);

  NCollection_Array1<double> aUParams = CreateUniformParams(-1.0, 1.0, 3);
  NCollection_Array1<double> aVParams = CreateUniformParams(-1.0, 1.0, 3);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  for (int iU = 1; iU <= 3; ++iU)
  {
    for (int iV = 1; iV <= 3; ++iV)
    {
      EXPECT_NEAR(aGrid.Value(iU, iV).Z(), 3.0, THE_TOLERANCE);
    }
  }

  EXPECT_NEAR(aGrid.Value(2, 2).X(), 1.0, THE_TOLERANCE);
  EXPECT_NEAR(aGrid.Value(2, 2).Y(), 2.0, THE_TOLERANCE);
}

TEST(GeomGridEval_SphereTest, BasicEvaluation)
{

  occ::handle<Geom_SphericalSurface> aSphere =
    new Geom_SphericalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 1.0);

  GeomGridEval_Sphere anEval(aSphere);
  EXPECT_FALSE(anEval.Geometry().IsNull());

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(-M_PI / 2, M_PI / 2, 5);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  for (int iU = 1; iU <= 9; ++iU)
  {
    for (int iV = 1; iV <= 5; ++iV)
    {
      double aDist = aGrid.Value(iU, iV).Distance(gp_Pnt(0, 0, 0));
      EXPECT_NEAR(aDist, 1.0, THE_TOLERANCE);
    }
  }

  for (int iU = 1; iU <= 9; ++iU)
  {
    EXPECT_NEAR(aGrid.Value(iU, 5).X(), 0.0, THE_TOLERANCE);
    EXPECT_NEAR(aGrid.Value(iU, 5).Y(), 0.0, THE_TOLERANCE);
    EXPECT_NEAR(aGrid.Value(iU, 5).Z(), 1.0, THE_TOLERANCE);
  }

  for (int iU = 1; iU <= 9; ++iU)
  {
    EXPECT_NEAR(aGrid.Value(iU, 1).X(), 0.0, THE_TOLERANCE);
    EXPECT_NEAR(aGrid.Value(iU, 1).Y(), 0.0, THE_TOLERANCE);
    EXPECT_NEAR(aGrid.Value(iU, 1).Z(), -1.0, THE_TOLERANCE);
  }
}

TEST(GeomGridEval_SphereTest, NonUnitSphere)
{

  occ::handle<Geom_SphericalSurface> aSphere =
    new Geom_SphericalSurface(gp_Ax3(gp_Pnt(1, 2, 3), gp_Dir(0, 0, 1)), 3.0);

  GeomGridEval_Sphere anEval(aSphere);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 17);
  NCollection_Array1<double> aVParams = CreateUniformParams(-M_PI / 2, M_PI / 2, 9);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  const gp_Pnt aCenter(1, 2, 3);
  for (int iU = 1; iU <= 17; ++iU)
  {
    for (int iV = 1; iV <= 9; ++iV)
    {
      double aDist = aGrid.Value(iU, iV).Distance(aCenter);
      EXPECT_NEAR(aDist, 3.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_OtherSurfaceTest, CylinderFallback)
{

  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 2.0);
  GeomAdaptor_Surface anAdaptor(aCyl);

  GeomGridEval_OtherSurface anEval(&anAdaptor);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 6);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  for (int iU = 1; iU <= 9; ++iU)
  {
    for (int iV = 1; iV <= 6; ++iV)
    {
      gp_Pnt aExpected = aCyl->Value(aUParams.Value(iU), aVParams.Value(iV));
      EXPECT_NEAR(aGrid.Value(iU, iV).Distance(aExpected), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SurfaceTest, PlaneDispatch)
{
  occ::handle<Geom_Plane> aGeomPlane = new Geom_Plane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  GeomAdaptor_Surface     anAdaptor(aGeomPlane);

  GeomGridEval_Surface anEval;
  anEval.Initialize(anAdaptor);
  EXPECT_TRUE(anEval.IsInitialized());
  EXPECT_EQ(anEval.GetType(), GeomAbs_Plane);

  NCollection_Array1<double> aUParams = CreateUniformParams(-5.0, 5.0, 11);
  NCollection_Array1<double> aVParams = CreateUniformParams(-3.0, 3.0, 7);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  for (int iU = 1; iU <= 11; ++iU)
  {
    for (int iV = 1; iV <= 7; ++iV)
    {
      gp_Pnt aExpected = aGeomPlane->Value(aUParams.Value(iU), aVParams.Value(iV));
      EXPECT_NEAR(aGrid.Value(iU, iV).Distance(aExpected), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SurfaceTest, SphereDispatch)
{
  occ::handle<Geom_SphericalSurface> aGeomSphere =
    new Geom_SphericalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 2.0);
  GeomAdaptor_Surface anAdaptor(aGeomSphere);

  GeomGridEval_Surface anEval;
  anEval.Initialize(anAdaptor);
  EXPECT_TRUE(anEval.IsInitialized());
  EXPECT_EQ(anEval.GetType(), GeomAbs_Sphere);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 13);
  NCollection_Array1<double> aVParams = CreateUniformParams(-M_PI / 2, M_PI / 2, 7);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  for (int iU = 1; iU <= 13; ++iU)
  {
    for (int iV = 1; iV <= 7; ++iV)
    {
      gp_Pnt aExpected = aGeomSphere->Value(aUParams.Value(iU), aVParams.Value(iV));
      EXPECT_NEAR(aGrid.Value(iU, iV).Distance(aExpected), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SurfaceTest, BSplineDispatch)
{
  occ::handle<Geom_BSplineSurface> aSurf = CreateSimpleBSplineSurface();
  GeomAdaptor_Surface              anAdaptor(aSurf);

  GeomGridEval_Surface anEval;
  anEval.Initialize(anAdaptor);
  EXPECT_TRUE(anEval.IsInitialized());
  EXPECT_EQ(anEval.GetType(), GeomAbs_BSplineSurface);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 1.0, 11);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 1.0, 11);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  for (int iU = 1; iU <= 11; ++iU)
  {
    for (int iV = 1; iV <= 11; ++iV)
    {
      gp_Pnt aExpected = aSurf->Value(aUParams.Value(iU), aVParams.Value(iV));
      EXPECT_NEAR(aGrid.Value(iU, iV).Distance(aExpected), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SurfaceTest, BezierSurfaceDispatch)
{
  NCollection_Array2<gp_Pnt> aPoles(1, 2, 1, 2);
  aPoles.SetValue(1, 1, gp_Pnt(0, 0, 0));
  aPoles.SetValue(2, 1, gp_Pnt(1, 0, 0));
  aPoles.SetValue(1, 2, gp_Pnt(0, 1, 0));
  aPoles.SetValue(2, 2, gp_Pnt(1, 1, 0));
  occ::handle<Geom_BezierSurface> aBezier = new Geom_BezierSurface(aPoles);
  GeomAdaptor_Surface             anAdaptor(aBezier);

  GeomGridEval_Surface anEval;
  anEval.Initialize(anAdaptor);
  EXPECT_TRUE(anEval.IsInitialized());
  EXPECT_EQ(anEval.GetType(), GeomAbs_BezierSurface);

  NCollection_Array1<double> aParams = CreateUniformParams(0.0, 1.0, 5);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aParams, aParams);

  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 5; ++j)
    {
      gp_Pnt aExpected = aBezier->Value(aParams.Value(i), aParams.Value(j));
      EXPECT_NEAR(aGrid.Value(i, j).Distance(aExpected), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SurfaceTest, CylinderDispatch)
{
  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 2.0);
  GeomAdaptor_Surface anAdaptor(aCyl);

  GeomGridEval_Surface anEval;
  anEval.Initialize(anAdaptor);
  EXPECT_TRUE(anEval.IsInitialized());
  EXPECT_EQ(anEval.GetType(), GeomAbs_Cylinder);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 6);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  for (int iU = 1; iU <= 9; ++iU)
  {
    for (int iV = 1; iV <= 6; ++iV)
    {
      gp_Pnt aExpected = aCyl->Value(aUParams.Value(iU), aVParams.Value(iV));
      EXPECT_NEAR(aGrid.Value(iU, iV).Distance(aExpected), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SurfaceTest, TorusDispatch)
{
  occ::handle<Geom_ToroidalSurface> aTorus =
    new Geom_ToroidalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 4.0, 1.0);
  GeomAdaptor_Surface anAdaptor(aTorus);

  GeomGridEval_Surface anEval;
  anEval.Initialize(anAdaptor);
  EXPECT_TRUE(anEval.IsInitialized());
  EXPECT_EQ(anEval.GetType(), GeomAbs_Torus);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 2 * M_PI, 9);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  for (int iU = 1; iU <= 9; ++iU)
  {
    for (int iV = 1; iV <= 9; ++iV)
    {
      gp_Pnt aExpected = aTorus->Value(aUParams.Value(iU), aVParams.Value(iV));
      EXPECT_NEAR(aGrid.Value(iU, iV).Distance(aExpected), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SurfaceTest, ConeDispatch)
{
  occ::handle<Geom_ConicalSurface> aCone =
    new Geom_ConicalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), M_PI / 4, 1.0);
  GeomAdaptor_Surface anAdaptor(aCone);

  GeomGridEval_Surface anEval;
  anEval.Initialize(anAdaptor);
  EXPECT_TRUE(anEval.IsInitialized());
  EXPECT_EQ(anEval.GetType(), GeomAbs_Cone);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 6);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  for (int iU = 1; iU <= 9; ++iU)
  {
    for (int iV = 1; iV <= 6; ++iV)
    {
      gp_Pnt aExpected = aCone->Value(aUParams.Value(iU), aVParams.Value(iV));
      EXPECT_NEAR(aGrid.Value(iU, iV).Distance(aExpected), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SurfaceTest, SurfaceOfRevolutionFallbackDispatch)
{

  occ::handle<Geom_Line>                aLine    = new Geom_Line(gp_Pnt(1, 0, 0), gp_Dir(0, 0, 1));
  occ::handle<Geom_SurfaceOfRevolution> aRevSurf = new Geom_SurfaceOfRevolution(aLine, gp::OZ());

  GeomAdaptor_Surface anAdaptor(aRevSurf);

  GeomGridEval_Surface anEval;
  anEval.Initialize(anAdaptor);
  EXPECT_TRUE(anEval.IsInitialized());
  EXPECT_EQ(anEval.GetType(), GeomAbs_SurfaceOfRevolution);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 6);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  for (int iU = 1; iU <= 9; ++iU)
  {
    for (int iV = 1; iV <= 6; ++iV)
    {
      gp_Pnt aExpected = aRevSurf->Value(aUParams.Value(iU), aVParams.Value(iV));
      EXPECT_NEAR(aGrid.Value(iU, iV).Distance(aExpected), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SurfaceTest, DirectHandleInit)
{
  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));

  GeomGridEval_Surface anEval;
  anEval.Initialize(aPlane);

  EXPECT_TRUE(anEval.IsInitialized());
  EXPECT_EQ(anEval.GetType(), GeomAbs_Plane);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 1.0, 5);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 1.0, 5);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);
  EXPECT_FALSE(aGrid.IsEmpty());

  EXPECT_NEAR(aGrid.Value(1, 1).Z(), 0.0, THE_TOLERANCE);
}

TEST(GeomGridEval_SurfaceTest, UninitializedState)
{
  GeomGridEval_Surface anEval;
  EXPECT_FALSE(anEval.IsInitialized());

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 1.0, 5);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 1.0, 5);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);
  EXPECT_TRUE(aGrid.IsEmpty());
}

TEST(GeomGridEval_SurfaceTest, EmptyParams)
{
  occ::handle<Geom_Plane> aGeomPlane = new Geom_Plane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  GeomAdaptor_Surface     anAdaptor(aGeomPlane);

  GeomGridEval_Surface anEval;
  anEval.Initialize(anAdaptor);
  EXPECT_TRUE(anEval.IsInitialized());

  NCollection_Array1<double> aEmptyParams;
  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aEmptyParams, aEmptyParams);
  EXPECT_TRUE(aGrid.IsEmpty());
}

TEST(GeomGridEval_PlaneTest, DerivativeD1)
{

  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  GeomGridEval_Plane      anEval(aPlane);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 5.0, 6);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 3.0, 4);

  NCollection_Array2<GeomGridEval::SurfD1> aGrid = anEval.EvaluateGridD1(aUParams, aVParams);

  gp_Pnt aPnt;
  gp_Vec aD1URef, aD1VRef;
  aPlane->D1(0.0, 0.0, aPnt, aD1URef, aD1VRef);

  for (int iU = 1; iU <= 6; ++iU)
  {
    for (int iV = 1; iV <= 4; ++iV)
    {
      EXPECT_NEAR((aGrid.Value(iU, iV).D1U - aD1URef).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D1V - aD1VRef).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_PlaneTest, DerivativeD2)
{
  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  GeomGridEval_Plane      anEval(aPlane);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 5.0, 6);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 3.0, 4);

  NCollection_Array2<GeomGridEval::SurfD2> aGrid = anEval.EvaluateGridD2(aUParams, aVParams);

  for (int iU = 1; iU <= 6; ++iU)
  {
    for (int iV = 1; iV <= 4; ++iV)
    {
      EXPECT_NEAR(aGrid.Value(iU, iV).D2U.Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR(aGrid.Value(iU, iV).D2V.Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR(aGrid.Value(iU, iV).D2UV.Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SphereTest, DerivativeD1)
{
  occ::handle<Geom_SphericalSurface> aSphere =
    new Geom_SphericalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 2.0);
  GeomGridEval_Sphere anEval(aSphere);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(-M_PI / 2, M_PI / 2, 5);

  NCollection_Array2<GeomGridEval::SurfD1> aGrid = anEval.EvaluateGridD1(aUParams, aVParams);

  for (int iU = 1; iU <= 9; ++iU)
  {
    for (int iV = 1; iV <= 5; ++iV)
    {
      gp_Pnt aPnt;
      gp_Vec aD1U, aD1V;
      aSphere->D1(aUParams.Value(iU), aVParams.Value(iV), aPnt, aD1U, aD1V);
      EXPECT_NEAR(aGrid.Value(iU, iV).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D1U - aD1U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D1V - aD1V).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SphereTest, DerivativeD2)
{
  occ::handle<Geom_SphericalSurface> aSphere =
    new Geom_SphericalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 2.0);
  GeomGridEval_Sphere anEval(aSphere);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(-M_PI / 2, M_PI / 2, 5);

  NCollection_Array2<GeomGridEval::SurfD2> aGrid = anEval.EvaluateGridD2(aUParams, aVParams);

  for (int iU = 1; iU <= 9; ++iU)
  {
    for (int iV = 1; iV <= 5; ++iV)
    {
      gp_Pnt aPnt;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV;
      aSphere->D2(aUParams.Value(iU), aVParams.Value(iV), aPnt, aD1U, aD1V, aD2U, aD2V, aD2UV);
      EXPECT_NEAR(aGrid.Value(iU, iV).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D1U - aD1U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D1V - aD1V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D2U - aD2U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D2V - aD2V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D2UV - aD2UV).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SurfaceTest, UnifiedDerivativeD1)
{
  occ::handle<Geom_SphericalSurface> aSphere =
    new Geom_SphericalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 2.0);
  GeomAdaptor_Surface anAdaptor(aSphere);

  GeomGridEval_Surface anEval;
  anEval.Initialize(anAdaptor);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(-M_PI / 2, M_PI / 2, 5);

  NCollection_Array2<GeomGridEval::SurfD1> aGrid = anEval.EvaluateGridD1(aUParams, aVParams);

  for (int iU = 1; iU <= 9; ++iU)
  {
    for (int iV = 1; iV <= 5; ++iV)
    {
      gp_Pnt aPnt;
      gp_Vec aD1U, aD1V;
      aSphere->D1(aUParams.Value(iU), aVParams.Value(iV), aPnt, aD1U, aD1V);
      EXPECT_NEAR(aGrid.Value(iU, iV).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D1U - aD1U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D1V - aD1V).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SurfaceTest, UnifiedDerivativeD2)
{
  occ::handle<Geom_BSplineSurface> aSurf = CreateSimpleBSplineSurface();
  GeomAdaptor_Surface              anAdaptor(aSurf);

  GeomGridEval_Surface anEval;
  anEval.Initialize(anAdaptor);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 1.0, 5);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 1.0, 5);

  NCollection_Array2<GeomGridEval::SurfD2> aGrid = anEval.EvaluateGridD2(aUParams, aVParams);

  for (int iU = 1; iU <= 5; ++iU)
  {
    for (int iV = 1; iV <= 5; ++iV)
    {
      gp_Pnt aPnt;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV;
      aSurf->D2(aUParams.Value(iU), aVParams.Value(iV), aPnt, aD1U, aD1V, aD2U, aD2V, aD2UV);
      EXPECT_NEAR(aGrid.Value(iU, iV).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D1U - aD1U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D1V - aD1V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D2U - aD2U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D2V - aD2V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D2UV - aD2UV).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_PlaneTest, DerivativeD3)
{
  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  GeomGridEval_Plane      anEval(aPlane);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 5.0, 6);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 3.0, 4);

  NCollection_Array2<GeomGridEval::SurfD3> aGrid = anEval.EvaluateGridD3(aUParams, aVParams);

  for (int iU = 1; iU <= 6; ++iU)
  {
    for (int iV = 1; iV <= 4; ++iV)
    {
      EXPECT_NEAR(aGrid.Value(iU, iV).D2U.Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR(aGrid.Value(iU, iV).D2V.Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR(aGrid.Value(iU, iV).D2UV.Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR(aGrid.Value(iU, iV).D3U.Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR(aGrid.Value(iU, iV).D3V.Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR(aGrid.Value(iU, iV).D3UUV.Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR(aGrid.Value(iU, iV).D3UVV.Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SphereTest, DerivativeD3)
{
  occ::handle<Geom_SphericalSurface> aSphere =
    new Geom_SphericalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 2.0);
  GeomGridEval_Sphere anEval(aSphere);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(-M_PI / 2 + 0.1, M_PI / 2 - 0.1, 5);

  NCollection_Array2<GeomGridEval::SurfD3> aGrid = anEval.EvaluateGridD3(aUParams, aVParams);

  GeomAdaptor_Surface anAdaptor(aSphere);
  for (int iU = 1; iU <= 9; ++iU)
  {
    for (int iV = 1; iV <= 5; ++iV)
    {
      gp_Pnt aPnt;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;
      anAdaptor.D3(aUParams.Value(iU),
                   aVParams.Value(iV),
                   aPnt,
                   aD1U,
                   aD1V,
                   aD2U,
                   aD2V,
                   aD2UV,
                   aD3U,
                   aD3V,
                   aD3UUV,
                   aD3UVV);
      EXPECT_NEAR(aGrid.Value(iU, iV).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D1U - aD1U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D1V - aD1V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D2U - aD2U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D2V - aD2V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D2UV - aD2UV).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3U - aD3U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3V - aD3V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3UUV - aD3UUV).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3UVV - aD3UVV).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_CylinderTest, DerivativeD3)
{
  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 2.0);
  GeomGridEval_Cylinder anEval(aCyl);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 6);

  NCollection_Array2<GeomGridEval::SurfD3> aGrid = anEval.EvaluateGridD3(aUParams, aVParams);

  GeomAdaptor_Surface anAdaptor(aCyl);
  for (int iU = 1; iU <= 9; ++iU)
  {
    for (int iV = 1; iV <= 6; ++iV)
    {
      gp_Pnt aPnt;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;
      anAdaptor.D3(aUParams.Value(iU),
                   aVParams.Value(iV),
                   aPnt,
                   aD1U,
                   aD1V,
                   aD2U,
                   aD2V,
                   aD2UV,
                   aD3U,
                   aD3V,
                   aD3UUV,
                   aD3UVV);
      EXPECT_NEAR(aGrid.Value(iU, iV).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3U - aD3U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3V - aD3V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3UUV - aD3UUV).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3UVV - aD3UVV).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_ConeTest, DerivativeD3)
{
  occ::handle<Geom_ConicalSurface> aCone =
    new Geom_ConicalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), M_PI / 4, 1.0);
  GeomGridEval_Cone anEval(aCone);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 6);

  NCollection_Array2<GeomGridEval::SurfD3> aGrid = anEval.EvaluateGridD3(aUParams, aVParams);

  GeomAdaptor_Surface anAdaptor(aCone);
  for (int iU = 1; iU <= 9; ++iU)
  {
    for (int iV = 1; iV <= 6; ++iV)
    {
      gp_Pnt aPnt;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;
      anAdaptor.D3(aUParams.Value(iU),
                   aVParams.Value(iV),
                   aPnt,
                   aD1U,
                   aD1V,
                   aD2U,
                   aD2V,
                   aD2UV,
                   aD3U,
                   aD3V,
                   aD3UUV,
                   aD3UVV);
      EXPECT_NEAR(aGrid.Value(iU, iV).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3U - aD3U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3V - aD3V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3UUV - aD3UUV).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3UVV - aD3UVV).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_TorusTest, DerivativeD3)
{
  occ::handle<Geom_ToroidalSurface> aTorus =
    new Geom_ToroidalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 4.0, 1.0);
  GeomGridEval_Torus anEval(aTorus);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 2 * M_PI, 9);

  NCollection_Array2<GeomGridEval::SurfD3> aGrid = anEval.EvaluateGridD3(aUParams, aVParams);

  GeomAdaptor_Surface anAdaptor(aTorus);
  for (int iU = 1; iU <= 9; ++iU)
  {
    for (int iV = 1; iV <= 9; ++iV)
    {
      gp_Pnt aPnt;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;
      anAdaptor.D3(aUParams.Value(iU),
                   aVParams.Value(iV),
                   aPnt,
                   aD1U,
                   aD1V,
                   aD2U,
                   aD2V,
                   aD2UV,
                   aD3U,
                   aD3V,
                   aD3UUV,
                   aD3UVV);
      EXPECT_NEAR(aGrid.Value(iU, iV).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3U - aD3U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3V - aD3V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3UUV - aD3UUV).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3UVV - aD3UVV).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_SurfaceTest, UnifiedDerivativeD3)
{
  occ::handle<Geom_ToroidalSurface> aTorus =
    new Geom_ToroidalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 4.0, 1.0);
  GeomAdaptor_Surface anAdaptor(aTorus);

  GeomGridEval_Surface anEval;
  anEval.Initialize(anAdaptor);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 2 * M_PI, 9);

  NCollection_Array2<GeomGridEval::SurfD3> aGrid = anEval.EvaluateGridD3(aUParams, aVParams);

  for (int iU = 1; iU <= 9; ++iU)
  {
    for (int iV = 1; iV <= 9; ++iV)
    {
      gp_Pnt aPnt;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;
      aTorus->D3(aUParams.Value(iU),
                 aVParams.Value(iV),
                 aPnt,
                 aD1U,
                 aD1V,
                 aD2U,
                 aD2V,
                 aD2UV,
                 aD3U,
                 aD3V,
                 aD3UUV,
                 aD3UVV);
      EXPECT_NEAR(aGrid.Value(iU, iV).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3U - aD3U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3V - aD3V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3UUV - aD3UUV).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(iU, iV).D3UVV - aD3UVV).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}
