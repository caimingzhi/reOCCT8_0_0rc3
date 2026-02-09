

#include <PLib_JacobiPolynomial.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <GeomAbs_Shape.hpp>
#include <Precision.hpp>

namespace
{

}

class PLibJacobiPolynomialTest : public ::testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(PLibJacobiPolynomialTest, ConstructorAndBasicProperties)
{

  PLib_JacobiPolynomial aJacC0(10, GeomAbs_C0);
  PLib_JacobiPolynomial aJacC1(15, GeomAbs_C1);
  PLib_JacobiPolynomial aJacC2(20, GeomAbs_C2);

  EXPECT_EQ(aJacC0.WorkDegree(), 10);
  EXPECT_EQ(aJacC1.WorkDegree(), 15);
  EXPECT_EQ(aJacC2.WorkDegree(), 20);

  EXPECT_EQ(aJacC0.NivConstr(), 0);
  EXPECT_EQ(aJacC1.NivConstr(), 1);
  EXPECT_EQ(aJacC2.NivConstr(), 2);
}

TEST_F(PLibJacobiPolynomialTest, ConstructorEdgeCases)
{

  PLib_JacobiPolynomial aJacMinC0(2, GeomAbs_C0);
  EXPECT_EQ(aJacMinC0.WorkDegree(), 2);

  PLib_JacobiPolynomial aJacMinC1(4, GeomAbs_C1);
  EXPECT_EQ(aJacMinC1.WorkDegree(), 4);

  PLib_JacobiPolynomial aJacMinC2(6, GeomAbs_C2);
  EXPECT_EQ(aJacMinC2.WorkDegree(), 6);

  PLib_JacobiPolynomial aJacMax(30, GeomAbs_C0);
  EXPECT_EQ(aJacMax.WorkDegree(), 30);

  PLib_JacobiPolynomial aJacHigh(25, GeomAbs_C0);
  EXPECT_GT(aJacHigh.WorkDegree(), 20) << "High degree should be supported";
}

TEST_F(PLibJacobiPolynomialTest, GaussIntegrationPoints)
{
  PLib_JacobiPolynomial aJac(10, GeomAbs_C0);

  std::vector<int> aGaussNumbers = {8, 10, 15, 20, 25, 30, 40, 50, 61};

  for (int aNbGauss : aGaussNumbers)
  {
    if (aNbGauss > aJac.WorkDegree())
    {
      NCollection_Array1<double> aPoints(0, aNbGauss / 2);

      EXPECT_NO_THROW({ aJac.Points(aNbGauss, aPoints); })
        << "Points calculation failed for " << aNbGauss << " Gauss points";

      for (int i = aPoints.Lower(); i <= aPoints.Upper(); i++)
      {
        if (i == 0 && aNbGauss % 2 == 0)
        {

          EXPECT_EQ(aPoints(i), -999) << "TabPoints(0) should be UNDEFINED for even NbGaussPoints";
        }
        else if (i == 0 && aNbGauss % 2 == 1)
        {

          EXPECT_EQ(aPoints(i), 0.0) << "TabPoints(0) should be 0 for odd NbGaussPoints";
        }
        else
        {

          EXPECT_GT(aPoints(i), 0.0) << "Gauss point should be positive";
          EXPECT_LE(aPoints(i), 1.0) << "Gauss point should be <= 1";

          if (i > aPoints.Lower() && i > 0)
          {
            EXPECT_GE(aPoints(i), aPoints(i - 1)) << "Gauss points should be ordered";
          }
        }
      }
    }
  }
}

