

#include <BSplSLib.hpp>
#include <BSplSLib_Cache.hpp>

#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

#include <NCollection_Array2.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

#include <gtest/gtest.h>

namespace
{
  constexpr double THE_TOLERANCE = 1e-10;
}

class BSplSLib_CacheTest : public ::testing::Test
{
protected:
  void SetUp() override {}

  void createFlatKnots(const NCollection_Array1<double>& theKnots,
                       const NCollection_Array1<int>&    theMults,
                       NCollection_Array1<double>&       theFlatKnots) const
  {
    int aFlatIndex = theFlatKnots.Lower();
    for (int i = theKnots.Lower(); i <= theKnots.Upper(); ++i)
    {
      for (int j = 0; j < theMults(i); ++j)
      {
        theFlatKnots(aFlatIndex++) = theKnots(i);
      }
    }
  }
};

TEST_F(BSplSLib_CacheTest, D0_NonRationalSurface)
{

  NCollection_Array2<gp_Pnt> aPoles(1, 3, 1, 3);

  aPoles(1, 1) = gp_Pnt(0, 0, 0);
  aPoles(2, 1) = gp_Pnt(1, 0, 1);
  aPoles(3, 1) = gp_Pnt(2, 0, 0);

  aPoles(1, 2) = gp_Pnt(0, 1, 1);
  aPoles(2, 2) = gp_Pnt(1, 1, 2);
  aPoles(3, 2) = gp_Pnt(2, 1, 1);

  aPoles(1, 3) = gp_Pnt(0, 2, 0);
  aPoles(2, 3) = gp_Pnt(1, 2, 1);
  aPoles(3, 3) = gp_Pnt(2, 2, 0);

  NCollection_Array1<double> aKnotsU(1, 2);
  aKnotsU(1) = 0.0;
  aKnotsU(2) = 1.0;

  NCollection_Array1<double> aKnotsV(1, 2);
  aKnotsV(1) = 0.0;
  aKnotsV(2) = 1.0;

  NCollection_Array1<int> aMultsU(1, 2);
  aMultsU(1) = 3;
  aMultsU(2) = 3;

  NCollection_Array1<int> aMultsV(1, 2);
  aMultsV(1) = 3;
  aMultsV(2) = 3;

  NCollection_Array1<double> aFlatKnotsU(1, 6);
  createFlatKnots(aKnotsU, aMultsU, aFlatKnotsU);

  NCollection_Array1<double> aFlatKnotsV(1, 6);
  createFlatKnots(aKnotsV, aMultsV, aFlatKnotsV);

  const int aDegreeU = 2;
  const int aDegreeV = 2;

  occ::handle<BSplSLib_Cache> aCache =
    new BSplSLib_Cache(aDegreeU, false, aFlatKnotsU, aDegreeV, false, aFlatKnotsV, nullptr);
  aCache->BuildCache(0.5, 0.5, aFlatKnotsU, aFlatKnotsV, aPoles, nullptr);

  for (double u = 0.0; u <= 1.0; u += 0.2)
  {
    for (double v = 0.0; v <= 1.0; v += 0.2)
    {
      gp_Pnt aCachePnt, aDirectPnt;

      if (!aCache->IsCacheValid(u, v))
      {
        aCache->BuildCache(u, v, aFlatKnotsU, aFlatKnotsV, aPoles, nullptr);
      }
      aCache->D0(u, v, aCachePnt);

      BSplSLib::D0(u,
                   v,
                   0,
                   0,
                   aPoles,
                   nullptr,
                   aKnotsU,
                   aKnotsV,
                   &aMultsU,
                   &aMultsV,
                   aDegreeU,
                   aDegreeV,
                   false,
                   false,
                   false,
                   false,
                   aDirectPnt);

      EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE)
        << "D0 X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCachePnt.Y(), aDirectPnt.Y(), THE_TOLERANCE)
        << "D0 Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCachePnt.Z(), aDirectPnt.Z(), THE_TOLERANCE)
        << "D0 Z mismatch at u=" << u << ", v=" << v;
    }
  }
}

