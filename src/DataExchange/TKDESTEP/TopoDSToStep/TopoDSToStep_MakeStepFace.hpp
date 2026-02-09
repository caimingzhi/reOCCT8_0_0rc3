#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDSToStep_MakeFaceError.hpp>
#include <TopoDSToStep_Root.hpp>
class StepShape_TopologicalRepresentationItem;
class TopoDS_Face;
class TopoDSToStep_Tool;
class Transfer_FinderProcess;

class TopoDSToStep_MakeStepFace : public TopoDSToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopoDSToStep_MakeStepFace();

  Standard_EXPORT TopoDSToStep_MakeStepFace(
    const TopoDS_Face&                         F,
    TopoDSToStep_Tool&                         T,
    const occ::handle<Transfer_FinderProcess>& FP,
    const StepData_Factors&                    theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const TopoDS_Face&                         F,
                            TopoDSToStep_Tool&                         T,
                            const occ::handle<Transfer_FinderProcess>& FP,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepShape_TopologicalRepresentationItem>& Value() const;

  Standard_EXPORT TopoDSToStep_MakeFaceError Error() const;

private:
  occ::handle<StepShape_TopologicalRepresentationItem> myResult;
  TopoDSToStep_MakeFaceError                           myError;
};