TEST_F(PLibJacobiPolynomialTest, GaussIntegrationWeights)
{
  PLib_JacobiPolynomial aJac(8, GeomAbs_C1);

  int                        aNbGauss = 15;
  NCollection_Array2<double> aWeights(0, aNbGauss / 2, 0, aJac.WorkDegree());

  aJac.Weights(aNbGauss, aWeights);

  EXPECT_EQ(aWeights.LowerRow(), 0) << "Lower row should be 0";
  EXPECT_EQ(aWeights.UpperRow(), aNbGauss / 2) << "Upper row mismatch";
  EXPECT_EQ(aWeights.LowerCol(), 0) << "Lower col should be 0";
  EXPECT_EQ(aWeights.UpperCol(), aJac.WorkDegree()) << "Upper col should match work degree";

  for (int i = aWeights.LowerRow(); i <= aWeights.UpperRow(); i++)
  {
    for (int j = aWeights.LowerCol(); j <= aWeights.UpperCol(); j++)
    {
      EXPECT_FALSE(Precision::IsInfinite(aWeights(i, j)))
        << "Weight should be finite at (" << i << "," << j << ")";
    }
  }
}

TEST_F(PLibJacobiPolynomialTest, MaxValue)
{
  PLib_JacobiPolynomial aJac(10, GeomAbs_C0);

  int aTabSize = aJac.WorkDegree() - 2 * (aJac.NivConstr() + 1);
  if (aTabSize > 0)
  {
    NCollection_Array1<double> aTabMax(0, aTabSize);

    aJac.MaxValue(aTabMax);

    for (int i = aTabMax.Lower(); i <= aTabMax.Upper(); i++)
    {
      EXPECT_GT(aTabMax(i), 0.0) << "Max value should be positive at index " << i;
      EXPECT_FALSE(Precision::IsInfinite(aTabMax(i)))
        << "Max value should be finite at index " << i;
    }
  }
}

TEST_F(PLibJacobiPolynomialTest, BasisFunctionD0)
{
  PLib_JacobiPolynomial aJac(6, GeomAbs_C0);

  int aDegree = aJac.WorkDegree() - 2 * (aJac.NivConstr() + 1);

  NCollection_Array1<double> aBasisValue(0, aDegree);

  std::vector<double> aTestParams = {-1.0, -0.5, 0.0, 0.5, 1.0};

  for (double aU : aTestParams)
  {
    aJac.D0(aU, aBasisValue);

    for (int i = aBasisValue.Lower(); i <= aBasisValue.Upper(); i++)
    {
      EXPECT_FALSE(Precision::IsInfinite(aBasisValue(i)))
        << "Basis value should be finite at index " << i << ", U=" << aU;
    }
  }
}

TEST_F(PLibJacobiPolynomialTest, BasisFunctionDerivatives)
{
  PLib_JacobiPolynomial aJac(8, GeomAbs_C1);

  int aDegree = aJac.WorkDegree() - 2 * (aJac.NivConstr() + 1);

  NCollection_Array1<double> aBasisValue(0, aDegree);
  NCollection_Array1<double> aBasisD1(0, aDegree);
  NCollection_Array1<double> aBasisD2(0, aDegree);
  NCollection_Array1<double> aBasisD3(0, aDegree);

  double aU = 0.5;

  aJac.D1(aU, aBasisValue, aBasisD1);
  aJac.D2(aU, aBasisValue, aBasisD1, aBasisD2);
  aJac.D3(aU, aBasisValue, aBasisD1, aBasisD2, aBasisD3);

  for (int i = aBasisValue.Lower(); i <= aBasisValue.Upper(); i++)
  {
    EXPECT_FALSE(Precision::IsInfinite(aBasisValue(i))) << "Basis value should be finite at " << i;
    EXPECT_FALSE(Precision::IsInfinite(aBasisD1(i)))
      << "First derivative should be finite at " << i;
    EXPECT_FALSE(Precision::IsInfinite(aBasisD2(i)))
      << "Second derivative should be finite at " << i;
    EXPECT_FALSE(Precision::IsInfinite(aBasisD3(i)))
      << "Third derivative should be finite at " << i;
  }
}

