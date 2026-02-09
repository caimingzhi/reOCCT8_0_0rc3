

#include <STEPConstruct_RenderingProperties.hpp>

#include <STEPConstruct_Styles.hpp>
#include <StepVisual_SurfaceStyleRenderingWithProperties.hpp>
#include <StepVisual_RenderingPropertiesSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_SurfaceStyleTransparent.hpp>
#include <StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular.hpp>
#include <StepVisual_ColourRgb.hpp>
#include <Quantity_Color.hpp>
#include <Quantity_ColorRGBA.hpp>
#include <TCollection_HAsciiString.hpp>

#include <gtest/gtest.h>

class STEPConstruct_RenderingPropertiesTest : public ::testing::Test
{
protected:
  void SetUp() override
  {

    mySurfaceColor     = Quantity_Color(0.8, 0.5, 0.2, Quantity_TOC_RGB);
    myTransparency     = 0.25;
    myAmbientFactor    = 0.3;
    myDiffuseFactor    = 1.0;
    mySpecularFactor   = 0.8;
    mySpecularExponent = 45.0;
    mySpecularColor    = Quantity_Color(0.9, 0.9, 0.9, Quantity_TOC_RGB);
  }

  occ::handle<StepVisual_SurfaceStyleRenderingWithProperties> CreateStepRenderingProperties()
  {

    occ::handle<TCollection_HAsciiString> aColorName = new TCollection_HAsciiString("");
    occ::handle<StepVisual_Colour>        aSurfaceColor =
      STEPConstruct_Styles::EncodeColor(mySurfaceColor);

    occ::handle<StepVisual_SurfaceStyleTransparent> aTransp =
      new StepVisual_SurfaceStyleTransparent();
    aTransp->Init(myTransparency);

    occ::handle<StepVisual_Colour> aSpecColor = STEPConstruct_Styles::EncodeColor(mySpecularColor);

    occ::handle<StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular> aReflectance =
      new StepVisual_SurfaceStyleReflectanceAmbientDiffuseSpecular();
    aReflectance->Init(myAmbientFactor,
                       myDiffuseFactor,
                       mySpecularFactor,
                       mySpecularExponent,
                       aSpecColor);

    occ::handle<NCollection_HArray1<StepVisual_RenderingPropertiesSelect>> aProps =
      new NCollection_HArray1<StepVisual_RenderingPropertiesSelect>(1, 2);

    StepVisual_RenderingPropertiesSelect aRps1, aRps2;
    aRps1.SetValue(aTransp);
    aRps2.SetValue(aReflectance);

    aProps->SetValue(1, aRps1);
    aProps->SetValue(2, aRps2);

    occ::handle<StepVisual_SurfaceStyleRenderingWithProperties> aResult =
      new StepVisual_SurfaceStyleRenderingWithProperties();
    aResult->Init(StepVisual_ssmNormalShading, aSurfaceColor, aProps);

    return aResult;
  }

  XCAFDoc_VisMaterialCommon CreateMaterial()
  {
    XCAFDoc_VisMaterialCommon aMaterial;

    aMaterial.DiffuseColor = mySurfaceColor;
    aMaterial.Transparency = static_cast<float>(myTransparency);

    aMaterial.AmbientColor = Quantity_Color(mySurfaceColor.Red() * myAmbientFactor,
                                            mySurfaceColor.Green() * myAmbientFactor,
                                            mySurfaceColor.Blue() * myAmbientFactor,
                                            Quantity_TOC_RGB);

    aMaterial.SpecularColor = mySpecularColor;
    aMaterial.Shininess     = (float)(mySpecularExponent / 128.0);

    aMaterial.IsDefined = true;

    return aMaterial;
  }

  bool AreColorsEqual(const Quantity_Color& theC1,
                      const Quantity_Color& theC2,
                      const double          theTol = 0.01)
  {
    return (std::abs(theC1.Red() - theC2.Red()) <= theTol)
           && (std::abs(theC1.Green() - theC2.Green()) <= theTol)
           && (std::abs(theC1.Blue() - theC2.Blue()) <= theTol);
  }

  Quantity_Color mySurfaceColor;
  Quantity_Color mySpecularColor;
  double         myTransparency;
  double         myAmbientFactor;
  double         myDiffuseFactor;
  double         mySpecularFactor;
  double         mySpecularExponent;
};

