#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
class StepGeom_Conic;
class Geom_Conic;
class Geom2d_Conic;

//! This class implements the mapping between classes
//! Conic from Geom and the class Conic from StepGeom
//! which describes a Conic from prostep. As Conic is an abstract
//! Conic this class is an access to the sub-class required.
class GeomToStep_MakeConic : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeConic(
    const occ::handle<Geom_Conic>& C,
    const StepData_Factors&        theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeConic(
    const occ::handle<Geom2d_Conic>& C,
    const StepData_Factors&          theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Conic>& Value() const;

private:
  occ::handle<StepGeom_Conic> theConic;
};
