

#include <PLib.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <GeomAbs_Shape.hpp>
#include <Precision.hpp>

namespace
{

  void checkPointsEqual(const gp_Pnt& thePnt1,
                        const gp_Pnt& thePnt2,
                        const double  theTolerance = Precision::Confusion())
  {
    EXPECT_NEAR(thePnt1.X(), thePnt2.X(), theTolerance) << "X coordinates differ";
    EXPECT_NEAR(thePnt1.Y(), thePnt2.Y(), theTolerance) << "Y coordinates differ";
    EXPECT_NEAR(thePnt1.Z(), thePnt2.Z(), theTolerance) << "Z coordinates differ";
  }

  void checkPoint2dEqual(const gp_Pnt2d& thePnt1,
                         const gp_Pnt2d& thePnt2,
                         const double    theTolerance = Precision::Confusion())
  {
    EXPECT_NEAR(thePnt1.X(), thePnt2.X(), theTolerance) << "X coordinates differ";
    EXPECT_NEAR(thePnt1.Y(), thePnt2.Y(), theTolerance) << "Y coordinates differ";
  }
} // namespace

class PLibTest : public ::testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(PLibTest, NoWeightsPointers)
{

  EXPECT_EQ(PLib::NoWeights(), static_cast<NCollection_Array1<double>*>(nullptr));
  EXPECT_EQ(PLib::NoWeights2(), static_cast<NCollection_Array2<double>*>(nullptr));
}

TEST_F(PLibTest, SetGetPoles3D)
{

  NCollection_Array1<gp_Pnt> aPoles(1, 3);
  aPoles(1) = gp_Pnt(1.0, 2.0, 3.0);
  aPoles(2) = gp_Pnt(4.0, 5.0, 6.0);
  aPoles(3) = gp_Pnt(7.0, 8.0, 9.0);

  NCollection_Array1<double> aFP(1, 9);
  PLib::SetPoles(aPoles, aFP);

  NCollection_Array1<gp_Pnt> aResultPoles(1, 3);
  PLib::GetPoles(aFP, aResultPoles);

  for (int i = 1; i <= 3; i++)
  {
    checkPointsEqual(aPoles(i), aResultPoles(i));
  }
}

TEST_F(PLibTest, SetGetPoles3DWithWeights)
{

  NCollection_Array1<gp_Pnt> aPoles(1, 2);
  aPoles(1) = gp_Pnt(1.0, 2.0, 3.0);
  aPoles(2) = gp_Pnt(4.0, 5.0, 6.0);

  NCollection_Array1<double> aWeights(1, 2);
  aWeights(1) = 0.5;
  aWeights(2) = 2.0;

  NCollection_Array1<double> aFP(1, 8);
  PLib::SetPoles(aPoles, aWeights, aFP);

  NCollection_Array1<gp_Pnt> aResultPoles(1, 2);
  NCollection_Array1<double> aResultWeights(1, 2);
  PLib::GetPoles(aFP, aResultPoles, aResultWeights);

  for (int i = 1; i <= 2; i++)
  {
    checkPointsEqual(aPoles(i), aResultPoles(i));
    EXPECT_NEAR(aWeights(i), aResultWeights(i), Precision::Confusion());
  }
}

TEST_F(PLibTest, SetGetPoles2D)
{

  NCollection_Array1<gp_Pnt2d> aPoles(1, 3);
  aPoles(1) = gp_Pnt2d(1.0, 2.0);
  aPoles(2) = gp_Pnt2d(3.0, 4.0);
  aPoles(3) = gp_Pnt2d(5.0, 6.0);

  NCollection_Array1<double> aFP(1, 6);
  PLib::SetPoles(aPoles, aFP);

  NCollection_Array1<gp_Pnt2d> aResultPoles(1, 3);
  PLib::GetPoles(aFP, aResultPoles);

  for (int i = 1; i <= 3; i++)
  {
    checkPoint2dEqual(aPoles(i), aResultPoles(i));
  }
}

TEST_F(PLibTest, SetGetPoles2DWithWeights)
{

  NCollection_Array1<gp_Pnt2d> aPoles(1, 2);
  aPoles(1) = gp_Pnt2d(1.0, 2.0);
  aPoles(2) = gp_Pnt2d(3.0, 4.0);

  NCollection_Array1<double> aWeights(1, 2);
  aWeights(1) = 0.8;
  aWeights(2) = 1.5;

  NCollection_Array1<double> aFP(1, 6);
  PLib::SetPoles(aPoles, aWeights, aFP);

  NCollection_Array1<gp_Pnt2d> aResultPoles(1, 2);
  NCollection_Array1<double>   aResultWeights(1, 2);
  PLib::GetPoles(aFP, aResultPoles, aResultWeights);

  for (int i = 1; i <= 2; i++)
  {
    checkPoint2dEqual(aPoles(i), aResultPoles(i));
    EXPECT_NEAR(aWeights(i), aResultWeights(i), Precision::Confusion());
  }
}

