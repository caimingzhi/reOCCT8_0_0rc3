

#include <Geom2dGcc_Circ2d3Tan.hpp>
#include <Geom2dGcc_QualifiedCurve.hpp>
#include <Geom2dGcc.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Dir2d.hpp>
#include <Precision.hpp>

#include <gtest/gtest.h>

class Geom2dGcc_Circ2d3TanTest : public ::testing::Test
{
protected:
  void SetUp() override { myTolerance = Precision::Confusion(); }

  double myTolerance;

  void verifyTangencyConstraints(const gp_Circ2d& theSolution,
                                 const gp_Circ2d& theCircle1,
                                 const gp_Circ2d& theCircle2,
                                 const gp_Circ2d& theCircle3,
                                 const int        theSolutionIndex,
                                 const double     theTolerance = 1e-6) const
  {
    gp_Pnt2d aSolCenter = theSolution.Location();
    double   aSolRadius = theSolution.Radius();

    for (int i = 1; i <= 3; i++)
    {
      const gp_Circ2d* aCircle     = (i == 1) ? &theCircle1 : (i == 2) ? &theCircle2 : &theCircle3;
      gp_Pnt2d         aCircCenter = aCircle->Location();
      double           aCircRadius = aCircle->Radius();

      double aDistanceCenters = aSolCenter.Distance(aCircCenter);

      double aExpectedDistExt = aSolRadius + aCircRadius;
      double aExpectedDistInt = std::abs(aSolRadius - aCircRadius);

      bool isTangent = (std::abs(aDistanceCenters - aExpectedDistExt) <= theTolerance)
                       || (std::abs(aDistanceCenters - aExpectedDistInt) <= theTolerance);

      EXPECT_TRUE(isTangent) << "Solution " << theSolutionIndex << " should be tangent to circle "
                             << i << " (distance=" << aDistanceCenters
                             << ", expected external=" << aExpectedDistExt
                             << ", expected internal=" << aExpectedDistInt << ")";
    }
  }

  Geom2dGcc_QualifiedCurve createQualifiedCircle(const double theX,
                                                 const double theY,
                                                 const double theRadius) const
  {
    gp_Pnt2d                   aCenter(theX, theY);
    occ::handle<Geom2d_Circle> aCircle =
      new Geom2d_Circle(gp_Circ2d(gp_Ax2d(aCenter, gp_Dir2d(1, 0)), theRadius));
    Geom2dAdaptor_Curve anAdaptor(aCircle);
    return Geom2dGcc::Unqualified(anAdaptor);
  }

  void verifySolutionValidity(const gp_Circ2d& theSolution,
                              const int        theSolutionIndex,
                              const double     theMinX      = -10000.0,
                              const double     theMaxX      = 10000.0,
                              const double     theMinY      = -10000.0,
                              const double     theMaxY      = 10000.0,
                              const double     theMaxRadius = 100000.0) const
  {
    EXPECT_GT(theSolution.Radius(), 0)
      << "Solution " << theSolutionIndex << " should have positive radius";
    EXPECT_LT(theSolution.Radius(), theMaxRadius)
      << "Solution " << theSolutionIndex << " should have reasonable radius";

    gp_Pnt2d aCenter = theSolution.Location();
    EXPECT_GT(aCenter.X(), theMinX)
      << "Solution " << theSolutionIndex << " X coordinate should be reasonable";
    EXPECT_LT(aCenter.X(), theMaxX)
      << "Solution " << theSolutionIndex << " X coordinate should be reasonable";
    EXPECT_GT(aCenter.Y(), theMinY)
      << "Solution " << theSolutionIndex << " Y coordinate should be reasonable";
    EXPECT_LT(aCenter.Y(), theMaxY)
      << "Solution " << theSolutionIndex << " Y coordinate should be reasonable";
  }
};

