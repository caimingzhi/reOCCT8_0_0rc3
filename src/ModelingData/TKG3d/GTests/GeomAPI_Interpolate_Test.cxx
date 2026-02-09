

#include <gtest/gtest.h>

#include <GeomAPI_Interpolate.hpp>
#include <Geom_BSplineCurve.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>

#include <cmath>

TEST(GeomAPI_Interpolate_Test, BUC60902_TangentPreservation)
{

  occ::handle<NCollection_HArray1<gp_Pnt>> aPnts = new NCollection_HArray1<gp_Pnt>(1, 5);
  gp_Pnt                                   aP(0., 0., 0.);
  for (int i = 1; i <= 5; i++)
  {
    aP.SetX((i - 1) * 1.57);
    aP.SetY(sin((i - 1) * 1.57));
    aPnts->SetValue(i, aP);
  }

  GeomAPI_Interpolate anInterpolater(aPnts, false, Precision::Confusion());
  anInterpolater.Perform();
  ASSERT_TRUE(anInterpolater.IsDone()) << "First interpolation should succeed";

  occ::handle<Geom_BSplineCurve> aCur = anInterpolater.Curve();
  ASSERT_FALSE(aCur.IsNull()) << "Interpolated curve should not be null";

  gp_Vec aFirstTang, aLastTang;
  aCur->D1(aCur->FirstParameter(), aP, aFirstTang);
  aCur->D1(aCur->LastParameter(), aP, aLastTang);

  GeomAPI_Interpolate anInterpolater1(aPnts, false, Precision::Confusion());
  anInterpolater1.Load(aFirstTang, aLastTang, false);
  anInterpolater1.Perform();
  ASSERT_TRUE(anInterpolater1.IsDone()) << "Second interpolation should succeed";

  aCur = anInterpolater1.Curve();
  ASSERT_FALSE(aCur.IsNull()) << "Second interpolated curve should not be null";

  gp_Vec aFirstTang1, aLastTang1;
  aCur->D1(aCur->FirstParameter(), aP, aFirstTang1);
  aCur->D1(aCur->LastParameter(), aP, aLastTang1);

  EXPECT_TRUE(aFirstTang.IsEqual(aFirstTang1, Precision::Confusion(), Precision::Angular()))
    << "First tangent should be preserved after recomputation";

  EXPECT_TRUE(aLastTang.IsEqual(aLastTang1, Precision::Confusion(), Precision::Angular()))
    << "Last tangent should be preserved after recomputation";
}
