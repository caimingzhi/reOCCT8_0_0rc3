

#include <gtest/gtest.h>

#include <CSLib.hpp>
#include <CSLib_Class2d.hpp>
#include <CSLib_DerivativeStatus.hpp>
#include <CSLib_NormalPolyDef.hpp>
#include <CSLib_NormalStatus.hpp>

#include <gp.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_Sequence.hpp>

#include <cmath>

namespace
{

  void checkDirEqual(const gp_Dir& theDir1,
                     const gp_Dir& theDir2,
                     const double  theTolerance = 1e-10)
  {
    EXPECT_NEAR(theDir1.X(), theDir2.X(), theTolerance) << "X components differ";
    EXPECT_NEAR(theDir1.Y(), theDir2.Y(), theTolerance) << "Y components differ";
    EXPECT_NEAR(theDir1.Z(), theDir2.Z(), theTolerance) << "Z components differ";
  }

  void checkVecEqual(const gp_Vec& theVec1,
                     const gp_Vec& theVec2,
                     const double  theTolerance = 1e-10)
  {
    EXPECT_NEAR(theVec1.X(), theVec2.X(), theTolerance) << "X components differ";
    EXPECT_NEAR(theVec1.Y(), theVec2.Y(), theTolerance) << "Y components differ";
    EXPECT_NEAR(theVec1.Z(), theVec2.Z(), theTolerance) << "Z components differ";
  }
} // namespace

class CSLibNormalTest : public ::testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(CSLibNormalTest, Normal_FromD1U_D1V_OrthogonalVectors)
{

  const gp_Vec aD1U(1.0, 0.0, 0.0);
  const gp_Vec aD1V(0.0, 1.0, 0.0);

  CSLib_DerivativeStatus aStatus;
  gp_Dir                 aNormal;

  CSLib::Normal(aD1U, aD1V, 1e-10, aStatus, aNormal);

  EXPECT_EQ(aStatus, CSLib_Done);
  checkDirEqual(aNormal, gp_Dir(0.0, 0.0, 1.0));
}

TEST_F(CSLibNormalTest, Normal_FromD1U_D1V_ScaledVectors)
{

  const gp_Vec aD1U(3.0, 0.0, 0.0);
  const gp_Vec aD1V(0.0, 5.0, 0.0);

  CSLib_DerivativeStatus aStatus;
  gp_Dir                 aNormal;

  CSLib::Normal(aD1U, aD1V, 1e-10, aStatus, aNormal);

  EXPECT_EQ(aStatus, CSLib_Done);
  checkDirEqual(aNormal, gp_Dir(0.0, 0.0, 1.0));
}

TEST_F(CSLibNormalTest, Normal_FromD1U_D1V_ParallelVectors)
{

  const gp_Vec aD1U(1.0, 0.0, 0.0);
  const gp_Vec aD1V(2.0, 0.0, 0.0);

  CSLib_DerivativeStatus aStatus;
  gp_Dir                 aNormal;

  CSLib::Normal(aD1U, aD1V, 1e-6, aStatus, aNormal);

  EXPECT_EQ(aStatus, CSLib_D1uIsParallelD1v);
}

TEST_F(CSLibNormalTest, Normal_FromD1U_D1V_D1UIsNull)
{
  const gp_Vec aD1U(0.0, 0.0, 0.0);
  const gp_Vec aD1V(0.0, 1.0, 0.0);

  CSLib_DerivativeStatus aStatus;
  gp_Dir                 aNormal;

  CSLib::Normal(aD1U, aD1V, 1e-10, aStatus, aNormal);

  EXPECT_EQ(aStatus, CSLib_D1uIsNull);
}

TEST_F(CSLibNormalTest, Normal_FromD1U_D1V_D1VIsNull)
{
  const gp_Vec aD1U(1.0, 0.0, 0.0);
  const gp_Vec aD1V(0.0, 0.0, 0.0);

  CSLib_DerivativeStatus aStatus;
  gp_Dir                 aNormal;

  CSLib::Normal(aD1U, aD1V, 1e-10, aStatus, aNormal);

  EXPECT_EQ(aStatus, CSLib_D1vIsNull);
}

