

#include <gtest/gtest.h>

#include <ShapeConstruct_ProjectCurveOnSurface.hpp>
#include <ShapeAnalysis_Surface.hpp>

#include <GC_MakeSegment.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_Circle.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Plane.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAPI_PointsToBSpline.hpp>
#include <gp_Ax2.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <ShapeExtend.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <Standard_Integer.hpp>

class ShapeConstruct_ProjectCurveOnSurfaceTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    myProjector = new ShapeConstruct_ProjectCurveOnSurface();
    myTolerance = Precision::Confusion();
  }

  occ::handle<Geom_BSplineCurve> createPlanarBSpline()
  {
    NCollection_Array1<gp_Pnt> aPoles(1, 5);
    aPoles(1) = gp_Pnt(0, 0, 0);
    aPoles(2) = gp_Pnt(2, 3, 0);
    aPoles(3) = gp_Pnt(5, 4, 0);
    aPoles(4) = gp_Pnt(8, 2, 0);
    aPoles(5) = gp_Pnt(10, 0, 0);

    GeomAPI_PointsToBSpline aBuilder(aPoles);
    return aBuilder.Curve();
  }

  occ::handle<Geom_BSplineCurve> createHelicalBSpline(const double theRadius, const int theNbPoints)
  {
    NCollection_Array1<gp_Pnt> aPoles(1, theNbPoints);
    for (int i = 1; i <= theNbPoints; ++i)
    {
      const double anAngle = (i - 1) * M_PI / 4.0;
      const double aZ      = (i - 1) * 1.0;
      aPoles(i)            = gp_Pnt(theRadius * cos(anAngle), theRadius * sin(anAngle), aZ);
    }
    GeomAPI_PointsToBSpline aBuilder(aPoles);
    return aBuilder.Curve();
  }

  void verifyProjection(const occ::handle<Geom_Curve>&            theCurve,
                        const occ::handle<Geom2d_Curve>&          thePCurve,
                        const occ::handle<ShapeAnalysis_Surface>& theSurface,
                        const double                              theTolerance)
  {
    const double aFirst = theCurve->FirstParameter();
    const double aLast  = theCurve->LastParameter();

    for (double t = 0.0; t <= 1.0; t += 0.25)
    {
      const double aParam = aFirst + t * (aLast - aFirst);
      gp_Pnt       a3DPnt;
      theCurve->D0(aParam, a3DPnt);

      const gp_Pnt2d a2DPnt   = thePCurve->Value(aParam);
      gp_Pnt         aSurfPnt = theSurface->Value(a2DPnt);

      EXPECT_NEAR(a3DPnt.Distance(aSurfPnt), 0.0, theTolerance) << "Point mismatch at t=" << t;
    }
  }

  occ::handle<ShapeConstruct_ProjectCurveOnSurface> myProjector;
  double                                            myTolerance;
};

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, LineOnPlane_A1)
{
  occ::handle<Geom_Plane>        aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
  occ::handle<Geom_TrimmedCurve> aLine = GC_MakeSegment(gp_Pnt(0, 0, 0), gp_Pnt(10, 10, 0)).Value();

  occ::handle<ShapeAnalysis_Surface> aSAS = new ShapeAnalysis_Surface(aPlane);
  myProjector->Init(aSAS, myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const double              aFirst  = aLine->FirstParameter();
  const double              aLast   = aLine->LastParameter();
  const bool                aResult = myProjector->Perform(aLine, aFirst, aLast, aPCurve);

  ASSERT_TRUE(aResult) << "Projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull()) << "PCurve should not be null";

  const gp_Pnt2d aStart = aPCurve->Value(aFirst);
  const gp_Pnt2d aEnd   = aPCurve->Value(aLast);
  EXPECT_NEAR(aStart.X(), 0.0, 0.01);
  EXPECT_NEAR(aStart.Y(), 0.0, 0.01);
  EXPECT_NEAR(aEnd.X(), 10.0, 0.01);
  EXPECT_NEAR(aEnd.Y(), 10.0, 0.01);
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, CircleOnCylinder_A2)
{
  const double                         aRadius = 5.0;
  occ::handle<Geom_CylindricalSurface> aCylinder =
    new Geom_CylindricalSurface(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), aRadius);

  gp_Circ                  aCirc(gp_Ax2(gp_Pnt(0, 0, 3), gp_Dir(0, 0, 1)), aRadius);
  occ::handle<Geom_Circle> aCircle = new Geom_Circle(aCirc);

  myProjector->Init(new ShapeAnalysis_Surface(aCylinder), myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult = myProjector->Perform(aCircle, 0.0, 2.0 * M_PI, aPCurve);

  ASSERT_TRUE(aResult) << "Projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull()) << "PCurve should not be null";

  const gp_Pnt2d aMid = aPCurve->Value(M_PI);
  EXPECT_NEAR(aMid.Y(), 3.0, 0.01) << "V coordinate should be 3";
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, IsoparametricLineOnCylinder_A3)
{
  const double                         aRadius = 5.0;
  occ::handle<Geom_CylindricalSurface> aCylinder =
    new Geom_CylindricalSurface(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), aRadius);

  occ::handle<Geom_TrimmedCurve> aLine =
    GC_MakeSegment(gp_Pnt(aRadius, 0, 0), gp_Pnt(aRadius, 0, 10)).Value();

  occ::handle<ShapeAnalysis_Surface> aSAS = new ShapeAnalysis_Surface(aCylinder);
  myProjector->Init(aSAS, myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const double              aFirst  = aLine->FirstParameter();
  const double              aLast   = aLine->LastParameter();
  const bool                aResult = myProjector->Perform(aLine, aFirst, aLast, aPCurve);

  ASSERT_TRUE(aResult) << "Projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull()) << "PCurve should not be null";

  const gp_Pnt2d aStart = aPCurve->Value(aFirst);
  const gp_Pnt2d aEnd   = aPCurve->Value(aLast);
  EXPECT_NEAR(aStart.X(), aEnd.X(), 0.01) << "U should be constant for isoparametric curve";
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, BSplineOnPlane_B1)
{
  occ::handle<Geom_Plane>        aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
  occ::handle<Geom_BSplineCurve> aBSpline = createPlanarBSpline();
  ASSERT_FALSE(aBSpline.IsNull());

  myProjector->Init(new ShapeAnalysis_Surface(aPlane), myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult =
    myProjector->Perform(aBSpline, aBSpline->FirstParameter(), aBSpline->LastParameter(), aPCurve);

  ASSERT_TRUE(aResult) << "Projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull()) << "PCurve should not be null";

  const gp_Pnt2d aStart = aPCurve->Value(aBSpline->FirstParameter());
  const gp_Pnt2d aEnd   = aPCurve->Value(aBSpline->LastParameter());
  EXPECT_NEAR(aStart.X(), 0.0, 0.1);
  EXPECT_NEAR(aStart.Y(), 0.0, 0.1);
  EXPECT_NEAR(aEnd.X(), 10.0, 0.1);
  EXPECT_NEAR(aEnd.Y(), 0.0, 0.1);
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, HelicalBSplineOnCylinder_B2)
{
  const double                         aRadius = 5.0;
  occ::handle<Geom_CylindricalSurface> aCylinder =
    new Geom_CylindricalSurface(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), aRadius);

  occ::handle<Geom_BSplineCurve> aBSpline = createHelicalBSpline(aRadius, 9);
  ASSERT_FALSE(aBSpline.IsNull());

  occ::handle<ShapeAnalysis_Surface> aSAS = new ShapeAnalysis_Surface(aCylinder);
  myProjector->Init(aSAS, myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult =
    myProjector->Perform(aBSpline, aBSpline->FirstParameter(), aBSpline->LastParameter(), aPCurve);

  ASSERT_TRUE(aResult) << "Projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull()) << "PCurve should not be null";

  verifyProjection(aBSpline, aPCurve, aSAS, 0.1);
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, HighDegreeBSpline_B3)
{
  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));

  const int                  aNbPoles = 50;
  NCollection_Array1<gp_Pnt> aPoles(1, aNbPoles);
  for (int i = 1; i <= aNbPoles; ++i)
  {
    const double aX = (i - 1) * 0.5;
    const double aY = 5.0 * sin(aX * M_PI / 10.0);
    aPoles(i)       = gp_Pnt(aX, aY, 0);
  }

  GeomAPI_PointsToBSpline        aBuilder(aPoles, 3, 8);
  occ::handle<Geom_BSplineCurve> aBSpline = aBuilder.Curve();
  ASSERT_FALSE(aBSpline.IsNull());

  occ::handle<ShapeAnalysis_Surface> aSAS = new ShapeAnalysis_Surface(aPlane);
  myProjector->Init(aSAS, myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult =
    myProjector->Perform(aBSpline, aBSpline->FirstParameter(), aBSpline->LastParameter(), aPCurve);

  ASSERT_TRUE(aResult) << "Projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull()) << "PCurve should not be null";

  verifyProjection(aBSpline, aPCurve, aSAS, 0.5);
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, EquatorOnSphere_C1)
{
  const double                       aRadius = 10.0;
  occ::handle<Geom_SphericalSurface> aSphere =
    new Geom_SphericalSurface(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), aRadius);

  gp_Circ                  aCirc(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), aRadius);
  occ::handle<Geom_Circle> aCircle = new Geom_Circle(aCirc);

  myProjector->Init(new ShapeAnalysis_Surface(aSphere), myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult = myProjector->Perform(aCircle, 0.0, 2.0 * M_PI, aPCurve);

  ASSERT_TRUE(aResult) << "Projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull()) << "PCurve should not be null";
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, LatitudeOnSphere_C2)
{
  const double                       aRadius = 10.0;
  occ::handle<Geom_SphericalSurface> aSphere =
    new Geom_SphericalSurface(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), aRadius);

  const double aLatitude   = M_PI / 4.0;
  const double aZ          = aRadius * sin(aLatitude);
  const double aCircRadius = aRadius * cos(aLatitude);

  gp_Circ                  aCirc(gp_Ax2(gp_Pnt(0, 0, aZ), gp_Dir(0, 0, 1)), aCircRadius);
  occ::handle<Geom_Circle> aCircle = new Geom_Circle(aCirc);

  myProjector->Init(new ShapeAnalysis_Surface(aSphere), myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult = myProjector->Perform(aCircle, 0.0, 2.0 * M_PI, aPCurve);

  ASSERT_TRUE(aResult) << "Projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull()) << "PCurve should not be null";

  const gp_Pnt2d aStart = aPCurve->Value(0.0);
  const gp_Pnt2d aMid   = aPCurve->Value(M_PI);
  EXPECT_NEAR(aStart.Y(), aMid.Y(), 0.01) << "V should be constant for latitude circle";
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, CircleOnTorus_C3)
{
  const double                      aMajorRadius = 10.0;
  const double                      aMinorRadius = 2.0;
  occ::handle<Geom_ToroidalSurface> aTorus =
    new Geom_ToroidalSurface(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), aMajorRadius, aMinorRadius);

  gp_Circ aCirc(gp_Ax2(gp_Pnt(aMajorRadius + aMinorRadius, 0, 0), gp_Dir(0, 1, 0)), aMinorRadius);
  occ::handle<Geom_Circle> aCircle = new Geom_Circle(aCirc);

  myProjector->Init(new ShapeAnalysis_Surface(aTorus), myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult = myProjector->Perform(aCircle, 0.0, 2.0 * M_PI, aPCurve);

  ASSERT_TRUE(aResult) << "Projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull()) << "PCurve should not be null";
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, CircleOnCone_D1)
{
  const double                     aRadius    = 5.0;
  const double                     aSemiAngle = M_PI / 6.0;
  occ::handle<Geom_ConicalSurface> aCone =
    new Geom_ConicalSurface(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), aSemiAngle, aRadius);

  const double             aZ         = 5.0;
  const double             aRadiusAtZ = aRadius + aZ * tan(aSemiAngle);
  gp_Circ                  aCirc(gp_Ax2(gp_Pnt(0, 0, aZ), gp_Dir(0, 0, 1)), aRadiusAtZ);
  occ::handle<Geom_Circle> aCircle = new Geom_Circle(aCirc);

  myProjector->Init(new ShapeAnalysis_Surface(aCone), myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult = myProjector->Perform(aCircle, 0.0, 2.0 * M_PI, aPCurve);

  ASSERT_TRUE(aResult) << "Projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull()) << "PCurve should not be null";
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, ArcOnPlane_E1)
{
  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));

  gp_Circ                        aCirc(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 5.0);
  occ::handle<Geom_Circle>       aFullCircle = new Geom_Circle(aCirc);
  occ::handle<Geom_TrimmedCurve> aArc        = new Geom_TrimmedCurve(aFullCircle, 0.0, M_PI / 2.0);

  occ::handle<ShapeAnalysis_Surface> aSAS = new ShapeAnalysis_Surface(aPlane);
  myProjector->Init(aSAS, myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const double              aFirst  = aArc->FirstParameter();
  const double              aLast   = aArc->LastParameter();
  const bool                aResult = myProjector->Perform(aArc, aFirst, aLast, aPCurve);

  ASSERT_TRUE(aResult) << "Projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull()) << "PCurve should not be null";

  const gp_Pnt2d aStart = aPCurve->Value(aFirst);
  const gp_Pnt2d aEnd   = aPCurve->Value(aLast);
  EXPECT_NEAR(aStart.X(), 5.0, 0.01);
  EXPECT_NEAR(aStart.Y(), 0.0, 0.01);
  EXPECT_NEAR(aEnd.X(), 0.0, 0.01);
  EXPECT_NEAR(aEnd.Y(), 5.0, 0.01);
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, DoublyTrimmedCurve_E2)
{
  occ::handle<Geom_Plane>        aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
  occ::handle<Geom_BSplineCurve> aBSpline = createPlanarBSpline();
  ASSERT_FALSE(aBSpline.IsNull());

  const double                   aFirst1 = aBSpline->FirstParameter();
  const double                   aLast1  = aBSpline->LastParameter();
  const double                   aMid    = (aFirst1 + aLast1) / 2.0;
  occ::handle<Geom_TrimmedCurve> aTrim1  = new Geom_TrimmedCurve(aBSpline, aFirst1, aMid);

  const double                   aFirst2 = aTrim1->FirstParameter();
  const double                   aLast2  = aTrim1->LastParameter();
  const double                   aQuart  = aFirst2 + (aLast2 - aFirst2) / 4.0;
  occ::handle<Geom_TrimmedCurve> aTrim2  = new Geom_TrimmedCurve(aTrim1, aFirst2, aQuart);

  myProjector->Init(new ShapeAnalysis_Surface(aPlane), myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult =
    myProjector->Perform(aTrim2, aTrim2->FirstParameter(), aTrim2->LastParameter(), aPCurve);

  ASSERT_TRUE(aResult) << "Projection of doubly-trimmed curve should succeed";
  ASSERT_FALSE(aPCurve.IsNull()) << "PCurve should not be null";
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, EllipseOnPlane_F1)
{
  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));

  gp_Elips                  anElips(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 10.0, 5.0);
  occ::handle<Geom_Ellipse> anEllipse = new Geom_Ellipse(anElips);

  occ::handle<ShapeAnalysis_Surface> aSAS = new ShapeAnalysis_Surface(aPlane);
  myProjector->Init(aSAS, myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult = myProjector->Perform(anEllipse, 0.0, 2.0 * M_PI, aPCurve);

  ASSERT_TRUE(aResult) << "Projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull()) << "PCurve should not be null";

  gp_Pnt2d aP0 = aPCurve->Value(0.0);
  EXPECT_NEAR(aP0.X(), 10.0, 0.01);
  EXPECT_NEAR(aP0.Y(), 0.0, 0.01);

  gp_Pnt2d aP1 = aPCurve->Value(M_PI / 2.0);
  EXPECT_NEAR(aP1.X(), 0.0, 0.01);
  EXPECT_NEAR(aP1.Y(), 5.0, 0.01);
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, InitWithGeomSurface_G1)
{
  occ::handle<Geom_Plane>        aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
  occ::handle<Geom_TrimmedCurve> aLine = GC_MakeSegment(gp_Pnt(0, 0, 0), gp_Pnt(10, 10, 0)).Value();

  myProjector->Init(aPlane, Precision::Confusion());

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult =
    myProjector->Perform(aLine, aLine->FirstParameter(), aLine->LastParameter(), aPCurve);

  ASSERT_TRUE(aResult) << "Init with Geom_Surface should work";
  ASSERT_FALSE(aPCurve.IsNull());
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, SetSurfaceAndPrecision_G2)
{
  occ::handle<Geom_Plane>        aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
  occ::handle<Geom_TrimmedCurve> aLine = GC_MakeSegment(gp_Pnt(0, 0, 0), gp_Pnt(10, 10, 0)).Value();

  myProjector->SetSurface(aPlane);
  myProjector->SetPrecision(Precision::Confusion());

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult =
    myProjector->Perform(aLine, aLine->FirstParameter(), aLine->LastParameter(), aPCurve);

  ASSERT_TRUE(aResult) << "SetSurface + SetPrecision should work";
  ASSERT_FALSE(aPCurve.IsNull());
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, AdjustOverDegenModeAccessor_G3)
{

  EXPECT_EQ(myProjector->AdjustOverDegenMode(), 1);

  myProjector->AdjustOverDegenMode() = 0;
  EXPECT_EQ(myProjector->AdjustOverDegenMode(), 0);

  myProjector->AdjustOverDegenMode() = 1;
  EXPECT_EQ(myProjector->AdjustOverDegenMode(), 1);
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, StatusMethod_G4)
{
  occ::handle<Geom_Plane>        aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
  occ::handle<Geom_TrimmedCurve> aLine = GC_MakeSegment(gp_Pnt(0, 0, 0), gp_Pnt(10, 10, 0)).Value();

  myProjector->Init(new ShapeAnalysis_Surface(aPlane), myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  myProjector->Perform(aLine, aLine->FirstParameter(), aLine->LastParameter(), aPCurve);

  EXPECT_TRUE(myProjector->Status(ShapeExtend_OK) || myProjector->Status(ShapeExtend_DONE))
    << "Status should indicate OK or DONE";
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, TightTolerance_H1)
{
  occ::handle<Geom_Plane>        aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
  occ::handle<Geom_TrimmedCurve> aLine = GC_MakeSegment(gp_Pnt(0, 0, 0), gp_Pnt(10, 10, 0)).Value();

  myProjector->Init(new ShapeAnalysis_Surface(aPlane), 1e-15);

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult =
    myProjector->Perform(aLine, aLine->FirstParameter(), aLine->LastParameter(), aPCurve);

  ASSERT_TRUE(aResult) << "Tight tolerance should work for exact curve";
  ASSERT_FALSE(aPCurve.IsNull());
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, DifferentEndpointTolerances_H2)
{
  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));

  NCollection_Array1<gp_Pnt> aPoles(1, 3);
  aPoles(1) = gp_Pnt(0, 0, 0);
  aPoles(2) = gp_Pnt(5, 5, 0.05);
  aPoles(3) = gp_Pnt(10, 10, 0.1);

  GeomAPI_PointsToBSpline        aBuilder(aPoles, 2, 2);
  occ::handle<Geom_BSplineCurve> aBSpline = aBuilder.Curve();
  ASSERT_FALSE(aBSpline.IsNull());

  myProjector->Init(new ShapeAnalysis_Surface(aPlane), myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const double              aTolFirst = 0.01;
  const double              aTolLast  = 0.2;
  const bool                aResult   = myProjector->Perform(aBSpline,
                                            aBSpline->FirstParameter(),
                                            aBSpline->LastParameter(),
                                            aPCurve,
                                            aTolFirst,
                                            aTolLast);

  ASSERT_TRUE(aResult) << "Projection with different endpoint tolerances should succeed";
  ASSERT_FALSE(aPCurve.IsNull());
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, PartialCircle_I1)
{
  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));

  gp_Circ                  aCirc(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 5.0);
  occ::handle<Geom_Circle> aCircle = new Geom_Circle(aCirc);

  occ::handle<ShapeAnalysis_Surface> aSAS = new ShapeAnalysis_Surface(aPlane);
  myProjector->Init(aSAS, myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult = myProjector->Perform(aCircle, 0.0, M_PI / 2.0, aPCurve);

  ASSERT_TRUE(aResult) << "Partial projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull());

  gp_Pnt2d aStart = aPCurve->Value(0.0);
  gp_Pnt2d aEnd   = aPCurve->Value(M_PI / 2.0);
  EXPECT_NEAR(aStart.X(), 5.0, 0.01);
  EXPECT_NEAR(aStart.Y(), 0.0, 0.01);
  EXPECT_NEAR(aEnd.X(), 0.0, 0.01);
  EXPECT_NEAR(aEnd.Y(), 5.0, 0.01);
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, MiddlePortionBSpline_I2)
{
  occ::handle<Geom_Plane>        aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
  occ::handle<Geom_BSplineCurve> aBSpline = createPlanarBSpline();
  ASSERT_FALSE(aBSpline.IsNull());

  myProjector->Init(new ShapeAnalysis_Surface(aPlane), myTolerance);

  const double aFirst = aBSpline->FirstParameter();
  const double aLast  = aBSpline->LastParameter();
  const double aRange = aLast - aFirst;

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult =
    myProjector->Perform(aBSpline, aFirst + 0.25 * aRange, aFirst + 0.75 * aRange, aPCurve);

  ASSERT_TRUE(aResult) << "Middle portion projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull());
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, MultipleProjections_J1)
{
  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
  occ::handle<ShapeAnalysis_Surface> aSAS = new ShapeAnalysis_Surface(aPlane);
  myProjector->Init(aSAS, myTolerance);

  for (int i = 0; i < 5; ++i)
  {
    const double                   aOffset = i * 10.0;
    occ::handle<Geom_TrimmedCurve> aLine =
      GC_MakeSegment(gp_Pnt(aOffset, 0, 0), gp_Pnt(aOffset + 5, 5, 0)).Value();

    occ::handle<Geom2d_Curve> aPCurve;
    const bool                aResult =
      myProjector->Perform(aLine, aLine->FirstParameter(), aLine->LastParameter(), aPCurve);

    EXPECT_TRUE(aResult) << "Projection " << i << " should succeed";
    EXPECT_FALSE(aPCurve.IsNull()) << "PCurve " << i << " should not be null";
  }
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, SurfaceReinitialization_J2)
{

  occ::handle<Geom_Plane> aPlane1 = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
  myProjector->Init(new ShapeAnalysis_Surface(aPlane1), myTolerance);

  occ::handle<Geom_TrimmedCurve> aLine1 =
    GC_MakeSegment(gp_Pnt(0, 0, 0), gp_Pnt(10, 10, 0)).Value();
  occ::handle<Geom2d_Curve> aPCurve1;
  myProjector->Perform(aLine1, aLine1->FirstParameter(), aLine1->LastParameter(), aPCurve1);
  ASSERT_FALSE(aPCurve1.IsNull());

  occ::handle<Geom_Plane> aPlane2 = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 5), gp_Dir(0, 0, 1)));
  myProjector->Init(new ShapeAnalysis_Surface(aPlane2), myTolerance);

  occ::handle<Geom_TrimmedCurve> aLine2 =
    GC_MakeSegment(gp_Pnt(0, 0, 5), gp_Pnt(10, 10, 5)).Value();
  occ::handle<Geom2d_Curve> aPCurve2;
  myProjector->Perform(aLine2, aLine2->FirstParameter(), aLine2->LastParameter(), aPCurve2);
  ASSERT_FALSE(aPCurve2.IsNull());
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, NearPoleOnSphere_K1)
{
  const double                       aRadius = 10.0;
  occ::handle<Geom_SphericalSurface> aSphere =
    new Geom_SphericalSurface(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), aRadius);

  const double aLatitude   = M_PI / 2.0 - 0.01;
  const double aZ          = aRadius * sin(aLatitude);
  const double aCircRadius = aRadius * cos(aLatitude);

  gp_Circ                  aCirc(gp_Ax2(gp_Pnt(0, 0, aZ), gp_Dir(0, 0, 1)), aCircRadius);
  occ::handle<Geom_Circle> aCircle = new Geom_Circle(aCirc);

  myProjector->Init(new ShapeAnalysis_Surface(aSphere), myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult = myProjector->Perform(aCircle, 0.0, 2.0 * M_PI, aPCurve);

  ASSERT_TRUE(aResult) << "Projection near pole should succeed";
  ASSERT_FALSE(aPCurve.IsNull());
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, VeryShortCurve_L1)
{
  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));

  occ::handle<Geom_TrimmedCurve> aLine =
    GC_MakeSegment(gp_Pnt(0, 0, 0), gp_Pnt(1e-6, 0, 0)).Value();

  myProjector->Init(new ShapeAnalysis_Surface(aPlane), 1e-4);

  occ::handle<Geom2d_Curve> aPCurve;

  (void)myProjector->Perform(aLine, aLine->FirstParameter(), aLine->LastParameter(), aPCurve);

  SUCCEED() << "Short curve projection completed without crash";
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, CurveFarFromSurface_L2)
{
  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));

  occ::handle<Geom_TrimmedCurve> aLine =
    GC_MakeSegment(gp_Pnt(0, 0, 100), gp_Pnt(10, 10, 100)).Value();

  myProjector->Init(new ShapeAnalysis_Surface(aPlane), myTolerance);

  occ::handle<Geom2d_Curve> aPCurve;
  (void)myProjector->Perform(aLine, aLine->FirstParameter(), aLine->LastParameter(), aPCurve);

  EXPECT_FALSE(aPCurve.IsNull()) << "PCurve should be created even for distant curve";
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, LargeTolerance_L3)
{
  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));

  occ::handle<Geom_TrimmedCurve> aLine =
    GC_MakeSegment(gp_Pnt(0, 0, 0.1), gp_Pnt(10, 10, 0.1)).Value();

  myProjector->Init(new ShapeAnalysis_Surface(aPlane), 1.0);

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult =
    myProjector->Perform(aLine, aLine->FirstParameter(), aLine->LastParameter(), aPCurve);

  ASSERT_TRUE(aResult) << "Large tolerance projection should succeed";
  ASSERT_FALSE(aPCurve.IsNull());
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, Bug27569_ManyKnotsBSpline_M1)
{

  const int aDegree  = 3;
  const int aNbKnots = 15;
  const int aNbPoles = aNbKnots + aDegree - 1;

  NCollection_Array1<gp_Pnt> aPoles(1, aNbPoles);
  for (int i = 1; i <= aNbPoles; ++i)
  {
    const double t       = (i - 1.0) / (aNbPoles - 1.0);
    const double aAngle  = t * 2.0 * M_PI;
    const double aRadius = 50.0 + 20.0 * cos(3.0 * aAngle);
    aPoles(i)            = gp_Pnt(aRadius * cos(aAngle), -30.0 * t, aRadius * sin(aAngle));
  }

  NCollection_Array1<double> aKnots(1, aNbKnots);
  NCollection_Array1<int>    aMults(1, aNbKnots);
  for (int i = 1; i <= aNbKnots; ++i)
  {
    aKnots(i) = (i - 1.0) / (aNbKnots - 1.0);
    aMults(i) = 1;
  }

  aMults(1)        = aDegree + 1;
  aMults(aNbKnots) = aDegree + 1;

  occ::handle<Geom_BSplineCurve> aBSplineCurve =
    new Geom_BSplineCurve(aPoles, aKnots, aMults, aDegree);
  ASSERT_FALSE(aBSplineCurve.IsNull()) << "B-Spline curve should be created";
  EXPECT_GE(aBSplineCurve->NbKnots(), 10) << "Curve should have at least 10 knots";

  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pnt(0, -15, 0), gp_Dir(0, 1, 0));

  myProjector->Init(aPlane, Precision::Confusion());

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult = myProjector->Perform(aBSplineCurve,
                                            aBSplineCurve->FirstParameter(),
                                            aBSplineCurve->LastParameter(),
                                            aPCurve);

  EXPECT_TRUE(aResult) << "Projection should succeed for B-spline with many knots";
  EXPECT_FALSE(aPCurve.IsNull()) << "PCurve should be created";
}