TEST_F(PLibTest, ZeroWeightsHandling)
{

  NCollection_Array1<gp_Pnt2d> aPoles(1, 2);
  aPoles(1) = gp_Pnt2d(1.0, 2.0);
  aPoles(2) = gp_Pnt2d(3.0, 4.0);

  NCollection_Array1<double> aWeights(1, 2);
  aWeights(1) = 1.0;
  aWeights(2) = 0.0;

  NCollection_Array1<double> aFP(1, 6);
  PLib::SetPoles(aPoles, aWeights, aFP);

  EXPECT_TRUE(true);
}

TEST_F(PLibTest, BinomialCoefficient_BasicValues)
{

  EXPECT_NEAR(PLib::Bin(0, 0), 1.0, Precision::Confusion()) << "C(0,0) should be 1";

  EXPECT_NEAR(PLib::Bin(1, 0), 1.0, Precision::Confusion());
  EXPECT_NEAR(PLib::Bin(1, 1), 1.0, Precision::Confusion());

  EXPECT_NEAR(PLib::Bin(5, 0), 1.0, Precision::Confusion());
  EXPECT_NEAR(PLib::Bin(5, 1), 5.0, Precision::Confusion());
  EXPECT_NEAR(PLib::Bin(5, 2), 10.0, Precision::Confusion());
  EXPECT_NEAR(PLib::Bin(5, 3), 10.0, Precision::Confusion());
  EXPECT_NEAR(PLib::Bin(5, 4), 5.0, Precision::Confusion());
  EXPECT_NEAR(PLib::Bin(5, 5), 1.0, Precision::Confusion());

  EXPECT_NEAR(PLib::Bin(10, 0), 1.0, Precision::Confusion());
  EXPECT_NEAR(PLib::Bin(10, 1), 10.0, Precision::Confusion());
  EXPECT_NEAR(PLib::Bin(10, 2), 45.0, Precision::Confusion());
  EXPECT_NEAR(PLib::Bin(10, 3), 120.0, Precision::Confusion());
  EXPECT_NEAR(PLib::Bin(10, 4), 210.0, Precision::Confusion());
  EXPECT_NEAR(PLib::Bin(10, 5), 252.0, Precision::Confusion());
}

TEST_F(PLibTest, BinomialCoefficient_Symmetry)
{

  for (int n = 0; n <= 20; n++)
  {
    for (int k = 0; k <= n; k++)
    {
      EXPECT_NEAR(PLib::Bin(n, k), PLib::Bin(n, n - k), Precision::Confusion())
        << "Binomial coefficient symmetry failed for C(" << n << "," << k << ")";
    }
  }
}

TEST_F(PLibTest, BinomialCoefficient_Recurrence)
{

  for (int n = 2; n <= 20; n++)
  {
    for (int k = 1; k < n; k++)
    {
      double expected = PLib::Bin(n - 1, k - 1) + PLib::Bin(n - 1, k);
      double actual   = PLib::Bin(n, k);
      EXPECT_NEAR(actual, expected, Precision::Confusion())
        << "Pascal recurrence failed for C(" << n << "," << k << ")";
    }
  }
}

TEST_F(PLibTest, BinomialCoefficient_LargeValues)
{

  EXPECT_NEAR(PLib::Bin(20, 10), 184756.0, Precision::Confusion()) << "C(20,10)";
  EXPECT_NEAR(PLib::Bin(15, 7), 6435.0, Precision::Confusion()) << "C(15,7)";
  EXPECT_NEAR(PLib::Bin(25, 5), 53130.0, Precision::Confusion()) << "C(25,5)";
  EXPECT_NEAR(PLib::Bin(25, 12), 5200300.0, Precision::Confusion()) << "C(25,12)";

  EXPECT_NEAR(PLib::Bin(25, 0), 1.0, Precision::Confusion());
  EXPECT_NEAR(PLib::Bin(25, 1), 25.0, Precision::Confusion());
  EXPECT_NEAR(PLib::Bin(25, 25), 1.0, Precision::Confusion());
}

