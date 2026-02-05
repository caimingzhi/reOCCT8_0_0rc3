#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_Surface;
class Geom_Surface;

//! This class implements the mapping between classes
//! Surface from Geom and the class Surface from StepGeom which
//! describes a Surface from prostep. As Surface is an abstract
//! Surface this class is an access to the sub-class required.
class GeomToStep_MakeSurface : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeSurface(
    const occ::handle<Geom_Surface>& C,
    const StepData_Factors&          theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Surface>& Value() const;

private:
  occ::handle<StepGeom_Surface> theSurface;
};
