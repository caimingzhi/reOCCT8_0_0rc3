#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_ElementarySurface;
class Geom_ElementarySurface;

//! This class implements the mapping between classes
//! ElementarySurface from Geom and the class ElementarySurface
//! from StepGeom which describes a ElementarySurface from
//! prostep. As ElementarySurface is an abstract Surface this
//! class is an access to the sub-class required.
class GeomToStep_MakeElementarySurface : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeElementarySurface(
    const occ::handle<Geom_ElementarySurface>& S,
    const StepData_Factors&                    theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_ElementarySurface>& Value() const;

private:
  occ::handle<StepGeom_ElementarySurface> theElementarySurface;
};

