#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
class StepGeom_BSplineSurfaceWithKnots;
class Geom_BSplineSurface;

//! This class implements the mapping between class
//! BSplineSurface from Geom and the class
//! BSplineSurfaceWithKnots from
//! StepGeom which describes a
//! bspline_Surface_with_knots from Prostep
class GeomToStep_MakeBSplineSurfaceWithKnots : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeBSplineSurfaceWithKnots(
    const occ::handle<Geom_BSplineSurface>& Bsplin,
    const StepData_Factors&                 theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_BSplineSurfaceWithKnots>& Value() const;

private:
  occ::handle<StepGeom_BSplineSurfaceWithKnots> theBSplineSurfaceWithKnots;
};