TEST_F(Geom2dGcc_Circ2d3TanTest, BUC60622_RegressionCase)
{

  Geom2dGcc_QualifiedCurve aQual1 = createQualifiedCircle(500.0, 1800.0, 500.0);
  Geom2dGcc_QualifiedCurve aQual2 = createQualifiedCircle(500.0, 1900.0, 400.0);
  Geom2dGcc_QualifiedCurve aQual3 = createQualifiedCircle(700.0, 1900.0, 200.0);

  gp_Circ2d aInputCirc1 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(500.0, 1800.0), gp_Dir2d(1, 0)), 500.0);
  gp_Circ2d aInputCirc2 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(500.0, 1900.0), gp_Dir2d(1, 0)), 400.0);
  gp_Circ2d aInputCirc3 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(700.0, 1900.0), gp_Dir2d(1, 0)), 200.0);

  Geom2dGcc_Circ2d3Tan aTangentSolver(aQual1, aQual2, aQual3, myTolerance, 0, 0, 0);

  EXPECT_TRUE(aTangentSolver.IsDone()) << "Algorithm should succeed";

  int aNbSolutions = aTangentSolver.NbSolutions();

  EXPECT_EQ(aNbSolutions, 3) << "BUC60622 case should find exactly 3 solutions";

  for (int i = 1; i <= aNbSolutions; i++)
  {
    gp_Circ2d aSol = aTangentSolver.ThisSolution(i);

    verifySolutionValidity(aSol, i, -1000.0, 2000.0, 1000.0, 3000.0, 10000.0);

    verifyTangencyConstraints(aSol, aInputCirc1, aInputCirc2, aInputCirc3, i);
  }

  if (aNbSolutions >= 3)
  {

    gp_Circ2d aSol1 = aTangentSolver.ThisSolution(1);
    EXPECT_NEAR(aSol1.Location().X(), 500.0, 1.0);
    EXPECT_NEAR(aSol1.Location().Y(), 1900.0, 1.0);
    EXPECT_NEAR(aSol1.Radius(), 400.0, 1.0);
  }
}

TEST_F(Geom2dGcc_Circ2d3TanTest, ToleranceImpact_Analysis)
{

  Geom2dGcc_QualifiedCurve aQual1 = createQualifiedCircle(500.0, 1800.0, 500.0);
  Geom2dGcc_QualifiedCurve aQual2 = createQualifiedCircle(500.0, 1900.0, 400.0);
  Geom2dGcc_QualifiedCurve aQual3 = createQualifiedCircle(700.0, 1900.0, 200.0);

  std::vector<double> aTestTolerances = {Precision::Confusion(), 1e-12, 1e-10, 1e-8};

  int aDefaultSolCount = 0;

  for (double aTol : aTestTolerances)
  {
    Geom2dGcc_Circ2d3Tan aSolver(aQual1, aQual2, aQual3, aTol, 0, 0, 0);

    EXPECT_TRUE(aSolver.IsDone()) << "Algorithm should succeed with tolerance " << aTol;

    int aNbSol = aSolver.NbSolutions();

    if (aTol == Precision::Confusion())
    {
      aDefaultSolCount = aNbSol;
      EXPECT_GE(aNbSol, 1) << "Should find at least 1 solution with default tolerance";
    }
    else
    {

      EXPECT_GE(aNbSol, 1) << "Should find at least 1 solution with tolerance " << aTol;
      EXPECT_LE(aNbSol, aDefaultSolCount + 2)
        << "Solution count shouldn't increase dramatically with tolerance " << aTol;
    }

    for (int i = 1; i <= aNbSol; i++)
    {
      gp_Circ2d aSol = aSolver.ThisSolution(i);
      verifySolutionValidity(aSol, i, -1000.0, 2000.0, 1000.0, 3000.0, 10000.0);
    }
  }
}

