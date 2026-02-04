#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDSToStep_Root.hpp>
#include <Message_ProgressRange.hpp>

class StepShape_FacetedBrep;
class StepVisual_TessellatedItem;
class TopoDS_Shell;
class Transfer_FinderProcess;
class TopoDS_Solid;

//! This class implements the mapping between classes
//! Shell or Solid from TopoDS and FacetedBrep from
//! StepShape. All the topology and geometry comprised
//! into the shell or the solid are taken into account and
//! translated.
class TopoDSToStep_MakeFacetedBrep : public TopoDSToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopoDSToStep_MakeFacetedBrep(
    const TopoDS_Shell&                        S,
    const occ::handle<Transfer_FinderProcess>& FP,
    const StepData_Factors&                    theLocalFactors = StepData_Factors(),
    const Message_ProgressRange&               theProgress     = Message_ProgressRange());

  Standard_EXPORT TopoDSToStep_MakeFacetedBrep(
    const TopoDS_Solid&                        S,
    const occ::handle<Transfer_FinderProcess>& FP,
    const StepData_Factors&                    theLocalFactors = StepData_Factors(),
    const Message_ProgressRange&               theProgress     = Message_ProgressRange());

  Standard_EXPORT const occ::handle<StepShape_FacetedBrep>& Value() const;
  Standard_EXPORT const occ::handle<StepVisual_TessellatedItem>& TessellatedValue() const;

private:
  occ::handle<StepShape_FacetedBrep>      theFacetedBrep;
  occ::handle<StepVisual_TessellatedItem> theTessellatedItem;
};

