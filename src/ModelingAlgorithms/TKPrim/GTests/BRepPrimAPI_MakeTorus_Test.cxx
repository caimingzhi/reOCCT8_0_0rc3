

#include <BRep_Tool.hpp>
#include <BRepCheck_Analyzer.hpp>
#include <BRepPrimAPI_MakeTorus.hpp>
#include <Geom_Surface.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>

#include <gtest/gtest.h>

namespace
{

  bool createAndCheckPartialTorus(double theR1,
                                  double theR2,
                                  double theAngle1,
                                  double theAngle2,
                                  double theAngle = 2.0 * M_PI)
  {
    gp_Ax2                anAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
    BRepPrimAPI_MakeTorus aMakeTorus(anAxis, theR1, theR2, theAngle1, theAngle2, theAngle);
    TopoDS_Shape          aShape = aMakeTorus.Shape();

    if (!aMakeTorus.IsDone() || aShape.IsNull())
    {
      return false;
    }

    BRepCheck_Analyzer anAnalyzer(aShape);
    return anAnalyzer.IsValid();
  }

} // namespace

TEST(BRepPrimAPI_MakeTorusTest, FullTorus)
{
  const double R1 = 10.0;
  const double R2 = 2.0;

  BRepPrimAPI_MakeTorus aMakeTorus(R1, R2);
  TopoDS_Shape          aShape = aMakeTorus.Shape();

  ASSERT_TRUE(aMakeTorus.IsDone()) << "Full torus creation failed";
  ASSERT_FALSE(aShape.IsNull()) << "Resulting shape is null";

  BRepCheck_Analyzer anAnalyzer(aShape);
  EXPECT_TRUE(anAnalyzer.IsValid()) << "Full torus shape is not valid";

  int aFaceCount = 0;
  for (TopExp_Explorer anExp(aShape, TopAbs_FACE); anExp.More(); anExp.Next())
  {
    aFaceCount++;
  }
  EXPECT_EQ(aFaceCount, 1) << "Expected 1 face for full torus";
}

TEST(BRepPrimAPI_MakeTorusTest, PartialTorusAngleOnly)
{
  const double R1    = 10.0;
  const double R2    = 2.0;
  const double angle = M_PI;

  BRepPrimAPI_MakeTorus aMakeTorus(R1, R2, angle);
  TopoDS_Shape          aShape = aMakeTorus.Shape();

  ASSERT_TRUE(aMakeTorus.IsDone()) << "Partial torus (angle only) creation failed";
  ASSERT_FALSE(aShape.IsNull()) << "Resulting shape is null";

  BRepCheck_Analyzer anAnalyzer(aShape);
  EXPECT_TRUE(anAnalyzer.IsValid()) << "Partial torus (angle only) shape is not valid";

  int aFaceCount = 0;
  for (TopExp_Explorer anExp(aShape, TopAbs_FACE); anExp.More(); anExp.Next())
  {
    aFaceCount++;
  }
  EXPECT_EQ(aFaceCount, 3) << "Expected 3 faces for partial torus with angle only";
}

TEST(BRepPrimAPI_MakeTorusTest, LateralFaceParameterization)
{
  const double R1 = 5.0;
  const double R2 = 1.0;

  BRepPrimAPI_MakeTorus aMakeTorus(R1, R2);
  TopoDS_Shape          aShape = aMakeTorus.Shape();
  ASSERT_TRUE(aMakeTorus.IsDone());

  TopExp_Explorer anExp(aShape, TopAbs_FACE);
  ASSERT_TRUE(anExp.More()) << "No faces found";

  const TopoDS_Face&                aFace      = TopoDS::Face(anExp.Current());
  occ::handle<Geom_Surface>         aSurface   = BRep_Tool::Surface(aFace);
  occ::handle<Geom_ToroidalSurface> aTorusSurf = occ::down_cast<Geom_ToroidalSurface>(aSurface);

  ASSERT_FALSE(aTorusSurf.IsNull()) << "Lateral face is not a toroidal surface";

  EXPECT_NEAR(aTorusSurf->MajorRadius(), R1, 1e-10);
  EXPECT_NEAR(aTorusSurf->MinorRadius(), R2, 1e-10);

  gp_Pnt aPnt;
  aTorusSurf->D0(0.0, M_PI_2, aPnt);
  EXPECT_NEAR(aPnt.Z(), R2, 1e-10) << "At V=PI/2, Z should be +MinorRadius";

  aTorusSurf->D0(0.0, -M_PI_2, aPnt);
  EXPECT_NEAR(aPnt.Z(), -R2, 1e-10) << "At V=-PI/2, Z should be -MinorRadius";
}

