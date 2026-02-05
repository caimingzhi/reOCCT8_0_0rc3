#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDSToStep_MakeWireError.hpp>
#include <TopoDSToStep_Root.hpp>
class StepShape_TopologicalRepresentationItem;
class TopoDS_Wire;
class TopoDSToStep_Tool;
class Transfer_FinderProcess;

//! This class implements the mapping between classes
//! Wire from TopoDS and TopologicalRepresentationItem from
//! StepShape.
class TopoDSToStep_MakeStepWire : public TopoDSToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopoDSToStep_MakeStepWire();

  Standard_EXPORT TopoDSToStep_MakeStepWire(
    const TopoDS_Wire&                         W,
    TopoDSToStep_Tool&                         T,
    const occ::handle<Transfer_FinderProcess>& FP,
    const StepData_Factors&                    theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const TopoDS_Wire&                         W,
                            TopoDSToStep_Tool&                         T,
                            const occ::handle<Transfer_FinderProcess>& FP,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepShape_TopologicalRepresentationItem>& Value() const;

  Standard_EXPORT TopoDSToStep_MakeWireError Error() const;

private:
  occ::handle<StepShape_TopologicalRepresentationItem> myResult;
  TopoDSToStep_MakeWireError                           myError;
};
