

#include <PLib_HermitJacobi.hpp>
#include <PLib_JacobiPolynomial.hpp>

#include <gtest/gtest.h>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <GeomAbs_Shape.hpp>
#include <Precision.hpp>

class PLibHermitJacobiTest : public ::testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(PLibHermitJacobiTest, ConstructorAndBasicProperties)
{

  PLib_HermitJacobi aHermC0(10, GeomAbs_C0);
  PLib_HermitJacobi aHermC1(15, GeomAbs_C1);
  PLib_HermitJacobi aHermC2(20, GeomAbs_C2);

  EXPECT_EQ(aHermC0.WorkDegree(), 10);
  EXPECT_EQ(aHermC1.WorkDegree(), 15);
  EXPECT_EQ(aHermC2.WorkDegree(), 20);

  EXPECT_EQ(aHermC0.NivConstr(), 0);
  EXPECT_EQ(aHermC1.NivConstr(), 1);
  EXPECT_EQ(aHermC2.NivConstr(), 2);
}

TEST_F(PLibHermitJacobiTest, BasisFunctionD0)
{
  PLib_HermitJacobi aHerm(6, GeomAbs_C0);

  NCollection_Array1<double> aBasisValue(0, aHerm.WorkDegree());

  std::vector<double> aTestParams = {-1.0, -0.5, 0.0, 0.5, 1.0};

  for (double aU : aTestParams)
  {
    EXPECT_NO_THROW({ aHerm.D0(aU, aBasisValue); }) << "D0 evaluation failed at U=" << aU;

    for (int i = aBasisValue.Lower(); i <= aBasisValue.Upper(); i++)
    {
      EXPECT_FALSE(Precision::IsInfinite(aBasisValue(i)))
        << "Basis value should be finite at index " << i << ", U=" << aU;
    }
  }
}

