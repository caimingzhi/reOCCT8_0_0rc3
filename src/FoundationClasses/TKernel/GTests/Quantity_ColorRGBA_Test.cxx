

#include <Quantity_ColorRGBA.hpp>
#include <Quantity_Color.hpp>

#include <gtest/gtest.h>
#include <cmath>

class Quantity_ColorRGBATest : public testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}

  bool IsNear(double theValue1, double theValue2, double theTolerance = 0.001) const
  {
    return std::abs(theValue1 - theValue2) < theTolerance;
  }
};

TEST_F(Quantity_ColorRGBATest, BasicConstruction)
{

  Quantity_ColorRGBA aColor1;
  EXPECT_TRUE(IsNear(1.0f, aColor1.GetRGB().Red()));
  EXPECT_TRUE(IsNear(1.0f, aColor1.GetRGB().Green()));
  EXPECT_TRUE(IsNear(0.0f, aColor1.GetRGB().Blue()));
  EXPECT_TRUE(IsNear(1.0f, aColor1.Alpha()));

  Quantity_ColorRGBA aColor2(Quantity_Color(0.5, 0.6, 0.7, Quantity_TOC_RGB), 0.8f);
  EXPECT_TRUE(IsNear(0.5f, aColor2.GetRGB().Red()));
  EXPECT_TRUE(IsNear(0.6f, aColor2.GetRGB().Green()));
  EXPECT_TRUE(IsNear(0.7f, aColor2.GetRGB().Blue()));
  EXPECT_TRUE(IsNear(0.8f, aColor2.Alpha()));

  Quantity_ColorRGBA aColor3(0.3f, 0.4f, 0.5f, 0.6f);
  EXPECT_TRUE(IsNear(0.3f, aColor3.GetRGB().Red()));
  EXPECT_TRUE(IsNear(0.4f, aColor3.GetRGB().Green()));
  EXPECT_TRUE(IsNear(0.5f, aColor3.GetRGB().Blue()));
  EXPECT_TRUE(IsNear(0.6f, aColor3.Alpha()));
}

TEST_F(Quantity_ColorRGBATest, ConstexprGetters)
{
  const Quantity_ColorRGBA aColor(0.2f, 0.4f, 0.6f, 0.8f);

  float aAlpha = aColor.Alpha();
  EXPECT_TRUE(IsNear(0.8f, aAlpha));
}

TEST_F(Quantity_ColorRGBATest, SetValues)
{
  Quantity_ColorRGBA aColor;

  aColor.SetValues(0.1f, 0.2f, 0.3f, 0.4f);
  EXPECT_TRUE(IsNear(0.1f, aColor.GetRGB().Red()));
  EXPECT_TRUE(IsNear(0.2f, aColor.GetRGB().Green()));
  EXPECT_TRUE(IsNear(0.3f, aColor.GetRGB().Blue()));
  EXPECT_TRUE(IsNear(0.4f, aColor.Alpha()));
}

TEST_F(Quantity_ColorRGBATest, HexColorParsing_RGB)
{
  Quantity_ColorRGBA aColor;

  bool aResult = Quantity_ColorRGBA::ColorFromHex("#FF0000", aColor, true);
  EXPECT_TRUE(aResult);
  EXPECT_TRUE(IsNear(1.0f, aColor.GetRGB().Red(), 0.01f));
  EXPECT_TRUE(IsNear(0.0f, aColor.GetRGB().Green(), 0.01f));
  EXPECT_TRUE(IsNear(0.0f, aColor.GetRGB().Blue(), 0.01f));

  aResult = Quantity_ColorRGBA::ColorFromHex("00FF00", aColor, true);
  EXPECT_TRUE(aResult);
  EXPECT_TRUE(IsNear(0.0f, aColor.GetRGB().Red(), 0.01f));
  EXPECT_TRUE(IsNear(1.0f, aColor.GetRGB().Green(), 0.01f));
  EXPECT_TRUE(IsNear(0.0f, aColor.GetRGB().Blue(), 0.01f));

  aResult = Quantity_ColorRGBA::ColorFromHex("#0000FF", aColor, true);
  EXPECT_TRUE(aResult);
  EXPECT_TRUE(IsNear(0.0f, aColor.GetRGB().Red(), 0.01f));
  EXPECT_TRUE(IsNear(0.0f, aColor.GetRGB().Green(), 0.01f));
  EXPECT_TRUE(IsNear(1.0f, aColor.GetRGB().Blue(), 0.01f));
}