TEST_F(STEPConstruct_RenderingPropertiesTest, DefaultConstructor)
{
  STEPConstruct_RenderingProperties aProps;

  EXPECT_FALSE(aProps.IsDefined());
  EXPECT_FALSE(aProps.IsAmbientReflectanceDefined());
  EXPECT_FALSE(aProps.IsDiffuseReflectanceDefined());
  EXPECT_FALSE(aProps.IsSpecularReflectanceDefined());
  EXPECT_FALSE(aProps.IsSpecularExponentDefined());
  EXPECT_FALSE(aProps.IsSpecularColourDefined());

  EXPECT_EQ(aProps.Transparency(), 0.0);
  EXPECT_EQ(aProps.RenderingMethod(), StepVisual_ssmNormalShading);
}

TEST_F(STEPConstruct_RenderingPropertiesTest, RGBAConstructor)
{

  Quantity_ColorRGBA aRgba(mySurfaceColor, 0.75);

  STEPConstruct_RenderingProperties aProps(aRgba);

  EXPECT_TRUE(aProps.IsDefined());
  EXPECT_FALSE(aProps.IsAmbientReflectanceDefined());
  EXPECT_FALSE(aProps.IsDiffuseReflectanceDefined());
  EXPECT_FALSE(aProps.IsSpecularReflectanceDefined());

  EXPECT_TRUE(AreColorsEqual(aProps.SurfaceColor(), mySurfaceColor));
  EXPECT_NEAR(aProps.Transparency(), 0.25, 0.001);
  EXPECT_EQ(aProps.RenderingMethod(), StepVisual_ssmNormalShading);
}

TEST_F(STEPConstruct_RenderingPropertiesTest, StepRenderingPropertiesConstructor)
{
  occ::handle<StepVisual_SurfaceStyleRenderingWithProperties> aStepProps =
    CreateStepRenderingProperties();

  STEPConstruct_RenderingProperties aProps(aStepProps);

  EXPECT_TRUE(aProps.IsDefined());
  EXPECT_TRUE(aProps.IsAmbientReflectanceDefined());
  EXPECT_TRUE(aProps.IsDiffuseReflectanceDefined());
  EXPECT_TRUE(aProps.IsSpecularReflectanceDefined());
  EXPECT_TRUE(aProps.IsSpecularExponentDefined());
  EXPECT_TRUE(aProps.IsSpecularColourDefined());

  EXPECT_TRUE(AreColorsEqual(aProps.SurfaceColor(), mySurfaceColor));
  EXPECT_NEAR(aProps.Transparency(), myTransparency, 0.001);
  EXPECT_NEAR(aProps.AmbientReflectance(), myAmbientFactor, 0.001);
  EXPECT_NEAR(aProps.DiffuseReflectance(), myDiffuseFactor, 0.001);
  EXPECT_NEAR(aProps.SpecularReflectance(), mySpecularFactor, 0.001);
  EXPECT_NEAR(aProps.SpecularExponent(), mySpecularExponent, 0.001);
  EXPECT_TRUE(AreColorsEqual(aProps.SpecularColour(), mySpecularColor));
  EXPECT_EQ(aProps.RenderingMethod(), StepVisual_ssmNormalShading);
}

TEST_F(STEPConstruct_RenderingPropertiesTest, MaterialConstructor)
{
  XCAFDoc_VisMaterialCommon aMaterial = CreateMaterial();

  STEPConstruct_RenderingProperties aProps(aMaterial);

  EXPECT_TRUE(aProps.IsDefined());
  EXPECT_TRUE(aProps.IsAmbientReflectanceDefined());
  EXPECT_TRUE(aProps.IsDiffuseReflectanceDefined());
  EXPECT_TRUE(aProps.IsSpecularReflectanceDefined());
  EXPECT_TRUE(aProps.IsSpecularExponentDefined());
  EXPECT_TRUE(aProps.IsSpecularColourDefined());

  EXPECT_TRUE(AreColorsEqual(aProps.SurfaceColor(), mySurfaceColor));
  EXPECT_NEAR(aProps.Transparency(), myTransparency, 0.001);
  EXPECT_NEAR(aProps.AmbientReflectance(), myAmbientFactor, 0.02);
  EXPECT_NEAR(aProps.DiffuseReflectance(), 1.0, 0.001);
}