TEST_F(PLibHermitJacobiTest, BasisFunctionDerivatives)
{
  PLib_HermitJacobi aHerm(8, GeomAbs_C1);

  NCollection_Array1<double> aBasisValue(0, aHerm.WorkDegree());
  NCollection_Array1<double> aBasisD1(0, aHerm.WorkDegree());
  NCollection_Array1<double> aBasisD2(0, aHerm.WorkDegree());
  NCollection_Array1<double> aBasisD3(0, aHerm.WorkDegree());

  double aU = 0.5;

  EXPECT_NO_THROW({ aHerm.D1(aU, aBasisValue, aBasisD1); }) << "D1 evaluation failed";

  EXPECT_NO_THROW({ aHerm.D2(aU, aBasisValue, aBasisD1, aBasisD2); }) << "D2 evaluation failed";

  EXPECT_NO_THROW({ aHerm.D3(aU, aBasisValue, aBasisD1, aBasisD2, aBasisD3); })
    << "D3 evaluation failed";

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

TEST_F(PLibHermitJacobiTest, CoefficientConversion)
{
  const int         aWorkDegree = 6;
  PLib_HermitJacobi aHerm(aWorkDegree, GeomAbs_C0);

  const int aDimension = 1;
  const int aDegree    = aHerm.WorkDegree() - 2 * (aHerm.NivConstr() + 1);

  int aHermJacSize = (aDegree + 1) * aDimension;
  int aCoeffSize   = (aDegree + 1) * aDimension;

  NCollection_Array1<double> aHermJacCoeff(0, aHermJacSize - 1);
  for (int i = aHermJacCoeff.Lower(); i <= aHermJacCoeff.Upper(); i++)
  {
    aHermJacCoeff(i) = std::sin(i * 0.3);
  }

  NCollection_Array1<double> aCoefficients(0, aCoeffSize - 1);

  EXPECT_NO_THROW({ aHerm.ToCoefficients(aDimension, aDegree, aHermJacCoeff, aCoefficients); })
    << "Coefficient conversion failed";

  for (int i = aCoefficients.Lower(); i <= aCoefficients.Upper(); i++)
  {
    EXPECT_FALSE(Precision::IsInfinite(aCoefficients(i)))
      << "Converted coefficient should be finite at index " << i;
  }
}

TEST_F(PLibHermitJacobiTest, DegreeReduction)
{
  PLib_HermitJacobi aHerm(10, GeomAbs_C0);

  const int    aDimension = 1;
  const int    aMaxDegree = 8;
  const double aTol       = 1e-6;

  const int                  aWorkDegree = aHerm.WorkDegree();
  NCollection_Array1<double> aCoeff(1, (aWorkDegree + 1) * aDimension);
  for (int i = aCoeff.Lower(); i <= aCoeff.Upper(); i++)
  {
    aCoeff(i) = 1.0 / (i + 1);
  }

  int    aNewDegree = -1;
  double aMaxError  = -1.0;

  EXPECT_NO_THROW({
    aHerm.ReduceDegree(aDimension, aMaxDegree, aTol, aCoeff.ChangeValue(1), aNewDegree, aMaxError);
  }) << "Degree reduction failed";

  EXPECT_LE(aNewDegree, aMaxDegree) << "New degree should not exceed max degree";
  EXPECT_GE(aNewDegree, 0) << "New degree should be non-negative";
  EXPECT_GE(aMaxError, 0.0) << "Max error should be non-negative";
  EXPECT_FALSE(Precision::IsInfinite(aMaxError)) << "Max error should be finite";
}

TEST_F(PLibHermitJacobiTest, ErrorEstimation)
{
  PLib_HermitJacobi aHerm(8, GeomAbs_C1);

  const int aDimension = 1;

  NCollection_Array1<double> aCoeff(1, 10 * aDimension);
  for (int i = aCoeff.Lower(); i <= aCoeff.Upper(); i++)
  {
    aCoeff(i) = 1.0 / (i + 1);
  }

  int aNewDegree = 6;

  double aMaxErr = -1.0;
  EXPECT_NO_THROW({ aMaxErr = aHerm.MaxError(aDimension, aCoeff.ChangeValue(1), aNewDegree); })
    << "MaxError calculation failed";

  EXPECT_GE(aMaxErr, 0.0) << "Max error should be non-negative";
  EXPECT_FALSE(Precision::IsInfinite(aMaxErr)) << "Max error should be finite";

  double aAvgErr = -1.0;
  EXPECT_NO_THROW({ aAvgErr = aHerm.AverageError(aDimension, aCoeff.ChangeValue(1), aNewDegree); })
    << "AverageError calculation failed";

  EXPECT_GE(aAvgErr, 0.0) << "Average error should be non-negative";
  EXPECT_FALSE(Precision::IsInfinite(aAvgErr)) << "Average error should be finite";

  EXPECT_LE(aAvgErr, aMaxErr + Precision::Confusion())
    << "Average error should not exceed max error significantly";
}

TEST_F(PLibHermitJacobiTest, ExtremeParameterValues)
{
  PLib_HermitJacobi aHerm(10, GeomAbs_C2);

  NCollection_Array1<double> aBasisValue(0, aHerm.WorkDegree());

  std::vector<double> aExtremeParams = {-0.99999, -1e-12, 1e-12, 0.99999};

  for (double aU : aExtremeParams)
  {
    EXPECT_NO_THROW({ aHerm.D0(aU, aBasisValue); })
      << "Extreme parameter U=" << aU << " should not crash";

    for (int i = aBasisValue.Lower(); i <= aBasisValue.Upper(); i++)
    {
      EXPECT_FALSE(Precision::IsInfinite(aBasisValue(i)))
        << "Basis value should be finite at extreme parameter U=" << aU;
    }
  }
}

TEST_F(PLibHermitJacobiTest, DerivativeConsistency)
{
  PLib_HermitJacobi aHerm(6, GeomAbs_C2);

  NCollection_Array1<double> aBasisValue1(0, aHerm.WorkDegree());
  NCollection_Array1<double> aBasisD1_1(0, aHerm.WorkDegree());

  NCollection_Array1<double> aBasisValue2(0, aHerm.WorkDegree());
  NCollection_Array1<double> aBasisD1_2(0, aHerm.WorkDegree());
  NCollection_Array1<double> aBasisD2_2(0, aHerm.WorkDegree());

  double aU = 0.3;

  aHerm.D1(aU, aBasisValue1, aBasisD1_1);
  aHerm.D2(aU, aBasisValue2, aBasisD1_2, aBasisD2_2);

  for (int i = aBasisValue1.Lower(); i <= aBasisValue1.Upper(); i++)
  {
    EXPECT_NEAR(aBasisValue1(i), aBasisValue2(i), Precision::Confusion())
      << "Function values should be consistent between D1 and D2 calls at index " << i;
    EXPECT_NEAR(aBasisD1_1(i), aBasisD1_2(i), Precision::Confusion())
      << "First derivatives should be consistent between D1 and D2 calls at index " << i;
  }
}

TEST_F(PLibHermitJacobiTest, PerformanceTest)
{
  PLib_HermitJacobi aHermMax(30, GeomAbs_C2);

  NCollection_Array1<double> aBasisValue(0, aHermMax.WorkDegree());
  NCollection_Array1<double> aBasisD1(0, aHermMax.WorkDegree());
  NCollection_Array1<double> aBasisD2(0, aHermMax.WorkDegree());
  NCollection_Array1<double> aBasisD3(0, aHermMax.WorkDegree());

  std::vector<double> aTestParams = {-0.8, -0.5, 0.0, 0.5, 0.8};

  for (double aU : aTestParams)
  {
    EXPECT_NO_THROW({
      aHermMax.D0(aU, aBasisValue);
      aHermMax.D1(aU, aBasisValue, aBasisD1);
      aHermMax.D2(aU, aBasisValue, aBasisD1, aBasisD2);
      aHermMax.D3(aU, aBasisValue, aBasisD1, aBasisD2, aBasisD3);
    }) << "High degree operations should complete without crashing at U="
       << aU;
  }
}
