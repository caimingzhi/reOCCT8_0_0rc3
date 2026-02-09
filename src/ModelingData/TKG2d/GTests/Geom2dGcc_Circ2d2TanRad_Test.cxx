

#include <gtest/gtest.h>

#include <Geom2d_Ellipse.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dGcc_Circ2d2TanRad.hpp>
#include <Geom2dGcc_QualifiedCurve.hpp>
#include <GccEnt_Position.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Pnt2d.hpp>

TEST(Geom2dGcc_Circ2d2TanRad_Test, OCC24303_CircleTangentToTwoEllipses)
{

  double   aMajorRadius = 2.0;
  double   aMinorRadius = 1.0;
  gp_Pnt2d aP0(gp::Origin2d());
  gp_Pnt2d aP1(4.0, 0.0);

  gp_Elips2d anEllipse1 = gp_Elips2d(gp_Ax2d(aP0, gp::DX2d()), aMajorRadius, aMinorRadius, true);
  gp_Elips2d anEllipse2 = gp_Elips2d(gp_Ax2d(aP1, gp::DX2d()), aMajorRadius, aMinorRadius, true);

  occ::handle<Geom2d_Curve> aCurve1 = new Geom2d_Ellipse(anEllipse1);
  occ::handle<Geom2d_Curve> aCurve2 = new Geom2d_Ellipse(anEllipse2);

  gp_Pnt2d  aCentre(5.0, 0.0);
  double    aRadius           = 3.0;
  gp_Circ2d aTheoricalTangent = gp_Circ2d(gp_Ax2d(aCentre, gp::DX2d()), aRadius);

  const Geom2dAdaptor_Curve anAdaptedCurve1(aCurve1);
  const Geom2dAdaptor_Curve anAdaptedCurve2(aCurve2);

  GccEnt_Position aCurveQualif1 = GccEnt_unqualified;
  GccEnt_Position aCurveQualif2 = GccEnt_unqualified;

  const Geom2dGcc_QualifiedCurve aQualifiedCurve1(anAdaptedCurve1, aCurveQualif1);
  const Geom2dGcc_QualifiedCurve aQualifiedCurve2(anAdaptedCurve2, aCurveQualif2);

  const Geom2dGcc_Circ2d2TanRad aCircCalc(aQualifiedCurve1, aQualifiedCurve2, aRadius, 1.0e-9);

  const int aNbSol = aCircCalc.NbSolutions();

  EXPECT_GT(aNbSol, 0) << "Should find at least one solution";

  for (int i = 1; i <= aNbSol; i++)
  {
    gp_Circ2d aCt = aCircCalc.ThisSolution(i);
    EXPECT_NEAR(aRadius, aCt.Radius(), 1.0e-6)
      << "Solution " << i << " should have radius " << aRadius;
  }

  if (aNbSol > 0)
  {
    gp_Circ2d aCalculatedTangent = aCircCalc.ThisSolution(1);
    double    aDist = aTheoricalTangent.Location().Distance(aCalculatedTangent.Location());

    EXPECT_LT(aDist, 10.0) << "Distance from theoretical tangent should be reasonable";
  }
}