TEST_F(PLibJacobiPolynomialTest, CoefficientConversion)
{
  const int             aWorkDegree = 6;
  PLib_JacobiPolynomial aJac(aWorkDegree, GeomAbs_C0);

  const int aDimension = 1;
  const int aDegree    = aJac.WorkDegree() - 2 * (aJac.NivConstr() + 1);

  int aJacSize   = (aDegree + 1) * aDimension;
  int aCoeffSize = (aDegree + 1) * aDimension;

  NCollection_Array1<double> aJacCoeff(0, aJacSize - 1);
  for (int i = aJacCoeff.Lower(); i <= aJacCoeff.Upper(); i++)
  {
    aJacCoeff(i) = std::sin(i * 0.1);
  }

  NCollection_Array1<double> aCoefficients(0, aCoeffSize - 1);

  aJac.ToCoefficients(aDimension, aDegree, aJacCoeff, aCoefficients);

  for (int i = aCoefficients.Lower(); i <= aCoefficients.Upper(); i++)
  {
    EXPECT_FALSE(Precision::IsInfinite(aCoefficients(i)))
      << "Converted coefficient should be finite at index " << i;
  }
}

TEST_F(PLibJacobiPolynomialTest, DegreeReduction)
{
  PLib_JacobiPolynomial aJac(10, GeomAbs_C0);

  const int    aDimension = 1;
  const int    aMaxDegree = 8;
  const double aTol       = 1e-6;

  const int                  aWorkDegree = aJac.WorkDegree();
  NCollection_Array1<double> aCoeff(1, (aWorkDegree + 1) * aDimension);
  for (int i = aCoeff.Lower(); i <= aCoeff.Upper(); i++)
  {
    aCoeff(i) = 1.0 / (i + 1);
  }

  int    aNewDegree = -1;
  double aMaxError  = -1.0;

  aJac.ReduceDegree(aDimension, aMaxDegree, aTol, aCoeff.ChangeValue(1), aNewDegree, aMaxError);

  EXPECT_LE(aNewDegree, aMaxDegree) << "New degree should not exceed max degree";
  EXPECT_GE(aNewDegree, 0) << "New degree should be non-negative";
  EXPECT_GE(aMaxError, 0.0) << "Max error should be non-negative";
  EXPECT_FALSE(Precision::IsInfinite(aMaxError)) << "Max error should be finite";
}

TEST_F(PLibJacobiPolynomialTest, ErrorEstimation)
{
  PLib_JacobiPolynomial aJac(8, GeomAbs_C1);

  const int aDimension = 1;

  NCollection_Array1<double> aCoeff(1, 10 * aDimension);
  for (int i = aCoeff.Lower(); i <= aCoeff.Upper(); i++)
  {
    aCoeff(i) = 1.0 / (i + 1);
  }

  int aNewDegree = 6;

  double aMaxErr = aJac.MaxError(aDimension, aCoeff.ChangeValue(1), aNewDegree);

  EXPECT_GE(aMaxErr, 0.0) << "Max error should be non-negative";
  EXPECT_FALSE(Precision::IsInfinite(aMaxErr)) << "Max error should be finite";

  double aAvgErr = aJac.AverageError(aDimension, aCoeff.ChangeValue(1), aNewDegree);

  EXPECT_GE(aAvgErr, 0.0) << "Average error should be non-negative";
  EXPECT_FALSE(Precision::IsInfinite(aAvgErr)) << "Average error should be finite";

  EXPECT_LE(aAvgErr, aMaxErr + Precision::Confusion())
    << "Average error should not exceed max error significantly";
}

TEST_F(PLibJacobiPolynomialTest, StressTests)
{

  PLib_JacobiPolynomial aJacMax(30, GeomAbs_C2);

  int aDegree = aJacMax.WorkDegree() - 2 * (aJacMax.NivConstr() + 1);

  NCollection_Array1<double> aBasisValue(0, aDegree);

  aJacMax.D0(0.0, aBasisValue);
  aJacMax.D0(0.5, aBasisValue);
  aJacMax.D0(1.0, aBasisValue);

  std::vector<double> aExtremeParams = {-0.99999, -1e-10, 1e-10, 0.99999};

  for (double aU : aExtremeParams)
  {
    aJacMax.D0(aU, aBasisValue);

    for (int i = aBasisValue.Lower(); i <= aBasisValue.Upper(); i++)
    {
      EXPECT_FALSE(Precision::IsInfinite(aBasisValue(i))) << "Basis value should be finite";
    }
  }
}
