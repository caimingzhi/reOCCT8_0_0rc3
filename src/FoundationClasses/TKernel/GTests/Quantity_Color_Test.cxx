

#include <Quantity_Color.hpp>
#include <Quantity_NameOfColor.hpp>

#include <gtest/gtest.h>
#include <cmath>

class Quantity_ColorTest : public testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}

  bool IsNear(double theValue1, double theValue2, double theTolerance = 0.001) const
  {
    return std::abs(theValue1 - theValue2) < theTolerance;
  }
};

TEST_F(Quantity_ColorTest, BasicConstruction)
{

  Quantity_Color aColor1;
  EXPECT_TRUE(IsNear(1.0, aColor1.Red()));
  EXPECT_TRUE(IsNear(1.0, aColor1.Green()));
  EXPECT_TRUE(IsNear(0.0, aColor1.Blue()));

  Quantity_Color aColor2(0.5, 0.6, 0.7, Quantity_TOC_RGB);
  EXPECT_TRUE(IsNear(0.5, aColor2.Red()));
  EXPECT_TRUE(IsNear(0.6, aColor2.Green()));
  EXPECT_TRUE(IsNear(0.7, aColor2.Blue()));

  Quantity_Color aColor3(Quantity_NOC_RED);
  EXPECT_TRUE(IsNear(1.0, aColor3.Red()));
  EXPECT_TRUE(IsNear(0.0, aColor3.Green()));
  EXPECT_TRUE(IsNear(0.0, aColor3.Blue()));
}

TEST_F(Quantity_ColorTest, ConstexprGetters)
{
  const Quantity_Color aColor(0.3, 0.5, 0.7, Quantity_TOC_RGB);

  double aR = aColor.Red();
  double aG = aColor.Green();
  double aB = aColor.Blue();

  EXPECT_TRUE(IsNear(0.3, aR));
  EXPECT_TRUE(IsNear(0.5, aG));
  EXPECT_TRUE(IsNear(0.7, aB));
}

TEST_F(Quantity_ColorTest, EqualityComparison)
{
  Quantity_Color aColor1(0.5, 0.6, 0.7, Quantity_TOC_RGB);
  Quantity_Color aColor2(0.5, 0.6, 0.7, Quantity_TOC_RGB);
  Quantity_Color aColor3(0.5, 0.6, 0.8, Quantity_TOC_RGB);

  EXPECT_TRUE(aColor1.IsEqual(aColor2));
  EXPECT_TRUE(aColor1 == aColor2);
  EXPECT_FALSE(aColor1.IsDifferent(aColor2));
  EXPECT_FALSE(aColor1 != aColor2);

  EXPECT_FALSE(aColor1.IsEqual(aColor3));
  EXPECT_FALSE(aColor1 == aColor3);
  EXPECT_TRUE(aColor1.IsDifferent(aColor3));
  EXPECT_TRUE(aColor1 != aColor3);
}

TEST_F(Quantity_ColorTest, DistanceCalculation)
{
  Quantity_Color aColor1(0.0, 0.0, 0.0, Quantity_TOC_RGB);
  Quantity_Color aColor2(0.3, 0.4, 0.0, Quantity_TOC_RGB);

  double aDist = aColor1.Distance(aColor2);
  EXPECT_TRUE(IsNear(0.5, aDist));

  double aSquareDist = aColor1.SquareDistance(aColor2);
  EXPECT_TRUE(IsNear(0.25, aSquareDist));
}

TEST_F(Quantity_ColorTest, RGB_to_HLS_Conversion)
{

  Quantity_Color          aRed(Quantity_NOC_RED);
  NCollection_Vec3<float> aHLS = Quantity_Color::Convert_sRGB_To_HLS(aRed.Rgb());

  EXPECT_TRUE(IsNear(0.0, aHLS[0], 1.0));
  EXPECT_TRUE(IsNear(1.0, aHLS[1]));
  EXPECT_TRUE(IsNear(1.0, aHLS[2]));

  Quantity_Color          aGray(0.5, 0.5, 0.5, Quantity_TOC_RGB);
  NCollection_Vec3<float> aHLS_Gray = Quantity_Color::Convert_sRGB_To_HLS(aGray.Rgb());

  EXPECT_TRUE(IsNear(0.5, aHLS_Gray[1]));
  EXPECT_TRUE(IsNear(0.0, aHLS_Gray[2]));
}

