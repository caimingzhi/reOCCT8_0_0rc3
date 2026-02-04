#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDSToStep_Root.hpp>
#include <Message_ProgressRange.hpp>

class StepShape_FacetedBrepAndBrepWithVoids;
class StepVisual_TessellatedItem;
class TopoDS_Solid;
class Transfer_FinderProcess;

//! This class implements the mapping between classes
//! Solid from TopoDS and FacetedBrepAndBrepWithVoids from
//! StepShape. All the topology and geometry comprised
//! into the shell or the solid are taken into account and
//! translated.
class TopoDSToStep_MakeFacetedBrepAndBrepWithVoids : public TopoDSToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopoDSToStep_MakeFacetedBrepAndBrepWithVoids(
    const TopoDS_Solid&                        S,
    const occ::handle<Transfer_FinderProcess>& FP,
    const StepData_Factors&                    theLocalFactors = StepData_Factors(),
    const Message_ProgressRange&               theProgress     = Message_ProgressRange());

  Standard_EXPORT const occ::handle<StepShape_FacetedBrepAndBrepWithVoids>& Value() const;
  Standard_EXPORT const occ::handle<StepVisual_TessellatedItem>& TessellatedValue() const;

private:
  occ::handle<StepShape_FacetedBrepAndBrepWithVoids> theFacetedBrepAndBrepWithVoids;
  occ::handle<StepVisual_TessellatedItem>            theTessellatedItem;
};

