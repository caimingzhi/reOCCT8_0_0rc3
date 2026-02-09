

#include <gtest/gtest.h>

#include <Geom2d_BezierCurve.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>

class Geom2d_BezierCurve_Test : public ::testing::Test
{
protected:
  void SetUp() override
  {

    NCollection_Array1<gp_Pnt2d> aPoles(1, 4);
    aPoles(1) = gp_Pnt2d(0, 0);
    aPoles(2) = gp_Pnt2d(1, 1);
    aPoles(3) = gp_Pnt2d(2, 1);
    aPoles(4) = gp_Pnt2d(3, 0);

    myOriginalCurve = new Geom2d_BezierCurve(aPoles);
  }

  occ::handle<Geom2d_BezierCurve> myOriginalCurve;
};

TEST_F(Geom2d_BezierCurve_Test, CopyConstructorBasicProperties)
{

  occ::handle<Geom2d_BezierCurve> aCopiedCurve = new Geom2d_BezierCurve(*myOriginalCurve);

  EXPECT_EQ(myOriginalCurve->Degree(), aCopiedCurve->Degree());
  EXPECT_EQ(myOriginalCurve->NbPoles(), aCopiedCurve->NbPoles());
  EXPECT_EQ(myOriginalCurve->IsRational(), aCopiedCurve->IsRational());
  EXPECT_EQ(myOriginalCurve->IsClosed(), aCopiedCurve->IsClosed());
}

TEST_F(Geom2d_BezierCurve_Test, CopyConstructorPoles)
{
  occ::handle<Geom2d_BezierCurve> aCopiedCurve = new Geom2d_BezierCurve(*myOriginalCurve);

  for (int i = 1; i <= myOriginalCurve->NbPoles(); ++i)
  {
    gp_Pnt2d anOrigPole = myOriginalCurve->Pole(i);
    gp_Pnt2d aCopyPole  = aCopiedCurve->Pole(i);
    EXPECT_TRUE(anOrigPole.IsEqual(aCopyPole, 1e-10));
  }
}

TEST_F(Geom2d_BezierCurve_Test, CopyMethodUsesOptimizedConstructor)
{

  occ::handle<Geom2d_Geometry>    aCopiedGeom  = myOriginalCurve->Copy();
  occ::handle<Geom2d_BezierCurve> aCopiedCurve = occ::down_cast<Geom2d_BezierCurve>(aCopiedGeom);

  EXPECT_FALSE(aCopiedCurve.IsNull());

  EXPECT_EQ(myOriginalCurve->Degree(), aCopiedCurve->Degree());
  EXPECT_EQ(myOriginalCurve->NbPoles(), aCopiedCurve->NbPoles());

  for (double u = 0.0; u <= 1.0; u += 0.25)
  {
    gp_Pnt2d anOrigPnt = myOriginalCurve->Value(u);
    gp_Pnt2d aCopyPnt  = aCopiedCurve->Value(u);
    EXPECT_TRUE(anOrigPnt.IsEqual(aCopyPnt, 1e-10));
  }
}

TEST_F(Geom2d_BezierCurve_Test, RationalCurveCopyConstructor)
{

  NCollection_Array1<gp_Pnt2d> aPoles(1, 3);
  aPoles(1) = gp_Pnt2d(0, 0);
  aPoles(2) = gp_Pnt2d(1, 1);
  aPoles(3) = gp_Pnt2d(2, 0);

  NCollection_Array1<double> aWeights(1, 3);
  aWeights(1) = 1.0;
  aWeights(2) = 2.0;
  aWeights(3) = 1.0;

  occ::handle<Geom2d_BezierCurve> aRationalCurve  = new Geom2d_BezierCurve(aPoles, aWeights);
  occ::handle<Geom2d_BezierCurve> aCopiedRational = new Geom2d_BezierCurve(*aRationalCurve);

  EXPECT_TRUE(aCopiedRational->IsRational());

  for (int i = 1; i <= aRationalCurve->NbPoles(); ++i)
  {
    EXPECT_DOUBLE_EQ(aRationalCurve->Weight(i), aCopiedRational->Weight(i));
  }
}

TEST_F(Geom2d_BezierCurve_Test, CopyIndependence)
{
  occ::handle<Geom2d_BezierCurve> aCopiedCurve = new Geom2d_BezierCurve(*myOriginalCurve);

  gp_Pnt2d aNewPole(10, 10);
  myOriginalCurve->SetPole(2, aNewPole);

  gp_Pnt2d anOrigPole = aCopiedCurve->Pole(2);
  EXPECT_FALSE(anOrigPole.IsEqual(aNewPole, 1e-10));
}
