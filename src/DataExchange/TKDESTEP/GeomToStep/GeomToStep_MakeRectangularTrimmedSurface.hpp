#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_RectangularTrimmedSurface;
class Geom_RectangularTrimmedSurface;

//! This class implements the mapping between class
//! RectangularTrimmedSurface from Geom and the class
//! RectangularTrimmedSurface from
//! StepGeom which describes a
//! rectangular_trimmed_surface from ISO-IS 10303-42
class GeomToStep_MakeRectangularTrimmedSurface : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeRectangularTrimmedSurface(
    const occ::handle<Geom_RectangularTrimmedSurface>& RTSurf,
    const StepData_Factors&                            theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_RectangularTrimmedSurface>& Value() const;

private:
  occ::handle<StepGeom_RectangularTrimmedSurface> theRectangularTrimmedSurface;
};
