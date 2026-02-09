

#include <BSplCLib.hpp>
#include <BSplCLib_Cache.hpp>

#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>

#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>

#include <gtest/gtest.h>

namespace
{
  constexpr double THE_TOLERANCE = 1e-10;
}

class BSplCLib_CacheTest : public ::testing::Test
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

TEST_F(BSplCLib_CacheTest, D0_NonRationalCurve3D)
{

  NCollection_Array1<gp_Pnt> aPoles(1, 4);
  aPoles(1) = gp_Pnt(0, 0, 0);
  aPoles(2) = gp_Pnt(1, 2, 0);
  aPoles(3) = gp_Pnt(2, 2, 0);
  aPoles(4) = gp_Pnt(3, 0, 0);

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.0;
  aKnots(2) = 1.0;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 4;
  aMults(2) = 4;

  NCollection_Array1<double> aFlatKnots(1, 8);
  createFlatKnots(aKnots, aMults, aFlatKnots);

  const int aDegree = 3;

  occ::handle<BSplCLib_Cache> aCache =
    new BSplCLib_Cache(aDegree, false, aFlatKnots, aPoles, nullptr);
  aCache->BuildCache(0.5, aFlatKnots, aPoles, nullptr);

  for (double u = 0.0; u <= 1.0; u += 0.1)
  {
    gp_Pnt aCachePnt, aDirectPnt;

    if (!aCache->IsCacheValid(u))
    {
      aCache->BuildCache(u, aFlatKnots, aPoles, nullptr);
    }
    aCache->D0(u, aCachePnt);

    BSplCLib::D0(u, 0, aDegree, false, aPoles, nullptr, aKnots, &aMults, aDirectPnt);

    EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE) << "D0 X mismatch at u=" << u;
    EXPECT_NEAR(aCachePnt.Y(), aDirectPnt.Y(), THE_TOLERANCE) << "D0 Y mismatch at u=" << u;
    EXPECT_NEAR(aCachePnt.Z(), aDirectPnt.Z(), THE_TOLERANCE) << "D0 Z mismatch at u=" << u;
  }
}

TEST_F(BSplCLib_CacheTest, D1_NonRationalCurve3D)
{

  NCollection_Array1<gp_Pnt> aPoles(1, 4);
  aPoles(1) = gp_Pnt(0, 0, 0);
  aPoles(2) = gp_Pnt(1, 2, 1);
  aPoles(3) = gp_Pnt(2, 2, 1);
  aPoles(4) = gp_Pnt(3, 0, 0);

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.0;
  aKnots(2) = 1.0;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 4;
  aMults(2) = 4;

  NCollection_Array1<double> aFlatKnots(1, 8);
  createFlatKnots(aKnots, aMults, aFlatKnots);

  const int aDegree = 3;

  occ::handle<BSplCLib_Cache> aCache =
    new BSplCLib_Cache(aDegree, false, aFlatKnots, aPoles, nullptr);
  aCache->BuildCache(0.5, aFlatKnots, aPoles, nullptr);

  for (double u = 0.0; u <= 1.0; u += 0.1)
  {
    gp_Pnt aCachePnt, aDirectPnt;
    gp_Vec aCacheTan, aDirectTan;

    if (!aCache->IsCacheValid(u))
    {
      aCache->BuildCache(u, aFlatKnots, aPoles, nullptr);
    }
    aCache->D1(u, aCachePnt, aCacheTan);

    BSplCLib::D1(u, 0, aDegree, false, aPoles, nullptr, aKnots, &aMults, aDirectPnt, aDirectTan);

    EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE) << "D1 point X mismatch at u=" << u;
    EXPECT_NEAR(aCachePnt.Y(), aDirectPnt.Y(), THE_TOLERANCE) << "D1 point Y mismatch at u=" << u;
    EXPECT_NEAR(aCachePnt.Z(), aDirectPnt.Z(), THE_TOLERANCE) << "D1 point Z mismatch at u=" << u;

    EXPECT_NEAR(aCacheTan.X(), aDirectTan.X(), THE_TOLERANCE) << "D1 tangent X mismatch at u=" << u;
    EXPECT_NEAR(aCacheTan.Y(), aDirectTan.Y(), THE_TOLERANCE) << "D1 tangent Y mismatch at u=" << u;
    EXPECT_NEAR(aCacheTan.Z(), aDirectTan.Z(), THE_TOLERANCE) << "D1 tangent Z mismatch at u=" << u;
  }
}