TEST_F(BSplSLib_CacheTest, D1_NonRationalSurface)
{

  NCollection_Array2<gp_Pnt> aPoles(1, 3, 1, 3);

  aPoles(1, 1) = gp_Pnt(0, 0, 0);
  aPoles(2, 1) = gp_Pnt(1, 0, 1);
  aPoles(3, 1) = gp_Pnt(2, 0, 0);

  aPoles(1, 2) = gp_Pnt(0, 1, 1);
  aPoles(2, 2) = gp_Pnt(1, 1, 2);
  aPoles(3, 2) = gp_Pnt(2, 1, 1);

  aPoles(1, 3) = gp_Pnt(0, 2, 0);
  aPoles(2, 3) = gp_Pnt(1, 2, 1);
  aPoles(3, 3) = gp_Pnt(2, 2, 0);

  NCollection_Array1<double> aKnotsU(1, 2);
  aKnotsU(1) = 0.0;
  aKnotsU(2) = 1.0;

  NCollection_Array1<double> aKnotsV(1, 2);
  aKnotsV(1) = 0.0;
  aKnotsV(2) = 1.0;

  NCollection_Array1<int> aMultsU(1, 2);
  aMultsU(1) = 3;
  aMultsU(2) = 3;

  NCollection_Array1<int> aMultsV(1, 2);
  aMultsV(1) = 3;
  aMultsV(2) = 3;

  NCollection_Array1<double> aFlatKnotsU(1, 6);
  createFlatKnots(aKnotsU, aMultsU, aFlatKnotsU);

  NCollection_Array1<double> aFlatKnotsV(1, 6);
  createFlatKnots(aKnotsV, aMultsV, aFlatKnotsV);

  const int aDegreeU = 2;
  const int aDegreeV = 2;

  occ::handle<BSplSLib_Cache> aCache =
    new BSplSLib_Cache(aDegreeU, false, aFlatKnotsU, aDegreeV, false, aFlatKnotsV, nullptr);
  aCache->BuildCache(0.5, 0.5, aFlatKnotsU, aFlatKnotsV, aPoles, nullptr);

  for (double u = 0.0; u <= 1.0; u += 0.2)
  {
    for (double v = 0.0; v <= 1.0; v += 0.2)
    {
      gp_Pnt aCachePnt, aDirectPnt;
      gp_Vec aCacheTanU, aCacheTanV, aDirectTanU, aDirectTanV;

      if (!aCache->IsCacheValid(u, v))
      {
        aCache->BuildCache(u, v, aFlatKnotsU, aFlatKnotsV, aPoles, nullptr);
      }
      aCache->D1(u, v, aCachePnt, aCacheTanU, aCacheTanV);

      BSplSLib::D1(u,
                   v,
                   0,
                   0,
                   aPoles,
                   nullptr,
                   aKnotsU,
                   aKnotsV,
                   &aMultsU,
                   &aMultsV,
                   aDegreeU,
                   aDegreeV,
                   false,
                   false,
                   false,
                   false,
                   aDirectPnt,
                   aDirectTanU,
                   aDirectTanV);

      EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE)
        << "D1 point X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCachePnt.Y(), aDirectPnt.Y(), THE_TOLERANCE)
        << "D1 point Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCachePnt.Z(), aDirectPnt.Z(), THE_TOLERANCE)
        << "D1 point Z mismatch at u=" << u << ", v=" << v;

      EXPECT_NEAR(aCacheTanU.X(), aDirectTanU.X(), THE_TOLERANCE)
        << "D1 tangentU X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanU.Y(), aDirectTanU.Y(), THE_TOLERANCE)
        << "D1 tangentU Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanU.Z(), aDirectTanU.Z(), THE_TOLERANCE)
        << "D1 tangentU Z mismatch at u=" << u << ", v=" << v;

      EXPECT_NEAR(aCacheTanV.X(), aDirectTanV.X(), THE_TOLERANCE)
        << "D1 tangentV X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanV.Y(), aDirectTanV.Y(), THE_TOLERANCE)
        << "D1 tangentV Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanV.Z(), aDirectTanV.Z(), THE_TOLERANCE)
        << "D1 tangentV Z mismatch at u=" << u << ", v=" << v;
    }
  }
}

