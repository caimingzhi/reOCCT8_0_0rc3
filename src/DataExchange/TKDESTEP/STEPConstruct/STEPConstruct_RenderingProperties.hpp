#pragma once

#include <Quantity_Color.hpp>
#include <Quantity_ColorRGBA.hpp>
#include <StepVisual_ShadingSurfaceMethod.hpp>
#include <StepVisual_SurfaceStyleRenderingWithProperties.hpp>
#include <XCAFDoc_VisMaterialCommon.hpp>

#include <utility>

class StepVisual_SurfaceStyleRenderingWithProperties;
class StepVisual_Colour;
class XCAFDoc_VisMaterial;

class STEPConstruct_RenderingProperties
{
public:
  DEFINE_STANDARD_ALLOC
public:
  Standard_EXPORT STEPConstruct_RenderingProperties();

  Standard_EXPORT STEPConstruct_RenderingProperties(
    const occ::handle<StepVisual_SurfaceStyleRenderingWithProperties>& theRenderingProperties);

  Standard_EXPORT STEPConstruct_RenderingProperties(const Quantity_ColorRGBA& theRGBAColor);

  Standard_EXPORT STEPConstruct_RenderingProperties(const occ::handle<StepVisual_Colour>& theColor,
                                                    const double theTransparency);

  Standard_EXPORT STEPConstruct_RenderingProperties(const XCAFDoc_VisMaterialCommon& theMaterial);

  Standard_EXPORT STEPConstruct_RenderingProperties(
    const occ::handle<XCAFDoc_VisMaterial>& theMaterial);

  Standard_EXPORT STEPConstruct_RenderingProperties(const Quantity_Color& theSurfaceColor,
                                                    const double          theTransparency = 0.0);

  Standard_EXPORT void Init(
    const occ::handle<StepVisual_SurfaceStyleRenderingWithProperties>& theRenderingProperties);

  Standard_EXPORT void Init(const Quantity_ColorRGBA& theRGBAColor);

  Standard_EXPORT void Init(const occ::handle<StepVisual_Colour>& theColor,
                            const double                          theTransparency);

  Standard_EXPORT void Init(const XCAFDoc_VisMaterialCommon& theMaterial);

  Standard_EXPORT void Init(const occ::handle<XCAFDoc_VisMaterial>& theMaterial);

  Standard_EXPORT void Init(const Quantity_Color& theSurfaceColor,
                            const double          theTransparency = 0.0);

  Standard_EXPORT void SetAmbientReflectance(const double theAmbientReflectance);

  Standard_EXPORT void SetAmbientAndDiffuseReflectance(const double theAmbientReflectance,
                                                       const double theDiffuseReflectance);

  Standard_EXPORT void SetAmbientDiffuseAndSpecularReflectance(
    const double          theAmbientReflectance,
    const double          theDiffuseReflectance,
    const double          theSpecularReflectance,
    const double          theSpecularExponent,
    const Quantity_Color& theSpecularColour);

  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleRenderingWithProperties>
                  CreateRenderingProperties() const;

  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleRenderingWithProperties>
    CreateRenderingProperties(const occ::handle<StepVisual_Colour>& theRenderColour) const;

  Standard_EXPORT XCAFDoc_VisMaterialCommon CreateXCAFMaterial() const;

  Quantity_ColorRGBA GetRGBAColor() const
  {
    return Quantity_ColorRGBA(mySurfaceColor, static_cast<float>(1.0 - myTransparency));
  }

  Quantity_Color SurfaceColor() const { return mySurfaceColor; }

  double Transparency() const { return myTransparency; }

  StepVisual_ShadingSurfaceMethod RenderingMethod() const { return myRenderingMethod; }

  void SetRenderingMethod(const StepVisual_ShadingSurfaceMethod theRenderingMethod)
  {
    myRenderingMethod = theRenderingMethod;
  }

  bool IsDefined() const { return myIsDefined; }

  Standard_EXPORT bool IsMaterialConvertible() const;

  Standard_EXPORT double AmbientReflectance() const;

  Standard_EXPORT bool IsAmbientReflectanceDefined() const;

  Standard_EXPORT double DiffuseReflectance() const;

  Standard_EXPORT bool IsDiffuseReflectanceDefined() const;

  Standard_EXPORT double SpecularReflectance() const;

  Standard_EXPORT bool IsSpecularReflectanceDefined() const;

  Standard_EXPORT double SpecularExponent() const;

  Standard_EXPORT bool IsSpecularExponentDefined() const;

  Standard_EXPORT Quantity_Color SpecularColour() const;

  Standard_EXPORT bool IsSpecularColourDefined() const;

private:
  Quantity_Color                  mySurfaceColor;
  double                          myTransparency;
  StepVisual_ShadingSurfaceMethod myRenderingMethod;
  bool                            myIsDefined;

  std::pair<double, bool> myAmbientReflectance;

  std::pair<double, bool> myDiffuseReflectance;

  std::pair<double, bool> mySpecularReflectance;

  std::pair<double, bool> mySpecularExponent;

  std::pair<Quantity_Color, bool> mySpecularColour;
};
