#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDSToStep_MakeVertexError.hpp>
#include <TopoDSToStep_Root.hpp>
class StepShape_TopologicalRepresentationItem;
class TopoDS_Vertex;
class TopoDSToStep_Tool;
class Transfer_FinderProcess;

//! This class implements the mapping between classes
//! Vertex from TopoDS and TopologicalRepresentationItem from
//! StepShape.
class TopoDSToStep_MakeStepVertex : public TopoDSToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopoDSToStep_MakeStepVertex();

  Standard_EXPORT TopoDSToStep_MakeStepVertex(
    const TopoDS_Vertex&                       V,
    TopoDSToStep_Tool&                         T,
    const occ::handle<Transfer_FinderProcess>& FP,
    const StepData_Factors&                    theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const TopoDS_Vertex&                       V,
                            TopoDSToStep_Tool&                         T,
                            const occ::handle<Transfer_FinderProcess>& FP,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepShape_TopologicalRepresentationItem>& Value() const;

  Standard_EXPORT TopoDSToStep_MakeVertexError Error() const;

private:
  occ::handle<StepShape_TopologicalRepresentationItem> myResult;
  TopoDSToStep_MakeVertexError                         myError;
};

