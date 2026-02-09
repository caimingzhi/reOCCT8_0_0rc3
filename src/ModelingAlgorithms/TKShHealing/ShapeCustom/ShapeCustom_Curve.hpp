#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom_Curve;

class ShapeCustom_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeCustom_Curve();

  Standard_EXPORT ShapeCustom_Curve(const occ::handle<Geom_Curve>& C);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C);

  Standard_EXPORT occ::handle<Geom_Curve> ConvertToPeriodic(const bool   substitute,
                                                            const double preci = -1);

private:
  occ::handle<Geom_Curve> myCurve;
};