TEST_F(BSplSLib_CacheTest, D2_NonRationalSurface)
{

  NCollection_Array2<gp_Pnt> aPoles(1, 3, 1, 3);

  aPoles(1, 1) = gp_Pnt(0, 0, 0);
  aPoles(2, 1) = gp_Pnt(1, 0, 1);
  aPoles(3, 1) = gp_Pnt(2, 0, 0);

  aPoles(1, 2) = gp_Pnt(0, 1, 1);
  aPoles(2, 2) = gp_Pnt(1, 1, 2);
  aPoles(3, 2) = gp_Pnt(2, 1, 1);

  aPoles(1, 3) = gp_Pnt(0, 2, 0);
  aPoles(2, 3) = gp_Pnt(1, 2, 1);
  aPoles(3, 3) = gp_Pnt(2, 2, 0);

  NCollection_Array1<double> aKnotsU(1, 2);
  aKnotsU(1) = 0.0;
  aKnotsU(2) = 1.0;

  NCollection_Array1<double> aKnotsV(1, 2);
  aKnotsV(1) = 0.0;
  aKnotsV(2) = 1.0;

  NCollection_Array1<int> aMultsU(1, 2);
  aMultsU(1) = 3;
  aMultsU(2) = 3;

  NCollection_Array1<int> aMultsV(1, 2);
  aMultsV(1) = 3;
  aMultsV(2) = 3;

  NCollection_Array1<double> aFlatKnotsU(1, 6);
  createFlatKnots(aKnotsU, aMultsU, aFlatKnotsU);

  NCollection_Array1<double> aFlatKnotsV(1, 6);
  createFlatKnots(aKnotsV, aMultsV, aFlatKnotsV);

  const int aDegreeU = 2;
  const int aDegreeV = 2;

  occ::handle<BSplSLib_Cache> aCache =
    new BSplSLib_Cache(aDegreeU, false, aFlatKnotsU, aDegreeV, false, aFlatKnotsV, nullptr);
  aCache->BuildCache(0.5, 0.5, aFlatKnotsU, aFlatKnotsV, aPoles, nullptr);

  for (double u = 0.0; u <= 1.0; u += 0.2)
  {
    for (double v = 0.0; v <= 1.0; v += 0.2)
    {
      gp_Pnt aCachePnt, aDirectPnt;
      gp_Vec aCacheTanU, aCacheTanV, aDirectTanU, aDirectTanV;
      gp_Vec aCacheCurvU, aCacheCurvV, aCacheCurvUV;
      gp_Vec aDirectCurvU, aDirectCurvV, aDirectCurvUV;

      if (!aCache->IsCacheValid(u, v))
      {
        aCache->BuildCache(u, v, aFlatKnotsU, aFlatKnotsV, aPoles, nullptr);
      }
      aCache->D2(u, v, aCachePnt, aCacheTanU, aCacheTanV, aCacheCurvU, aCacheCurvV, aCacheCurvUV);

      BSplSLib::D2(u,
                   v,
                   0,
                   0,
                   aPoles,
                   nullptr,
                   aKnotsU,
                   aKnotsV,
                   &aMultsU,
                   &aMultsV,
                   aDegreeU,
                   aDegreeV,
                   false,
                   false,
                   false,
                   false,
                   aDirectPnt,
                   aDirectTanU,
                   aDirectTanV,
                   aDirectCurvU,
                   aDirectCurvV,
                   aDirectCurvUV);

      EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE)
        << "D2 point X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCachePnt.Y(), aDirectPnt.Y(), THE_TOLERANCE)
        << "D2 point Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCachePnt.Z(), aDirectPnt.Z(), THE_TOLERANCE)
        << "D2 point Z mismatch at u=" << u << ", v=" << v;

      EXPECT_NEAR(aCacheTanU.X(), aDirectTanU.X(), THE_TOLERANCE)
        << "D2 tangentU X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanU.Y(), aDirectTanU.Y(), THE_TOLERANCE)
        << "D2 tangentU Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanU.Z(), aDirectTanU.Z(), THE_TOLERANCE)
        << "D2 tangentU Z mismatch at u=" << u << ", v=" << v;

      EXPECT_NEAR(aCacheTanV.X(), aDirectTanV.X(), THE_TOLERANCE)
        << "D2 tangentV X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanV.Y(), aDirectTanV.Y(), THE_TOLERANCE)
        << "D2 tangentV Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanV.Z(), aDirectTanV.Z(), THE_TOLERANCE)
        << "D2 tangentV Z mismatch at u=" << u << ", v=" << v;

      EXPECT_NEAR(aCacheCurvU.X(), aDirectCurvU.X(), THE_TOLERANCE)
        << "D2 curvU X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheCurvU.Y(), aDirectCurvU.Y(), THE_TOLERANCE)
        << "D2 curvU Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheCurvU.Z(), aDirectCurvU.Z(), THE_TOLERANCE)
        << "D2 curvU Z mismatch at u=" << u << ", v=" << v;

      EXPECT_NEAR(aCacheCurvV.X(), aDirectCurvV.X(), THE_TOLERANCE)
        << "D2 curvV X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheCurvV.Y(), aDirectCurvV.Y(), THE_TOLERANCE)
        << "D2 curvV Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheCurvV.Z(), aDirectCurvV.Z(), THE_TOLERANCE)
        << "D2 curvV Z mismatch at u=" << u << ", v=" << v;

      EXPECT_NEAR(aCacheCurvUV.X(), aDirectCurvUV.X(), THE_TOLERANCE)
        << "D2 curvUV X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheCurvUV.Y(), aDirectCurvUV.Y(), THE_TOLERANCE)
        << "D2 curvUV Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheCurvUV.Z(), aDirectCurvUV.Z(), THE_TOLERANCE)
        << "D2 curvUV Z mismatch at u=" << u << ", v=" << v;
    }
  }
}