TEST_F(BSplCLib_CacheTest, D2_NonRationalCurve3D)
{

  NCollection_Array1<gp_Pnt> aPoles(1, 4);
  aPoles(1) = gp_Pnt(0, 0, 0);
  aPoles(2) = gp_Pnt(1, 2, 1);
  aPoles(3) = gp_Pnt(2, 2, 1);
  aPoles(4) = gp_Pnt(3, 0, 0);

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.0;
  aKnots(2) = 1.0;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 4;
  aMults(2) = 4;

  NCollection_Array1<double> aFlatKnots(1, 8);
  createFlatKnots(aKnots, aMults, aFlatKnots);

  const int aDegree = 3;

  occ::handle<BSplCLib_Cache> aCache =
    new BSplCLib_Cache(aDegree, false, aFlatKnots, aPoles, nullptr);
  aCache->BuildCache(0.5, aFlatKnots, aPoles, nullptr);

  for (double u = 0.0; u <= 1.0; u += 0.1)
  {
    gp_Pnt aCachePnt, aDirectPnt;
    gp_Vec aCacheTan, aDirectTan;
    gp_Vec aCacheCurv, aDirectCurv;

    if (!aCache->IsCacheValid(u))
    {
      aCache->BuildCache(u, aFlatKnots, aPoles, nullptr);
    }
    aCache->D2(u, aCachePnt, aCacheTan, aCacheCurv);

    BSplCLib::D2(u,
                 0,
                 aDegree,
                 false,
                 aPoles,
                 nullptr,
                 aKnots,
                 &aMults,
                 aDirectPnt,
                 aDirectTan,
                 aDirectCurv);

    EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE) << "D2 point X mismatch at u=" << u;
    EXPECT_NEAR(aCachePnt.Y(), aDirectPnt.Y(), THE_TOLERANCE) << "D2 point Y mismatch at u=" << u;
    EXPECT_NEAR(aCachePnt.Z(), aDirectPnt.Z(), THE_TOLERANCE) << "D2 point Z mismatch at u=" << u;

    EXPECT_NEAR(aCacheTan.X(), aDirectTan.X(), THE_TOLERANCE) << "D2 tangent X mismatch at u=" << u;
    EXPECT_NEAR(aCacheTan.Y(), aDirectTan.Y(), THE_TOLERANCE) << "D2 tangent Y mismatch at u=" << u;
    EXPECT_NEAR(aCacheTan.Z(), aDirectTan.Z(), THE_TOLERANCE) << "D2 tangent Z mismatch at u=" << u;

    EXPECT_NEAR(aCacheCurv.X(), aDirectCurv.X(), THE_TOLERANCE)
      << "D2 curvature X mismatch at u=" << u;
    EXPECT_NEAR(aCacheCurv.Y(), aDirectCurv.Y(), THE_TOLERANCE)
      << "D2 curvature Y mismatch at u=" << u;
    EXPECT_NEAR(aCacheCurv.Z(), aDirectCurv.Z(), THE_TOLERANCE)
      << "D2 curvature Z mismatch at u=" << u;
  }
}

TEST_F(BSplCLib_CacheTest, D0_RationalCurve3D)
{

  NCollection_Array1<gp_Pnt> aPoles(1, 3);
  aPoles(1) = gp_Pnt(1, 0, 0);
  aPoles(2) = gp_Pnt(1, 1, 0);
  aPoles(3) = gp_Pnt(0, 1, 0);

  NCollection_Array1<double> aWeights(1, 3);
  aWeights(1) = 1.0;
  aWeights(2) = 0.707106781186548;
  aWeights(3) = 1.0;

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.0;
  aKnots(2) = 1.0;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 3;
  aMults(2) = 3;

  NCollection_Array1<double> aFlatKnots(1, 6);
  createFlatKnots(aKnots, aMults, aFlatKnots);

  const int aDegree = 2;

  occ::handle<BSplCLib_Cache> aCache =
    new BSplCLib_Cache(aDegree, false, aFlatKnots, aPoles, &aWeights);
  aCache->BuildCache(0.5, aFlatKnots, aPoles, &aWeights);

  for (double u = 0.0; u <= 1.0; u += 0.1)
  {
    gp_Pnt aCachePnt, aDirectPnt;

    if (!aCache->IsCacheValid(u))
    {
      aCache->BuildCache(u, aFlatKnots, aPoles, &aWeights);
    }
    aCache->D0(u, aCachePnt);

    BSplCLib::D0(u, 0, aDegree, false, aPoles, &aWeights, aKnots, &aMults, aDirectPnt);

    EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE)
      << "Rational D0 X mismatch at u=" << u;
    EXPECT_NEAR(aCachePnt.Y(), aDirectPnt.Y(), THE_TOLERANCE)
      << "Rational D0 Y mismatch at u=" << u;
    EXPECT_NEAR(aCachePnt.Z(), aDirectPnt.Z(), THE_TOLERANCE)
      << "Rational D0 Z mismatch at u=" << u;
  }
}

