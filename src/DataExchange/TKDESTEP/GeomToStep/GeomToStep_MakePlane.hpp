#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
class StepGeom_Plane;
class gp_Pln;
class Geom_Plane;

//! This class implements the mapping between classes
//! Plane from Geom and Pln from gp, and the class
//! Plane from StepGeom which describes a plane from
//! Prostep.
class GeomToStep_MakePlane : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakePlane(
    const gp_Pln&           P,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakePlane(
    const occ::handle<Geom_Plane>& P,
    const StepData_Factors&        theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Plane>& Value() const;

private:
  occ::handle<StepGeom_Plane> thePlane;
};

