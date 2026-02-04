#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
class StepGeom_ConicalSurface;
class Geom_ConicalSurface;

//! This class implements the mapping between class
//! ConicalSurface from Geom and the class
//! ConicalSurface from StepGeom which describes a
//! conical_surface from Prostep
class GeomToStep_MakeConicalSurface : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeConicalSurface(
    const occ::handle<Geom_ConicalSurface>& CSurf,
    const StepData_Factors&                 theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_ConicalSurface>& Value() const;

private:
  occ::handle<StepGeom_ConicalSurface> theConicalSurface;
};

