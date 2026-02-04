#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>

class StepGeom_Polyline;

//! This class implements the mapping between an Array1 of points
//! from gp and a Polyline from StepGeom.
class GeomToStep_MakePolyline : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakePolyline(
    const NCollection_Array1<gp_Pnt>& P,
    const StepData_Factors&           theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakePolyline(
    const NCollection_Array1<gp_Pnt2d>& P,
    const StepData_Factors&             theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_Polyline>& Value() const;

private:
  occ::handle<StepGeom_Polyline> thePolyline;
};

