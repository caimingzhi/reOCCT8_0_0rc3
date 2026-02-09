

#include <gtest/gtest.h>

#include <GeomAdaptor_Curve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Line.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <gp_Circ.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>

class GeomAdaptor_Curve_Test : public ::testing::Test
{
protected:
  void SetUp() override
  {

    gp_Pnt aP1(0.0, 0.0, 0.0);
    gp_Lin aLine(aP1, gp_Dir(1.0, 1.0, 0.0));
    myLine = new Geom_Line(aLine);

    gp_Pnt  aCenter(5.0, 5.0, 0.0);
    gp_Circ aCirc(gp_Ax2(aCenter, gp_Dir(0.0, 0.0, 1.0)), 3.0);
    myCircle = new Geom_Circle(aCirc);
  }

  occ::handle<Geom_Line>   myLine;
  occ::handle<Geom_Circle> myCircle;
};

TEST_F(GeomAdaptor_Curve_Test, Load_ValidParameters_Success)
{

  GeomAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myLine, 0.0, 10.0));

  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), 0.0);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), 10.0);
}

TEST_F(GeomAdaptor_Curve_Test, Load_EqualParameters_Success)
{

  GeomAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myLine, 5.0, 5.0));

  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), 5.0);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), 5.0);

  gp_Pnt aP1 = anAdaptor.Value(5.0);
  gp_Pnt aP2 = myLine->Value(5.0);
  EXPECT_TRUE(aP1.IsEqual(aP2, Precision::Confusion()));
}

TEST_F(GeomAdaptor_Curve_Test, Load_ParametersWithinConfusion_Success)
{

  const double aParam1 = 5.0;
  const double aParam2 = 5.0 + Precision::Confusion() * 0.5;

  GeomAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myLine, aParam1, aParam2));

  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), aParam1);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), aParam2);
}

TEST_F(GeomAdaptor_Curve_Test, Load_ParametersAtConfusionBoundary_Success)
{

  const double aParam1 = 5.0;
  const double aParam2 = 5.0 + Precision::Confusion();

  GeomAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myLine, aParam1, aParam2));

  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), aParam1);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), aParam2);
}

TEST_F(GeomAdaptor_Curve_Test, Load_FirstGreaterThanLastWithinConfusion_Success)
{

  const double aParam1 = 5.0 + Precision::Confusion() * 0.5;
  const double aParam2 = 5.0;

  GeomAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myLine, aParam1, aParam2));

  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), aParam1);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), aParam2);
}

TEST_F(GeomAdaptor_Curve_Test, Load_FirstGreaterThanLastBeyondConfusion_ThrowsException)
{

  const double aParam1 = 10.0;
  const double aParam2 = 5.0;

  GeomAdaptor_Curve anAdaptor;
  EXPECT_THROW(anAdaptor.Load(myLine, aParam1, aParam2), Standard_ConstructionError);
}

TEST_F(GeomAdaptor_Curve_Test, Load_FirstSlightlyGreaterThanLast_ThrowsException)
{

  const double aParam1 = 5.0;
  const double aParam2 = 5.0 - Precision::Confusion() * 2.0;

  GeomAdaptor_Curve anAdaptor;
  EXPECT_THROW(anAdaptor.Load(myLine, aParam1, aParam2), Standard_ConstructionError);
}

TEST_F(GeomAdaptor_Curve_Test, Constructor_DegeneratedCurve_Success)
{

  EXPECT_NO_THROW(GeomAdaptor_Curve anAdaptor(myCircle, 0.0, 0.0));

  GeomAdaptor_Curve anAdaptor(myCircle, 0.0, 0.0);
  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), 0.0);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), 0.0);
}

TEST_F(GeomAdaptor_Curve_Test, Constructor_InvalidParameters_ThrowsException)
{

  EXPECT_THROW(GeomAdaptor_Curve anAdaptor(myCircle, 10.0, 0.0), Standard_ConstructionError);
}

TEST_F(GeomAdaptor_Curve_Test, Load_NullCurve_ThrowsException)
{

  occ::handle<Geom_Curve> aNullCurve;
  GeomAdaptor_Curve       anAdaptor;

  EXPECT_THROW(anAdaptor.Load(aNullCurve, 0.0, 10.0), Standard_NullObject);
}

TEST_F(GeomAdaptor_Curve_Test, DegeneratedCurve_CircleAtZeroLength_Success)
{

  const double aParam = M_PI;

  GeomAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myCircle, aParam, aParam));

  gp_Pnt aPoint         = anAdaptor.Value(aParam);
  gp_Pnt aExpectedPoint = myCircle->Value(aParam);

  EXPECT_TRUE(aPoint.IsEqual(aExpectedPoint, Precision::Confusion()));
  EXPECT_TRUE(anAdaptor.IsClosed() || anAdaptor.FirstParameter() == anAdaptor.LastParameter());
}

TEST_F(GeomAdaptor_Curve_Test, DegeneratedCurve_TrimmedCurve_Success)
{

  occ::handle<Geom_TrimmedCurve> aTrimmedCurve = new Geom_TrimmedCurve(myLine, 0.0, 20.0);

  const double      aParam = 10.0;
  GeomAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(aTrimmedCurve, aParam, aParam));

  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), aParam);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), aParam);
}

TEST_F(GeomAdaptor_Curve_Test, ToleranceBoundary_NegativeCase_ThrowsException)
{

  const double aParam1 = 5.0;
  const double aParam2 = 5.0 - Precision::Confusion() - 1e-10;

  GeomAdaptor_Curve anAdaptor;
  EXPECT_THROW(anAdaptor.Load(myLine, aParam1, aParam2), Standard_ConstructionError);
}

TEST_F(GeomAdaptor_Curve_Test, LoadWithoutParameters_Success)
{

  GeomAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myCircle));

  EXPECT_NEAR(anAdaptor.FirstParameter(), myCircle->FirstParameter(), Precision::Confusion());
  EXPECT_NEAR(anAdaptor.LastParameter(), myCircle->LastParameter(), Precision::Confusion());
  EXPECT_TRUE(anAdaptor.IsPeriodic());
}

TEST_F(GeomAdaptor_Curve_Test, DegeneratedCurve_MultipleLocations_Success)
{

  const double aParams[] = {0.0, 1.0, -5.0, 100.0, M_PI};

  for (const double aParam : aParams)
  {
    GeomAdaptor_Curve anAdaptor;
    EXPECT_NO_THROW(anAdaptor.Load(myLine, aParam, aParam));

    gp_Pnt aPoint1 = anAdaptor.Value(aParam);
    gp_Pnt aPoint2 = myLine->Value(aParam);
    EXPECT_TRUE(aPoint1.IsEqual(aPoint2, Precision::Confusion()));
  }
}

TEST_F(GeomAdaptor_Curve_Test, BoundaryConditions_VerySmallInterval_Success)
{

  const double aParam1 = 5.0;
  const double aParam2 = 5.0 + Precision::Confusion() + 1e-12;

  GeomAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myLine, aParam1, aParam2));

  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), aParam1);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), aParam2);
}

TEST_F(GeomAdaptor_Curve_Test, Constructor_WithValidRange_Success)
{

  const double aFirst = 0.0;
  const double aLast  = 2.0 * M_PI;

  EXPECT_NO_THROW(GeomAdaptor_Curve anAdaptor(myCircle, aFirst, aLast));

  GeomAdaptor_Curve anAdaptor(myCircle, aFirst, aLast);
  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), aFirst);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), aLast);
  EXPECT_EQ(anAdaptor.GetType(), GeomAbs_Circle);
}