TEST(BRepPrimAPI_MakeTorusTest, PartialTorus_SymmetricAroundZero)
{
  const double R1     = 1.0;
  const double R2     = 0.1;
  const double angle1 = -M_PI_2;
  const double angle2 = M_PI_2;
  const double angle  = 2.094;

  gp_Ax2                anAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  BRepPrimAPI_MakeTorus aMakeTorus(anAxis, R1, R2, angle1, angle2, angle);
  TopoDS_Shape          aShape = aMakeTorus.Shape();

  ASSERT_TRUE(aMakeTorus.IsDone()) << "Torus creation failed";
  ASSERT_FALSE(aShape.IsNull()) << "Resulting shape is null";

  BRepCheck_Analyzer anAnalyzer(aShape);
  EXPECT_TRUE(anAnalyzer.IsValid()) << "Symmetric partial torus should be valid";

  int aFaceCount = 0;
  for (TopExp_Explorer anExp(aShape, TopAbs_FACE); anExp.More(); anExp.Next())
  {
    aFaceCount++;
  }
  EXPECT_EQ(aFaceCount, 5) << "Expected 5 faces for partial torus with sides";
}

TEST(BRepPrimAPI_MakeTorusTest, PartialTorus_SmallSymmetricRange)
{
  const double angle1 = -M_PI / 4.0;
  const double angle2 = M_PI / 4.0;

  bool isValid = createAndCheckPartialTorus(10.0, 2.0, angle1, angle2, M_PI / 4.0);
  EXPECT_TRUE(isValid) << "Small symmetric range (-45 to +45) should produce valid shape";
}

TEST(BRepPrimAPI_MakeTorusTest, PartialTorus_Bug23612)
{
  const double R1     = 10.0;
  const double R2     = 2.0;
  const double angle1 = M_PI_2;
  const double angle2 = 3.0 * M_PI_2;
  const double angle  = M_PI / 4.0;

  gp_Ax2                anAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  BRepPrimAPI_MakeTorus aMakeTorus(anAxis, R1, R2, angle1, angle2, angle);
  TopoDS_Shape          aShape = aMakeTorus.Shape();

  ASSERT_TRUE(aMakeTorus.IsDone()) << "Torus creation failed";
  ASSERT_FALSE(aShape.IsNull()) << "Resulting shape is null";

  BRepCheck_Analyzer anAnalyzer(aShape);

  EXPECT_TRUE(anAnalyzer.IsValid())
    << "Bug 23612 fixed: V range (90, 270) should produce valid shape";
}

TEST(BRepPrimAPI_MakeTorusTest, PartialTorus_ZeroTo180)
{
  const double angle1 = 0.0;
  const double angle2 = M_PI;

  bool isValid = createAndCheckPartialTorus(10.0, 2.0, angle1, angle2, M_PI / 4.0);

  EXPECT_FALSE(isValid) << "Known limitation: equal heights (sin(0)=sin(180)=0) not supported";
}

TEST(BRepPrimAPI_MakeTorusTest, PartialTorus_Minus180ToZero)
{
  const double angle1 = -M_PI;
  const double angle2 = 0.0;

  bool isValid = createAndCheckPartialTorus(10.0, 2.0, angle1, angle2, M_PI / 4.0);

  EXPECT_FALSE(isValid) << "Known limitation: equal heights (sin(-180)=sin(0)=0) not supported";
}

TEST(BRepPrimAPI_MakeTorusTest, PartialTorus_180To360)
{
  const double angle1 = M_PI;
  const double angle2 = 2 * M_PI;

  bool isValid = createAndCheckPartialTorus(10.0, 2.0, angle1, angle2, M_PI / 4.0);

  EXPECT_FALSE(isValid) << "Known limitation: equal heights (sin(180)=sin(360)=0) not supported";
}

