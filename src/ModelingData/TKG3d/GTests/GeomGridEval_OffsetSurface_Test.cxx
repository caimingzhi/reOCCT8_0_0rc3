

#include <gtest/gtest.h>

#include <Geom_CylindricalSurface.hpp>
#include <Geom_OffsetSurface.hpp>
#include <Geom_Plane.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomGridEval_OffsetSurface.hpp>
#include <GeomGridEval_Surface.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <NCollection_Array1.hpp>

#include <cmath>

namespace
{
  const double THE_TOLERANCE = 1e-9;

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

TEST(GeomGridEval_OffsetSurfaceTest, PlaneOffset)
{

  occ::handle<Geom_Plane> aPlane = new Geom_Plane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));

  occ::handle<Geom_OffsetSurface> anOffset = new Geom_OffsetSurface(aPlane, 10.0);

  GeomGridEval_OffsetSurface anEval(anOffset);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 10.0, 5);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 10.0, 5);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 5; ++j)
    {
      gp_Pnt aExpected = anOffset->Value(aUParams.Value(i), aVParams.Value(j));
      EXPECT_NEAR(aGrid.Value(i, j).Distance(aExpected), 0.0, THE_TOLERANCE);
      EXPECT_NEAR(aGrid.Value(i, j).Z(), 10.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_OffsetSurfaceTest, CylinderOffset)
{

  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 5.0);

  occ::handle<Geom_OffsetSurface> anOffset = new Geom_OffsetSurface(aCyl, 2.0);

  GeomGridEval_OffsetSurface anEval(anOffset);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 9);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 5);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  for (int i = 1; i <= 9; ++i)
  {
    for (int j = 1; j <= 5; ++j)
    {
      gp_Pnt aExpected = anOffset->Value(aUParams.Value(i), aVParams.Value(j));
      EXPECT_NEAR(aGrid.Value(i, j).Distance(aExpected), 0.0, THE_TOLERANCE);

      double aDist = std::sqrt(aGrid.Value(i, j).X() * aGrid.Value(i, j).X()
                               + aGrid.Value(i, j).Y() * aGrid.Value(i, j).Y());
      EXPECT_NEAR(aDist, 7.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_OffsetSurfaceTest, DerivativeD1)
{

  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 5.0);
  occ::handle<Geom_OffsetSurface> anOffset = new Geom_OffsetSurface(aCyl, 2.0);

  GeomGridEval_OffsetSurface anEval(anOffset);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 5);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 3);

  NCollection_Array2<GeomGridEval::SurfD1> aGrid = anEval.EvaluateGridD1(aUParams, aVParams);

  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      gp_Pnt aPnt;
      gp_Vec aD1U, aD1V;
      anOffset->D1(aUParams.Value(i), aVParams.Value(j), aPnt, aD1U, aD1V);

      EXPECT_NEAR(aGrid.Value(i, j).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D1U - aD1U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D1V - aD1V).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_OffsetSurfaceTest, NestedDispatch)
{

  occ::handle<Geom_Plane>         aPlane   = new Geom_Plane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  occ::handle<Geom_OffsetSurface> anOffset = new Geom_OffsetSurface(aPlane, 5.0);

  GeomGridEval_Surface anEval;
  anEval.Initialize(anOffset);

  EXPECT_TRUE(anEval.IsInitialized());

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 1.0, 3);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 1.0, 3);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);
  EXPECT_EQ(aGrid.RowLength(), 3);
  EXPECT_EQ(aGrid.ColLength(), 3);

  EXPECT_NEAR(aGrid.Value(1, 1).Z(), 5.0, THE_TOLERANCE);
}

