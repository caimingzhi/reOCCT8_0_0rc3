#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDSToStep_Root.hpp>
#include <Message_ProgressRange.hpp>

class StepShape_ManifoldSolidBrep;
class StepVisual_TessellatedItem;
class TopoDS_Shell;
class Transfer_FinderProcess;
class TopoDS_Solid;

class TopoDSToStep_MakeManifoldSolidBrep : public TopoDSToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopoDSToStep_MakeManifoldSolidBrep(
    const TopoDS_Shell&                        S,
    const occ::handle<Transfer_FinderProcess>& FP,
    const StepData_Factors&                    theLocalFactors = StepData_Factors(),
    const Message_ProgressRange&               theProgress     = Message_ProgressRange());

  Standard_EXPORT TopoDSToStep_MakeManifoldSolidBrep(
    const TopoDS_Solid&                        S,
    const occ::handle<Transfer_FinderProcess>& FP,
    const StepData_Factors&                    theLocalFactors = StepData_Factors(),
    const Message_ProgressRange&               theProgress     = Message_ProgressRange());

  Standard_EXPORT const occ::handle<StepShape_ManifoldSolidBrep>& Value() const;
  Standard_EXPORT const occ::handle<StepVisual_TessellatedItem>& TessellatedValue() const;

private:
  occ::handle<StepShape_ManifoldSolidBrep> theManifoldSolidBrep;
  occ::handle<StepVisual_TessellatedItem>  theTessellatedItem;
};
