#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDSToStep_Root.hpp>
class StepShape_GeometricCurveSet;
class TopoDS_Shape;
class Transfer_FinderProcess;

//! This class implements the mapping between a Shape
//! from TopoDS and a GeometricCurveSet from StepShape in order
//! to create a GeometricallyBoundedWireframeRepresentation.
class TopoDSToStep_MakeGeometricCurveSet : public TopoDSToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopoDSToStep_MakeGeometricCurveSet(
    const TopoDS_Shape&                        SH,
    const occ::handle<Transfer_FinderProcess>& FP,
    const StepData_Factors&                    theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepShape_GeometricCurveSet>& Value() const;

private:
  occ::handle<StepShape_GeometricCurveSet> theGeometricCurveSet;
};

