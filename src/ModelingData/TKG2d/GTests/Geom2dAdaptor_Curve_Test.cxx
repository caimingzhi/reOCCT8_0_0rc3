

#include <gtest/gtest.h>

#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>

class Geom2dAdaptor_Curve_Test : public ::testing::Test
{
protected:
  void SetUp() override
  {

    gp_Pnt2d aP1(0.0, 0.0);
    gp_Lin2d aLine(aP1, gp_Dir2d(1.0, 1.0));
    myLine = new Geom2d_Line(aLine);

    gp_Pnt2d  aCenter(5.0, 5.0);
    gp_Circ2d aCirc(gp_Ax2d(aCenter, gp_Dir2d(1.0, 0.0)), 3.0);
    myCircle = new Geom2d_Circle(aCirc);
  }

  occ::handle<Geom2d_Line>   myLine;
  occ::handle<Geom2d_Circle> myCircle;
};

TEST_F(Geom2dAdaptor_Curve_Test, Load_ValidParameters_Success)
{

  Geom2dAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myLine, 0.0, 10.0));

  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), 0.0);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), 10.0);
}

TEST_F(Geom2dAdaptor_Curve_Test, Load_EqualParameters_Success)
{

  Geom2dAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myLine, 5.0, 5.0));

  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), 5.0);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), 5.0);

  gp_Pnt2d aP1 = anAdaptor.Value(5.0);
  gp_Pnt2d aP2 = myLine->Value(5.0);
  EXPECT_TRUE(aP1.IsEqual(aP2, Precision::Confusion()));
}

TEST_F(Geom2dAdaptor_Curve_Test, Load_ParametersWithinConfusion_Success)
{

  const double aParam1 = 5.0;
  const double aParam2 = 5.0 + Precision::Confusion() * 0.5;

  Geom2dAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myLine, aParam1, aParam2));

  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), aParam1);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), aParam2);
}

TEST_F(Geom2dAdaptor_Curve_Test, Load_ParametersAtConfusionBoundary_Success)
{

  const double aParam1 = 5.0;
  const double aParam2 = 5.0 + Precision::Confusion();

  Geom2dAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myLine, aParam1, aParam2));

  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), aParam1);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), aParam2);
}

TEST_F(Geom2dAdaptor_Curve_Test, Load_FirstGreaterThanLastWithinConfusion_Success)
{

  const double aParam1 = 5.0 + Precision::Confusion() * 0.5;
  const double aParam2 = 5.0;

  Geom2dAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myLine, aParam1, aParam2));

  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), aParam1);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), aParam2);
}

TEST_F(Geom2dAdaptor_Curve_Test, Load_FirstGreaterThanLastBeyondConfusion_ThrowsException)
{

  const double aParam1 = 10.0;
  const double aParam2 = 5.0;

  Geom2dAdaptor_Curve anAdaptor;
  EXPECT_THROW(anAdaptor.Load(myLine, aParam1, aParam2), Standard_ConstructionError);
}

TEST_F(Geom2dAdaptor_Curve_Test, Load_FirstSlightlyGreaterThanLast_ThrowsException)
{

  const double aParam1 = 5.0;
  const double aParam2 = 5.0 - Precision::Confusion() * 2.0;

  Geom2dAdaptor_Curve anAdaptor;
  EXPECT_THROW(anAdaptor.Load(myLine, aParam1, aParam2), Standard_ConstructionError);
}

TEST_F(Geom2dAdaptor_Curve_Test, Constructor_DegeneratedCurve_Success)
{

  EXPECT_NO_THROW(Geom2dAdaptor_Curve anAdaptor(myCircle, 0.0, 0.0));

  Geom2dAdaptor_Curve anAdaptor(myCircle, 0.0, 0.0);
  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), 0.0);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), 0.0);
}

TEST_F(Geom2dAdaptor_Curve_Test, Constructor_InvalidParameters_ThrowsException)
{

  EXPECT_THROW(Geom2dAdaptor_Curve anAdaptor(myCircle, 10.0, 0.0), Standard_ConstructionError);
}

TEST_F(Geom2dAdaptor_Curve_Test, Load_NullCurve_ThrowsException)
{

  occ::handle<Geom2d_Curve> aNullCurve;
  Geom2dAdaptor_Curve       anAdaptor;

  EXPECT_THROW(anAdaptor.Load(aNullCurve, 0.0, 10.0), Standard_NullObject);
}

TEST_F(Geom2dAdaptor_Curve_Test, DegeneratedCurve_CircleAtZeroLength_Success)
{

  const double aParam = M_PI;

  Geom2dAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myCircle, aParam, aParam));

  gp_Pnt2d aPoint         = anAdaptor.Value(aParam);
  gp_Pnt2d aExpectedPoint = myCircle->Value(aParam);

  EXPECT_TRUE(aPoint.IsEqual(aExpectedPoint, Precision::Confusion()));
  EXPECT_TRUE(anAdaptor.IsClosed() || anAdaptor.FirstParameter() == anAdaptor.LastParameter());
}

TEST_F(Geom2dAdaptor_Curve_Test, DegeneratedCurve_TrimmedCurve_Success)
{

  occ::handle<Geom2d_TrimmedCurve> aTrimmedCurve = new Geom2d_TrimmedCurve(myLine, 0.0, 20.0);

  const double        aParam = 10.0;
  Geom2dAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(aTrimmedCurve, aParam, aParam));

  EXPECT_DOUBLE_EQ(anAdaptor.FirstParameter(), aParam);
  EXPECT_DOUBLE_EQ(anAdaptor.LastParameter(), aParam);
}

TEST_F(Geom2dAdaptor_Curve_Test, ToleranceBoundary_NegativeCase_ThrowsException)
{

  const double aParam1 = 5.0;
  const double aParam2 = 5.0 - Precision::Confusion() - 1e-10;

  Geom2dAdaptor_Curve anAdaptor;
  EXPECT_THROW(anAdaptor.Load(myLine, aParam1, aParam2), Standard_ConstructionError);
}

TEST_F(Geom2dAdaptor_Curve_Test, LoadWithoutParameters_Success)
{

  Geom2dAdaptor_Curve anAdaptor;
  EXPECT_NO_THROW(anAdaptor.Load(myCircle));

  EXPECT_NEAR(anAdaptor.FirstParameter(), myCircle->FirstParameter(), Precision::Confusion());
  EXPECT_NEAR(anAdaptor.LastParameter(), myCircle->LastParameter(), Precision::Confusion());
  EXPECT_TRUE(anAdaptor.IsPeriodic());
}
