#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_BoundedSurface;
class Geom_BoundedSurface;

//! This class implements the mapping between classes
//! BoundedSurface from Geom and the class BoundedSurface from
//! StepGeom which describes a BoundedSurface from prostep.
//! As BoundedSurface is an abstract BoundedSurface this class
//! is an access to the sub-class required.
class GeomToStep_MakeBoundedSurface : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeBoundedSurface(
    const occ::handle<Geom_BoundedSurface>& C,
    const StepData_Factors&                 theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_BoundedSurface>& Value() const;

private:
  occ::handle<StepGeom_BoundedSurface> theBoundedSurface;
};