TEST(BRepPrimAPI_MakeTorusTest, PartialTorus_PositiveRange)
{
  const double angle1 = M_PI / 4.0;
  const double angle2 = 3.0 * M_PI / 4.0;

  bool isValid = createAndCheckPartialTorus(10.0, 2.0, angle1, angle2, M_PI / 4.0);

  EXPECT_FALSE(isValid) << "Known limitation: equal heights (sin(45)=sin(135)) not supported";
}

TEST(BRepPrimAPI_MakeTorusTest, PartialTorus_NegativeRange)
{
  const double angle1 = -3.0 * M_PI / 4.0;
  const double angle2 = -M_PI / 4.0;

  bool isValid = createAndCheckPartialTorus(10.0, 2.0, angle1, angle2, M_PI / 4.0);

  EXPECT_FALSE(isValid) << "Known limitation: equal heights (sin(-135)=sin(-45)) not supported";
}

TEST(BRepPrimAPI_MakeTorusTest, PartialTorus_AsymmetricCrossingZero)
{
  const double angle1 = -M_PI / 6.0;
  const double angle2 = M_PI / 3.0;

  bool isValid = createAndCheckPartialTorus(10.0, 2.0, angle1, angle2, M_PI / 4.0);
  EXPECT_TRUE(isValid) << "Asymmetric range crossing 0 but within (-PI/2, PI/2) should be valid";
}

TEST(BRepPrimAPI_MakeTorusTest, PartialTorus_SmallPositiveRange)
{
  const double angle1 = M_PI / 6.0;
  const double angle2 = M_PI / 3.0;

  bool isValid = createAndCheckPartialTorus(10.0, 2.0, angle1, angle2, M_PI / 4.0);
  EXPECT_TRUE(isValid) << "Small positive range within (-PI/2, PI/2) should be valid";
}

TEST(BRepPrimAPI_MakeTorusTest, RootCause_HeightOrderingAssumption)
{
  const double R1 = 10.0;
  const double R2 = 2.0;

  auto computeHeight = [R2](double angleRad) { return R2 * std::sin(angleRad); };

  {
    const double vMin = -M_PI_2;
    const double vMax = M_PI_2;
    double       yMin = computeHeight(vMin);
    double       yMax = computeHeight(vMax);
    EXPECT_GT(yMax, yMin) << "Working case: Y(VMax) should be > Y(VMin)";

    bool isValid = createAndCheckPartialTorus(R1, R2, vMin, vMax, M_PI / 4.0);
    EXPECT_TRUE(isValid) << "Range with correct height ordering should produce valid shape";
  }

  {
    const double vMin = M_PI_2;
    const double vMax = 3.0 * M_PI_2;
    double       yMin = computeHeight(vMin);
    double       yMax = computeHeight(vMax);
    EXPECT_LT(yMax, yMin) << "Height ordering is inverted: Y(VMax) < Y(VMin)";

    bool isValid = createAndCheckPartialTorus(R1, R2, vMin, vMax, M_PI / 4.0);

    EXPECT_TRUE(isValid) << "Bug 23612 fixed: inverted height ordering now handled correctly";
  }

  {
    const double vMin = M_PI / 4.0;
    const double vMax = 3.0 * M_PI / 4.0;
    double       yMin = computeHeight(vMin);
    double       yMax = computeHeight(vMax);
    EXPECT_NEAR(yMax, yMin, 1e-10) << "Heights at VMin and VMax are equal";

    bool isValid = createAndCheckPartialTorus(R1, R2, vMin, vMax, M_PI / 4.0);

    EXPECT_FALSE(isValid) << "Known limitation: equal heights not yet supported";
  }
}

TEST(BRepPrimAPI_MakeTorusTest, FullTorus_EqualHeights)
{
  const double R1     = 10.0;
  const double R2     = 2.0;
  const double angle1 = 0.0;
  const double angle2 = M_PI;

  gp_Ax2 anAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));

  BRepPrimAPI_MakeTorus aMakeTorus(anAxis, R1, R2, angle1, angle2);
  TopoDS_Shape          aShape = aMakeTorus.Shape();

  ASSERT_TRUE(aMakeTorus.IsDone()) << "Torus creation failed";
  ASSERT_FALSE(aShape.IsNull()) << "Shape is null";

  BRepCheck_Analyzer anAnalyzer(aShape);
  EXPECT_TRUE(anAnalyzer.IsValid()) << "Full torus (no sides) with equal heights should be valid";
}