TEST_F(Quantity_ColorTest, LinearRGB_to_Lab_Conversion)
{

  Quantity_Color          aWhite(1.0, 1.0, 1.0, Quantity_TOC_RGB);
  NCollection_Vec3<float> aLab = Quantity_Color::Convert_LinearRGB_To_Lab(aWhite.Rgb());

  EXPECT_TRUE(IsNear(100.0, aLab[0], 1.0));
  EXPECT_TRUE(IsNear(0.0, aLab[1], 5.0));
  EXPECT_TRUE(IsNear(0.0, aLab[2], 5.0));

  Quantity_Color          aBlack(0.0, 0.0, 0.0, Quantity_TOC_RGB);
  NCollection_Vec3<float> aLabBlack = Quantity_Color::Convert_LinearRGB_To_Lab(aBlack.Rgb());

  EXPECT_TRUE(IsNear(0.0, aLabBlack[0], 1.0));
}

TEST_F(Quantity_ColorTest, Lab_to_Lch_Conversion)
{

  NCollection_Vec3<float> aLab(50.0f, 25.0f, 25.0f);
  NCollection_Vec3<float> aLch = Quantity_Color::Convert_Lab_To_Lch(aLab);

  EXPECT_TRUE(IsNear(50.0, aLch[0]));

  EXPECT_TRUE(IsNear(35.36, aLch[1], 0.1));

  EXPECT_TRUE(IsNear(45.0, aLch[2], 1.0));
}

TEST_F(Quantity_ColorTest, Lch_to_Lab_RoundTrip)
{
  NCollection_Vec3<float> aLab1(50.0f, 25.0f, 25.0f);
  NCollection_Vec3<float> aLch  = Quantity_Color::Convert_Lab_To_Lch(aLab1);
  NCollection_Vec3<float> aLab2 = Quantity_Color::Convert_Lch_To_Lab(aLch);

  EXPECT_TRUE(IsNear(aLab1[0], aLab2[0], 0.01));
  EXPECT_TRUE(IsNear(aLab1[1], aLab2[1], 0.01));
  EXPECT_TRUE(IsNear(aLab1[2], aLab2[2], 0.01));
}

TEST_F(Quantity_ColorTest, Lab_to_RGB_RoundTrip)
{
  Quantity_Color          aOriginal(0.5, 0.6, 0.7, Quantity_TOC_RGB);
  NCollection_Vec3<float> aLab = Quantity_Color::Convert_LinearRGB_To_Lab(aOriginal.Rgb());
  NCollection_Vec3<float> aRGB = Quantity_Color::Convert_Lab_To_LinearRGB(aLab);

  EXPECT_TRUE(IsNear(aOriginal.Red(), aRGB[0], 0.01));
  EXPECT_TRUE(IsNear(aOriginal.Green(), aRGB[1], 0.01));
  EXPECT_TRUE(IsNear(aOriginal.Blue(), aRGB[2], 0.01));
}

TEST_F(Quantity_ColorTest, DeltaE2000_Calculation)
{

  Quantity_Color aColor1(0.5, 0.6, 0.7, Quantity_TOC_RGB);
  Quantity_Color aColor2(0.5, 0.6, 0.7, Quantity_TOC_RGB);

  double aDeltaE = aColor1.DeltaE2000(aColor2);
  EXPECT_TRUE(IsNear(0.0, aDeltaE, 0.01));

  Quantity_Color aColor3(0.3, 0.4, 0.5, Quantity_TOC_RGB);
  double         aDeltaE2 = aColor1.DeltaE2000(aColor3);
  EXPECT_GT(aDeltaE2, 0.0);
}