TEST_F(CSLibNormalTest, Normal_FromD1U_D1V_BothNull)
{
  const gp_Vec aD1U(0.0, 0.0, 0.0);
  const gp_Vec aD1V(0.0, 0.0, 0.0);

  CSLib_DerivativeStatus aStatus;
  gp_Dir                 aNormal;

  CSLib::Normal(aD1U, aD1V, 1e-10, aStatus, aNormal);

  EXPECT_EQ(aStatus, CSLib_D1IsNull);
}

TEST_F(CSLibNormalTest, Normal_WithMagTol_Defined)
{
  const gp_Vec aD1U(1.0, 0.0, 0.0);
  const gp_Vec aD1V(0.0, 1.0, 0.0);

  CSLib_NormalStatus aStatus;
  gp_Dir             aNormal;

  CSLib::Normal(aD1U, aD1V, 1e-10, aStatus, aNormal);

  EXPECT_EQ(aStatus, CSLib_Defined);
  checkDirEqual(aNormal, gp_Dir(0.0, 0.0, 1.0));
}

TEST_F(CSLibNormalTest, Normal_WithMagTol_Singular)
{

  const gp_Vec aD1U(1e-12, 0.0, 0.0);
  const gp_Vec aD1V(0.0, 1e-12, 0.0);

  CSLib_NormalStatus aStatus;
  gp_Dir             aNormal;

  CSLib::Normal(aD1U, aD1V, 1e-10, aStatus, aNormal);

  EXPECT_EQ(aStatus, CSLib_Singular);
}

TEST_F(CSLibNormalTest, DNNUV_ZeroDerivative)
{

  NCollection_Array2<gp_Vec> aDerSurf(0, 2, 0, 2);

  aDerSurf.SetValue(1, 0, gp_Vec(1.0, 0.0, 0.0));
  aDerSurf.SetValue(0, 1, gp_Vec(0.0, 1.0, 0.0));
  aDerSurf.SetValue(0, 0, gp_Vec(0.0, 0.0, 0.0));
  aDerSurf.SetValue(1, 1, gp_Vec(0.0, 0.0, 0.0));
  aDerSurf.SetValue(2, 0, gp_Vec(0.0, 0.0, 0.0));
  aDerSurf.SetValue(0, 2, gp_Vec(0.0, 0.0, 0.0));

  gp_Vec aResult = CSLib::DNNUV(0, 0, aDerSurf);

  checkVecEqual(aResult, gp_Vec(0.0, 0.0, 1.0));
}

class CSLibClass2dTest : public ::testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(CSLibClass2dTest, SiDans_PointInsideSquare)
{
  NCollection_Array1<gp_Pnt2d> aPnts(1, 4);
  aPnts(1) = gp_Pnt2d(0.0, 0.0);
  aPnts(2) = gp_Pnt2d(1.0, 0.0);
  aPnts(3) = gp_Pnt2d(1.0, 1.0);
  aPnts(4) = gp_Pnt2d(0.0, 1.0);

  CSLib_Class2d aClassifier(aPnts, 1e-10, 1e-10, 0.0, 0.0, 1.0, 1.0);

  const gp_Pnt2d aPointInside(0.5, 0.5);
  EXPECT_EQ(aClassifier.SiDans(aPointInside), 1);
}

TEST_F(CSLibClass2dTest, SiDans_PointOutsideSquare)
{
  NCollection_Array1<gp_Pnt2d> aPnts(1, 4);
  aPnts(1) = gp_Pnt2d(0.0, 0.0);
  aPnts(2) = gp_Pnt2d(1.0, 0.0);
  aPnts(3) = gp_Pnt2d(1.0, 1.0);
  aPnts(4) = gp_Pnt2d(0.0, 1.0);

  CSLib_Class2d aClassifier(aPnts, 1e-10, 1e-10, 0.0, 0.0, 1.0, 1.0);

  const gp_Pnt2d aPointOutside(2.0, 2.0);
  EXPECT_EQ(aClassifier.SiDans(aPointOutside), -1);
}

TEST_F(CSLibClass2dTest, SiDans_PointOnBoundary)
{
  NCollection_Array1<gp_Pnt2d> aPnts(1, 4);
  aPnts(1) = gp_Pnt2d(0.0, 0.0);
  aPnts(2) = gp_Pnt2d(1.0, 0.0);
  aPnts(3) = gp_Pnt2d(1.0, 1.0);
  aPnts(4) = gp_Pnt2d(0.0, 1.0);

  CSLib_Class2d aClassifier(aPnts, 0.01, 0.01, 0.0, 0.0, 1.0, 1.0);

  const gp_Pnt2d aPointOnEdge(0.5, 0.0);

  EXPECT_EQ(aClassifier.SiDans(aPointOnEdge), 0);
}

