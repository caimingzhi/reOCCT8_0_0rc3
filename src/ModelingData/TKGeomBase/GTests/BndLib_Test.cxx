

#include <gtest/gtest.h>

#include <BndLib.hpp>
#include <BndLib_Add2dCurve.hpp>
#include <BndLib_Add3dCurve.hpp>
#include <BndLib_AddSurface.hpp>
#include <Bnd_Box.hpp>
#include <Bnd_Box2d.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Ellipse.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BezierSurface.hpp>
#include <Geom_Circle.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Ax3.hpp>
#include <gp_Circ.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Cone.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Dir.hpp>
#include <gp_Elips.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Hypr.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Lin.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Parab.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Pnt.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array2.hpp>
#include <Standard_Integer.hpp>

#include <cmath>
#include <limits>

TEST(BndLibTest, Line_FiniteSegment)
{

  gp_Lin  aLine(gp_Pnt(0., 0., 0.), gp_Dir(1., 0., 0.));
  Bnd_Box aBox;

  BndLib::Add(aLine, 0., 10., 0., aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, 0., Precision::Confusion());
  EXPECT_NEAR(aXmax, 10., Precision::Confusion());
  EXPECT_NEAR(aYmin, 0., Precision::Confusion());
  EXPECT_NEAR(aYmax, 0., Precision::Confusion());
  EXPECT_NEAR(aZmin, 0., Precision::Confusion());
  EXPECT_NEAR(aZmax, 0., Precision::Confusion());
}

TEST(BndLibTest, Line_PositiveDirection_NegativeInfinite)
{

  gp_Lin  aLine(gp_Pnt(0., 0., 0.), gp_Dir(1., 0., 0.));
  Bnd_Box aBox;

  BndLib::Add(aLine, -std::numeric_limits<double>::infinity(), 5., 0., aBox);

  EXPECT_TRUE(aBox.IsOpenXmin()) << "Xmin should be open for line in +X direction with P1=-Inf";
  EXPECT_FALSE(aBox.IsOpenXmax()) << "Xmax should not be open";
}

TEST(BndLibTest, Line_NegativeDirection_NegativeInfinite)
{

  gp_Lin  aLine(gp_Pnt(0., 0., 0.), gp_Dir(-1., 0., 0.));
  Bnd_Box aBox;

  BndLib::Add(aLine, -std::numeric_limits<double>::infinity(), 5., 0., aBox);

  EXPECT_TRUE(aBox.IsOpenXmax()) << "Xmax should be open for line in -X direction with P1=-Inf";
  EXPECT_FALSE(aBox.IsOpenXmin()) << "Xmin should not be open";
}

TEST(BndLibTest, Line_NegativeDirection_PositiveInfinite)
{

  gp_Lin  aLine(gp_Pnt(0., 0., 0.), gp_Dir(-1., 0., 0.));
  Bnd_Box aBox;

  BndLib::Add(aLine, -5., std::numeric_limits<double>::infinity(), 0., aBox);

  EXPECT_TRUE(aBox.IsOpenXmin()) << "Xmin should be open for line in -X direction with P2=+Inf";
  EXPECT_FALSE(aBox.IsOpenXmax()) << "Xmax should not be open";
}

TEST(BndLibTest, Line_DiagonalDirection_BothInfinite)
{

  gp_Lin  aLine(gp_Pnt(0., 0., 0.), gp_Dir(-1., -1., -1.));
  Bnd_Box aBox;

  BndLib::Add(aLine,
              -std::numeric_limits<double>::infinity(),
              std::numeric_limits<double>::infinity(),
              0.,
              aBox);

  EXPECT_TRUE(aBox.IsOpenXmin()) << "Xmin should be open";
  EXPECT_TRUE(aBox.IsOpenXmax()) << "Xmax should be open";
  EXPECT_TRUE(aBox.IsOpenYmin()) << "Ymin should be open";
  EXPECT_TRUE(aBox.IsOpenYmax()) << "Ymax should be open";
  EXPECT_TRUE(aBox.IsOpenZmin()) << "Zmin should be open";
  EXPECT_TRUE(aBox.IsOpenZmax()) << "Zmax should be open";
}

TEST(BndLibTest, Circle_Full)
{

  gp_Circ aCirc(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 5.);
  Bnd_Box aBoxFull;
  Bnd_Box aBoxArc;
  double  aTol = 0.;

  BndLib::Add(aCirc, aTol, aBoxFull);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBoxFull.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -5., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5., Precision::Confusion());
  EXPECT_NEAR(aYmin, -5., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
  EXPECT_NEAR(aZmin, 0., Precision::Confusion());
  EXPECT_NEAR(aZmax, 0., Precision::Confusion());

  BndLib::Add(aCirc, 0., 2. * M_PI, aTol, aBoxArc);
  aBoxArc.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -5., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5., Precision::Confusion());
  EXPECT_NEAR(aYmin, -5., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
}

TEST(BndLibTest, Circle_Arc_FirstQuadrant)
{

  gp_Circ aCirc(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 5.);
  Bnd_Box aBox;
  double  aTol = 0.;

  BndLib::Add(aCirc, 0., M_PI / 2., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, 0., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5., Precision::Confusion());
  EXPECT_NEAR(aYmin, 0., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
}

TEST(BndLibTest, Circle_RotatedAxis)
{

  gp_Circ aCirc(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 1., 0.)), 3.);
  Bnd_Box aBox;
  double  aTol = 0.;

  BndLib::Add(aCirc, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -3., Precision::Confusion());
  EXPECT_NEAR(aXmax, 3., Precision::Confusion());
  EXPECT_NEAR(aYmin, 0., Precision::Confusion());
  EXPECT_NEAR(aYmax, 0., Precision::Confusion());
  EXPECT_NEAR(aZmin, -3., Precision::Confusion());
  EXPECT_NEAR(aZmax, 3., Precision::Confusion());
}