TEST_F(STEPConstruct_RenderingPropertiesTest, SetReflectanceProperties)
{
  STEPConstruct_RenderingProperties aProps;

  aProps.Init(mySurfaceColor, myTransparency);
  EXPECT_TRUE(aProps.IsDefined());

  aProps.SetAmbientReflectance(myAmbientFactor);
  EXPECT_TRUE(aProps.IsAmbientReflectanceDefined());
  EXPECT_NEAR(aProps.AmbientReflectance(), myAmbientFactor, 0.001);
  EXPECT_FALSE(aProps.IsDiffuseReflectanceDefined());

  aProps.SetAmbientAndDiffuseReflectance(myAmbientFactor, myDiffuseFactor);
  EXPECT_TRUE(aProps.IsAmbientReflectanceDefined());
  EXPECT_TRUE(aProps.IsDiffuseReflectanceDefined());
  EXPECT_NEAR(aProps.AmbientReflectance(), myAmbientFactor, 0.001);
  EXPECT_NEAR(aProps.DiffuseReflectance(), myDiffuseFactor, 0.001);
  EXPECT_FALSE(aProps.IsSpecularReflectanceDefined());

  aProps.SetAmbientDiffuseAndSpecularReflectance(myAmbientFactor,
                                                 myDiffuseFactor,
                                                 mySpecularFactor,
                                                 mySpecularExponent,
                                                 mySpecularColor);

  EXPECT_TRUE(aProps.IsAmbientReflectanceDefined());
  EXPECT_TRUE(aProps.IsDiffuseReflectanceDefined());
  EXPECT_TRUE(aProps.IsSpecularReflectanceDefined());
  EXPECT_TRUE(aProps.IsSpecularExponentDefined());
  EXPECT_TRUE(aProps.IsSpecularColourDefined());

  EXPECT_NEAR(aProps.AmbientReflectance(), myAmbientFactor, 0.001);
  EXPECT_NEAR(aProps.DiffuseReflectance(), myDiffuseFactor, 0.001);
  EXPECT_NEAR(aProps.SpecularReflectance(), mySpecularFactor, 0.001);
  EXPECT_NEAR(aProps.SpecularExponent(), mySpecularExponent, 0.001);
  EXPECT_TRUE(AreColorsEqual(aProps.SpecularColour(), mySpecularColor));
}

TEST_F(STEPConstruct_RenderingPropertiesTest, CreateRenderingProperties)
{
  STEPConstruct_RenderingProperties aProps;
  aProps.Init(mySurfaceColor, myTransparency);
  aProps.SetAmbientDiffuseAndSpecularReflectance(myAmbientFactor,
                                                 myDiffuseFactor,
                                                 mySpecularFactor,
                                                 mySpecularExponent,
                                                 mySpecularColor);

  occ::handle<StepVisual_SurfaceStyleRenderingWithProperties> aStepProps =
    aProps.CreateRenderingProperties();

  ASSERT_FALSE(aStepProps.IsNull());
  EXPECT_EQ(aStepProps->RenderingMethod(), StepVisual_ssmNormalShading);

  STEPConstruct_RenderingProperties aParsedProps(aStepProps);

  EXPECT_TRUE(aParsedProps.IsDefined());
  EXPECT_TRUE(AreColorsEqual(aParsedProps.SurfaceColor(), mySurfaceColor));
  EXPECT_NEAR(aParsedProps.Transparency(), myTransparency, 0.001);
  EXPECT_NEAR(aParsedProps.AmbientReflectance(), myAmbientFactor, 0.001);
  EXPECT_NEAR(aParsedProps.DiffuseReflectance(), myDiffuseFactor, 0.001);
  EXPECT_NEAR(aParsedProps.SpecularReflectance(), mySpecularFactor, 0.001);
  EXPECT_NEAR(aParsedProps.SpecularExponent(), mySpecularExponent, 0.001);
  EXPECT_TRUE(AreColorsEqual(aParsedProps.SpecularColour(), mySpecularColor));
}

TEST_F(STEPConstruct_RenderingPropertiesTest, CreateXCAFMaterial)
{
  STEPConstruct_RenderingProperties aProps;
  aProps.Init(mySurfaceColor, myTransparency);
  aProps.SetAmbientDiffuseAndSpecularReflectance(myAmbientFactor,
                                                 myDiffuseFactor,
                                                 mySpecularFactor,
                                                 mySpecularExponent,
                                                 mySpecularColor);

  XCAFDoc_VisMaterialCommon aMaterial = aProps.CreateXCAFMaterial();
  EXPECT_TRUE(aMaterial.IsDefined);

  EXPECT_TRUE(AreColorsEqual(aMaterial.DiffuseColor, mySurfaceColor));
  EXPECT_NEAR(aMaterial.Transparency, myTransparency, 0.001);

  Quantity_Color anExpectedAmbient(mySurfaceColor.Red() * myAmbientFactor,
                                   mySurfaceColor.Green() * myAmbientFactor,
                                   mySurfaceColor.Blue() * myAmbientFactor,
                                   Quantity_TOC_RGB);
  EXPECT_TRUE(AreColorsEqual(aMaterial.AmbientColor, anExpectedAmbient));

  EXPECT_TRUE(AreColorsEqual(aMaterial.SpecularColor, mySpecularColor));
  EXPECT_NEAR(aMaterial.Shininess, mySpecularExponent / 128.0, 0.01);
}

