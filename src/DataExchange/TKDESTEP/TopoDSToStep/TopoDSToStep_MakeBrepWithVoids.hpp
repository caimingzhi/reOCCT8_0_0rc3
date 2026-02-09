#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDSToStep_Root.hpp>
#include <Message_ProgressRange.hpp>

class StepShape_BrepWithVoids;
class StepVisual_TessellatedItem;
class TopoDS_Solid;
class Transfer_FinderProcess;

class TopoDSToStep_MakeBrepWithVoids : public TopoDSToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopoDSToStep_MakeBrepWithVoids(
    const TopoDS_Solid&                        S,
    const occ::handle<Transfer_FinderProcess>& FP,
    const StepData_Factors&                    theLocalFactors = StepData_Factors(),
    const Message_ProgressRange&               theProgress     = Message_ProgressRange());

  Standard_EXPORT const occ::handle<StepShape_BrepWithVoids>& Value() const;
  Standard_EXPORT const occ::handle<StepVisual_TessellatedItem>& TessellatedValue() const;

private:
  occ::handle<StepShape_BrepWithVoids>    theBrepWithVoids;
  occ::handle<StepVisual_TessellatedItem> theTessellatedItem;
};