TEST_F(CSLibClass2dTest, SiDans_TriangularPolygon)
{
  NCollection_Array1<gp_Pnt2d> aPnts(1, 3);
  aPnts(1) = gp_Pnt2d(0.0, 0.0);
  aPnts(2) = gp_Pnt2d(2.0, 0.0);
  aPnts(3) = gp_Pnt2d(1.0, 2.0);

  CSLib_Class2d aClassifier(aPnts, 1e-10, 1e-10, 0.0, 0.0, 2.0, 2.0);

  const gp_Pnt2d aPointInside(1.0, 0.5);
  EXPECT_EQ(aClassifier.SiDans(aPointInside), 1);

  const gp_Pnt2d aPointOutside(0.0, 1.0);
  EXPECT_EQ(aClassifier.SiDans(aPointOutside), -1);
}

TEST_F(CSLibClass2dTest, SequenceConstructor_PointInsideSquare)
{
  NCollection_Sequence<gp_Pnt2d> aPnts;
  aPnts.Append(gp_Pnt2d(0.0, 0.0));
  aPnts.Append(gp_Pnt2d(1.0, 0.0));
  aPnts.Append(gp_Pnt2d(1.0, 1.0));
  aPnts.Append(gp_Pnt2d(0.0, 1.0));

  CSLib_Class2d aClassifier(aPnts, 1e-10, 1e-10, 0.0, 0.0, 1.0, 1.0);

  const gp_Pnt2d aPointInside(0.5, 0.5);
  EXPECT_EQ(aClassifier.SiDans(aPointInside), 1);
}

TEST_F(CSLibClass2dTest, InternalSiDans_NormalizedCoordinates)
{
  NCollection_Array1<gp_Pnt2d> aPnts(1, 4);
  aPnts(1) = gp_Pnt2d(0.0, 0.0);
  aPnts(2) = gp_Pnt2d(10.0, 0.0);
  aPnts(3) = gp_Pnt2d(10.0, 10.0);
  aPnts(4) = gp_Pnt2d(0.0, 10.0);

  CSLib_Class2d aClassifier(aPnts, 0.1, 0.1, 0.0, 0.0, 10.0, 10.0);

  EXPECT_EQ(aClassifier.SiDans(gp_Pnt2d(5.0, 5.0)), CSLib_Class2d::Result_Inside);
  EXPECT_EQ(aClassifier.SiDans(gp_Pnt2d(15.0, 15.0)), CSLib_Class2d::Result_Outside);
}

TEST_F(CSLibClass2dTest, SiDans_OnMode_PointInside)
{
  NCollection_Array1<gp_Pnt2d> aPnts(1, 4);
  aPnts(1) = gp_Pnt2d(0.0, 0.0);
  aPnts(2) = gp_Pnt2d(1.0, 0.0);
  aPnts(3) = gp_Pnt2d(1.0, 1.0);
  aPnts(4) = gp_Pnt2d(0.0, 1.0);

  CSLib_Class2d aClassifier(aPnts, 1e-10, 1e-10, 0.0, 0.0, 1.0, 1.0);

  const gp_Pnt2d aPointInside(0.5, 0.5);
  EXPECT_EQ(aClassifier.SiDans_OnMode(aPointInside, 0.01), 1);
}

TEST_F(CSLibClass2dTest, DegeneratePolygon_InvalidBounds)
{
  NCollection_Array1<gp_Pnt2d> aPnts(1, 4);
  aPnts(1) = gp_Pnt2d(0.0, 0.0);
  aPnts(2) = gp_Pnt2d(1.0, 0.0);
  aPnts(3) = gp_Pnt2d(1.0, 1.0);
  aPnts(4) = gp_Pnt2d(0.0, 1.0);

  CSLib_Class2d aClassifier(aPnts, 1e-10, 1e-10, 1.0, 0.0, 0.0, 1.0);

  const gp_Pnt2d aPoint(0.5, 0.5);
  EXPECT_EQ(aClassifier.SiDans(aPoint), 0);
}

