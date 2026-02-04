#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Quantity_Color.hpp>
#include <gp_Vec.hpp>
#include <Standard_OStream.hpp>

//! defines a directional light node of VRML specifying
//! properties of lights.
//! This node defines a directional light source that illuminates
//! along rays parallel to a given 3-dimensional vector
//! Color is written as an RGB triple.
//! Light intensity must be in the range 0.0 to 1.0, inclusive.
class Vrml_DirectionalLight
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_DirectionalLight();

  Standard_EXPORT Vrml_DirectionalLight(const bool            aOnOff,
                                        const double          aIntensity,
                                        const Quantity_Color& aColor,
                                        const gp_Vec&         aDirection);

  Standard_EXPORT void SetOnOff(const bool aOnOff);

  Standard_EXPORT bool OnOff() const;

  Standard_EXPORT void SetIntensity(const double aIntensity);

  Standard_EXPORT double Intensity() const;

  Standard_EXPORT void SetColor(const Quantity_Color& aColor);

  Standard_EXPORT Quantity_Color Color() const;

  Standard_EXPORT void SetDirection(const gp_Vec& aDirection);

  Standard_EXPORT gp_Vec Direction() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  bool           myOnOff;
  double         myIntensity;
  Quantity_Color myColor;
  gp_Vec         myDirection;
};

