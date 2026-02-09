

#include <gtest/gtest.h>

#include <Geom2d_OffsetCurve.hpp>
#include <Geom2d_Circle.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pnt2d.hpp>

class Geom2d_OffsetCurve_Test : public ::testing::Test
{
protected:
  void SetUp() override
  {

    gp_Circ2d                  aCircle(gp_Ax2d(gp_Pnt2d(0, 0), gp_Dir2d(gp_Dir2d::D::X)), 5.0);
    occ::handle<Geom2d_Circle> aBasisCurve = new Geom2d_Circle(aCircle);

    double anOffsetValue = 2.0;

    myOriginalCurve = new Geom2d_OffsetCurve(aBasisCurve, anOffsetValue);
  }

  occ::handle<Geom2d_OffsetCurve> myOriginalCurve;
};

TEST_F(Geom2d_OffsetCurve_Test, CopyConstructorBasicProperties)
{

  occ::handle<Geom2d_OffsetCurve> aCopiedCurve = new Geom2d_OffsetCurve(*myOriginalCurve);

  EXPECT_DOUBLE_EQ(myOriginalCurve->Offset(), aCopiedCurve->Offset());
  EXPECT_EQ(myOriginalCurve->IsPeriodic(), aCopiedCurve->IsPeriodic());
  EXPECT_EQ(myOriginalCurve->IsClosed(), aCopiedCurve->IsClosed());
}

TEST_F(Geom2d_OffsetCurve_Test, CopyConstructorBasisCurve)
{
  occ::handle<Geom2d_OffsetCurve> aCopiedCurve = new Geom2d_OffsetCurve(*myOriginalCurve);

  occ::handle<Geom2d_Curve> anOrigBasis = myOriginalCurve->BasisCurve();
  occ::handle<Geom2d_Curve> aCopyBasis  = aCopiedCurve->BasisCurve();

  EXPECT_NE(anOrigBasis.get(), aCopyBasis.get());

  EXPECT_DOUBLE_EQ(anOrigBasis->FirstParameter(), aCopyBasis->FirstParameter());
  EXPECT_DOUBLE_EQ(anOrigBasis->LastParameter(), aCopyBasis->LastParameter());
}

TEST_F(Geom2d_OffsetCurve_Test, CopyMethodUsesOptimizedConstructor)
{

  occ::handle<Geom2d_Geometry>    aCopiedGeom  = myOriginalCurve->Copy();
  occ::handle<Geom2d_OffsetCurve> aCopiedCurve = occ::down_cast<Geom2d_OffsetCurve>(aCopiedGeom);

  EXPECT_FALSE(aCopiedCurve.IsNull());

  EXPECT_DOUBLE_EQ(myOriginalCurve->Offset(), aCopiedCurve->Offset());

  double anUFirst = myOriginalCurve->FirstParameter();
  double anULast  = myOriginalCurve->LastParameter();
  double aStep    = (anULast - anUFirst) / 4.0;

  for (double u = anUFirst; u <= anULast; u += aStep)
  {
    gp_Pnt2d anOrigPnt = myOriginalCurve->Value(u);
    gp_Pnt2d aCopyPnt  = aCopiedCurve->Value(u);
    EXPECT_TRUE(anOrigPnt.IsEqual(aCopyPnt, 1e-10));
  }
}

TEST_F(Geom2d_OffsetCurve_Test, CopyIndependence)
{
  occ::handle<Geom2d_OffsetCurve> aCopiedCurve = new Geom2d_OffsetCurve(*myOriginalCurve);

  double anOrigOffset = aCopiedCurve->Offset();

  myOriginalCurve->SetOffsetValue(10.0);

  EXPECT_DOUBLE_EQ(aCopiedCurve->Offset(), anOrigOffset);
  EXPECT_NE(aCopiedCurve->Offset(), myOriginalCurve->Offset());
}