TEST_F(Quantity_ColorRGBATest, HexColorParsing_RGBA)
{
  Quantity_ColorRGBA aColor;

  bool aResult = Quantity_ColorRGBA::ColorFromHex("#FF000080", aColor, false);
  EXPECT_TRUE(aResult);
  EXPECT_TRUE(IsNear(1.0f, aColor.GetRGB().Red(), 0.01f));
  EXPECT_TRUE(IsNear(0.0f, aColor.GetRGB().Green(), 0.01f));
  EXPECT_TRUE(IsNear(0.0f, aColor.GetRGB().Blue(), 0.01f));
  EXPECT_TRUE(IsNear(0.5f, aColor.Alpha(), 0.02f));
}

TEST_F(Quantity_ColorRGBATest, HexColorParsing_ShortRGB)
{
  Quantity_ColorRGBA aColor;

  bool aResult = Quantity_ColorRGBA::ColorFromHex("#F00", aColor, true);
  EXPECT_TRUE(aResult);
  EXPECT_TRUE(IsNear(1.0f, aColor.GetRGB().Red(), 0.1f));
  EXPECT_TRUE(IsNear(0.0f, aColor.GetRGB().Green(), 0.1f));
  EXPECT_TRUE(IsNear(0.0f, aColor.GetRGB().Blue(), 0.1f));

  aResult = Quantity_ColorRGBA::ColorFromHex("#FFF", aColor, true);
  EXPECT_TRUE(aResult);
  EXPECT_TRUE(IsNear(1.0f, aColor.GetRGB().Red(), 0.1f));
  EXPECT_TRUE(IsNear(1.0f, aColor.GetRGB().Green(), 0.1f));
  EXPECT_TRUE(IsNear(1.0f, aColor.GetRGB().Blue(), 0.1f));
}

TEST_F(Quantity_ColorRGBATest, HexColorParsing_ShortRGBA)
{
  Quantity_ColorRGBA aColor;

  bool aResult = Quantity_ColorRGBA::ColorFromHex("#F008", aColor, false);
  EXPECT_TRUE(aResult);
  EXPECT_TRUE(IsNear(1.0f, aColor.GetRGB().Red(), 0.1f));
  EXPECT_TRUE(IsNear(0.0f, aColor.GetRGB().Green(), 0.1f));
  EXPECT_TRUE(IsNear(0.0f, aColor.GetRGB().Blue(), 0.1f));
  EXPECT_TRUE(IsNear(0.5f, aColor.Alpha(), 0.1f));
}

TEST_F(Quantity_ColorRGBATest, HexColorParsing_Invalid)
{
  Quantity_ColorRGBA aColor;

  EXPECT_FALSE(Quantity_ColorRGBA::ColorFromHex("", aColor, true));

  EXPECT_FALSE(Quantity_ColorRGBA::ColorFromHex("#FFFF", aColor, true));

  EXPECT_FALSE(Quantity_ColorRGBA::ColorFromHex("#GGGGGG", aColor, true));

  EXPECT_FALSE(Quantity_ColorRGBA::ColorFromHex("#FF0000FF", aColor, true));
}

TEST_F(Quantity_ColorRGBATest, HexColorParsing_MixedCase)
{
  Quantity_ColorRGBA aColor;

  bool aResult = Quantity_ColorRGBA::ColorFromHex("#FfAa00", aColor, true);
  EXPECT_TRUE(aResult);
  EXPECT_TRUE(IsNear(1.0f, aColor.GetRGB().Red(), 0.01f));

  EXPECT_TRUE(IsNear(0.402f, aColor.GetRGB().Green(), 0.01f));
  EXPECT_TRUE(IsNear(0.0f, aColor.GetRGB().Blue(), 0.01f));
}

