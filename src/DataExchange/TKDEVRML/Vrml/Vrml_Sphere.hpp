#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>

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
