

#include <Extrema_ExtPC.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <Geom_Circle.hpp>
#include <ElSLib.hpp>
#include <gp_Pnt.hpp>
#include <gp_Ax2.hpp>
#include <gp_Cylinder.hpp>

#include <gtest/gtest.h>

TEST(Extrema_ExtPC_Test, Bug24945_CylinderParameterNormalization)
{

  gp_Pnt aP3D(-1725.97, 843.257, -4.22741e-013);

  gp_Ax2                   aAxis(gp_Pnt(0, 843.257, 0), gp_Dir(gp::DY()).Reversed(), gp::DX());
  occ::handle<Geom_Circle> aCircle = new Geom_Circle(aAxis, 1725.9708621929999);
  GeomAdaptor_Curve        aC3D(aCircle);

  Extrema_ExtPC aExtPC(aP3D, aC3D);
  ASSERT_TRUE(aExtPC.IsDone());
  ASSERT_GT(aExtPC.NbExt(), 0);

  gp_Pnt aProj = aExtPC.Point(1).Value();

  EXPECT_NEAR(aProj.X(), -1725.97, 1.0e-2);
  EXPECT_NEAR(aProj.Y(), 843.257, 1.0e-2);
  EXPECT_NEAR(aProj.Z(), 0.0, 1.0e-10);

  gp_Ax2      aCylAxis(gp_Pnt(0, 2103.87, 0), gp::DY().Reversed(), gp::DX().Reversed());
  gp_Cylinder aCylinder(aCylAxis, 1890.);

  double aU = 0., aV = 0.;
  ElSLib::Parameters(aCylinder, aProj, aU, aV);

  EXPECT_NEAR(aU, 0.0, 1.0e-4);
  EXPECT_NEAR(aV, 1260.613, 1.0e-2);
}
