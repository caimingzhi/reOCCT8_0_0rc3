#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_SweptSurface;
class Geom_SweptSurface;

//! This class implements the mapping between classes
//! SweptSurface from Geom and the class SweptSurface from
//! StepGeom which describes a SweptSurface from prostep.
//! As SweptSurface is an abstract SweptSurface this class
//! is an access to the sub-class required.
class GeomToStep_MakeSweptSurface : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeSweptSurface(
    const occ::handle<Geom_SweptSurface>& S,
    const StepData_Factors&               theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_SweptSurface>& Value() const;

private:
  occ::handle<StepGeom_SweptSurface> theSweptSurface;
};