TEST_F(Quantity_ColorRGBATest, HexColorParsing_SpecificValues)
{
  Quantity_ColorRGBA aColor;

  bool aResult = Quantity_ColorRGBA::ColorFromHex("#102030", aColor, true);
  EXPECT_TRUE(aResult);

  EXPECT_TRUE(IsNear(0.00518f, aColor.GetRGB().Red(), 0.0001f));
  EXPECT_TRUE(IsNear(0.01444f, aColor.GetRGB().Green(), 0.0001f));
  EXPECT_TRUE(IsNear(0.02956f, aColor.GetRGB().Blue(), 0.0001f));
}

TEST_F(Quantity_ColorRGBATest, EqualityComparison)
{
  Quantity_ColorRGBA aColor1(0.5f, 0.6f, 0.7f, 0.8f);
  Quantity_ColorRGBA aColor2(0.5f, 0.6f, 0.7f, 0.8f);
  Quantity_ColorRGBA aColor3(0.5f, 0.6f, 0.7f, 0.9f);

  EXPECT_TRUE(aColor1.IsEqual(aColor2));
  EXPECT_FALSE(aColor1.IsEqual(aColor3));
}

TEST_F(Quantity_ColorRGBATest, RGBAccess)
{
  Quantity_ColorRGBA aColor(0.2f, 0.4f, 0.6f, 0.8f);

  const Quantity_Color& aRGB = aColor.GetRGB();
  EXPECT_TRUE(IsNear(0.2f, aRGB.Red()));
  EXPECT_TRUE(IsNear(0.4f, aRGB.Green()));
  EXPECT_TRUE(IsNear(0.6f, aRGB.Blue()));

  aColor.ChangeRGB().SetValues(0.3f, 0.5f, 0.7f, Quantity_TOC_RGB);
  EXPECT_TRUE(IsNear(0.3f, aColor.GetRGB().Red()));
  EXPECT_TRUE(IsNear(0.5f, aColor.GetRGB().Green()));
  EXPECT_TRUE(IsNear(0.7f, aColor.GetRGB().Blue()));
  EXPECT_TRUE(IsNear(0.8f, aColor.Alpha()));
}

TEST_F(Quantity_ColorRGBATest, SetAlpha)
{
  Quantity_ColorRGBA aColor(0.5f, 0.5f, 0.5f, 1.0f);
  EXPECT_TRUE(IsNear(1.0f, aColor.Alpha()));

  aColor.SetAlpha(0.5f);
  EXPECT_TRUE(IsNear(0.5f, aColor.Alpha()));

  EXPECT_TRUE(IsNear(0.5f, aColor.GetRGB().Red()));
  EXPECT_TRUE(IsNear(0.5f, aColor.GetRGB().Green()));
  EXPECT_TRUE(IsNear(0.5f, aColor.GetRGB().Blue()));
}

TEST_F(Quantity_ColorRGBATest, EdgeCases)
{

  Quantity_ColorRGBA aTransparent(0.0f, 0.0f, 0.0f, 0.0f);
  EXPECT_TRUE(IsNear(0.0f, aTransparent.Alpha()));

  Quantity_ColorRGBA aOpaque(1.0f, 1.0f, 1.0f, 1.0f);
  EXPECT_TRUE(IsNear(1.0f, aOpaque.Alpha()));
  EXPECT_TRUE(IsNear(1.0f, aOpaque.GetRGB().Red()));
}

TEST_F(Quantity_ColorRGBATest, ComponentOrder)
{
  Quantity_ColorRGBA aColor;

  bool aResult = Quantity_ColorRGBA::ColorFromHex("#123456", aColor, true);
  EXPECT_TRUE(aResult);

  float aExpectedR = 0.00605f;
  float aExpectedG = 0.03434f;
  float aExpectedB = 0.09306f;

  EXPECT_TRUE(IsNear(aExpectedR, aColor.GetRGB().Red(), 0.0001f));
  EXPECT_TRUE(IsNear(aExpectedG, aColor.GetRGB().Green(), 0.0001f));
  EXPECT_TRUE(IsNear(aExpectedB, aColor.GetRGB().Blue(), 0.0001f));
}
