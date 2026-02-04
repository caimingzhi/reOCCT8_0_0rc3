#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
class StepGeom_Hyperbola;
class Geom2d_Hyperbola;
class Geom_Hyperbola;

//! This class implements the mapping between the class
//! Hyperbola from Geom and the class Hyperbola from
//! StepGeom which describes a Hyperbola from ProSTEP
class GeomToStep_MakeHyperbola : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeHyperbola(
    const occ::handle<Geom2d_Hyperbola>& C,
    const StepData_Factors&              theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeHyperbola(
    const occ::handle<Geom_Hyperbola>& C,
    const StepData_Factors&            theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Hyperbola>& Value() const;

private:
  occ::handle<StepGeom_Hyperbola> theHyperbola;
};