class CSLibNormalPolyDefTest : public ::testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(CSLibNormalPolyDefTest, Value_ConstantPolynomial)
{

  NCollection_Array1<double> aLambda(0, 0);
  aLambda(0) = 1.0;

  CSLib_NormalPolyDef aPoly(0, aLambda);

  double aValue;
  EXPECT_TRUE(aPoly.Value(0.5, aValue));
  EXPECT_NEAR(aValue, 1.0, 1e-10);

  EXPECT_TRUE(aPoly.Value(1.0, aValue));
  EXPECT_NEAR(aValue, 1.0, 1e-10);
}

TEST_F(CSLibNormalPolyDefTest, Value_LinearPolynomial)
{

  NCollection_Array1<double> aLambda(0, 1);
  aLambda(0) = 1.0;
  aLambda(1) = 1.0;

  CSLib_NormalPolyDef aPoly(1, aLambda);

  double aValue;

  EXPECT_TRUE(aPoly.Value(M_PI / 4.0, aValue));
  EXPECT_NEAR(aValue, std::sqrt(2.0), 1e-10);
}

TEST_F(CSLibNormalPolyDefTest, Value_AtSingularPoints)
{

  NCollection_Array1<double> aLambda(0, 2);
  aLambda(0) = 1.0;
  aLambda(1) = 1.0;
  aLambda(2) = 1.0;

  CSLib_NormalPolyDef aPoly(2, aLambda);

  double aValue;

  EXPECT_TRUE(aPoly.Value(0.0, aValue));
  EXPECT_TRUE(std::isfinite(aValue));

  EXPECT_TRUE(aPoly.Value(M_PI / 2.0, aValue));
  EXPECT_TRUE(std::isfinite(aValue));
}

TEST_F(CSLibNormalPolyDefTest, Derivative_AtRegularPoint)
{

  NCollection_Array1<double> aLambda(0, 2);
  aLambda(0) = 1.0;
  aLambda(1) = 0.0;
  aLambda(2) = 1.0;

  CSLib_NormalPolyDef aPoly(2, aLambda);

  double aDeriv;
  EXPECT_TRUE(aPoly.Derivative(M_PI / 4.0, aDeriv));

  EXPECT_TRUE(std::isfinite(aDeriv));
}

TEST_F(CSLibNormalPolyDefTest, Derivative_AtSingularPoint)
{
  NCollection_Array1<double> aLambda(0, 2);
  aLambda(0) = 1.0;
  aLambda(1) = 1.0;
  aLambda(2) = 1.0;

  CSLib_NormalPolyDef aPoly(2, aLambda);

  double aDeriv;

  EXPECT_TRUE(aPoly.Derivative(0.0, aDeriv));
  EXPECT_NEAR(aDeriv, 0.0, 1e-10);
}

TEST_F(CSLibNormalPolyDefTest, Values_Consistency)
{
  NCollection_Array1<double> aLambda(0, 2);
  aLambda(0) = 1.0;
  aLambda(1) = 2.0;
  aLambda(2) = 1.0;

  CSLib_NormalPolyDef aPoly(2, aLambda);

  double aF1, aD1;
  double aF2, aD2;

  EXPECT_TRUE(aPoly.Value(0.7, aF1));
  EXPECT_TRUE(aPoly.Derivative(0.7, aD1));

  EXPECT_TRUE(aPoly.Values(0.7, aF2, aD2));

  EXPECT_NEAR(aF1, aF2, 1e-10);
  EXPECT_NEAR(aD1, aD2, 1e-10);
}

TEST_F(CSLibNormalPolyDefTest, Derivative_NumericalApproximation)
{
  NCollection_Array1<double> aLambda(0, 2);
  aLambda(0) = 1.0;
  aLambda(1) = 2.0;
  aLambda(2) = 3.0;

  CSLib_NormalPolyDef aPoly(2, aLambda);

  const double aX = 0.8;
  const double aH = 1e-6;

  double aFMinus, aFPlus, aAnalyticDeriv;

  EXPECT_TRUE(aPoly.Value(aX - aH, aFMinus));
  EXPECT_TRUE(aPoly.Value(aX + aH, aFPlus));
  EXPECT_TRUE(aPoly.Derivative(aX, aAnalyticDeriv));

  const double aNumericDeriv = (aFPlus - aFMinus) / (2.0 * aH);

  EXPECT_NEAR(aAnalyticDeriv, aNumericDeriv, 1e-4);
}