TEST_F(BSplSLib_CacheTest, D0_RationalSurface)
{

  NCollection_Array2<gp_Pnt> aPoles(1, 3, 1, 3);

  aPoles(1, 1) = gp_Pnt(1, 0, 0);
  aPoles(2, 1) = gp_Pnt(1, 1, 0);
  aPoles(3, 1) = gp_Pnt(0, 1, 0);

  aPoles(1, 2) = gp_Pnt(1, 0, 1);
  aPoles(2, 2) = gp_Pnt(1, 1, 1);
  aPoles(3, 2) = gp_Pnt(0, 1, 1);

  aPoles(1, 3) = gp_Pnt(0, 0, 1);
  aPoles(2, 3) = gp_Pnt(0, 0, 1);
  aPoles(3, 3) = gp_Pnt(0, 0, 1);

  NCollection_Array2<double> aWeights(1, 3, 1, 3);
  const double               aSqrt2_2 = 0.707106781186548;
  aWeights(1, 1)                      = 1.0;
  aWeights(2, 1)                      = aSqrt2_2;
  aWeights(3, 1)                      = 1.0;
  aWeights(1, 2)                      = aSqrt2_2;
  aWeights(2, 2)                      = 0.5;
  aWeights(3, 2)                      = aSqrt2_2;
  aWeights(1, 3)                      = 1.0;
  aWeights(2, 3)                      = aSqrt2_2;
  aWeights(3, 3)                      = 1.0;

  NCollection_Array1<double> aKnotsU(1, 2);
  aKnotsU(1) = 0.0;
  aKnotsU(2) = 1.0;

  NCollection_Array1<double> aKnotsV(1, 2);
  aKnotsV(1) = 0.0;
  aKnotsV(2) = 1.0;

  NCollection_Array1<int> aMultsU(1, 2);
  aMultsU(1) = 3;
  aMultsU(2) = 3;

  NCollection_Array1<int> aMultsV(1, 2);
  aMultsV(1) = 3;
  aMultsV(2) = 3;

  NCollection_Array1<double> aFlatKnotsU(1, 6);
  createFlatKnots(aKnotsU, aMultsU, aFlatKnotsU);

  NCollection_Array1<double> aFlatKnotsV(1, 6);
  createFlatKnots(aKnotsV, aMultsV, aFlatKnotsV);

  const int aDegreeU = 2;
  const int aDegreeV = 2;

  occ::handle<BSplSLib_Cache> aCache =
    new BSplSLib_Cache(aDegreeU, false, aFlatKnotsU, aDegreeV, false, aFlatKnotsV, &aWeights);
  aCache->BuildCache(0.5, 0.5, aFlatKnotsU, aFlatKnotsV, aPoles, &aWeights);

  for (double u = 0.0; u <= 1.0; u += 0.2)
  {
    for (double v = 0.0; v <= 1.0; v += 0.2)
    {
      gp_Pnt aCachePnt, aDirectPnt;

      if (!aCache->IsCacheValid(u, v))
      {
        aCache->BuildCache(u, v, aFlatKnotsU, aFlatKnotsV, aPoles, &aWeights);
      }
      aCache->D0(u, v, aCachePnt);

      BSplSLib::D0(u,
                   v,
                   0,
                   0,
                   aPoles,
                   &aWeights,
                   aKnotsU,
                   aKnotsV,
                   &aMultsU,
                   &aMultsV,
                   aDegreeU,
                   aDegreeV,
                   true,
                   true,
                   false,
                   false,
                   aDirectPnt);

      EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE)
        << "Rational D0 X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCachePnt.Y(), aDirectPnt.Y(), THE_TOLERANCE)
        << "Rational D0 Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCachePnt.Z(), aDirectPnt.Z(), THE_TOLERANCE)
        << "Rational D0 Z mismatch at u=" << u << ", v=" << v;
    }
  }
}