TEST_F(ShapeConstruct_ProjectCurveOnSurfaceTest, Bug27569_HighMultiplicityBSpline_M2)
{

  const int aDegree  = 7;
  const int aNbKnots = 7;

  NCollection_Array1<int> aMults(1, aNbKnots);
  aMults(1) = 8;
  aMults(2) = 7;
  aMults(3) = 7;
  aMults(4) = 7;
  aMults(5) = 7;
  aMults(6) = 7;
  aMults(7) = 8;

  const int aNbPoles = 43;

  NCollection_Array1<double> aKnots(1, aNbKnots);
  for (int i = 1; i <= aNbKnots; ++i)
  {
    aKnots(i) = (i - 1);
  }

  NCollection_Array1<gp_Pnt> aPoles(1, aNbPoles);

  for (int i = 1; i <= 15; ++i)
  {
    const double t  = (i - 1.0) / 14.0;
    const double aX = 144.0 - t * 74.0;
    const double aY = -t * 0.0002;
    const double aZ = 8.3 + t * 51.7;
    aPoles(i)       = gp_Pnt(aX, aY, aZ);
  }

  for (int i = 16; i <= 28; ++i)
  {
    aPoles(i) = gp_Pnt(70.0, 0.0, 60.0);
  }

  for (int i = 29; i <= aNbPoles; ++i)
  {
    const double t  = (i - 29.0) / (aNbPoles - 29.0);
    const double aX = 70.0 - t * 80.0;
    const double aY = -t * 32.0;
    const double aZ = 60.0 - t * 60.0;
    aPoles(i)       = gp_Pnt(aX, aY, aZ);
  }

  occ::handle<Geom_BSplineCurve> aBSplineCurve;
  try
  {
    aBSplineCurve = new Geom_BSplineCurve(aPoles, aKnots, aMults, aDegree);
  }
  catch (Standard_Failure const&)
  {

    GTEST_SKIP() << "Could not construct B-spline with high multiplicities";
  }
  ASSERT_FALSE(aBSplineCurve.IsNull()) << "B-Spline curve should be created";

  const int aNbUPoles = 8;
  const int aNbVPoles = 2;

  NCollection_Array2<gp_Pnt> aSurfPoles(1, aNbUPoles, 1, aNbVPoles);

  aSurfPoles(1, 1) = gp_Pnt(70, 0, 60);
  aSurfPoles(2, 1) = gp_Pnt(85.01, 0, 60);
  aSurfPoles(3, 1) = gp_Pnt(98.87, 0, 55.07);
  aSurfPoles(4, 1) = gp_Pnt(111.6, 0, 46.57);
  aSurfPoles(5, 1) = gp_Pnt(123.15, 0, 35.68);
  aSurfPoles(6, 1) = gp_Pnt(133.46, 0, 23.56);
  aSurfPoles(7, 1) = gp_Pnt(142.46, 0, 11.32);
  aSurfPoles(8, 1) = gp_Pnt(150, 0, 0);

  aSurfPoles(1, 2) = gp_Pnt(54.99, 0, 60);
  aSurfPoles(2, 2) = gp_Pnt(41.13, 0, 55.07);
  aSurfPoles(3, 2) = gp_Pnt(28.4, 0, 46.57);
  aSurfPoles(4, 2) = gp_Pnt(16.85, 0, 35.68);
  aSurfPoles(5, 2) = gp_Pnt(6.54, 0, 23.56);
  aSurfPoles(6, 2) = gp_Pnt(-2.46, 0, 11.32);
  aSurfPoles(7, 2) = gp_Pnt(-10, 0, 0);
  aSurfPoles(8, 2) = gp_Pnt(-10, -35.91, 0);

  NCollection_Array1<double> aUKnots(1, 2);
  NCollection_Array1<double> aVKnots(1, 2);
  NCollection_Array1<int>    aUMults(1, 2);
  NCollection_Array1<int>    aVMults(1, 2);

  aUKnots(1) = 0;
  aUKnots(2) = 1;
  aVKnots(1) = 0;
  aVKnots(2) = 1;
  aUMults(1) = 8;
  aUMults(2) = 8;
  aVMults(1) = 2;
  aVMults(2) = 2;

  occ::handle<Geom_BSplineSurface> aBSplineSurface;
  try
  {
    aBSplineSurface = new Geom_BSplineSurface(aSurfPoles, aUKnots, aVKnots, aUMults, aVMults, 7, 1);
  }
  catch (Standard_Failure const&)
  {

    occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pnt(70, 0, 30), gp_Dir(0, 1, 0));
    myProjector->Init(aPlane, Precision::Confusion());

    occ::handle<Geom2d_Curve> aPCurve;
    const bool                aResult = myProjector->Perform(aBSplineCurve,
                                              aBSplineCurve->FirstParameter(),
                                              aBSplineCurve->LastParameter(),
                                              aPCurve);

    EXPECT_TRUE(aResult) << "Projection should succeed";
    EXPECT_FALSE(aPCurve.IsNull()) << "PCurve should be created";
    return;
  }

  myProjector->Init(aBSplineSurface, Precision::Confusion());

  occ::handle<Geom2d_Curve> aPCurve;
  const bool                aResult = myProjector->Perform(aBSplineCurve,
                                            aBSplineCurve->FirstParameter(),
                                            aBSplineCurve->LastParameter(),
                                            aPCurve);

  EXPECT_TRUE(aResult) << "Projection should succeed for B-spline with degenerate section";
  EXPECT_FALSE(aPCurve.IsNull()) << "PCurve should be created";
}
