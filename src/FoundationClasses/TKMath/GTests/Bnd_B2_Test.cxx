

#include <gtest/gtest.h>

#include <Bnd_B2.hpp>
#include <gp_XY.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Ax2d.hpp>
#include <Precision.hpp>

TEST(Bnd_B2dTest, DefaultConstructor)
{
  Bnd_B2d aBox;
  EXPECT_TRUE(aBox.IsVoid());
}

TEST(Bnd_B2dTest, ConstructorWithCenterAndHSize)
{
  gp_XY aCenter(5.0, 10.0);
  gp_XY aHSize(2.0, 3.0);

  Bnd_B2d aBox(aCenter, aHSize);

  EXPECT_FALSE(aBox.IsVoid());

  gp_XY aMin = aBox.CornerMin();
  gp_XY aMax = aBox.CornerMax();

  EXPECT_NEAR(aMin.X(), 3.0, Precision::Confusion());
  EXPECT_NEAR(aMin.Y(), 7.0, Precision::Confusion());
  EXPECT_NEAR(aMax.X(), 7.0, Precision::Confusion());
  EXPECT_NEAR(aMax.Y(), 13.0, Precision::Confusion());
}

TEST(Bnd_B2dTest, Clear)
{
  Bnd_B2d aBox(gp_XY(0.0, 0.0), gp_XY(1.0, 1.0));
  EXPECT_FALSE(aBox.IsVoid());

  aBox.Clear();
  EXPECT_TRUE(aBox.IsVoid());
}