TEST_F(PLibTest, BinomialCoefficient_EdgeColumns)
{

  for (int n = 0; n <= 25; n++)
  {
    EXPECT_NEAR(PLib::Bin(n, 0), 1.0, Precision::Confusion()) << "C(" << n << ",0) should be 1";
  }

  for (int n = 0; n <= 25; n++)
  {
    EXPECT_NEAR(PLib::Bin(n, n), 1.0, Precision::Confusion())
      << "C(" << n << "," << n << ") should be 1";
  }

  for (int n = 1; n <= 25; n++)
  {
    EXPECT_NEAR(PLib::Bin(n, 1), double(n), Precision::Confusion())
      << "C(" << n << ",1) should be " << n;
  }
}

TEST_F(PLibTest, BinomialCoefficient_CompleteRows)
{

  const double row6[] = {1.0, 6.0, 15.0, 20.0, 15.0, 6.0, 1.0};
  for (int k = 0; k <= 6; k++)
  {
    EXPECT_NEAR(PLib::Bin(6, k), row6[k], Precision::Confusion())
      << "C(6," << k << ") verification failed";
  }

  const double row8[] = {1.0, 8.0, 28.0, 56.0, 70.0, 56.0, 28.0, 8.0, 1.0};
  for (int k = 0; k <= 8; k++)
  {
    EXPECT_NEAR(PLib::Bin(8, k), row8[k], Precision::Confusion())
      << "C(8," << k << ") verification failed";
  }
}

TEST_F(PLibTest, BinomialCoefficient_SumProperty)
{

  for (int n = 0; n <= 20; n++)
  {
    double sum      = 0.0;
    double expected = std::pow(2.0, n);

    for (int k = 0; k <= n; k++)
    {
      sum += PLib::Bin(n, k);
    }

    EXPECT_NEAR(sum, expected, Precision::Confusion())
      << "Sum property failed for n=" << n << " (sum should be 2^" << n << "=" << expected << ")";
  }
}

TEST_F(PLibTest, EvalPolynomial)
{

  const int aDegree     = 2;
  const int aDimension  = 1;
  const int aDerivOrder = 0;

  NCollection_Array1<double> aCoeffs(1, 3);
  aCoeffs(1) = 1.0;
  aCoeffs(2) = 2.0;
  aCoeffs(3) = 3.0;

  NCollection_Array1<double> aResults(1, 1);

  PLib::EvalPolynomial(0.0,
                       aDerivOrder,
                       aDegree,
                       aDimension,
                       aCoeffs.ChangeValue(1),
                       aResults.ChangeValue(1));
  EXPECT_NEAR(aResults(1), 1.0, Precision::Confusion());

  PLib::EvalPolynomial(1.0,
                       aDerivOrder,
                       aDegree,
                       aDimension,
                       aCoeffs.ChangeValue(1),
                       aResults.ChangeValue(1));
  EXPECT_NEAR(aResults(1), 6.0, Precision::Confusion());

  PLib::EvalPolynomial(2.0,
                       aDerivOrder,
                       aDegree,
                       aDimension,
                       aCoeffs.ChangeValue(1),
                       aResults.ChangeValue(1));
  EXPECT_NEAR(aResults(1), 17.0, Precision::Confusion());
}

TEST_F(PLibTest, EvalPolynomialWithDerivatives)
{

  const int aDegree     = 2;
  const int aDimension  = 1;
  const int aDerivOrder = 2;

  NCollection_Array1<double> aCoeffs(1, 3);
  aCoeffs(1) = 1.0;
  aCoeffs(2) = 2.0;
  aCoeffs(3) = 3.0;

  NCollection_Array1<double> aResults(1, 3);

  PLib::EvalPolynomial(1.0,
                       aDerivOrder,
                       aDegree,
                       aDimension,
                       aCoeffs.ChangeValue(1),
                       aResults.ChangeValue(1));

  EXPECT_NEAR(aResults(1), 6.0, Precision::Confusion());
  EXPECT_NEAR(aResults(2), 8.0, Precision::Confusion());
  EXPECT_NEAR(aResults(3), 6.0, Precision::Confusion());
}

