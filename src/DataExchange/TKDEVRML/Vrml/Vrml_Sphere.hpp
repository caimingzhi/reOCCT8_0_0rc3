#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>

//! defines a Sphere node of VRML specifying geometry shapes.
//! This node represents a sphere.
//! By default, the sphere is centred at (0,0,0) and has a radius of 1.
class Vrml_Sphere
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Sphere(const double aRadius = 1);

  Standard_EXPORT void SetRadius(const double aRadius);

  Standard_EXPORT double Radius() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  double myRadius;
};

