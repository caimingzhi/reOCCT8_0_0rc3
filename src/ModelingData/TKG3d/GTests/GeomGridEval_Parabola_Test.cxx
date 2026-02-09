

#include <gtest/gtest.h>

#include <Geom_Parabola.hpp>
#include <GeomGridEval_Parabola.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>
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
} // namespace

TEST(GeomGridEval_ParabolaTest, BasicEvaluation)
{

  occ::handle<Geom_Parabola> aParab =
    new Geom_Parabola(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 1.0);

  GeomGridEval_Parabola anEval(aParab);
  EXPECT_FALSE(anEval.Geometry().IsNull());

  NCollection_Array1<double> aParams = CreateUniformParams(-2.0, 2.0, 5);

  NCollection_Array1<gp_Pnt> aGrid = anEval.EvaluateGrid(aParams);
  EXPECT_EQ(aGrid.Size(), 5);

  for (int i = 1; i <= 5; ++i)
  {
    gp_Pnt aExpected = aParab->Value(aParams.Value(i));
    EXPECT_NEAR(aGrid.Value(i).Distance(aExpected), 0.0, THE_TOLERANCE);
  }
}

TEST(GeomGridEval_ParabolaTest, DerivativeD1)
{
  occ::handle<Geom_Parabola> aParab =
    new Geom_Parabola(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 1.0);
  GeomGridEval_Parabola anEval(aParab);

  NCollection_Array1<double> aParams = CreateUniformParams(-2.0, 2.0, 9);

  NCollection_Array1<GeomGridEval::CurveD1> aGrid = anEval.EvaluateGridD1(aParams);

  for (int i = 1; i <= 9; ++i)
  {
    gp_Pnt aPnt;
    gp_Vec aD1;
    aParab->D1(aParams.Value(i), aPnt, aD1);
    EXPECT_NEAR(aGrid.Value(i).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
    EXPECT_NEAR((aGrid.Value(i).D1 - aD1).Magnitude(), 0.0, THE_TOLERANCE);
  }
}

TEST(GeomGridEval_ParabolaTest, DerivativeD2)
{
  occ::handle<Geom_Parabola> aParab =
    new Geom_Parabola(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 1.0);
  GeomGridEval_Parabola anEval(aParab);

  NCollection_Array1<double> aParams = CreateUniformParams(-2.0, 2.0, 9);

  NCollection_Array1<GeomGridEval::CurveD2> aGrid = anEval.EvaluateGridD2(aParams);

  for (int i = 1; i <= 9; ++i)
  {
    gp_Pnt aPnt;
    gp_Vec aD1, aD2;
    aParab->D2(aParams.Value(i), aPnt, aD1, aD2);
    EXPECT_NEAR(aGrid.Value(i).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
    EXPECT_NEAR((aGrid.Value(i).D1 - aD1).Magnitude(), 0.0, THE_TOLERANCE);
    EXPECT_NEAR((aGrid.Value(i).D2 - aD2).Magnitude(), 0.0, THE_TOLERANCE);
  }
}

TEST(GeomGridEval_ParabolaTest, DerivativeD3)
{
  occ::handle<Geom_Parabola> aParab =
    new Geom_Parabola(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 1.0);
  GeomGridEval_Parabola anEval(aParab);

  NCollection_Array1<double> aParams = CreateUniformParams(-2.0, 2.0, 9);

  NCollection_Array1<GeomGridEval::CurveD3> aGrid = anEval.EvaluateGridD3(aParams);

  for (int i = 1; i <= 9; ++i)
  {
    gp_Pnt aPnt;
    gp_Vec aD1, aD2, aD3;
    aParab->D3(aParams.Value(i), aPnt, aD1, aD2, aD3);
    EXPECT_NEAR(aGrid.Value(i).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
    EXPECT_NEAR((aGrid.Value(i).D1 - aD1).Magnitude(), 0.0, THE_TOLERANCE);
    EXPECT_NEAR((aGrid.Value(i).D2 - aD2).Magnitude(), 0.0, THE_TOLERANCE);
    EXPECT_NEAR((aGrid.Value(i).D3 - aD3).Magnitude(), 0.0, THE_TOLERANCE);
  }
}
