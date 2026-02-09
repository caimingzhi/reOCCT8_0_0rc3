

#include <Geom_BSplineCurve.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>

#include <gtest/gtest.h>

class Geom_BSplineCurve_Test : public ::testing::Test
{
protected:
  void SetUp() override
  {

    NCollection_Array1<gp_Pnt> aPoles(1, 4);
    aPoles(1) = gp_Pnt(0, 0, 0);
    aPoles(2) = gp_Pnt(1, 1, 0);
    aPoles(3) = gp_Pnt(2, 1, 0);
    aPoles(4) = gp_Pnt(3, 0, 0);

    NCollection_Array1<double> aKnots(1, 2);
    aKnots(1) = 0.0;
    aKnots(2) = 1.0;

    NCollection_Array1<int> aMults(1, 2);
    aMults(1) = 4;
    aMults(2) = 4;

    myOriginalCurve = new Geom_BSplineCurve(aPoles, aKnots, aMults, 3);
  }

  occ::handle<Geom_BSplineCurve> myOriginalCurve;
};

TEST_F(Geom_BSplineCurve_Test, CopyConstructorBasicProperties)
{

  occ::handle<Geom_BSplineCurve> aCopiedCurve = new Geom_BSplineCurve(*myOriginalCurve);

  EXPECT_EQ(myOriginalCurve->Degree(), aCopiedCurve->Degree());
  EXPECT_EQ(myOriginalCurve->NbPoles(), aCopiedCurve->NbPoles());
  EXPECT_EQ(myOriginalCurve->NbKnots(), aCopiedCurve->NbKnots());
  EXPECT_EQ(myOriginalCurve->IsPeriodic(), aCopiedCurve->IsPeriodic());
  EXPECT_EQ(myOriginalCurve->IsRational(), aCopiedCurve->IsRational());
}

TEST_F(Geom_BSplineCurve_Test, CopyConstructorPoles)
{
  occ::handle<Geom_BSplineCurve> aCopiedCurve = new Geom_BSplineCurve(*myOriginalCurve);

  for (int i = 1; i <= myOriginalCurve->NbPoles(); ++i)
  {
    gp_Pnt anOrigPole = myOriginalCurve->Pole(i);
    gp_Pnt aCopyPole  = aCopiedCurve->Pole(i);
    EXPECT_TRUE(anOrigPole.IsEqual(aCopyPole, 1e-10));
  }
}

TEST_F(Geom_BSplineCurve_Test, CopyConstructorKnots)
{
  occ::handle<Geom_BSplineCurve> aCopiedCurve = new Geom_BSplineCurve(*myOriginalCurve);

  for (int i = 1; i <= myOriginalCurve->NbKnots(); ++i)
  {
    EXPECT_DOUBLE_EQ(myOriginalCurve->Knot(i), aCopiedCurve->Knot(i));
    EXPECT_EQ(myOriginalCurve->Multiplicity(i), aCopiedCurve->Multiplicity(i));
  }
}

TEST_F(Geom_BSplineCurve_Test, CopyMethodUsesOptimizedConstructor)
{

  occ::handle<Geom_Geometry>     aCopiedGeom  = myOriginalCurve->Copy();
  occ::handle<Geom_BSplineCurve> aCopiedCurve = occ::down_cast<Geom_BSplineCurve>(aCopiedGeom);

  EXPECT_FALSE(aCopiedCurve.IsNull());

  EXPECT_EQ(myOriginalCurve->Degree(), aCopiedCurve->Degree());
  EXPECT_EQ(myOriginalCurve->NbPoles(), aCopiedCurve->NbPoles());

  for (double u = 0.0; u <= 1.0; u += 0.25)
  {
    gp_Pnt anOrigPnt = myOriginalCurve->Value(u);
    gp_Pnt aCopyPnt  = aCopiedCurve->Value(u);
    EXPECT_TRUE(anOrigPnt.IsEqual(aCopyPnt, 1e-10));
  }
}

TEST_F(Geom_BSplineCurve_Test, RationalCurveCopyConstructor)
{

  NCollection_Array1<gp_Pnt> aPoles(1, 3);
  aPoles(1) = gp_Pnt(0, 0, 0);
  aPoles(2) = gp_Pnt(1, 1, 0);
  aPoles(3) = gp_Pnt(2, 0, 0);

  NCollection_Array1<double> aWeights(1, 3);
  aWeights(1) = 1.0;
  aWeights(2) = 2.0;
  aWeights(3) = 1.0;

  NCollection_Array1<double> aKnots(1, 2);
  aKnots(1) = 0.0;
  aKnots(2) = 1.0;

  NCollection_Array1<int> aMults(1, 2);
  aMults(1) = 3;
  aMults(2) = 3;

  occ::handle<Geom_BSplineCurve> aRationalCurve =
    new Geom_BSplineCurve(aPoles, aWeights, aKnots, aMults, 2);
  occ::handle<Geom_BSplineCurve> aCopiedRational = new Geom_BSplineCurve(*aRationalCurve);

  EXPECT_TRUE(aCopiedRational->IsRational());

  for (int i = 1; i <= aRationalCurve->NbPoles(); ++i)
  {
    EXPECT_DOUBLE_EQ(aRationalCurve->Weight(i), aCopiedRational->Weight(i));
  }
}
