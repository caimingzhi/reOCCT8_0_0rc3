#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_Circle;
class gp_Circ;
class Geom_Circle;
class Geom2d_Circle;

//! This class implements the mapping between classes
//! Circle from Geom, and Circ from gp, and the class
//! Circle from StepGeom which describes a circle from
//! Prostep.
class GeomToStep_MakeCircle : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeCircle(
    const gp_Circ&          C,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeCircle(
    const occ::handle<Geom_Circle>& C,
    const StepData_Factors&         theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeCircle(
    const occ::handle<Geom2d_Circle>& C,
    const StepData_Factors&           theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Circle>& Value() const;

private:
  occ::handle<StepGeom_Circle> theCircle;
};