TEST(GeomGridEval_OffsetSurfaceTest, DerivativeD2)
{

  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 5.0);
  occ::handle<Geom_OffsetSurface> anOffset = new Geom_OffsetSurface(aCyl, 2.0);

  GeomGridEval_OffsetSurface anEval(anOffset);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 5);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 3);

  NCollection_Array2<GeomGridEval::SurfD2> aGrid = anEval.EvaluateGridD2(aUParams, aVParams);

  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      gp_Pnt aPnt;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV;
      anOffset->D2(aUParams.Value(i), aVParams.Value(j), aPnt, aD1U, aD1V, aD2U, aD2V, aD2UV);

      EXPECT_NEAR(aGrid.Value(i, j).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D1U - aD1U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D1V - aD1V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D2U - aD2U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D2V - aD2V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D2UV - aD2UV).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_OffsetSurfaceTest, DerivativeD3)
{

  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 5.0);
  occ::handle<Geom_OffsetSurface> anOffset = new Geom_OffsetSurface(aCyl, 2.0);

  GeomGridEval_OffsetSurface anEval(anOffset);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 5);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 3);

  NCollection_Array2<GeomGridEval::SurfD3> aGrid = anEval.EvaluateGridD3(aUParams, aVParams);

  GeomAdaptor_Surface anAdaptor(anOffset);
  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      gp_Pnt aPnt;
      gp_Vec aD1U, aD1V, aD2U, aD2V, aD2UV, aD3U, aD3V, aD3UUV, aD3UVV;
      anAdaptor.D3(aUParams.Value(i),
                   aVParams.Value(j),
                   aPnt,
                   aD1U,
                   aD1V,
                   aD2U,
                   aD2V,
                   aD2UV,
                   aD3U,
                   aD3V,
                   aD3UUV,
                   aD3UVV);

      EXPECT_NEAR(aGrid.Value(i, j).Point.Distance(aPnt), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D1U - aD1U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D1V - aD1V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D2U - aD2U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D2V - aD2V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D2UV - aD2UV).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D3U - aD3U).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D3V - aD3V).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D3UUV - aD3UUV).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGrid.Value(i, j).D3UVV - aD3UVV).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_OffsetSurfaceTest, DerivativeDN_U1V0)
{

  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 5.0);
  occ::handle<Geom_OffsetSurface> anOffset = new Geom_OffsetSurface(aCyl, 2.0);

  GeomGridEval_OffsetSurface anEval(anOffset);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 5);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 3);

  NCollection_Array2<gp_Vec> aGrid = anEval.EvaluateGridDN(aUParams, aVParams, 1, 0);

  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      gp_Vec aExpected = anOffset->DN(aUParams.Value(i), aVParams.Value(j), 1, 0);
      EXPECT_NEAR((aGrid.Value(i, j) - aExpected).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_OffsetSurfaceTest, DerivativeDN_U0V1)
{

  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 5.0);
  occ::handle<Geom_OffsetSurface> anOffset = new Geom_OffsetSurface(aCyl, 2.0);

  GeomGridEval_OffsetSurface anEval(anOffset);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 5);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 3);

  NCollection_Array2<gp_Vec> aGrid = anEval.EvaluateGridDN(aUParams, aVParams, 0, 1);

  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      gp_Vec aExpected = anOffset->DN(aUParams.Value(i), aVParams.Value(j), 0, 1);
      EXPECT_NEAR((aGrid.Value(i, j) - aExpected).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_OffsetSurfaceTest, DerivativeDN_U1V1)
{

  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 5.0);
  occ::handle<Geom_OffsetSurface> anOffset = new Geom_OffsetSurface(aCyl, 2.0);

  GeomGridEval_OffsetSurface anEval(anOffset);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 5);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 3);

  NCollection_Array2<gp_Vec> aGrid = anEval.EvaluateGridDN(aUParams, aVParams, 1, 1);

  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      gp_Vec aExpected = anOffset->DN(aUParams.Value(i), aVParams.Value(j), 1, 1);
      EXPECT_NEAR((aGrid.Value(i, j) - aExpected).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_OffsetSurfaceTest, DerivativeDN_U2V0)
{

  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 5.0);
  occ::handle<Geom_OffsetSurface> anOffset = new Geom_OffsetSurface(aCyl, 2.0);

  GeomGridEval_OffsetSurface anEval(anOffset);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 5);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 3);

  NCollection_Array2<gp_Vec> aGrid = anEval.EvaluateGridDN(aUParams, aVParams, 2, 0);

  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      gp_Vec aExpected = anOffset->DN(aUParams.Value(i), aVParams.Value(j), 2, 0);
      EXPECT_NEAR((aGrid.Value(i, j) - aExpected).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_OffsetSurfaceTest, DerivativeDN_PlaneOffset)
{

  occ::handle<Geom_Plane>         aPlane   = new Geom_Plane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  occ::handle<Geom_OffsetSurface> anOffset = new Geom_OffsetSurface(aPlane, 10.0);

  GeomGridEval_OffsetSurface anEval(anOffset);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 10.0, 5);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 10.0, 5);

  NCollection_Array2<gp_Vec> aGridU = anEval.EvaluateGridDN(aUParams, aVParams, 1, 0);
  NCollection_Array2<gp_Vec> aGridV = anEval.EvaluateGridDN(aUParams, aVParams, 0, 1);

  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 5; ++j)
    {
      gp_Vec aExpectedU = anOffset->DN(aUParams.Value(i), aVParams.Value(j), 1, 0);
      gp_Vec aExpectedV = anOffset->DN(aUParams.Value(i), aVParams.Value(j), 0, 1);
      EXPECT_NEAR((aGridU.Value(i, j) - aExpectedU).Magnitude(), 0.0, THE_TOLERANCE);
      EXPECT_NEAR((aGridV.Value(i, j) - aExpectedV).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }

  NCollection_Array2<gp_Vec> aGrid2U = anEval.EvaluateGridDN(aUParams, aVParams, 2, 0);
  for (int i = 1; i <= 5; ++i)
  {
    for (int j = 1; j <= 5; ++j)
    {
      EXPECT_NEAR(aGrid2U.Value(i, j).Magnitude(), 0.0, THE_TOLERANCE);
    }
  }
}

