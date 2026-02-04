#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_Ellipse;
class gp_Elips;
class Geom_Ellipse;
class Geom2d_Ellipse;

//! This class implements the mapping between classes
//! Ellipse from Geom, and Circ from gp, and the class
//! Ellipse from StepGeom which describes a Ellipse from
//! Prostep.
class GeomToStep_MakeEllipse : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeEllipse(
    const gp_Elips&         C,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeEllipse(
    const occ::handle<Geom_Ellipse>& C,
    const StepData_Factors&          theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeEllipse(
    const occ::handle<Geom2d_Ellipse>& C,
    const StepData_Factors&            theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Ellipse>& Value() const;

private:
  occ::handle<StepGeom_Ellipse> theEllipse;
};

