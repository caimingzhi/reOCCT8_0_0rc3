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

//! defines a Cylinder node of VRML specifying geometry shapes.
//! This node represents a simple capped cylinder centred around the y-axis.
//! By default, the cylinder is centred at (0,0,0)
//! and has size of -1 to +1 in the all three dimensions.
//! The cylinder has three parts:
//! the sides, the top (y=+1) and the bottom (y=-1)
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