TEST(Bnd_B2dTest, AddPoint)
{
  Bnd_B2d aBox;

  aBox.Add(gp_XY(1.0, 2.0));
  EXPECT_FALSE(aBox.IsVoid());

  gp_XY aMin = aBox.CornerMin();
  gp_XY aMax = aBox.CornerMax();
  EXPECT_NEAR(aMin.X(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aMin.Y(), 2.0, Precision::Confusion());
  EXPECT_NEAR(aMax.X(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aMax.Y(), 2.0, Precision::Confusion());

  aBox.Add(gp_XY(4.0, 5.0));
  aMin = aBox.CornerMin();
  aMax = aBox.CornerMax();
  EXPECT_NEAR(aMin.X(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aMin.Y(), 2.0, Precision::Confusion());
  EXPECT_NEAR(aMax.X(), 4.0, Precision::Confusion());
  EXPECT_NEAR(aMax.Y(), 5.0, Precision::Confusion());
}

TEST(Bnd_B2dTest, AddPnt2d)
{
  Bnd_B2d aBox;
  aBox.Add(gp_Pnt2d(1.0, 2.0));

  EXPECT_FALSE(aBox.IsVoid());
  gp_XY aMin = aBox.CornerMin();
  EXPECT_NEAR(aMin.X(), 1.0, Precision::Confusion());
  EXPECT_NEAR(aMin.Y(), 2.0, Precision::Confusion());
}

TEST(Bnd_B2dTest, AddBox)
{
  Bnd_B2d aBox1(gp_XY(0.0, 0.0), gp_XY(1.0, 1.0));
  Bnd_B2d aBox2(gp_XY(3.0, 3.0), gp_XY(1.0, 1.0));

  aBox1.Add(aBox2);

  gp_XY aMin = aBox1.CornerMin();
  gp_XY aMax = aBox1.CornerMax();
  EXPECT_NEAR(aMin.X(), -1.0, Precision::Confusion());
  EXPECT_NEAR(aMin.Y(), -1.0, Precision::Confusion());
  EXPECT_NEAR(aMax.X(), 4.0, Precision::Confusion());
  EXPECT_NEAR(aMax.Y(), 4.0, Precision::Confusion());
}

TEST(Bnd_B2dTest, SquareExtent)
{
  Bnd_B2d aBox(gp_XY(0.0, 0.0), gp_XY(3.0, 4.0));
  double  aSqExtent = aBox.SquareExtent();

  EXPECT_NEAR(aSqExtent, 100.0, Precision::Confusion());
}

TEST(Bnd_B2dTest, Enlarge)
{
  Bnd_B2d aBox(gp_XY(0.0, 0.0), gp_XY(1.0, 1.0));
  aBox.Enlarge(0.5);

  gp_XY aMin = aBox.CornerMin();
  gp_XY aMax = aBox.CornerMax();
  EXPECT_NEAR(aMin.X(), -1.5, Precision::Confusion());
  EXPECT_NEAR(aMin.Y(), -1.5, Precision::Confusion());
  EXPECT_NEAR(aMax.X(), 1.5, Precision::Confusion());
  EXPECT_NEAR(aMax.Y(), 1.5, Precision::Confusion());
}

TEST(Bnd_B2dTest, Limit)
{

  Bnd_B2d aBox1(gp_XY(0.0, 0.0), gp_XY(5.0, 5.0));
  Bnd_B2d aBox2(gp_XY(2.0, 2.0), gp_XY(2.0, 2.0));

  bool isLimited = aBox1.Limit(aBox2);
  EXPECT_TRUE(isLimited);

  gp_XY aMin = aBox1.CornerMin();
  gp_XY aMax = aBox1.CornerMax();
  EXPECT_NEAR(aMin.X(), 0.0, Precision::Confusion());
  EXPECT_NEAR(aMin.Y(), 0.0, Precision::Confusion());
  EXPECT_NEAR(aMax.X(), 5.0, Precision::Confusion());
  EXPECT_NEAR(aMax.Y(), 5.0, Precision::Confusion());

  Bnd_B2d aBox3(gp_XY(0.0, 0.0), gp_XY(1.0, 1.0));
  Bnd_B2d aBox4(gp_XY(10.0, 10.0), gp_XY(1.0, 1.0));
  bool    isLimited2 = aBox3.Limit(aBox4);
  EXPECT_FALSE(isLimited2);
}

TEST(Bnd_B2dTest, IsOutPoint)
{
  Bnd_B2d aBox(gp_XY(0.0, 0.0), gp_XY(1.0, 1.0));

  EXPECT_FALSE(aBox.IsOut(gp_XY(0.0, 0.0)));
  EXPECT_FALSE(aBox.IsOut(gp_XY(0.5, 0.5)));
  EXPECT_TRUE(aBox.IsOut(gp_XY(2.0, 0.0)));
  EXPECT_TRUE(aBox.IsOut(gp_XY(0.0, 2.0)));
}

TEST(Bnd_B2dTest, IsOutCircle)
{
  Bnd_B2d aBox(gp_XY(0.0, 0.0), gp_XY(1.0, 1.0));

  EXPECT_FALSE(aBox.IsOut(gp_XY(0.0, 0.0), 0.5));

  EXPECT_TRUE(aBox.IsOut(gp_XY(10.0, 10.0), 1.0));
}

TEST(Bnd_B2dTest, IsOutBox)
{
  Bnd_B2d aBox1(gp_XY(0.0, 0.0), gp_XY(1.0, 1.0));
  Bnd_B2d aBox2(gp_XY(0.5, 0.5), gp_XY(1.0, 1.0));
  Bnd_B2d aBox3(gp_XY(5.0, 5.0), gp_XY(1.0, 1.0));

  EXPECT_FALSE(aBox1.IsOut(aBox2));
  EXPECT_TRUE(aBox1.IsOut(aBox3));
}

TEST(Bnd_B2dTest, IsOutLine)
{
  Bnd_B2d aBox(gp_XY(0.0, 0.0), gp_XY(1.0, 1.0));

  gp_Ax2d aLine1(gp_Pnt2d(-2.0, 0.0), gp_Dir2d(1.0, 0.0));
  EXPECT_FALSE(aBox.IsOut(aLine1));

  gp_Ax2d aLine2(gp_Pnt2d(-2.0, 5.0), gp_Dir2d(1.0, 0.0));
  EXPECT_TRUE(aBox.IsOut(aLine2));
}

TEST(Bnd_B2dTest, IsOutSegment)
{
  Bnd_B2d aBox(gp_XY(0.0, 0.0), gp_XY(1.0, 1.0));

  EXPECT_FALSE(aBox.IsOut(gp_XY(-2.0, 0.0), gp_XY(2.0, 0.0)));

  EXPECT_TRUE(aBox.IsOut(gp_XY(5.0, 5.0), gp_XY(6.0, 6.0)));
}

TEST(Bnd_B2dTest, IsInBox)
{
  Bnd_B2d aBox1(gp_XY(0.0, 0.0), gp_XY(0.5, 0.5));
  Bnd_B2d aBox2(gp_XY(0.0, 0.0), gp_XY(2.0, 2.0));

  EXPECT_TRUE(aBox1.IsIn(aBox2));
  EXPECT_FALSE(aBox2.IsIn(aBox1));
}

TEST(Bnd_B2dTest, Transformed)
{
  Bnd_B2d aBox(gp_XY(1.0, 1.0), gp_XY(1.0, 1.0));

  gp_Trsf2d aTrsf;
  aTrsf.SetTranslation(gp_Vec2d(2.0, 3.0));

  Bnd_B2d aTransformedBox = aBox.Transformed(aTrsf);

  gp_XY aMin = aTransformedBox.CornerMin();
  gp_XY aMax = aTransformedBox.CornerMax();

  EXPECT_NEAR(aMin.X(), 2.0, Precision::Confusion());
  EXPECT_NEAR(aMin.Y(), 3.0, Precision::Confusion());
  EXPECT_NEAR(aMax.X(), 4.0, Precision::Confusion());
  EXPECT_NEAR(aMax.Y(), 5.0, Precision::Confusion());
}

TEST(Bnd_B2dTest, SetCenterAndHSize)
{
  Bnd_B2d aBox;

  aBox.SetCenter(gp_XY(5.0, 10.0));
  aBox.SetHSize(gp_XY(2.0, 3.0));

  gp_XY aMin = aBox.CornerMin();
  gp_XY aMax = aBox.CornerMax();

  EXPECT_NEAR(aMin.X(), 3.0, Precision::Confusion());
  EXPECT_NEAR(aMin.Y(), 7.0, Precision::Confusion());
  EXPECT_NEAR(aMax.X(), 7.0, Precision::Confusion());
  EXPECT_NEAR(aMax.Y(), 13.0, Precision::Confusion());
}

TEST(Bnd_B2fTest, FloatPrecision)
{
  Bnd_B2f aBox(gp_XY(1.0f, 2.0f), gp_XY(0.5f, 0.5f));

  EXPECT_FALSE(aBox.IsVoid());

  gp_XY aMin = aBox.CornerMin();
  gp_XY aMax = aBox.CornerMax();

  EXPECT_NEAR(aMin.X(), 0.5, 1e-5);
  EXPECT_NEAR(aMin.Y(), 1.5, 1e-5);
  EXPECT_NEAR(aMax.X(), 1.5, 1e-5);
  EXPECT_NEAR(aMax.Y(), 2.5, 1e-5);
}
