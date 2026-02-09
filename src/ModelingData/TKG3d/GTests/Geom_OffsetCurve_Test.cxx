

#include <gtest/gtest.h>

#include <Geom_OffsetCurve.hpp>
#include <Geom_Circle.hpp>
#include <gp_Circ.hpp>
#include <gp_Ax2.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>

class Geom_OffsetCurve_Test : public ::testing::Test
{
protected:
  void SetUp() override
  {

    gp_Circ                  aCircle(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)), 5.0);
    occ::handle<Geom_Circle> aBasisCurve = new Geom_Circle(aCircle);

    gp_Dir anOffsetDir(gp_Dir::D::Z);
    double anOffsetValue = 2.0;

    myOriginalCurve = new Geom_OffsetCurve(aBasisCurve, anOffsetValue, anOffsetDir);
  }

  occ::handle<Geom_OffsetCurve> myOriginalCurve;
};

TEST_F(Geom_OffsetCurve_Test, CopyConstructorBasicProperties)
{

  occ::handle<Geom_OffsetCurve> aCopiedCurve = new Geom_OffsetCurve(*myOriginalCurve);

  EXPECT_DOUBLE_EQ(myOriginalCurve->Offset(), aCopiedCurve->Offset());
  EXPECT_TRUE(myOriginalCurve->Direction().IsEqual(aCopiedCurve->Direction(), 1e-10));
  EXPECT_EQ(myOriginalCurve->IsPeriodic(), aCopiedCurve->IsPeriodic());
  EXPECT_EQ(myOriginalCurve->IsClosed(), aCopiedCurve->IsClosed());
}

TEST_F(Geom_OffsetCurve_Test, CopyConstructorBasisCurve)
{
  occ::handle<Geom_OffsetCurve> aCopiedCurve = new Geom_OffsetCurve(*myOriginalCurve);

  occ::handle<Geom_Curve> anOrigBasis = myOriginalCurve->BasisCurve();
  occ::handle<Geom_Curve> aCopyBasis  = aCopiedCurve->BasisCurve();

  EXPECT_NE(anOrigBasis.get(), aCopyBasis.get());

  EXPECT_DOUBLE_EQ(anOrigBasis->FirstParameter(), aCopyBasis->FirstParameter());
  EXPECT_DOUBLE_EQ(anOrigBasis->LastParameter(), aCopyBasis->LastParameter());
}

TEST_F(Geom_OffsetCurve_Test, CopyMethodUsesOptimizedConstructor)
{

  occ::handle<Geom_Geometry>    aCopiedGeom  = myOriginalCurve->Copy();
  occ::handle<Geom_OffsetCurve> aCopiedCurve = occ::down_cast<Geom_OffsetCurve>(aCopiedGeom);

  EXPECT_FALSE(aCopiedCurve.IsNull());

  EXPECT_DOUBLE_EQ(myOriginalCurve->Offset(), aCopiedCurve->Offset());

  double anUFirst = myOriginalCurve->FirstParameter();
  double anULast  = myOriginalCurve->LastParameter();
  double aStep    = (anULast - anUFirst) / 4.0;

  for (double u = anUFirst; u <= anULast; u += aStep)
  {
    gp_Pnt anOrigPnt = myOriginalCurve->Value(u);
    gp_Pnt aCopyPnt  = aCopiedCurve->Value(u);
    EXPECT_TRUE(anOrigPnt.IsEqual(aCopyPnt, 1e-10));
  }
}

TEST_F(Geom_OffsetCurve_Test, CopyIndependence)
{
  occ::handle<Geom_OffsetCurve> aCopiedCurve = new Geom_OffsetCurve(*myOriginalCurve);

  double anOrigOffset = aCopiedCurve->Offset();

  myOriginalCurve->SetOffsetValue(10.0);

  EXPECT_DOUBLE_EQ(aCopiedCurve->Offset(), anOrigOffset);
  EXPECT_NE(aCopiedCurve->Offset(), myOriginalCurve->Offset());
}
