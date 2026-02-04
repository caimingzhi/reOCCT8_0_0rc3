#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_Vector;
class gp_Vec;
class gp_Vec2d;
class Geom_Vector;
class Geom2d_Vector;

//! This class implements the mapping between classes
//! Vector from Geom, Geom2d and Vec, Vec2d from gp, and the class
//! Vector from StepGeom which describes a Vector from
//! Prostep.
class GeomToStep_MakeVector : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeVector(
    const gp_Vec&           V,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeVector(
    const gp_Vec2d&         V,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeVector(
    const occ::handle<Geom_Vector>& V,
    const StepData_Factors&         theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeVector(
    const occ::handle<Geom2d_Vector>& V,
    const StepData_Factors&           theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Vector>& Value() const;

private:
  occ::handle<StepGeom_Vector> theVector;
};