TEST_F(STEPConstruct_RenderingPropertiesTest, BidirectionalConversion)
{

  XCAFDoc_VisMaterialCommon aOriginalMaterial = CreateMaterial();

  STEPConstruct_RenderingProperties aProps(aOriginalMaterial);

  XCAFDoc_VisMaterialCommon aConvertedMaterial = aProps.CreateXCAFMaterial();

  EXPECT_TRUE(aConvertedMaterial.IsDefined);

  EXPECT_TRUE(AreColorsEqual(aConvertedMaterial.DiffuseColor, aOriginalMaterial.DiffuseColor));
  EXPECT_NEAR(aConvertedMaterial.Transparency, aOriginalMaterial.Transparency, 0.001);
  EXPECT_TRUE(
    AreColorsEqual(aConvertedMaterial.AmbientColor, aOriginalMaterial.AmbientColor, 0.05));
  EXPECT_TRUE(
    AreColorsEqual(aConvertedMaterial.SpecularColor, aOriginalMaterial.SpecularColor, 0.05));
  EXPECT_NEAR(aConvertedMaterial.Shininess, aOriginalMaterial.Shininess, 0.05);
}

TEST_F(STEPConstruct_RenderingPropertiesTest, InitWithRGBAColor)
{
  STEPConstruct_RenderingProperties aProps;

  Quantity_ColorRGBA aRgba(Quantity_Color(0.3, 0.6, 0.9, Quantity_TOC_RGB), 0.6f);

  aProps.Init(aRgba);

  EXPECT_TRUE(aProps.IsDefined());
  EXPECT_FALSE(aProps.IsAmbientReflectanceDefined());
  EXPECT_FALSE(aProps.IsDiffuseReflectanceDefined());
  EXPECT_FALSE(aProps.IsSpecularReflectanceDefined());

  Quantity_Color expectedColor(0.3, 0.6, 0.9, Quantity_TOC_RGB);
  EXPECT_TRUE(AreColorsEqual(aProps.SurfaceColor(), expectedColor));
  EXPECT_NEAR(aProps.Transparency(), 0.4, 0.001);
}

TEST_F(STEPConstruct_RenderingPropertiesTest, InitWithCustomRenderingMethod)
{
  STEPConstruct_RenderingProperties aProps;

  aProps.Init(mySurfaceColor, myTransparency);
  aProps.SetRenderingMethod(StepVisual_ssmDotShading);

  EXPECT_TRUE(aProps.IsDefined());
  EXPECT_TRUE(AreColorsEqual(aProps.SurfaceColor(), mySurfaceColor));
  EXPECT_NEAR(aProps.Transparency(), myTransparency, 0.001);
  EXPECT_EQ(aProps.RenderingMethod(), StepVisual_ssmDotShading);
}

TEST_F(STEPConstruct_RenderingPropertiesTest, MaterialConvertible)
{
  STEPConstruct_RenderingProperties aProps;

  EXPECT_FALSE(aProps.IsMaterialConvertible());

  aProps.Init(mySurfaceColor, myTransparency);
  EXPECT_FALSE(aProps.IsMaterialConvertible());

  aProps.SetAmbientDiffuseAndSpecularReflectance(myAmbientFactor,
                                                 myDiffuseFactor,
                                                 mySpecularFactor,
                                                 mySpecularExponent,
                                                 mySpecularColor);

  EXPECT_TRUE(aProps.IsMaterialConvertible());
}

TEST_F(STEPConstruct_RenderingPropertiesTest, NullInputs)
{
  STEPConstruct_RenderingProperties aProps;

  occ::handle<StepVisual_SurfaceStyleRenderingWithProperties> nullProps;
  aProps.Init(nullProps);

  EXPECT_FALSE(aProps.IsDefined());

  XCAFDoc_VisMaterialCommon nullMaterial;
  nullMaterial.IsDefined = false;

  STEPConstruct_RenderingProperties propsFromNull(nullMaterial);
  EXPECT_FALSE(propsFromNull.IsDefined());
}