TEST_F(BSplCLib_CacheTest, D1_RationalCurve3D)
{

  NCollection_Array1<gp_Pnt> aPoles(1, 3);
  aPoles(1) = gp_Pnt(1, 0, 0);
  aPoles(2) = gp_Pnt(1, 1, 0);
  aPoles(3) = gp_Pnt(0, 1, 0);

  NCollection_Array1<double> aWeights(1, 3);
  aWeights(1) = 1.0;
  aWeights(2) = 0.707106781186548;
  aWeights(3) = 1.0;

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.0;
  aKnots(2) = 1.0;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 3;
  aMults(2) = 3;

  NCollection_Array1<double> aFlatKnots(1, 6);
  createFlatKnots(aKnots, aMults, aFlatKnots);

  const int aDegree = 2;

  occ::handle<BSplCLib_Cache> aCache =
    new BSplCLib_Cache(aDegree, false, aFlatKnots, aPoles, &aWeights);
  aCache->BuildCache(0.5, aFlatKnots, aPoles, &aWeights);

  for (double u = 0.0; u <= 1.0; u += 0.1)
  {
    gp_Pnt aCachePnt, aDirectPnt;
    gp_Vec aCacheTan, aDirectTan;

    if (!aCache->IsCacheValid(u))
    {
      aCache->BuildCache(u, aFlatKnots, aPoles, &aWeights);
    }
    aCache->D1(u, aCachePnt, aCacheTan);

    BSplCLib::D1(u, 0, aDegree, false, aPoles, &aWeights, aKnots, &aMults, aDirectPnt, aDirectTan);

    EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE)
      << "Rational D1 point X mismatch at u=" << u;
    EXPECT_NEAR(aCachePnt.Y(), aDirectPnt.Y(), THE_TOLERANCE)
      << "Rational D1 point Y mismatch at u=" << u;
    EXPECT_NEAR(aCachePnt.Z(), aDirectPnt.Z(), THE_TOLERANCE)
      << "Rational D1 point Z mismatch at u=" << u;

    EXPECT_NEAR(aCacheTan.X(), aDirectTan.X(), THE_TOLERANCE)
      << "Rational D1 tangent X mismatch at u=" << u;
    EXPECT_NEAR(aCacheTan.Y(), aDirectTan.Y(), THE_TOLERANCE)
      << "Rational D1 tangent Y mismatch at u=" << u;
    EXPECT_NEAR(aCacheTan.Z(), aDirectTan.Z(), THE_TOLERANCE)
      << "Rational D1 tangent Z mismatch at u=" << u;
  }
}

