#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface;
class Geom_BSplineSurface;

class GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface(
    const occ::handle<Geom_BSplineSurface>& Bsplin,
    const StepData_Factors&                 theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface>&
                        Value() const;

private:
  occ::handle<StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface>
    theBSplineSurfaceWithKnotsAndRationalBSplineSurface;
};