TEST_F(BSplSLib_CacheTest, D1_RationalSurface)
{

  NCollection_Array2<gp_Pnt> aPoles(1, 3, 1, 3);

  aPoles(1, 1) = gp_Pnt(1, 0, 0);
  aPoles(2, 1) = gp_Pnt(1, 1, 0);
  aPoles(3, 1) = gp_Pnt(0, 1, 0);

  aPoles(1, 2) = gp_Pnt(1, 0, 1);
  aPoles(2, 2) = gp_Pnt(1, 1, 1);
  aPoles(3, 2) = gp_Pnt(0, 1, 1);

  aPoles(1, 3) = gp_Pnt(0, 0, 1);
  aPoles(2, 3) = gp_Pnt(0, 0, 1);
  aPoles(3, 3) = gp_Pnt(0, 0, 1);

  NCollection_Array2<double> aWeights(1, 3, 1, 3);
  const double               aSqrt2_2 = 0.707106781186548;
  aWeights(1, 1)                      = 1.0;
  aWeights(2, 1)                      = aSqrt2_2;
  aWeights(3, 1)                      = 1.0;
  aWeights(1, 2)                      = aSqrt2_2;
  aWeights(2, 2)                      = 0.5;
  aWeights(3, 2)                      = aSqrt2_2;
  aWeights(1, 3)                      = 1.0;
  aWeights(2, 3)                      = aSqrt2_2;
  aWeights(3, 3)                      = 1.0;

  NCollection_Array1<double> aKnotsU(1, 2);
  aKnotsU(1) = 0.0;
  aKnotsU(2) = 1.0;

  NCollection_Array1<double> aKnotsV(1, 2);
  aKnotsV(1) = 0.0;
  aKnotsV(2) = 1.0;

  NCollection_Array1<int> aMultsU(1, 2);
  aMultsU(1) = 3;
  aMultsU(2) = 3;

  NCollection_Array1<int> aMultsV(1, 2);
  aMultsV(1) = 3;
  aMultsV(2) = 3;

  NCollection_Array1<double> aFlatKnotsU(1, 6);
  createFlatKnots(aKnotsU, aMultsU, aFlatKnotsU);

  NCollection_Array1<double> aFlatKnotsV(1, 6);
  createFlatKnots(aKnotsV, aMultsV, aFlatKnotsV);

  const int aDegreeU = 2;
  const int aDegreeV = 2;

  occ::handle<BSplSLib_Cache> aCache =
    new BSplSLib_Cache(aDegreeU, false, aFlatKnotsU, aDegreeV, false, aFlatKnotsV, &aWeights);
  aCache->BuildCache(0.5, 0.5, aFlatKnotsU, aFlatKnotsV, aPoles, &aWeights);

  for (double u = 0.0; u <= 1.0; u += 0.2)
  {
    for (double v = 0.0; v <= 1.0; v += 0.2)
    {
      gp_Pnt aCachePnt, aDirectPnt;
      gp_Vec aCacheTanU, aCacheTanV, aDirectTanU, aDirectTanV;

      if (!aCache->IsCacheValid(u, v))
      {
        aCache->BuildCache(u, v, aFlatKnotsU, aFlatKnotsV, aPoles, &aWeights);
      }
      aCache->D1(u, v, aCachePnt, aCacheTanU, aCacheTanV);

      BSplSLib::D1(u,
                   v,
                   0,
                   0,
                   aPoles,
                   &aWeights,
                   aKnotsU,
                   aKnotsV,
                   &aMultsU,
                   &aMultsV,
                   aDegreeU,
                   aDegreeV,
                   true,
                   true,
                   false,
                   false,
                   aDirectPnt,
                   aDirectTanU,
                   aDirectTanV);

      EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE)
        << "Rational D1 point X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCachePnt.Y(), aDirectPnt.Y(), THE_TOLERANCE)
        << "Rational D1 point Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCachePnt.Z(), aDirectPnt.Z(), THE_TOLERANCE)
        << "Rational D1 point Z mismatch at u=" << u << ", v=" << v;

      EXPECT_NEAR(aCacheTanU.X(), aDirectTanU.X(), THE_TOLERANCE)
        << "Rational D1 tangentU X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanU.Y(), aDirectTanU.Y(), THE_TOLERANCE)
        << "Rational D1 tangentU Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanU.Z(), aDirectTanU.Z(), THE_TOLERANCE)
        << "Rational D1 tangentU Z mismatch at u=" << u << ", v=" << v;

      EXPECT_NEAR(aCacheTanV.X(), aDirectTanV.X(), THE_TOLERANCE)
        << "Rational D1 tangentV X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanV.Y(), aDirectTanV.Y(), THE_TOLERANCE)
        << "Rational D1 tangentV Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanV.Z(), aDirectTanV.Z(), THE_TOLERANCE)
        << "Rational D1 tangentV Z mismatch at u=" << u << ", v=" << v;
    }
  }
}