TEST(CSLibEnumTest, DerivativeStatus_AllValues)
{

  EXPECT_NE(CSLib_Done, CSLib_D1uIsNull);
  EXPECT_NE(CSLib_Done, CSLib_D1vIsNull);
  EXPECT_NE(CSLib_Done, CSLib_D1IsNull);
  EXPECT_NE(CSLib_Done, CSLib_D1uD1vRatioIsNull);
  EXPECT_NE(CSLib_Done, CSLib_D1vD1uRatioIsNull);
  EXPECT_NE(CSLib_Done, CSLib_D1uIsParallelD1v);
}

TEST(CSLibEnumTest, NormalStatus_AllValues)
{

  EXPECT_NE(CSLib_Singular, CSLib_Defined);
  EXPECT_NE(CSLib_Singular, CSLib_InfinityOfSolutions);
  EXPECT_NE(CSLib_Singular, CSLib_D1NuIsNull);
  EXPECT_NE(CSLib_Singular, CSLib_D1NvIsNull);
  EXPECT_NE(CSLib_Singular, CSLib_D1NIsNull);
  EXPECT_NE(CSLib_Singular, CSLib_D1NuNvRatioIsNull);
  EXPECT_NE(CSLib_Singular, CSLib_D1NvNuRatioIsNull);
  EXPECT_NE(CSLib_Singular, CSLib_D1NuIsParallelD1Nv);
}

class CSLibIntegrationTest : public ::testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(CSLibIntegrationTest, PlanarSurface_ConstantNormal)
{

  const gp_Vec aD1U(1.0, 0.0, 0.0);
  const gp_Vec aD1V(0.0, 1.0, 0.0);

  CSLib_DerivativeStatus aStatus;
  gp_Dir                 aNormal;

  CSLib::Normal(aD1U, aD1V, 1e-10, aStatus, aNormal);

  EXPECT_EQ(aStatus, CSLib_Done);
  checkDirEqual(aNormal, gp_Dir(0.0, 0.0, 1.0));
}

TEST_F(CSLibIntegrationTest, CylindricalSurface_VaryingNormal)
{

  {
    const gp_Vec aD1U(0.0, 1.0, 0.0);
    const gp_Vec aD1V(0.0, 0.0, 1.0);

    CSLib_DerivativeStatus aStatus;
    gp_Dir                 aNormal;

    CSLib::Normal(aD1U, aD1V, 1e-10, aStatus, aNormal);

    EXPECT_EQ(aStatus, CSLib_Done);
    checkDirEqual(aNormal, gp_Dir(1.0, 0.0, 0.0));
  }

  {
    const gp_Vec aD1U(-1.0, 0.0, 0.0);
    const gp_Vec aD1V(0.0, 0.0, 1.0);

    CSLib_DerivativeStatus aStatus;
    gp_Dir                 aNormal;

    CSLib::Normal(aD1U, aD1V, 1e-10, aStatus, aNormal);

    EXPECT_EQ(aStatus, CSLib_Done);
    checkDirEqual(aNormal, gp_Dir(0.0, 1.0, 0.0));
  }
}

TEST_F(CSLibIntegrationTest, Class2d_ComplexPolygon)
{

  NCollection_Array1<gp_Pnt2d> aPnts(1, 6);
  aPnts(1) = gp_Pnt2d(0.0, 0.0);
  aPnts(2) = gp_Pnt2d(2.0, 0.0);
  aPnts(3) = gp_Pnt2d(2.0, 1.0);
  aPnts(4) = gp_Pnt2d(1.0, 1.0);
  aPnts(5) = gp_Pnt2d(1.0, 2.0);
  aPnts(6) = gp_Pnt2d(0.0, 2.0);

  CSLib_Class2d aClassifier(aPnts, 1e-10, 1e-10, 0.0, 0.0, 2.0, 2.0);

  EXPECT_EQ(aClassifier.SiDans(gp_Pnt2d(0.5, 0.5)), 1);

  EXPECT_EQ(aClassifier.SiDans(gp_Pnt2d(1.5, 1.5)), -1);

  EXPECT_EQ(aClassifier.SiDans(gp_Pnt2d(3.0, 3.0)), -1);
}