TEST(BndLibTest, Ellipse_Full)
{

  gp_Elips aElips(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 10., 5.);
  Bnd_Box  aBox;
  double   aTol = 0.;

  BndLib::Add(aElips, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -10., Precision::Confusion());
  EXPECT_NEAR(aXmax, 10., Precision::Confusion());
  EXPECT_NEAR(aYmin, -5., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
  EXPECT_NEAR(aZmin, 0., Precision::Confusion());
  EXPECT_NEAR(aZmax, 0., Precision::Confusion());
}

TEST(BndLibTest, Ellipse_Arc)
{

  gp_Elips aElips(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 10., 5.);
  Bnd_Box  aBox;
  double   aTol = 0.;

  BndLib::Add(aElips, 0., M_PI / 2., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, 0., Precision::Confusion());
  EXPECT_NEAR(aXmax, 10., Precision::Confusion());
  EXPECT_NEAR(aYmin, 0., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
}

TEST(BndLibTest, Hyperbola_SimpleArc)
{

  gp_Hypr aHypr(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 3., 2.);
  Bnd_Box aBox;
  double  aTol = 0.;

  BndLib::Add(aHypr, -1., 1., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  double aExpectedXmin = 3.;
  double aExpectedXmax = 3. * std::cosh(1.);
  double aExpectedYmin = 2. * std::sinh(-1.);
  double aExpectedYmax = 2. * std::sinh(1.);

  EXPECT_NEAR(aXmin, aExpectedXmin, Precision::Confusion());
  EXPECT_NEAR(aXmax, aExpectedXmax, Precision::Confusion());
  EXPECT_NEAR(aYmin, aExpectedYmin, Precision::Confusion());
  EXPECT_NEAR(aYmax, aExpectedYmax, Precision::Confusion());
}

TEST(BndLibTest, Hyperbola_Rotated_MultipleExtrema)
{

  gp_Ax2  aAx2(gp_Pnt(0., 0., 0.), gp_Dir(1., 1., 1.), gp_Dir(1., -1., 0.));
  gp_Hypr aHypr(aAx2, 5., 3.);
  Bnd_Box aBox;
  double  aTol = 0.;

  BndLib::Add(aHypr, -2., 2., aTol, aBox);

  EXPECT_FALSE(aBox.IsVoid()) << "Box should not be void";

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_LT(aXmin, aXmax) << "X range should be non-zero";
  EXPECT_LT(aYmin, aYmax) << "Y range should be non-zero";
}

TEST(BndLibTest, Hyperbola_InfiniteParameter)
{

  gp_Hypr aHypr(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 3., 2.);
  Bnd_Box aBox;
  double  aTol = 0.;

  BndLib::Add(aHypr, 0., std::numeric_limits<double>::infinity(), aTol, aBox);

  EXPECT_TRUE(aBox.IsOpenXmax()) << "Xmax should be open for hyperbola with P2=+Inf";
  EXPECT_TRUE(aBox.IsOpenYmax()) << "Ymax should be open for hyperbola with P2=+Inf";
}

TEST(BndLibTest, Parabola_FiniteArc)
{

  gp_Parab aParab(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 2.);
  Bnd_Box  aBox;
  double   aTol = 0.;

  BndLib::Add(aParab, -4., 4., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, 0., Precision::Confusion());
  EXPECT_NEAR(aXmax, 2., Precision::Confusion());
  EXPECT_NEAR(aYmin, -4., Precision::Confusion());
  EXPECT_NEAR(aYmax, 4., Precision::Confusion());
}

TEST(BndLibTest, Parabola_InfiniteParameter)
{

  gp_Parab aParab(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 2.);
  Bnd_Box  aBox;
  double   aTol = 0.;

  BndLib::Add(aParab, 0., std::numeric_limits<double>::infinity(), aTol, aBox);

  EXPECT_TRUE(aBox.IsOpenXmax()) << "Xmax should be open for parabola with P2=+Inf";
  EXPECT_TRUE(aBox.IsOpenYmax()) << "Ymax should be open for parabola with P2=+Inf";
}

TEST(BndLibTest, Sphere_Full)
{

  gp_Sphere aSphere(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 7.);
  Bnd_Box   aBox;
  double    aTol = 0.;

  BndLib::Add(aSphere, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -7., Precision::Confusion());
  EXPECT_NEAR(aXmax, 7., Precision::Confusion());
  EXPECT_NEAR(aYmin, -7., Precision::Confusion());
  EXPECT_NEAR(aYmax, 7., Precision::Confusion());
  EXPECT_NEAR(aZmin, -7., Precision::Confusion());
  EXPECT_NEAR(aZmax, 7., Precision::Confusion());
}

TEST(BndLibTest, Sphere_Patch)
{

  gp_Sphere aSphere(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 5.);
  Bnd_Box   aBox;
  double    aTol = 0.;

  BndLib::Add(aSphere, 0., 2. * M_PI, 0., M_PI / 2., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -5., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5., Precision::Confusion());
  EXPECT_NEAR(aYmin, -5., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
  EXPECT_NEAR(aZmin, 0., Precision::Confusion());
  EXPECT_NEAR(aZmax, 5., Precision::Confusion());
}

TEST(BndLibTest, Sphere_Translated)
{

  gp_Sphere aSphere(gp_Ax3(gp_Pnt(10., 20., 30.), gp_Dir(0., 0., 1.)), 3.);
  Bnd_Box   aBox;
  double    aTol = 0.;

  BndLib::Add(aSphere, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, 7., Precision::Confusion());
  EXPECT_NEAR(aXmax, 13., Precision::Confusion());
  EXPECT_NEAR(aYmin, 17., Precision::Confusion());
  EXPECT_NEAR(aYmax, 23., Precision::Confusion());
  EXPECT_NEAR(aZmin, 27., Precision::Confusion());
  EXPECT_NEAR(aZmax, 33., Precision::Confusion());
}

TEST(BndLibTest, Cylinder_FinitePatch)
{

  gp_Cylinder aCyl(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 4.);
  Bnd_Box     aBox;
  double      aTol = 0.;

  BndLib::Add(aCyl, 0., 2. * M_PI, 0., 10., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -4., Precision::Confusion());
  EXPECT_NEAR(aXmax, 4., Precision::Confusion());
  EXPECT_NEAR(aYmin, -4., Precision::Confusion());
  EXPECT_NEAR(aYmax, 4., Precision::Confusion());
  EXPECT_NEAR(aZmin, 0., Precision::Confusion());
  EXPECT_NEAR(aZmax, 10., Precision::Confusion());
}

TEST(BndLibTest, Cylinder_InfiniteV)
{

  gp_Cylinder aCyl(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 4.);
  Bnd_Box     aBox;
  double      aTol = 0.;

  BndLib::Add(aCyl, 0., std::numeric_limits<double>::infinity(), aTol, aBox);

  EXPECT_TRUE(aBox.IsOpenZmax()) << "Zmax should be open for cylinder with VMax=+Inf";
  EXPECT_FALSE(aBox.IsOpenZmin()) << "Zmin should not be open";
}

TEST(BndLibTest, Cylinder_PartialU)
{

  gp_Cylinder aCyl(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 5.);
  Bnd_Box     aBox;
  double      aTol = 0.;

  BndLib::Add(aCyl, 0., M_PI / 2., 0., 10., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, 0., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5., Precision::Confusion());
  EXPECT_NEAR(aYmin, 0., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
  EXPECT_NEAR(aZmin, 0., Precision::Confusion());
  EXPECT_NEAR(aZmax, 10., Precision::Confusion());
}

TEST(BndLibTest, Cone_FinitePatch)
{

  gp_Cone aCone(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), M_PI / 4., 2.);
  Bnd_Box aBox;
  double  aTol = 0.;

  BndLib::Add(aCone, 0., 2. * M_PI, 0., 5., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  double aMaxRadius = 2. + 5. * std::sin(M_PI / 4.);
  double aMaxZ      = 5. * std::cos(M_PI / 4.);
  EXPECT_NEAR(aXmax, aMaxRadius, Precision::Confusion());
  EXPECT_NEAR(aYmax, aMaxRadius, Precision::Confusion());
  EXPECT_NEAR(aZmax, aMaxZ, Precision::Confusion());
  EXPECT_NEAR(aZmin, 0., Precision::Confusion());
}

TEST(BndLibTest, Cone_NegativeV)
{

  gp_Cone aCone(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), M_PI / 6., 3.);
  Bnd_Box aBox;
  double  aTol = 0.;

  BndLib::Add(aCone, 0., 2. * M_PI, -5., 0., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  double aExpectedZmin = -5. * std::cos(M_PI / 6.);
  EXPECT_NEAR(aZmin, aExpectedZmin, Precision::Confusion());
  EXPECT_NEAR(aZmax, 0., Precision::Confusion());
}

TEST(BndLibTest, Cone_InfiniteV)
{

  gp_Cone aCone(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), M_PI / 4., 2.);
  Bnd_Box aBox;
  double  aTol = 0.;

  BndLib::Add(aCone, 0., std::numeric_limits<double>::infinity(), aTol, aBox);

  EXPECT_TRUE(aBox.IsOpenZmax()) << "Zmax should be open for cone with VMax=+Inf";
}

TEST(BndLibTest, Torus_Full)
{

  gp_Torus aTorus(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 10., 3.);
  Bnd_Box  aBox;
  double   aTol = 0.;

  BndLib::Add(aTorus, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -13., Precision::Confusion());
  EXPECT_NEAR(aXmax, 13., Precision::Confusion());
  EXPECT_NEAR(aYmin, -13., Precision::Confusion());
  EXPECT_NEAR(aYmax, 13., Precision::Confusion());
  EXPECT_NEAR(aZmin, -3., Precision::Confusion());
  EXPECT_NEAR(aZmax, 3., Precision::Confusion());
}

TEST(BndLibTest, Torus_Patch)
{

  gp_Torus aTorus(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 10., 3.);
  Bnd_Box  aBox;
  double   aTol = 0.;

  BndLib::Add(aTorus, 0., M_PI / 2., 0., M_PI, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_FALSE(aBox.IsVoid()) << "Box should not be void for torus patch";

  EXPECT_GE(aXmin, -Precision::Confusion()) << "Xmin should be >= 0 for first quadrant";
  EXPECT_GE(aYmin, -Precision::Confusion()) << "Ymin should be >= 0 for first quadrant";

  EXPECT_LE(aZmax, 3. + Precision::Confusion()) << "Zmax should not exceed r";
}

TEST(BndLibTest, Torus_NegativeVParameter)
{

  gp_Torus aTorus(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 10., 3.);
  Bnd_Box  aBox;
  double   aTol = 0.;

  BndLib::Add(aTorus, 0., 2. * M_PI, -M_PI, 0., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_FALSE(aBox.IsVoid()) << "Box should not be void for negative V parameters";

  EXPECT_LE(aZmin, 0.) << "Zmin should be <= 0 for V in [-PI, 0]";
  EXPECT_GE(aZmin, -3. - Precision::Confusion()) << "Zmin should be >= -r";
}

TEST(BndLibTest, Torus_LargeNegativeVParameter)
{

  gp_Torus aTorus(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 10., 3.);
  Bnd_Box  aBox;
  double   aTol = 0.;

  BndLib::Add(aTorus, 0., 2. * M_PI, -3. * M_PI, -2. * M_PI, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_FALSE(aBox.IsVoid()) << "Box should not be void for large negative V parameters";

  EXPECT_LE(aXmin, -13. + Precision::Confusion()) << "Xmin should be at least -(R+r)";
  EXPECT_GE(aXmax, 13. - Precision::Confusion()) << "Xmax should be at least R+r";
  EXPECT_LE(aYmin, -13. + Precision::Confusion()) << "Ymin should be at least -(R+r)";
  EXPECT_GE(aYmax, 13. - Precision::Confusion()) << "Ymax should be at least R+r";
}

TEST(BndLibTest, Torus_Translated)
{

  gp_Torus aTorus(gp_Ax3(gp_Pnt(5., 5., 5.), gp_Dir(0., 0., 1.)), 8., 2.);
  Bnd_Box  aBox;
  double   aTol = 0.;

  BndLib::Add(aTorus, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, 5. - 10., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5. + 10., Precision::Confusion());
  EXPECT_NEAR(aYmin, 5. - 10., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5. + 10., Precision::Confusion());
  EXPECT_NEAR(aZmin, 5. - 2., Precision::Confusion());
  EXPECT_NEAR(aZmax, 5. + 2., Precision::Confusion());
}

TEST(BndLibTest, Line2d_FiniteSegment)
{
  gp_Lin2d  aLine(gp_Pnt2d(0., 0.), gp_Dir2d(1., 1.));
  Bnd_Box2d aBox;
  double    aTol = 0.;

  BndLib::Add(aLine, 0., 10., aTol, aBox);

  double aXmin, aYmin, aXmax, aYmax;
  aBox.Get(aXmin, aYmin, aXmax, aYmax);

  double aExpected = 10. / std::sqrt(2.);
  EXPECT_NEAR(aXmin, 0., Precision::Confusion());
  EXPECT_NEAR(aXmax, aExpected, Precision::Confusion());
  EXPECT_NEAR(aYmin, 0., Precision::Confusion());
  EXPECT_NEAR(aYmax, aExpected, Precision::Confusion());
}

TEST(BndLibTest, Circle2d_Full)
{
  gp_Circ2d aCirc(gp_Ax2d(gp_Pnt2d(0., 0.), gp_Dir2d(1., 0.)), 5.);
  Bnd_Box2d aBox;
  double    aTol = 0.;

  BndLib::Add(aCirc, aTol, aBox);

  double aXmin, aYmin, aXmax, aYmax;
  aBox.Get(aXmin, aYmin, aXmax, aYmax);

  EXPECT_NEAR(aXmin, -5., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5., Precision::Confusion());
  EXPECT_NEAR(aYmin, -5., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
}

TEST(BndLibTest, Ellipse2d_Full)
{
  gp_Elips2d aElips(gp_Ax2d(gp_Pnt2d(0., 0.), gp_Dir2d(1., 0.)), 8., 4.);
  Bnd_Box2d  aBox;
  double     aTol = 0.;

  BndLib::Add(aElips, aTol, aBox);

  double aXmin, aYmin, aXmax, aYmax;
  aBox.Get(aXmin, aYmin, aXmax, aYmax);

  EXPECT_NEAR(aXmin, -8., Precision::Confusion());
  EXPECT_NEAR(aXmax, 8., Precision::Confusion());
  EXPECT_NEAR(aYmin, -4., Precision::Confusion());
  EXPECT_NEAR(aYmax, 4., Precision::Confusion());
}

TEST(BndLibTest, Hyperbola2d_SimpleArc)
{
  gp_Hypr2d aHypr(gp_Ax2d(gp_Pnt2d(0., 0.), gp_Dir2d(1., 0.)), 3., 2.);
  Bnd_Box2d aBox;
  double    aTol = 0.;

  BndLib::Add(aHypr, -1., 1., aTol, aBox);

  double aXmin, aYmin, aXmax, aYmax;
  aBox.Get(aXmin, aYmin, aXmax, aYmax);

  EXPECT_NEAR(aXmin, 3., Precision::Confusion());
  EXPECT_NEAR(aXmax, 3. * std::cosh(1.), Precision::Confusion());
  EXPECT_NEAR(aYmin, 2. * std::sinh(-1.), Precision::Confusion());
  EXPECT_NEAR(aYmax, 2. * std::sinh(1.), Precision::Confusion());
}

TEST(BndLibTest, Parabola2d_FiniteArc)
{
  gp_Parab2d aParab(gp_Ax2d(gp_Pnt2d(0., 0.), gp_Dir2d(1., 0.)), 2.);
  Bnd_Box2d  aBox;
  double     aTol = 0.;

  BndLib::Add(aParab, -4., 4., aTol, aBox);

  double aXmin, aYmin, aXmax, aYmax;
  aBox.Get(aXmin, aYmin, aXmax, aYmax);

  EXPECT_NEAR(aXmin, 0., Precision::Confusion());
  EXPECT_NEAR(aXmax, 2., Precision::Confusion());
  EXPECT_NEAR(aYmin, -4., Precision::Confusion());
  EXPECT_NEAR(aYmax, 4., Precision::Confusion());
}

TEST(BndLibTest, Circle_WithTolerance)
{
  gp_Circ aCirc(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 5.);
  Bnd_Box aBox;
  double  aTol = 0.5;

  BndLib::Add(aCirc, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -5.5, Precision::Confusion());
  EXPECT_NEAR(aXmax, 5.5, Precision::Confusion());
  EXPECT_NEAR(aYmin, -5.5, Precision::Confusion());
  EXPECT_NEAR(aYmax, 5.5, Precision::Confusion());
  EXPECT_NEAR(aZmin, -0.5, Precision::Confusion());
  EXPECT_NEAR(aZmax, 0.5, Precision::Confusion());
}

TEST(BndLibTest, Sphere_WithTolerance)
{
  gp_Sphere aSphere(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 3.);
  Bnd_Box   aBox;
  double    aTol = 1.;

  BndLib::Add(aSphere, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -4., Precision::Confusion());
  EXPECT_NEAR(aXmax, 4., Precision::Confusion());
  EXPECT_NEAR(aYmin, -4., Precision::Confusion());
  EXPECT_NEAR(aYmax, 4., Precision::Confusion());
  EXPECT_NEAR(aZmin, -4., Precision::Confusion());
  EXPECT_NEAR(aZmax, 4., Precision::Confusion());
}

TEST(BndLib_Add3dCurveTest, Circle_Full)
{

  occ::handle<Geom_Circle> aCircle =
    new Geom_Circle(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 5.);
  GeomAdaptor_Curve aCurve(aCircle);
  Bnd_Box           aBox;
  double            aTol = 0.;

  BndLib_Add3dCurve::Add(aCurve, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -5., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5., Precision::Confusion());
  EXPECT_NEAR(aYmin, -5., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
  EXPECT_NEAR(aZmin, 0., Precision::Confusion());
  EXPECT_NEAR(aZmax, 0., Precision::Confusion());
}

TEST(BndLib_Add3dCurveTest, Circle_Arc)
{

  occ::handle<Geom_Circle> aCircle =
    new Geom_Circle(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 5.);
  GeomAdaptor_Curve aCurve(aCircle);
  Bnd_Box           aBox;
  double            aTol = 0.;

  BndLib_Add3dCurve::Add(aCurve, 0., M_PI / 2., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, 0., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5., Precision::Confusion());
  EXPECT_NEAR(aYmin, 0., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
}

TEST(BndLib_Add3dCurveTest, Ellipse_Full)
{

  occ::handle<Geom_Ellipse> anEllipse =
    new Geom_Ellipse(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 10., 5.);
  GeomAdaptor_Curve aCurve(anEllipse);
  Bnd_Box           aBox;
  double            aTol = 0.;

  BndLib_Add3dCurve::Add(aCurve, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -10., Precision::Confusion());
  EXPECT_NEAR(aXmax, 10., Precision::Confusion());
  EXPECT_NEAR(aYmin, -5., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
}

TEST(BndLib_Add3dCurveTest, Line_Segment)
{

  occ::handle<Geom_Line>         aLine    = new Geom_Line(gp_Pnt(0., 0., 0.), gp_Dir(1., 0., 0.));
  occ::handle<Geom_TrimmedCurve> aTrimmed = new Geom_TrimmedCurve(aLine, 0., 10.);
  GeomAdaptor_Curve              aCurve(aTrimmed);
  Bnd_Box                        aBox;
  double                         aTol = 0.;

  BndLib_Add3dCurve::Add(aCurve, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, 0., Precision::Confusion());
  EXPECT_NEAR(aXmax, 10., Precision::Confusion());
  EXPECT_NEAR(aYmin, 0., Precision::Confusion());
  EXPECT_NEAR(aYmax, 0., Precision::Confusion());
  EXPECT_NEAR(aZmin, 0., Precision::Confusion());
  EXPECT_NEAR(aZmax, 0., Precision::Confusion());
}

TEST(BndLib_Add3dCurveTest, BezierCurve)
{

  NCollection_Array1<gp_Pnt> aPoles(1, 4);
  aPoles(1) = gp_Pnt(0., 0., 0.);
  aPoles(2) = gp_Pnt(1., 2., 0.);
  aPoles(3) = gp_Pnt(3., 2., 0.);
  aPoles(4) = gp_Pnt(4., 0., 0.);

  occ::handle<Geom_BezierCurve> aBezier = new Geom_BezierCurve(aPoles);
  GeomAdaptor_Curve             aCurve(aBezier);
  Bnd_Box                       aBox;
  double                        aTol = 0.;

  BndLib_Add3dCurve::Add(aCurve, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_FALSE(aBox.IsVoid()) << "Box should not be void";
  EXPECT_LE(aXmin, 0.);
  EXPECT_GE(aXmax, 4.);
  EXPECT_LE(aYmin, 0.);

  EXPECT_GT(aYmax, 1.) << "Y max should be > 1 (curve rises above Y=0)";
}

TEST(BndLib_Add3dCurveTest, BSplineCurve)
{

  NCollection_Array1<gp_Pnt> aPoles(1, 4);
  aPoles(1) = gp_Pnt(0., 0., 0.);
  aPoles(2) = gp_Pnt(1., 1., 0.);
  aPoles(3) = gp_Pnt(2., 1., 0.);
  aPoles(4) = gp_Pnt(3., 0., 0.);

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.;
  aKnots(2) = 1.;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 4;
  aMults(2) = 4;

  occ::handle<Geom_BSplineCurve> aBSpline = new Geom_BSplineCurve(aPoles, aKnots, aMults, 3);
  GeomAdaptor_Curve              aCurve(aBSpline);
  Bnd_Box                        aBox;
  double                         aTol = 0.;

  BndLib_Add3dCurve::Add(aCurve, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_FALSE(aBox.IsVoid()) << "Box should not be void";
  EXPECT_LE(aXmin, 0.);
  EXPECT_GE(aXmax, 3.);
}

TEST(BndLib_Add3dCurveTest, AddOptimal_Circle)
{

  occ::handle<Geom_Circle> aCircle =
    new Geom_Circle(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 5.);
  GeomAdaptor_Curve aCurve(aCircle);
  Bnd_Box           aBox;
  double            aTol = 0.;

  BndLib_Add3dCurve::AddOptimal(aCurve, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -5., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5., Precision::Confusion());
  EXPECT_NEAR(aYmin, -5., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
}

TEST(BndLib_Add3dCurveTest, Circle_Rotated)
{

  occ::handle<Geom_Circle> aCircle =
    new Geom_Circle(gp_Ax2(gp_Pnt(0., 0., 0.), gp_Dir(1., 0., 0.)), 4.);
  GeomAdaptor_Curve aCurve(aCircle);
  Bnd_Box           aBox;
  double            aTol = 0.;

  BndLib_Add3dCurve::Add(aCurve, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, 0., Precision::Confusion());
  EXPECT_NEAR(aXmax, 0., Precision::Confusion());
  EXPECT_NEAR(aYmin, -4., Precision::Confusion());
  EXPECT_NEAR(aYmax, 4., Precision::Confusion());
  EXPECT_NEAR(aZmin, -4., Precision::Confusion());
  EXPECT_NEAR(aZmax, 4., Precision::Confusion());
}

TEST(BndLib_Add2dCurveTest, Circle_Full)
{

  occ::handle<Geom2d_Circle> aCircle =
    new Geom2d_Circle(gp_Ax2d(gp_Pnt2d(0., 0.), gp_Dir2d(1., 0.)), 5.);
  Bnd_Box2d aBox;
  double    aTol = 0.;

  BndLib_Add2dCurve::Add(aCircle, aTol, aBox);

  double aXmin, aYmin, aXmax, aYmax;
  aBox.Get(aXmin, aYmin, aXmax, aYmax);

  EXPECT_NEAR(aXmin, -5., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5., Precision::Confusion());
  EXPECT_NEAR(aYmin, -5., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
}

TEST(BndLib_Add2dCurveTest, Circle_Arc)
{

  occ::handle<Geom2d_Circle> aCircle =
    new Geom2d_Circle(gp_Ax2d(gp_Pnt2d(0., 0.), gp_Dir2d(1., 0.)), 5.);
  Bnd_Box2d aBox;
  double    aTol = 0.;

  BndLib_Add2dCurve::Add(aCircle, 0., M_PI / 2., aTol, aBox);

  double aXmin, aYmin, aXmax, aYmax;
  aBox.Get(aXmin, aYmin, aXmax, aYmax);

  EXPECT_NEAR(aXmin, 0., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5., Precision::Confusion());
  EXPECT_NEAR(aYmin, 0., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
}

TEST(BndLib_Add2dCurveTest, Ellipse_Full)
{

  occ::handle<Geom2d_Ellipse> anEllipse =
    new Geom2d_Ellipse(gp_Ax2d(gp_Pnt2d(0., 0.), gp_Dir2d(1., 0.)), 8., 4.);
  Bnd_Box2d aBox;
  double    aTol = 0.;

  BndLib_Add2dCurve::Add(anEllipse, aTol, aBox);

  double aXmin, aYmin, aXmax, aYmax;
  aBox.Get(aXmin, aYmin, aXmax, aYmax);

  EXPECT_NEAR(aXmin, -8., Precision::Confusion());
  EXPECT_NEAR(aXmax, 8., Precision::Confusion());
  EXPECT_NEAR(aYmin, -4., Precision::Confusion());
  EXPECT_NEAR(aYmax, 4., Precision::Confusion());
}

TEST(BndLib_Add2dCurveTest, Line_Segment)
{

  occ::handle<Geom2d_Line>         aLine    = new Geom2d_Line(gp_Pnt2d(0., 0.), gp_Dir2d(2., 1.));
  occ::handle<Geom2d_TrimmedCurve> aTrimmed = new Geom2d_TrimmedCurve(aLine, 0., std::sqrt(125.));
  Geom2dAdaptor_Curve              aCurve(aTrimmed);
  Bnd_Box2d                        aBox;
  double                           aTol = 0.;

  BndLib_Add2dCurve::Add(aCurve, aTol, aBox);

  double aXmin, aYmin, aXmax, aYmax;
  aBox.Get(aXmin, aYmin, aXmax, aYmax);

  EXPECT_NEAR(aXmin, 0., Precision::Confusion());
  EXPECT_NEAR(aXmax, 10., 0.01);
  EXPECT_NEAR(aYmin, 0., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., 0.01);
}

TEST(BndLib_Add2dCurveTest, BezierCurve)
{

  NCollection_Array1<gp_Pnt2d> aPoles(1, 4);
  aPoles(1) = gp_Pnt2d(0., 0.);
  aPoles(2) = gp_Pnt2d(1., 3.);
  aPoles(3) = gp_Pnt2d(3., 3.);
  aPoles(4) = gp_Pnt2d(4., 0.);

  occ::handle<Geom2d_BezierCurve> aBezier = new Geom2d_BezierCurve(aPoles);
  Geom2dAdaptor_Curve             aCurve(aBezier);
  Bnd_Box2d                       aBox;
  double                          aTol = 0.;

  BndLib_Add2dCurve::Add(aCurve, aTol, aBox);

  double aXmin, aYmin, aXmax, aYmax;
  aBox.Get(aXmin, aYmin, aXmax, aYmax);

  EXPECT_LE(aXmin, 0.);
  EXPECT_GE(aXmax, 4.);
  EXPECT_LE(aYmin, 0.);
  EXPECT_GE(aYmax, 3.);
}

TEST(BndLib_Add2dCurveTest, AddOptimal_Ellipse)
{

  occ::handle<Geom2d_Ellipse> anEllipse =
    new Geom2d_Ellipse(gp_Ax2d(gp_Pnt2d(0., 0.), gp_Dir2d(1., 0.)), 6., 3.);
  Bnd_Box2d aBox;
  double    aTol = 0.;

  BndLib_Add2dCurve::AddOptimal(anEllipse, 0., 2. * M_PI, aTol, aBox);

  double aXmin, aYmin, aXmax, aYmax;
  aBox.Get(aXmin, aYmin, aXmax, aYmax);

  EXPECT_NEAR(aXmin, -6., Precision::Confusion());
  EXPECT_NEAR(aXmax, 6., Precision::Confusion());
  EXPECT_NEAR(aYmin, -3., Precision::Confusion());
  EXPECT_NEAR(aYmax, 3., Precision::Confusion());
}

TEST(BndLib_Add2dCurveTest, Adaptor_Circle)
{

  occ::handle<Geom2d_Circle> aCircle =
    new Geom2d_Circle(gp_Ax2d(gp_Pnt2d(5., 5.), gp_Dir2d(1., 0.)), 3.);
  Geom2dAdaptor_Curve aCurve(aCircle);
  Bnd_Box2d           aBox;
  double              aTol = 0.;

  BndLib_Add2dCurve::Add(aCurve, aTol, aBox);

  double aXmin, aYmin, aXmax, aYmax;
  aBox.Get(aXmin, aYmin, aXmax, aYmax);

  EXPECT_NEAR(aXmin, 2., Precision::Confusion());
  EXPECT_NEAR(aXmax, 8., Precision::Confusion());
  EXPECT_NEAR(aYmin, 2., Precision::Confusion());
  EXPECT_NEAR(aYmax, 8., Precision::Confusion());
}

TEST(BndLib_AddSurfaceTest, Plane)
{

  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)));
  GeomAdaptor_Surface     aSurf(aPlane);
  Bnd_Box                 aBox;
  double                  aTol = 0.;

  BndLib_AddSurface::Add(aSurf, -5., 5., -5., 5., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -5., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5., Precision::Confusion());
  EXPECT_NEAR(aYmin, -5., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
  EXPECT_NEAR(aZmin, 0., Precision::Confusion());
  EXPECT_NEAR(aZmax, 0., Precision::Confusion());
}

TEST(BndLib_AddSurfaceTest, Cylinder_Full)
{

  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 5.);
  GeomAdaptor_Surface aSurf(aCyl);
  Bnd_Box             aBox;
  double              aTol = 0.;

  BndLib_AddSurface::Add(aSurf, 0., 2. * M_PI, 0., 10., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -5., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5., Precision::Confusion());
  EXPECT_NEAR(aYmin, -5., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
  EXPECT_NEAR(aZmin, 0., Precision::Confusion());
  EXPECT_NEAR(aZmax, 10., Precision::Confusion());
}

TEST(BndLib_AddSurfaceTest, Sphere_Full)
{

  occ::handle<Geom_SphericalSurface> aSphere =
    new Geom_SphericalSurface(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 7.);
  GeomAdaptor_Surface aSurf(aSphere);
  Bnd_Box             aBox;
  double              aTol = 0.;

  BndLib_AddSurface::Add(aSurf, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -7., Precision::Confusion());
  EXPECT_NEAR(aXmax, 7., Precision::Confusion());
  EXPECT_NEAR(aYmin, -7., Precision::Confusion());
  EXPECT_NEAR(aYmax, 7., Precision::Confusion());
  EXPECT_NEAR(aZmin, -7., Precision::Confusion());
  EXPECT_NEAR(aZmax, 7., Precision::Confusion());
}

TEST(BndLib_AddSurfaceTest, Sphere_Patch)
{

  occ::handle<Geom_SphericalSurface> aSphere =
    new Geom_SphericalSurface(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 5.);
  GeomAdaptor_Surface aSurf(aSphere);
  Bnd_Box             aBox;
  double              aTol = 0.;

  BndLib_AddSurface::Add(aSurf, 0., 2. * M_PI, 0., M_PI / 2., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -5., Precision::Confusion());
  EXPECT_NEAR(aXmax, 5., Precision::Confusion());
  EXPECT_NEAR(aYmin, -5., Precision::Confusion());
  EXPECT_NEAR(aYmax, 5., Precision::Confusion());
  EXPECT_NEAR(aZmin, 0., Precision::Confusion());
  EXPECT_NEAR(aZmax, 5., Precision::Confusion());
}

TEST(BndLib_AddSurfaceTest, Cone_Full)
{

  occ::handle<Geom_ConicalSurface> aCone =
    new Geom_ConicalSurface(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), M_PI / 4., 2.);
  GeomAdaptor_Surface aSurf(aCone);
  Bnd_Box             aBox;
  double              aTol = 0.;

  BndLib_AddSurface::Add(aSurf, 0., 2. * M_PI, 0., 5., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  double aMaxRadius = 2. + 5. * std::sin(M_PI / 4.);
  double aMaxZ      = 5. * std::cos(M_PI / 4.);

  EXPECT_NEAR(aXmax, aMaxRadius, Precision::Confusion());
  EXPECT_NEAR(aYmax, aMaxRadius, Precision::Confusion());
  EXPECT_NEAR(aZmax, aMaxZ, Precision::Confusion());
}

TEST(BndLib_AddSurfaceTest, Torus_Full)
{

  occ::handle<Geom_ToroidalSurface> aTorus =
    new Geom_ToroidalSurface(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 10., 3.);
  GeomAdaptor_Surface aSurf(aTorus);
  Bnd_Box             aBox;
  double              aTol = 0.;

  BndLib_AddSurface::Add(aSurf, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_LE(aXmin, -13. + Precision::Confusion());
  EXPECT_GE(aXmax, 13. - Precision::Confusion());
  EXPECT_LE(aYmin, -13. + Precision::Confusion());
  EXPECT_GE(aYmax, 13. - Precision::Confusion());
  EXPECT_NEAR(aZmin, -3., Precision::Confusion());
  EXPECT_NEAR(aZmax, 3., Precision::Confusion());
}

TEST(BndLib_AddSurfaceTest, BezierSurface)
{

  NCollection_Array2<gp_Pnt> aPoles(1, 2, 1, 2);
  aPoles(1, 1) = gp_Pnt(0., 0., 0.);
  aPoles(1, 2) = gp_Pnt(0., 10., 2.);
  aPoles(2, 1) = gp_Pnt(10., 0., 2.);
  aPoles(2, 2) = gp_Pnt(10., 10., 0.);

  occ::handle<Geom_BezierSurface> aBezier = new Geom_BezierSurface(aPoles);
  GeomAdaptor_Surface             aSurf(aBezier);
  Bnd_Box                         aBox;
  double                          aTol = 0.;

  BndLib_AddSurface::Add(aSurf, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_LE(aXmin, 0.);
  EXPECT_GE(aXmax, 10.);
  EXPECT_LE(aYmin, 0.);
  EXPECT_GE(aYmax, 10.);
  EXPECT_LE(aZmin, 0.);
  EXPECT_GE(aZmax, 2.);
}

TEST(BndLib_AddSurfaceTest, AddOptimal_Sphere)
{

  occ::handle<Geom_SphericalSurface> aSphere =
    new Geom_SphericalSurface(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)), 4.);
  GeomAdaptor_Surface aSurf(aSphere);
  Bnd_Box             aBox;
  double              aTol = 0.;

  BndLib_AddSurface::AddOptimal(aSurf, aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, -4., Precision::Confusion());
  EXPECT_NEAR(aXmax, 4., Precision::Confusion());
  EXPECT_NEAR(aYmin, -4., Precision::Confusion());
  EXPECT_NEAR(aYmax, 4., Precision::Confusion());
  EXPECT_NEAR(aZmin, -4., Precision::Confusion());
  EXPECT_NEAR(aZmax, 4., Precision::Confusion());
}

TEST(BndLib_AddSurfaceTest, Cylinder_Translated)
{

  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(5., 5., 0.), gp_Dir(0., 0., 1.)), 3.);
  GeomAdaptor_Surface aSurf(aCyl);
  Bnd_Box             aBox;
  double              aTol = 0.;

  BndLib_AddSurface::Add(aSurf, 0., 2. * M_PI, 0., 10., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_NEAR(aXmin, 2., Precision::Confusion());
  EXPECT_NEAR(aXmax, 8., Precision::Confusion());
  EXPECT_NEAR(aYmin, 2., Precision::Confusion());
  EXPECT_NEAR(aYmax, 8., Precision::Confusion());
  EXPECT_NEAR(aZmin, 0., Precision::Confusion());
  EXPECT_NEAR(aZmax, 10., Precision::Confusion());
}

TEST(BndLib_AddSurfaceTest, Plane_Tilted)
{

  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 1., 1.)));
  GeomAdaptor_Surface     aSurf(aPlane);
  Bnd_Box                 aBox;
  double                  aTol = 0.;

  BndLib_AddSurface::Add(aSurf, 0., 1., 0., 1., aTol, aBox);

  EXPECT_FALSE(aBox.IsVoid()) << "Box should not be void for tilted plane";
}

TEST(BndLib_AddSurfaceTest, LargeParameters_PrecisionTest)
{

  NCollection_Array2<gp_Pnt> aPoles(1, 3, 1, 3);

  for (int i = 1; i <= 3; i++)
  {
    for (int j = 1; j <= 3; j++)
    {
      aPoles(i, j) = gp_Pnt((i - 1) * 10., (j - 1) * 10., 0.);
    }
  }
  occ::handle<Geom_BezierSurface> aBezier = new Geom_BezierSurface(aPoles);
  GeomAdaptor_Surface             aSurf(aBezier);
  Bnd_Box                         aBox;
  double                          aTol = 0.;

  BndLib_AddSurface::Add(aSurf, 0., 1., 0., 1., aTol, aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  EXPECT_LE(aXmin, 1.) << "XMin should capture sampled points";
  EXPECT_GE(aXmax, 19.) << "XMax should capture sampled points";
  EXPECT_LE(aYmin, 1.) << "YMin should capture sampled points";
  EXPECT_GE(aYmax, 19.) << "YMax should capture sampled points";
}

TEST(BndLib_AddSurfaceTest, OffsetSurface_ParameterPrecision)
{

  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Ax3(gp_Pnt(0., 0., 0.), gp_Dir(0., 0., 1.)));
  GeomAdaptor_Surface     aSurf(aPlane);
  Bnd_Box                 aBox;
  double                  aTol = 0.;

  const double aLargeOffset = 1.0e10;
  const double aRange       = 100.;
  BndLib_AddSurface::Add(aSurf,
                         aLargeOffset,
                         aLargeOffset + aRange,
                         aLargeOffset,
                         aLargeOffset + aRange,
                         aTol,
                         aBox);

  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  const double aTolerance = 1.0;

  EXPECT_NEAR(aXmin, aLargeOffset, aTolerance) << "XMin should be near the large offset value";
  EXPECT_NEAR(aXmax, aLargeOffset + aRange, aTolerance) << "XMax should capture the full range";
  EXPECT_NEAR(aYmin, aLargeOffset, aTolerance) << "YMin should be near the large offset value";
  EXPECT_NEAR(aYmax, aLargeOffset + aRange, aTolerance) << "YMax should capture the full range";

  const double aComputedRangeX = aXmax - aXmin;
  const double aComputedRangeY = aYmax - aYmin;

  EXPECT_GT(aComputedRangeX, aRange * 0.9)
    << "X range should not collapse due to floating-point precision issues";
  EXPECT_GT(aComputedRangeY, aRange * 0.9)
    << "Y range should not collapse due to floating-point precision issues";
}
