#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_ToroidalSurface;
class Geom_ToroidalSurface;

//! This class implements the mapping between class
//! ToroidalSurface from Geom and the class
//! ToroidalSurface from StepGeom which describes a
//! toroidal_surface from Prostep
class GeomToStep_MakeToroidalSurface : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeToroidalSurface(
    const occ::handle<Geom_ToroidalSurface>& TorSurf,
    const StepData_Factors&                  theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_ToroidalSurface>& Value() const;

private:
  occ::handle<StepGeom_ToroidalSurface> theToroidalSurface;
};
