

#include <IntAna_IntQuadQuad.hpp>
#include <IntAna_Quadric.hpp>
#include <gp_Sphere.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Cone.hpp>
#include <gp_Pln.hpp>
#include <gp_Ax3.hpp>

#include <gtest/gtest.h>

class IntAna_IntQuadQuad_Test : public ::testing::Test
{
protected:
  void SetUp() override
  {

    gp_Pnt anOrigin(0, 0, 0);
    gp_Dir aZDir(gp_Dir::D::Z);
    gp_Dir anXDir(gp_Dir::D::X);
    gp_Ax3 anAxis(anOrigin, aZDir, anXDir);

    mySphere1 = gp_Sphere(anAxis, 5.0);

    myCylinder1 = gp_Cylinder(anAxis, 3.0);

    myCone1 = gp_Cone(anAxis, M_PI / 6, 2.0);

    gp_Pnt aPlaneOrigin(0, 0, 2);
    myPlane1 = gp_Pln(aPlaneOrigin, aZDir);
  }

  gp_Sphere   mySphere1;
  gp_Cylinder myCylinder1;
  gp_Cone     myCone1;
  gp_Pln      myPlane1;
};

TEST_F(IntAna_IntQuadQuad_Test, CylinderVsSphereIntersection)
{
  IntAna_Quadric aSphereQuad(mySphere1);

  IntAna_IntQuadQuad anIntersector(myCylinder1, aSphereQuad, 1e-7);

  EXPECT_TRUE(anIntersector.IsDone());
  EXPECT_FALSE(anIntersector.IdenticalElements());

  EXPECT_GT(anIntersector.NbCurve(), 0);

  for (int i = 1; i <= anIntersector.NbCurve(); i++)
  {

    EXPECT_NO_THROW(anIntersector.Curve(i));
  }
}

TEST_F(IntAna_IntQuadQuad_Test, NextCurveMethodCorrectness)
{
  IntAna_Quadric aSphereQuad(mySphere1);

  IntAna_IntQuadQuad anIntersector(myCylinder1, aSphereQuad, 1e-7);

  EXPECT_TRUE(anIntersector.IsDone());

  for (int i = 1; i <= anIntersector.NbCurve(); i++)
  {

    bool aHasNext = anIntersector.HasNextCurve(i);

    if (aHasNext)
    {
      bool anOpposite;
      int  aNextIdx = anIntersector.NextCurve(i, anOpposite);

      EXPECT_GT(aNextIdx, 0);
      EXPECT_LE(aNextIdx, anIntersector.NbCurve());
      EXPECT_NE(aNextIdx, i);
    }
  }
}

TEST_F(IntAna_IntQuadQuad_Test, NextCurveBoundaryConditions)
{
  IntAna_Quadric aSphereQuad(mySphere1);

  IntAna_IntQuadQuad anIntersector(myCylinder1, aSphereQuad, 1e-7);

  EXPECT_TRUE(anIntersector.IsDone());

  EXPECT_THROW(anIntersector.HasNextCurve(0), Standard_OutOfRange);
  EXPECT_THROW(anIntersector.HasNextCurve(anIntersector.NbCurve() + 1), Standard_OutOfRange);

  for (int i = 1; i <= anIntersector.NbCurve(); i++)
  {
    if (!anIntersector.HasNextCurve(i))
    {
      bool anOpposite;
      EXPECT_THROW(anIntersector.NextCurve(i, anOpposite), Standard_DomainError);
    }
  }
}

TEST_F(IntAna_IntQuadQuad_Test, ConnectedCurvesScenario)
{

  gp_Pnt aCenter1(0, 0, 0);
  gp_Pnt aCenter2(3, 0, 0);
  gp_Dir aZDir(gp_Dir::D::Z);
  gp_Dir anXDir(gp_Dir::D::X);
  gp_Ax3 anAxis1(aCenter1, aZDir, anXDir);
  gp_Ax3 anAxis2(aCenter2, aZDir, anXDir);

  gp_Sphere aSphere1(anAxis1, 2.0);
  gp_Sphere aSphere2(anAxis2, 2.0);

  IntAna_Quadric aSphere2Quad(aSphere2);

  IntAna_IntQuadQuad anIntersector;
  anIntersector.Perform(gp_Cylinder(anAxis1, 2.0), aSphere2Quad, 1e-7);

  EXPECT_TRUE(anIntersector.IsDone());

  EXPECT_FALSE(anIntersector.IdenticalElements());

  for (int i = 1; i <= anIntersector.NbCurve(); i++)
  {
    if (anIntersector.HasNextCurve(i))
    {
      bool anOpposite;
      int  aNextIdx = anIntersector.NextCurve(i, anOpposite);

      EXPECT_GT(aNextIdx, 0);
      EXPECT_LE(aNextIdx, anIntersector.NbCurve());

      if (anIntersector.HasNextCurve(aNextIdx))
      {
        bool aReverseOpposite;
        int  aReverseNext = anIntersector.NextCurve(aNextIdx, aReverseOpposite);

        EXPECT_GT(aReverseNext, 0);
        EXPECT_LE(aReverseNext, anIntersector.NbCurve());
      }
    }
  }
}

TEST_F(IntAna_IntQuadQuad_Test, IndexingConsistencyTest)
{

  IntAna_Quadric aSphereQuad(mySphere1);

  IntAna_IntQuadQuad anIntersector(myCylinder1, aSphereQuad, 1e-7);

  EXPECT_TRUE(anIntersector.IsDone());

  for (int i = 1; i <= anIntersector.NbCurve(); i++)
  {

    bool aHasNext = anIntersector.HasNextCurve(i);

    if (aHasNext)
    {
      bool anOpposite;

      int aNextIdx = anIntersector.NextCurve(i, anOpposite);

      EXPECT_GT(aNextIdx, 0);
      EXPECT_LE(aNextIdx, anIntersector.NbCurve());
    }
  }
}