TEST_F(BSplCLib_CacheTest, D2_RationalCurve3D)
{

  NCollection_Array1<gp_Pnt> aPoles(1, 3);
  aPoles(1) = gp_Pnt(1, 0, 0);
  aPoles(2) = gp_Pnt(1, 1, 0);
  aPoles(3) = gp_Pnt(0, 1, 0);

  NCollection_Array1<double> aWeights(1, 3);
  aWeights(1) = 1.0;
  aWeights(2) = 0.707106781186548;
  aWeights(3) = 1.0;

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.0;
  aKnots(2) = 1.0;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 3;
  aMults(2) = 3;

  NCollection_Array1<double> aFlatKnots(1, 6);
  createFlatKnots(aKnots, aMults, aFlatKnots);

  const int aDegree = 2;

  occ::handle<BSplCLib_Cache> aCache =
    new BSplCLib_Cache(aDegree, false, aFlatKnots, aPoles, &aWeights);
  aCache->BuildCache(0.5, aFlatKnots, aPoles, &aWeights);

  for (double u = 0.0; u <= 1.0; u += 0.1)
  {
    gp_Pnt aCachePnt, aDirectPnt;
    gp_Vec aCacheTan, aDirectTan;
    gp_Vec aCacheCurv, aDirectCurv;

    if (!aCache->IsCacheValid(u))
    {
      aCache->BuildCache(u, aFlatKnots, aPoles, &aWeights);
    }
    aCache->D2(u, aCachePnt, aCacheTan, aCacheCurv);

    BSplCLib::D2(u,
                 0,
                 aDegree,
                 false,
                 aPoles,
                 &aWeights,
                 aKnots,
                 &aMults,
                 aDirectPnt,
                 aDirectTan,
                 aDirectCurv);

    EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE)
      << "Rational D2 point X mismatch at u=" << u;
    EXPECT_NEAR(aCachePnt.Y(), aDirectPnt.Y(), THE_TOLERANCE)
      << "Rational D2 point Y mismatch at u=" << u;
    EXPECT_NEAR(aCachePnt.Z(), aDirectPnt.Z(), THE_TOLERANCE)
      << "Rational D2 point Z mismatch at u=" << u;

    EXPECT_NEAR(aCacheTan.X(), aDirectTan.X(), THE_TOLERANCE)
      << "Rational D2 tangent X mismatch at u=" << u;
    EXPECT_NEAR(aCacheTan.Y(), aDirectTan.Y(), THE_TOLERANCE)
      << "Rational D2 tangent Y mismatch at u=" << u;
    EXPECT_NEAR(aCacheTan.Z(), aDirectTan.Z(), THE_TOLERANCE)
      << "Rational D2 tangent Z mismatch at u=" << u;

    EXPECT_NEAR(aCacheCurv.X(), aDirectCurv.X(), THE_TOLERANCE)
      << "Rational D2 curvature X mismatch at u=" << u;
    EXPECT_NEAR(aCacheCurv.Y(), aDirectCurv.Y(), THE_TOLERANCE)
      << "Rational D2 curvature Y mismatch at u=" << u;
    EXPECT_NEAR(aCacheCurv.Z(), aDirectCurv.Z(), THE_TOLERANCE)
      << "Rational D2 curvature Z mismatch at u=" << u;
  }
}

TEST_F(BSplCLib_CacheTest, D3_NonRationalCurve3D)
{

  NCollection_Array1<gp_Pnt> aPoles(1, 4);
  aPoles(1) = gp_Pnt(0, 0, 0);
  aPoles(2) = gp_Pnt(1, 2, 1);
  aPoles(3) = gp_Pnt(2, 2, 1);
  aPoles(4) = gp_Pnt(3, 0, 0);

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.0;
  aKnots(2) = 1.0;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 4;
  aMults(2) = 4;

  NCollection_Array1<double> aFlatKnots(1, 8);
  createFlatKnots(aKnots, aMults, aFlatKnots);

  const int aDegree = 3;

  occ::handle<BSplCLib_Cache> aCache =
    new BSplCLib_Cache(aDegree, false, aFlatKnots, aPoles, nullptr);
  aCache->BuildCache(0.5, aFlatKnots, aPoles, nullptr);

  for (double u = 0.0; u <= 1.0; u += 0.1)
  {
    gp_Pnt aCachePnt, aDirectPnt;
    gp_Vec aCacheTan, aDirectTan;
    gp_Vec aCacheCurv, aDirectCurv;
    gp_Vec aCacheTors, aDirectTors;

    if (!aCache->IsCacheValid(u))
    {
      aCache->BuildCache(u, aFlatKnots, aPoles, nullptr);
    }
    aCache->D3(u, aCachePnt, aCacheTan, aCacheCurv, aCacheTors);

    BSplCLib::D3(u,
                 0,
                 aDegree,
                 false,
                 aPoles,
                 nullptr,
                 aKnots,
                 &aMults,
                 aDirectPnt,
                 aDirectTan,
                 aDirectCurv,
                 aDirectTors);

    EXPECT_NEAR(aCachePnt.X(), aDirectPnt.X(), THE_TOLERANCE) << "D3 point X mismatch at u=" << u;

    EXPECT_NEAR(aCacheTan.X(), aDirectTan.X(), THE_TOLERANCE) << "D3 tangent X mismatch at u=" << u;

    EXPECT_NEAR(aCacheCurv.X(), aDirectCurv.X(), THE_TOLERANCE)
      << "D3 curvature X mismatch at u=" << u;

    EXPECT_NEAR(aCacheTors.X(), aDirectTors.X(), THE_TOLERANCE)
      << "D3 torsion X mismatch at u=" << u;
  }
}