TEST_F(Geom2dGcc_Circ2d3TanTest, Simple_ThreeCircle_Case)
{

  Geom2dGcc_QualifiedCurve aQual1 = createQualifiedCircle(0.0, 0.0, 2.0);
  Geom2dGcc_QualifiedCurve aQual2 = createQualifiedCircle(10.0, 0.0, 2.0);
  Geom2dGcc_QualifiedCurve aQual3 = createQualifiedCircle(5.0, 8.0, 2.0);

  gp_Circ2d aInputCirc1 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(1, 0)), 2.0);
  gp_Circ2d aInputCirc2 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(10.0, 0.0), gp_Dir2d(1, 0)), 2.0);
  gp_Circ2d aInputCirc3 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(5.0, 8.0), gp_Dir2d(1, 0)), 2.0);

  Geom2dGcc_Circ2d3Tan aSolver(aQual1, aQual2, aQual3, myTolerance, 0, 0, 0);

  EXPECT_TRUE(aSolver.IsDone()) << "Simple case should always work";

  int aNbSol = aSolver.NbSolutions();
  EXPECT_GE(aNbSol, 1) << "Should find at least one solution for simple case";

  for (int i = 1; i <= aNbSol; i++)
  {
    gp_Circ2d aSol = aSolver.ThisSolution(i);
    verifySolutionValidity(aSol, i);
    verifyTangencyConstraints(aSol, aInputCirc1, aInputCirc2, aInputCirc3, i);
  }
}

TEST_F(Geom2dGcc_Circ2d3TanTest, Concentric_Circles_EdgeCase)
{

  Geom2dGcc_QualifiedCurve aQual1 = createQualifiedCircle(0.0, 0.0, 1.0);
  Geom2dGcc_QualifiedCurve aQual2 = createQualifiedCircle(0.0, 0.0, 3.0);
  Geom2dGcc_QualifiedCurve aQual3 = createQualifiedCircle(10.0, 0.0, 2.0);

  Geom2dGcc_Circ2d3Tan aSolver(aQual1, aQual2, aQual3, myTolerance, 0, 0, 0);

  EXPECT_TRUE(aSolver.IsDone())
    << "Algorithm should complete successfully even when no solutions exist";

  int aNbSol = aSolver.NbSolutions();

  EXPECT_EQ(aNbSol, 0) << "This concentric configuration geometrically has no solutions";
}

TEST_F(Geom2dGcc_Circ2d3TanTest, SmallCircles_PrecisionTest)
{

  Geom2dGcc_QualifiedCurve aQual1 = createQualifiedCircle(0.0, 0.0, 0.01);
  Geom2dGcc_QualifiedCurve aQual2 = createQualifiedCircle(0.1, 0.0, 0.01);
  Geom2dGcc_QualifiedCurve aQual3 = createQualifiedCircle(0.05, 0.08, 0.01);

  gp_Circ2d aInputCirc1 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(1, 0)), 0.01);
  gp_Circ2d aInputCirc2 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(0.1, 0.0), gp_Dir2d(1, 0)), 0.01);
  gp_Circ2d aInputCirc3 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(0.05, 0.08), gp_Dir2d(1, 0)), 0.01);

  Geom2dGcc_Circ2d3Tan aSolver(aQual1, aQual2, aQual3, myTolerance, 0, 0, 0);

  EXPECT_TRUE(aSolver.IsDone()) << "Small circles should be handled correctly";

  int aNbSol = aSolver.NbSolutions();
  EXPECT_GE(aNbSol, 1) << "Should find at least one solution for small circles";

  for (int i = 1; i <= aNbSol; i++)
  {
    gp_Circ2d aSol = aSolver.ThisSolution(i);
    verifySolutionValidity(aSol, i, -10.0, 10.0, -10.0, 10.0, 10.0);
    verifyTangencyConstraints(aSol, aInputCirc1, aInputCirc2, aInputCirc3, i, 1e-3);
  }
}

