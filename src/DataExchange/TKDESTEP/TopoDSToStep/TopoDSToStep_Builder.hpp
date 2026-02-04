#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Message_ProgressRange.hpp>
#include <StepData_Factors.hpp>
#include <TopoDSToStep_BuilderError.hpp>
#include <TopoDSToStep_Root.hpp>

class StepShape_TopologicalRepresentationItem;
class StepVisual_TessellatedItem;
class TopoDS_Shape;
class TopoDSToStep_Tool;
class Transfer_FinderProcess;

//! This builder Class provides services to build
//! a ProSTEP Shape model from a Cas.Cad BRep.
class TopoDSToStep_Builder : public TopoDSToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopoDSToStep_Builder();

  Standard_EXPORT TopoDSToStep_Builder(
    const TopoDS_Shape&                        S,
    TopoDSToStep_Tool&                         T,
    const occ::handle<Transfer_FinderProcess>& FP,
    const int                                  theTessellatedGeomParam,
    const StepData_Factors&                    theLocalFactors = StepData_Factors(),
    const Message_ProgressRange&               theProgress     = Message_ProgressRange());

  Standard_EXPORT void Init(const TopoDS_Shape&                        S,
                            TopoDSToStep_Tool&                         T,
                            const occ::handle<Transfer_FinderProcess>& FP,
                            const int                                  theTessellatedGeomParam,
                            const StepData_Factors&      theLocalFactors = StepData_Factors(),
                            const Message_ProgressRange& theProgress     = Message_ProgressRange());

  Standard_EXPORT TopoDSToStep_BuilderError Error() const;

  Standard_EXPORT const occ::handle<StepShape_TopologicalRepresentationItem>& Value() const;
  Standard_EXPORT const occ::handle<StepVisual_TessellatedItem>& TessellatedValue() const;

private:
  occ::handle<StepShape_TopologicalRepresentationItem> myResult;
  occ::handle<StepVisual_TessellatedItem>              myTessellatedResult;
  TopoDSToStep_BuilderError                            myError;
};

