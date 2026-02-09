#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

enum Vrml_ConeParts
{
  Vrml_ConeSIDES,
  Vrml_ConeBOTTOM,
  Vrml_ConeALL
};

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>

class Vrml_Cone
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Cone(const Vrml_ConeParts aParts        = Vrml_ConeALL,
                            const double         aBottomRadius = 1,
                            const double         aHeight       = 2);

  Standard_EXPORT void SetParts(const Vrml_ConeParts aParts);

  Standard_EXPORT Vrml_ConeParts Parts() const;

  Standard_EXPORT void SetBottomRadius(const double aBottomRadius);

  Standard_EXPORT double BottomRadius() const;

  Standard_EXPORT void SetHeight(const double aHeight);

  Standard_EXPORT double Height() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  Vrml_ConeParts myParts;
  double         myBottomRadius;
  double         myHeight;
};