TEST_F(Geom2dGcc_Circ2d3TanTest, LargeCircles_ScalingTest)
{

  Geom2dGcc_QualifiedCurve aQual1 = createQualifiedCircle(0.0, 0.0, 1000.0);
  Geom2dGcc_QualifiedCurve aQual2 = createQualifiedCircle(5000.0, 0.0, 1500.0);
  Geom2dGcc_QualifiedCurve aQual3 = createQualifiedCircle(2500.0, 4000.0, 800.0);

  gp_Circ2d aInputCirc1 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(1, 0)), 1000.0);
  gp_Circ2d aInputCirc2 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(5000.0, 0.0), gp_Dir2d(1, 0)), 1500.0);
  gp_Circ2d aInputCirc3 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(2500.0, 4000.0), gp_Dir2d(1, 0)), 800.0);

  Geom2dGcc_Circ2d3Tan aSolver(aQual1, aQual2, aQual3, myTolerance, 0, 0, 0);

  EXPECT_TRUE(aSolver.IsDone()) << "Large circles should be handled correctly";

  int aNbSol = aSolver.NbSolutions();
  EXPECT_GE(aNbSol, 1) << "Should find at least one solution for large circles";

  for (int i = 1; i <= aNbSol; i++)
  {
    gp_Circ2d aSol = aSolver.ThisSolution(i);
    verifySolutionValidity(aSol, i, -10000.0, 10000.0, -10000.0, 10000.0, 50000.0);
    verifyTangencyConstraints(aSol, aInputCirc1, aInputCirc2, aInputCirc3, i, 1.0);
  }
}

TEST_F(Geom2dGcc_Circ2d3TanTest, LinearConfiguration_GeometricTest)
{

  Geom2dGcc_QualifiedCurve aQual1 = createQualifiedCircle(0.0, 0.0, 1.0);
  Geom2dGcc_QualifiedCurve aQual2 = createQualifiedCircle(5.0, 0.0, 1.5);
  Geom2dGcc_QualifiedCurve aQual3 = createQualifiedCircle(10.0, 0.0, 1.2);

  gp_Circ2d aInputCirc1 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(1, 0)), 1.0);
  gp_Circ2d aInputCirc2 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(5.0, 0.0), gp_Dir2d(1, 0)), 1.5);
  gp_Circ2d aInputCirc3 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(10.0, 0.0), gp_Dir2d(1, 0)), 1.2);

  Geom2dGcc_Circ2d3Tan aSolver(aQual1, aQual2, aQual3, myTolerance, 0, 0, 0);

  EXPECT_TRUE(aSolver.IsDone()) << "Linear configuration should be solvable";

  int aNbSol = aSolver.NbSolutions();
  EXPECT_GE(aNbSol, 1) << "Should find at least one solution for linear configuration";

  for (int i = 1; i <= aNbSol; i++)
  {
    gp_Circ2d aSol = aSolver.ThisSolution(i);
    verifySolutionValidity(aSol, i);
    verifyTangencyConstraints(aSol, aInputCirc1, aInputCirc2, aInputCirc3, i);
  }
}

TEST_F(Geom2dGcc_Circ2d3TanTest, TouchingCircles_DegenerateCase)
{

  Geom2dGcc_QualifiedCurve aQual1 = createQualifiedCircle(0.0, 0.0, 2.0);
  Geom2dGcc_QualifiedCurve aQual2 = createQualifiedCircle(4.0, 0.0, 2.0);
  Geom2dGcc_QualifiedCurve aQual3 = createQualifiedCircle(2.0, 5.0, 1.5);

  gp_Circ2d aInputCirc1 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(0.0, 0.0), gp_Dir2d(1, 0)), 2.0);
  gp_Circ2d aInputCirc2 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(4.0, 0.0), gp_Dir2d(1, 0)), 2.0);
  gp_Circ2d aInputCirc3 = gp_Circ2d(gp_Ax2d(gp_Pnt2d(2.0, 5.0), gp_Dir2d(1, 0)), 1.5);

  Geom2dGcc_Circ2d3Tan aSolver(aQual1, aQual2, aQual3, myTolerance, 0, 0, 0);

  EXPECT_TRUE(aSolver.IsDone()) << "Touching circles configuration should be solvable";

  int aNbSol = aSolver.NbSolutions();
  EXPECT_GE(aNbSol, 1) << "Should find at least one solution for touching circles case";

  for (int i = 1; i <= aNbSol; i++)
  {
    gp_Circ2d aSol = aSolver.ThisSolution(i);
    verifySolutionValidity(aSol, i);
    verifyTangencyConstraints(aSol, aInputCirc1, aInputCirc2, aInputCirc3, i);
  }
}
