#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Quantity_Color.hpp>
#include <gp_Vec.hpp>
#include <Standard_OStream.hpp>

class Vrml_PointLight
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_PointLight();

  Standard_EXPORT Vrml_PointLight(const bool            aOnOff,
                                  const double          aIntensity,
                                  const Quantity_Color& aColor,
                                  const gp_Vec&         aLocation);

  Standard_EXPORT void SetOnOff(const bool aOnOff);

  Standard_EXPORT bool OnOff() const;

  Standard_EXPORT void SetIntensity(const double aIntensity);

  Standard_EXPORT double Intensity() const;

  Standard_EXPORT void SetColor(const Quantity_Color& aColor);

  Standard_EXPORT Quantity_Color Color() const;

  Standard_EXPORT void SetLocation(const gp_Vec& aLocation);

  Standard_EXPORT gp_Vec Location() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  bool           myOnOff;
  double         myIntensity;
  Quantity_Color myColor;
  gp_Vec         myLocation;
};
