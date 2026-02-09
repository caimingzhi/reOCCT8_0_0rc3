#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

enum Vrml_CylinderParts
{
  Vrml_CylinderSIDES,
  Vrml_CylinderTOP,
  Vrml_CylinderBOTTOM,
  Vrml_CylinderALL
};

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>

class Vrml_Cylinder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Cylinder(const Vrml_CylinderParts aParts  = Vrml_CylinderALL,
                                const double             aRadius = 1,
                                const double             aHeight = 2);

  Standard_EXPORT void SetParts(const Vrml_CylinderParts aParts);

  Standard_EXPORT Vrml_CylinderParts Parts() const;

  Standard_EXPORT void SetRadius(const double aRadius);

  Standard_EXPORT double Radius() const;

  Standard_EXPORT void SetHeight(const double aHeight);

  Standard_EXPORT double Height() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  Vrml_CylinderParts myParts;
  double             myRadius;
  double             myHeight;
};
