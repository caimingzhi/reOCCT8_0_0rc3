#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Quantity_Color.hpp>
#include <gp_Vec.hpp>
#include <Standard_OStream.hpp>

class Vrml_SpotLight
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_SpotLight();

  Standard_EXPORT Vrml_SpotLight(const bool            aOnOff,
                                 const double          aIntensity,
                                 const Quantity_Color& aColor,
                                 const gp_Vec&         aLocation,
                                 const gp_Vec&         aDirection,
                                 const double          aDropOffRate,
                                 const double          aCutOffAngle);

  Standard_EXPORT void SetOnOff(const bool anOnOff);

  Standard_EXPORT bool OnOff() const;

  Standard_EXPORT void SetIntensity(const double aIntensity);

  Standard_EXPORT double Intensity() const;

  Standard_EXPORT void SetColor(const Quantity_Color& aColor);

  Standard_EXPORT Quantity_Color Color() const;

  Standard_EXPORT void SetLocation(const gp_Vec& aLocation);

  Standard_EXPORT gp_Vec Location() const;

  Standard_EXPORT void SetDirection(const gp_Vec& aDirection);

  Standard_EXPORT gp_Vec Direction() const;

  Standard_EXPORT void SetDropOffRate(const double aDropOffRate);

  Standard_EXPORT double DropOffRate() const;

  Standard_EXPORT void SetCutOffAngle(const double aCutOffAngle);

  Standard_EXPORT double CutOffAngle() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  bool           myOnOff;
  double         myIntensity;
  Quantity_Color myColor;
  gp_Vec         myLocation;
  gp_Vec         myDirection;
  double         myDropOffRate;
  double         myCutOffAngle;
};