TEST_F(BSplSLib_CacheTest, D2_RationalSurface)
{

  NCollection_Array2<gp_Pnt> aPoles(1, 3, 1, 3);

  aPoles(1, 1) = gp_Pnt(1, 0, 0);
  aPoles(2, 1) = gp_Pnt(1, 1, 0);
  aPoles(3, 1) = gp_Pnt(0, 1, 0);

  aPoles(1, 2) = gp_Pnt(1, 0, 1);
  aPoles(2, 2) = gp_Pnt(1, 1, 1);
  aPoles(3, 2) = gp_Pnt(0, 1, 1);

  aPoles(1, 3) = gp_Pnt(0, 0, 1);
  aPoles(2, 3) = gp_Pnt(0, 0, 1);
  aPoles(3, 3) = gp_Pnt(0, 0, 1);

  NCollection_Array2<double> aWeights(1, 3, 1, 3);
  const double               aSqrt2_2 = 0.707106781186548;
  aWeights(1, 1)                      = 1.0;
  aWeights(2, 1)                      = aSqrt2_2;
  aWeights(3, 1)                      = 1.0;
  aWeights(1, 2)                      = aSqrt2_2;
  aWeights(2, 2)                      = 0.5;
  aWeights(3, 2)                      = aSqrt2_2;
  aWeights(1, 3)                      = 1.0;
  aWeights(2, 3)                      = aSqrt2_2;
  aWeights(3, 3)                      = 1.0;

  NCollection_Array1<double> aKnotsU(1, 2);
  aKnotsU(1) = 0.0;
  aKnotsU(2) = 1.0;

  NCollection_Array1<double> aKnotsV(1, 2);
  aKnotsV(1) = 0.0;
  aKnotsV(2) = 1.0;

  NCollection_Array1<int> aMultsU(1, 2);
  aMultsU(1) = 3;
  aMultsU(2) = 3;

  NCollection_Array1<int> aMultsV(1, 2);
  aMultsV(1) = 3;
  aMultsV(2) = 3;

  NCollection_Array1<double> aFlatKnotsU(1, 6);
  createFlatKnots(aKnotsU, aMultsU, aFlatKnotsU);

  NCollection_Array1<double> aFlatKnotsV(1, 6);
  createFlatKnots(aKnotsV, aMultsV, aFlatKnotsV);

  const int aDegreeU = 2;
  const int aDegreeV = 2;

  occ::handle<BSplSLib_Cache> aCache =
    new BSplSLib_Cache(aDegreeU, false, aFlatKnotsU, aDegreeV, false, aFlatKnotsV, &aWeights);
  aCache->BuildCache(0.5, 0.5, aFlatKnotsU, aFlatKnotsV, aPoles, &aWeights);

  for (double u = 0.0; u <= 1.0; u += 0.2)
  {
    for (double v = 0.0; v <= 1.0; v += 0.2)
    {
      gp_Pnt aCachePnt, aDirectPnt;
      gp_Vec aCacheTanU, aCacheTanV, aDirectTanU, aDirectTanV;
      gp_Vec aCacheCurvU, aCacheCurvV, aCacheCurvUV;
      gp_Vec aDirectCurvU, aDirectCurvV, aDirectCurvUV;

      if (!aCache->IsCacheValid(u, v))
      {
        aCache->BuildCache(u, v, aFlatKnotsU, aFlatKnotsV, aPoles, &aWeights);
      }
      aCache->D2(u, v, aCachePnt, aCacheTanU, aCacheTanV, aCacheCurvU, aCacheCurvV, aCacheCurvUV);

      BSplSLib::D2(u,
                   v,
                   0,
                   0,
                   aPoles,
                   &aWeights,
                   aKnotsU,
                   aKnotsV,
                   &aMultsU,
                   &aMultsV,
                   aDegreeU,
                   aDegreeV,
                   true,
                   true,
                   false,
                   false,
                   aDirectPnt,
                   aDirectTanU,
                   aDirectTanV,
                   aDirectCurvU,
                   aDirectCurvV,
                   aDirectCurvUV);

      EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE)
        << "Rational D2 point X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCachePnt.Y(), aDirectPnt.Y(), THE_TOLERANCE)
        << "Rational D2 point Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCachePnt.Z(), aDirectPnt.Z(), THE_TOLERANCE)
        << "Rational D2 point Z mismatch at u=" << u << ", v=" << v;

      EXPECT_NEAR(aCacheTanU.X(), aDirectTanU.X(), THE_TOLERANCE)
        << "Rational D2 tangentU X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanU.Y(), aDirectTanU.Y(), THE_TOLERANCE)
        << "Rational D2 tangentU Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanU.Z(), aDirectTanU.Z(), THE_TOLERANCE)
        << "Rational D2 tangentU Z mismatch at u=" << u << ", v=" << v;

      EXPECT_NEAR(aCacheTanV.X(), aDirectTanV.X(), THE_TOLERANCE)
        << "Rational D2 tangentV X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanV.Y(), aDirectTanV.Y(), THE_TOLERANCE)
        << "Rational D2 tangentV Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanV.Z(), aDirectTanV.Z(), THE_TOLERANCE)
        << "Rational D2 tangentV Z mismatch at u=" << u << ", v=" << v;

      EXPECT_NEAR(aCacheCurvU.X(), aDirectCurvU.X(), THE_TOLERANCE)
        << "Rational D2 curvU X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheCurvU.Y(), aDirectCurvU.Y(), THE_TOLERANCE)
        << "Rational D2 curvU Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheCurvU.Z(), aDirectCurvU.Z(), THE_TOLERANCE)
        << "Rational D2 curvU Z mismatch at u=" << u << ", v=" << v;

      EXPECT_NEAR(aCacheCurvV.X(), aDirectCurvV.X(), THE_TOLERANCE)
        << "Rational D2 curvV X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheCurvV.Y(), aDirectCurvV.Y(), THE_TOLERANCE)
        << "Rational D2 curvV Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheCurvV.Z(), aDirectCurvV.Z(), THE_TOLERANCE)
        << "Rational D2 curvV Z mismatch at u=" << u << ", v=" << v;

      EXPECT_NEAR(aCacheCurvUV.X(), aDirectCurvUV.X(), THE_TOLERANCE)
        << "Rational D2 curvUV X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheCurvUV.Y(), aDirectCurvUV.Y(), THE_TOLERANCE)
        << "Rational D2 curvUV Y mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheCurvUV.Z(), aDirectCurvUV.Z(), THE_TOLERANCE)
        << "Rational D2 curvUV Z mismatch at u=" << u << ", v=" << v;
    }
  }
}