TEST(GeomGridEval_OffsetSurfaceTest, IsolineU_CompareToGeomD0)
{

  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 5.0);
  occ::handle<Geom_OffsetSurface> anOffset = new Geom_OffsetSurface(aCyl, 2.0);

  GeomGridEval_OffsetSurface anEval(anOffset);

  NCollection_Array1<double> aUParams(1, 1);
  aUParams.SetValue(1, M_PI / 4);
  NCollection_Array1<double> aVParams = CreateUniformParams(0.0, 5.0, 15);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  EXPECT_EQ(aGrid.RowLength(), 15);
  EXPECT_EQ(aGrid.ColLength(), 1);

  for (int j = 1; j <= 15; ++j)
  {
    gp_Pnt aExpected;
    anOffset->D0(aUParams.Value(1), aVParams.Value(j), aExpected);
    EXPECT_NEAR(aGrid.Value(1, j).Distance(aExpected), 0.0, THE_TOLERANCE);
  }
}

TEST(GeomGridEval_OffsetSurfaceTest, IsolineV_CompareToGeomD0)
{

  occ::handle<Geom_CylindricalSurface> aCyl =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 5.0);
  occ::handle<Geom_OffsetSurface> anOffset = new Geom_OffsetSurface(aCyl, 2.0);

  GeomGridEval_OffsetSurface anEval(anOffset);

  NCollection_Array1<double> aUParams = CreateUniformParams(0.0, 2 * M_PI, 15);
  NCollection_Array1<double> aVParams(1, 1);
  aVParams.SetValue(1, 2.5);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  EXPECT_EQ(aGrid.RowLength(), 1);
  EXPECT_EQ(aGrid.ColLength(), 15);

  for (int i = 1; i <= 15; ++i)
  {
    gp_Pnt aExpected;
    anOffset->D0(aUParams.Value(i), aVParams.Value(1), aExpected);
    EXPECT_NEAR(aGrid.Value(i, 1).Distance(aExpected), 0.0, THE_TOLERANCE);
  }
}

TEST(GeomGridEval_OffsetSurfaceTest, IsolinePlane_CompareToGeomD0)
{

  occ::handle<Geom_Plane>         aPlane   = new Geom_Plane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  occ::handle<Geom_OffsetSurface> anOffset = new Geom_OffsetSurface(aPlane, 3.0);

  GeomGridEval_OffsetSurface anEval(anOffset);

  NCollection_Array1<double> aUParams(1, 1);
  aUParams.SetValue(1, 5.0);
  NCollection_Array1<double> aVParams = CreateUniformParams(-10.0, 10.0, 20);

  NCollection_Array2<gp_Pnt> aGrid = anEval.EvaluateGrid(aUParams, aVParams);

  for (int j = 1; j <= 20; ++j)
  {
    gp_Pnt aExpected;
    anOffset->D0(aUParams.Value(1), aVParams.Value(j), aExpected);
    EXPECT_NEAR(aGrid.Value(1, j).Distance(aExpected), 0.0, THE_TOLERANCE);
  }
}