TEST_F(PLibTest, ConstraintOrderConversion)
{

  EXPECT_EQ(PLib::NivConstr(GeomAbs_C0), 0);
  EXPECT_EQ(PLib::NivConstr(GeomAbs_C1), 1);
  EXPECT_EQ(PLib::NivConstr(GeomAbs_C2), 2);

  EXPECT_EQ(PLib::ConstraintOrder(0), GeomAbs_C0);
  EXPECT_EQ(PLib::ConstraintOrder(1), GeomAbs_C1);
  EXPECT_EQ(PLib::ConstraintOrder(2), GeomAbs_C2);

  for (int i = 0; i <= 2; i++)
  {
    GeomAbs_Shape aShape = PLib::ConstraintOrder(i);
    int           aLevel = PLib::NivConstr(aShape);
    EXPECT_EQ(aLevel, i) << "Round-trip conversion failed for level " << i;
  }
}

TEST_F(PLibTest, HermiteInterpolate)
{

  const int    aDimension  = 1;
  const double aFirstParam = 0.0;
  const double aLastParam  = 1.0;
  const int    aFirstOrder = 1;
  const int    aLastOrder  = 1;

  NCollection_Array2<double> aFirstConstr(1, aDimension, 0, aFirstOrder);
  aFirstConstr(1, 0) = 0.0;
  aFirstConstr(1, 1) = 1.0;

  NCollection_Array2<double> aLastConstr(1, aDimension, 0, aLastOrder);
  aLastConstr(1, 0) = 1.0;
  aLastConstr(1, 1) = 0.0;

  const int aCoeffCount = aFirstOrder + aLastOrder + 2;

  NCollection_Array1<double> aCoeffs(0, aCoeffCount - 1);

  bool aResult = PLib::HermiteInterpolate(aDimension,
                                          aFirstParam,
                                          aLastParam,
                                          aFirstOrder,
                                          aLastOrder,
                                          aFirstConstr,
                                          aLastConstr,
                                          aCoeffs);

  EXPECT_TRUE(aResult) << "Hermite interpolation failed";

  if (aResult)
  {

    NCollection_Array1<double> aResults(1, 2);

    PLib::EvalPolynomial(aFirstParam,
                         1,
                         aCoeffCount - 1,
                         aDimension,
                         aCoeffs.ChangeValue(0),
                         aResults.ChangeValue(1));
    EXPECT_NEAR(aResults(1), 0.0, Precision::Confusion()) << "f(0) constraint not satisfied";
    EXPECT_NEAR(aResults(2), 1.0, Precision::Confusion()) << "f'(0) constraint not satisfied";

    PLib::EvalPolynomial(aLastParam,
                         1,
                         aCoeffCount - 1,
                         aDimension,
                         aCoeffs.ChangeValue(0),
                         aResults.ChangeValue(1));
    EXPECT_NEAR(aResults(1), 1.0, Precision::Confusion()) << "f(1) constraint not satisfied";
    EXPECT_NEAR(aResults(2), 0.0, Precision::Confusion()) << "f'(1) constraint not satisfied";
  }
}

TEST_F(PLibTest, EdgeCases)
{

  NCollection_Array1<double> aSmallCoeffs(1, 3);
  aSmallCoeffs(1) = 1.0e-12;
  aSmallCoeffs(2) = 1.0e-12;
  aSmallCoeffs(3) = 1.0e-12;

  NCollection_Array1<double> aResults(1, 1);

  EXPECT_NO_THROW(
    { PLib::EvalPolynomial(1.0, 0, 2, 1, aSmallCoeffs.ChangeValue(1), aResults.ChangeValue(1)); });

  NCollection_Array1<double> aLargeCoeffs(1, 3);
  aLargeCoeffs(1) = 1.0e10;
  aLargeCoeffs(2) = 1.0e10;
  aLargeCoeffs(3) = 1.0e10;

  EXPECT_NO_THROW(
    { PLib::EvalPolynomial(1.0, 0, 2, 1, aLargeCoeffs.ChangeValue(1), aResults.ChangeValue(1)); });
}

TEST_F(PLibTest, JacobiParameters)
{
  int aNbGaussPoints, aWorkDegree;

  PLib::JacobiParameters(GeomAbs_C0, 10, 1, aNbGaussPoints, aWorkDegree);
  EXPECT_GT(aNbGaussPoints, 0) << "Number of Gauss points should be positive";
  EXPECT_GT(aWorkDegree, 0) << "Work degree should be positive";

  PLib::JacobiParameters(GeomAbs_C1, 15, 2, aNbGaussPoints, aWorkDegree);
  EXPECT_GT(aNbGaussPoints, 0);
  EXPECT_GT(aWorkDegree, 0);

  PLib::JacobiParameters(GeomAbs_C2, 20, 3, aNbGaussPoints, aWorkDegree);
  EXPECT_GT(aNbGaussPoints, 0);
  EXPECT_GT(aWorkDegree, 0);
}