TEST_F(BSplSLib_CacheTest, D1_DifferentDegrees_UGreaterV)
{

  NCollection_Array2<gp_Pnt> aPoles(1, 4, 1, 3);

  for (int i = 1; i <= 4; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      aPoles(i, j) = gp_Pnt((i - 1) * 1.0, (j - 1) * 1.0, sin((i - 1) * 0.5) * cos((j - 1) * 0.5));
    }
  }

  NCollection_Array1<double> aKnotsU(1, 2);
  aKnotsU(1) = 0.0;
  aKnotsU(2) = 1.0;

  NCollection_Array1<double> aKnotsV(1, 2);
  aKnotsV(1) = 0.0;
  aKnotsV(2) = 1.0;

  NCollection_Array1<int> aMultsU(1, 2);
  aMultsU(1) = 4;
  aMultsU(2) = 4;

  NCollection_Array1<int> aMultsV(1, 2);
  aMultsV(1) = 3;
  aMultsV(2) = 3;

  NCollection_Array1<double> aFlatKnotsU(1, 8);
  createFlatKnots(aKnotsU, aMultsU, aFlatKnotsU);

  NCollection_Array1<double> aFlatKnotsV(1, 6);
  createFlatKnots(aKnotsV, aMultsV, aFlatKnotsV);

  const int aDegreeU = 3;
  const int aDegreeV = 2;

  occ::handle<BSplSLib_Cache> aCache =
    new BSplSLib_Cache(aDegreeU, false, aFlatKnotsU, aDegreeV, false, aFlatKnotsV, nullptr);
  aCache->BuildCache(0.5, 0.5, aFlatKnotsU, aFlatKnotsV, aPoles, nullptr);

  for (double u = 0.0; u <= 1.0; u += 0.25)
  {
    for (double v = 0.0; v <= 1.0; v += 0.25)
    {
      gp_Pnt aCachePnt, aDirectPnt;
      gp_Vec aCacheTanU, aCacheTanV, aDirectTanU, aDirectTanV;

      if (!aCache->IsCacheValid(u, v))
      {
        aCache->BuildCache(u, v, aFlatKnotsU, aFlatKnotsV, aPoles, nullptr);
      }
      aCache->D1(u, v, aCachePnt, aCacheTanU, aCacheTanV);

      BSplSLib::D1(u,
                   v,
                   0,
                   0,
                   aPoles,
                   nullptr,
                   aKnotsU,
                   aKnotsV,
                   &aMultsU,
                   &aMultsV,
                   aDegreeU,
                   aDegreeV,
                   false,
                   false,
                   false,
                   false,
                   aDirectPnt,
                   aDirectTanU,
                   aDirectTanV);

      EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE)
        << "DifferentDeg D1 point X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanU.X(), aDirectTanU.X(), THE_TOLERANCE)
        << "DifferentDeg D1 tanU X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanV.X(), aDirectTanV.X(), THE_TOLERANCE)
        << "DifferentDeg D1 tanV X mismatch at u=" << u << ", v=" << v;
    }
  }
}