TEST_F(Quantity_ColorTest, NamedColors)
{

  Quantity_Color aRed(Quantity_NOC_RED);
  EXPECT_TRUE(IsNear(1.0, aRed.Red()));
  EXPECT_TRUE(IsNear(0.0, aRed.Green()));
  EXPECT_TRUE(IsNear(0.0, aRed.Blue()));

  Quantity_Color aGreen(Quantity_NOC_GREEN);
  EXPECT_TRUE(IsNear(0.0, aGreen.Red()));
  EXPECT_GT(aGreen.Green(), 0.5);
  EXPECT_TRUE(IsNear(0.0, aGreen.Blue()));

  Quantity_Color aBlue(Quantity_NOC_BLUE);
  EXPECT_TRUE(IsNear(0.0, aBlue.Red()));
  EXPECT_TRUE(IsNear(0.0, aBlue.Green()));
  EXPECT_TRUE(IsNear(1.0, aBlue.Blue()));
}

TEST_F(Quantity_ColorTest, SetValues)
{
  Quantity_Color aColor;

  aColor.SetValues(0.2, 0.4, 0.6, Quantity_TOC_RGB);
  EXPECT_TRUE(IsNear(0.2, aColor.Red()));
  EXPECT_TRUE(IsNear(0.4, aColor.Green()));
  EXPECT_TRUE(IsNear(0.6, aColor.Blue()));

  aColor.SetValues(Quantity_NOC_YELLOW);
  EXPECT_TRUE(IsNear(1.0, aColor.Red()));
  EXPECT_TRUE(IsNear(1.0, aColor.Green()));
  EXPECT_TRUE(IsNear(0.0, aColor.Blue()));
}

TEST_F(Quantity_ColorTest, HLS_Extraction)
{
  Quantity_Color aRed(Quantity_NOC_RED);

  double aHue   = aRed.Hue();
  double aLight = aRed.Light();
  double aSat   = aRed.Saturation();

  EXPECT_TRUE(IsNear(0.0, aHue, 5.0) || IsNear(360.0, aHue, 5.0));
  EXPECT_TRUE(IsNear(1.0, aLight, 0.01));
  EXPECT_TRUE(IsNear(1.0, aSat, 0.01));
}

TEST_F(Quantity_ColorTest, EpsilonThreadSafety)
{
  double aOriginalEpsilon = Quantity_Color::Epsilon();

  Quantity_Color::SetEpsilon(0.0002);
  EXPECT_TRUE(IsNear(0.0002, Quantity_Color::Epsilon()));

  Quantity_Color::SetEpsilon(aOriginalEpsilon);
  EXPECT_TRUE(IsNear(aOriginalEpsilon, Quantity_Color::Epsilon()));
}

TEST_F(Quantity_ColorTest, ColorNameString)
{
  const char* aRedName = Quantity_Color::StringName(Quantity_NOC_RED);
  EXPECT_STREQ("RED", aRedName);

  const char* aBlueName = Quantity_Color::StringName(Quantity_NOC_BLUE);
  EXPECT_STREQ("BLUE", aBlueName);
}

TEST_F(Quantity_ColorTest, EdgeCases)
{

  Quantity_Color aBlack(0.0, 0.0, 0.0, Quantity_TOC_RGB);
  EXPECT_TRUE(IsNear(0.0, aBlack.Red()));
  EXPECT_TRUE(IsNear(0.0, aBlack.Green()));
  EXPECT_TRUE(IsNear(0.0, aBlack.Blue()));

  Quantity_Color aWhite(1.0, 1.0, 1.0, Quantity_TOC_RGB);
  EXPECT_TRUE(IsNear(1.0, aWhite.Red()));
  EXPECT_TRUE(IsNear(1.0, aWhite.Green()));
  EXPECT_TRUE(IsNear(1.0, aWhite.Blue()));

  Quantity_Color aColor1(0.5, 0.5, 0.5, Quantity_TOC_RGB);
  Quantity_Color aColor2(0.50001, 0.50001, 0.50001, Quantity_TOC_RGB);
  EXPECT_TRUE(aColor1.IsEqual(aColor2));
}
