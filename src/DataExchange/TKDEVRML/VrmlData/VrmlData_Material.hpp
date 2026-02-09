#pragma once

#include <VrmlData_Node.hpp>
#include <Quantity_Color.hpp>

class VrmlData_Material : public VrmlData_Node
{
public:
  Standard_EXPORT VrmlData_Material();

  Standard_EXPORT VrmlData_Material(const VrmlData_Scene& theScene,
                                    const char*           theName,
                                    const double          theAmbientIntensity = -1.,
                                    const double          theShininess        = -1.,
                                    const double          theTransparency     = -1.);

  inline double AmbientIntensity() const { return myAmbientIntensity; }

  inline double Shininess() const { return myShininess; }

  inline double Transparency() const { return myTransparency; }

  inline const Quantity_Color& AmbientColor() const { return myAmbientColor; }

  inline const Quantity_Color& DiffuseColor() const { return myDiffuseColor; }

  inline const Quantity_Color& EmissiveColor() const { return myEmissiveColor; }

  inline const Quantity_Color& SpecularColor() const { return mySpecularColor; }

  inline void SetAmbientIntensity(const double theAmbientIntensity)
  {
    myAmbientIntensity = theAmbientIntensity;
  }

  inline void SetShininess(const double theShininess) { myShininess = theShininess; }

  inline void SetTransparency(const double theTransparency) { myTransparency = theTransparency; }

  inline void SetAmbientColor(const Quantity_Color& theColor) { myAmbientColor = theColor; }

  inline void SetDiffuseColor(const Quantity_Color& theColor) { myDiffuseColor = theColor; }

  inline void SetEmissiveColor(const Quantity_Color& theColor) { myEmissiveColor = theColor; }

  inline void SetSpecularColor(const Quantity_Color& theColor) { mySpecularColor = theColor; }

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

  Standard_EXPORT bool IsDefault() const override;

private:
  double         myAmbientIntensity;
  double         myShininess;
  double         myTransparency;
  Quantity_Color myAmbientColor;
  Quantity_Color myDiffuseColor;
  Quantity_Color myEmissiveColor;
  Quantity_Color mySpecularColor;

public:
  DEFINE_STANDARD_RTTIEXT(VrmlData_Material, VrmlData_Node)
};
