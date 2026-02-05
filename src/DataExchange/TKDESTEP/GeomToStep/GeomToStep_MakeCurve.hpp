#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
class StepGeom_Curve;
class Geom_Curve;
class Geom2d_Curve;

//! This class implements the mapping between classes
//! Curve from Geom and the class Curve from StepGeom which
//! describes a Curve from prostep. As Curve is an
//! abstract curve this class an access to the sub-class required.
class GeomToStep_MakeCurve : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeCurve(
    const occ::handle<Geom_Curve>& C,
    const StepData_Factors&        theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeCurve(
    const occ::handle<Geom2d_Curve>& C,
    const StepData_Factors&          theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Curve>& Value() const;

private:
  occ::handle<StepGeom_Curve> theCurve;
};
