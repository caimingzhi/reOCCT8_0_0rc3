#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class Geom_Plane;

class BRepBuilderAPI
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Plane(const occ::handle<Geom_Plane>& P);

  Standard_EXPORT static const occ::handle<Geom_Plane>& Plane();

  Standard_EXPORT static void Precision(const double P);

  Standard_EXPORT static double Precision();
};