TEST_F(STEPConstruct_RenderingPropertiesTest, CreateAmbientOnlyProperties)
{
  STEPConstruct_RenderingProperties aProps;
  aProps.Init(mySurfaceColor, myTransparency);
  aProps.SetAmbientReflectance(myAmbientFactor);

  occ::handle<StepVisual_SurfaceStyleRenderingWithProperties> aStepProps =
    aProps.CreateRenderingProperties();

  ASSERT_FALSE(aStepProps.IsNull());

  STEPConstruct_RenderingProperties aParsedProps(aStepProps);

  EXPECT_TRUE(aParsedProps.IsDefined());
  EXPECT_TRUE(aParsedProps.IsAmbientReflectanceDefined());
  EXPECT_FALSE(aParsedProps.IsDiffuseReflectanceDefined());
  EXPECT_FALSE(aParsedProps.IsSpecularReflectanceDefined());

  EXPECT_TRUE(AreColorsEqual(aParsedProps.SurfaceColor(), mySurfaceColor));
  EXPECT_NEAR(aParsedProps.Transparency(), myTransparency, 0.001);
  EXPECT_NEAR(aParsedProps.AmbientReflectance(), myAmbientFactor, 0.001);
}

TEST_F(STEPConstruct_RenderingPropertiesTest, CreateAmbientAndDiffuseProperties)
{
  STEPConstruct_RenderingProperties aProps;
  aProps.Init(mySurfaceColor, myTransparency);
  aProps.SetAmbientAndDiffuseReflectance(myAmbientFactor, myDiffuseFactor);

  occ::handle<StepVisual_SurfaceStyleRenderingWithProperties> aStepProps =
    aProps.CreateRenderingProperties();

  ASSERT_FALSE(aStepProps.IsNull());

  STEPConstruct_RenderingProperties aParsedProps(aStepProps);

  EXPECT_TRUE(aParsedProps.IsDefined());
  EXPECT_TRUE(aParsedProps.IsAmbientReflectanceDefined());
  EXPECT_TRUE(aParsedProps.IsDiffuseReflectanceDefined());
  EXPECT_FALSE(aParsedProps.IsSpecularReflectanceDefined());

  EXPECT_TRUE(AreColorsEqual(aParsedProps.SurfaceColor(), mySurfaceColor));
  EXPECT_NEAR(aParsedProps.Transparency(), myTransparency, 0.001);
  EXPECT_NEAR(aParsedProps.AmbientReflectance(), myAmbientFactor, 0.001);
  EXPECT_NEAR(aParsedProps.DiffuseReflectance(), myDiffuseFactor, 0.001);
}

TEST_F(STEPConstruct_RenderingPropertiesTest, NonStandardSpecularColor)
{

  XCAFDoc_VisMaterialCommon aMaterial = CreateMaterial();
  Quantity_Color            aCustomSpecular(0.1, 0.8, 0.2, Quantity_TOC_RGB);
  aMaterial.SpecularColor = aCustomSpecular;

  STEPConstruct_RenderingProperties aProps(aMaterial);

  EXPECT_TRUE(aProps.IsSpecularColourDefined());
  EXPECT_TRUE(AreColorsEqual(aProps.SpecularColour(), aCustomSpecular));

  XCAFDoc_VisMaterialCommon aReconvertedMaterial = aProps.CreateXCAFMaterial();
  EXPECT_TRUE(AreColorsEqual(aReconvertedMaterial.SpecularColor, aCustomSpecular, 0.05));
}

TEST_F(STEPConstruct_RenderingPropertiesTest, ExtremeValues)
{
  STEPConstruct_RenderingProperties aProps;

  aProps.Init(mySurfaceColor, 1.0);
  EXPECT_NEAR(aProps.Transparency(), 1.0, 0.001);

  aProps.SetAmbientDiffuseAndSpecularReflectance(0.0, 2.0, 1.0, 256.0, mySpecularColor);

  XCAFDoc_VisMaterialCommon aMaterial = aProps.CreateXCAFMaterial();

  EXPECT_NEAR(aMaterial.AmbientColor.Red(), 0.0, 0.001);
  EXPECT_NEAR(aMaterial.AmbientColor.Green(), 0.0, 0.001);
  EXPECT_NEAR(aMaterial.AmbientColor.Blue(), 0.0, 0.001);

  EXPECT_NEAR(aMaterial.Shininess, 1.0, 0.1);
}
