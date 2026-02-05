#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
class StepGeom_Parabola;
class Geom2d_Parabola;
class Geom_Parabola;

//! This class implements the mapping between the class
//! Parabola from Geom and the class Parabola from
//! StepGeom which describes a Parabola from ProSTEP
class GeomToStep_MakeParabola : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeParabola(
    const occ::handle<Geom2d_Parabola>& C,
    const StepData_Factors&             theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeParabola(
    const occ::handle<Geom_Parabola>& C,
    const StepData_Factors&           theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Parabola>& Value() const;

private:
  occ::handle<StepGeom_Parabola> theParabola;
};