TEST_F(BSplSLib_CacheTest, D1_DifferentDegrees_VGreaterU)
{

  NCollection_Array2<gp_Pnt> aPoles(1, 3, 1, 4);

  for (int i = 1; i <= 3; ++i)
  {
    for (int j = 1; j <= 4; ++j)
    {
      aPoles(i, j) = gp_Pnt((i - 1) * 1.0, (j - 1) * 1.0, sin((i - 1) * 0.5) * cos((j - 1) * 0.5));
    }
  }

  NCollection_Array1<double> aKnotsU(1, 2);
  aKnotsU(1) = 0.0;
  aKnotsU(2) = 1.0;

  NCollection_Array1<double> aKnotsV(1, 2);
  aKnotsV(1) = 0.0;
  aKnotsV(2) = 1.0;

  NCollection_Array1<int> aMultsU(1, 2);
  aMultsU(1) = 3;
  aMultsU(2) = 3;

  NCollection_Array1<int> aMultsV(1, 2);
  aMultsV(1) = 4;
  aMultsV(2) = 4;

  NCollection_Array1<double> aFlatKnotsU(1, 6);
  createFlatKnots(aKnotsU, aMultsU, aFlatKnotsU);

  NCollection_Array1<double> aFlatKnotsV(1, 8);
  createFlatKnots(aKnotsV, aMultsV, aFlatKnotsV);

  const int aDegreeU = 2;
  const int aDegreeV = 3;

  occ::handle<BSplSLib_Cache> aCache =
    new BSplSLib_Cache(aDegreeU, false, aFlatKnotsU, aDegreeV, false, aFlatKnotsV, nullptr);
  aCache->BuildCache(0.5, 0.5, aFlatKnotsU, aFlatKnotsV, aPoles, nullptr);

  for (double u = 0.0; u <= 1.0; u += 0.25)
  {
    for (double v = 0.0; v <= 1.0; v += 0.25)
    {
      gp_Pnt aCachePnt, aDirectPnt;
      gp_Vec aCacheTanU, aCacheTanV, aDirectTanU, aDirectTanV;

      if (!aCache->IsCacheValid(u, v))
      {
        aCache->BuildCache(u, v, aFlatKnotsU, aFlatKnotsV, aPoles, nullptr);
      }
      aCache->D1(u, v, aCachePnt, aCacheTanU, aCacheTanV);

      BSplSLib::D1(u,
                   v,
                   0,
                   0,
                   aPoles,
                   nullptr,
                   aKnotsU,
                   aKnotsV,
                   &aMultsU,
                   &aMultsV,
                   aDegreeU,
                   aDegreeV,
                   false,
                   false,
                   false,
                   false,
                   aDirectPnt,
                   aDirectTanU,
                   aDirectTanV);

      EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE)
        << "DifferentDeg V>U D1 point X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanU.X(), aDirectTanU.X(), THE_TOLERANCE)
        << "DifferentDeg V>U D1 tanU X mismatch at u=" << u << ", v=" << v;
      EXPECT_NEAR(aCacheTanV.X(), aDirectTanV.X(), THE_TOLERANCE)
        << "DifferentDeg V>U D1 tanV X mismatch at u=" << u << ", v=" << v;
    }
  }
}
