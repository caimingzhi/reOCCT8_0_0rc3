#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedItem.hpp>

#include <StepVisual_TessellatedEdgeOrVertex.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_PathOrCompositeCurve.hpp>

class StepVisual_TessellatedWire : public StepVisual_TessellatedItem
{

public:
  Standard_EXPORT StepVisual_TessellatedWire();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
    const occ::handle<NCollection_HArray1<StepVisual_TessellatedEdgeOrVertex>>& theItems,
    const bool                             theHasGeometricModelLink,
    const StepVisual_PathOrCompositeCurve& theGeometricModelLink);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepVisual_TessellatedEdgeOrVertex>> Items()
    const;

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepVisual_TessellatedEdgeOrVertex>>& theItems);

  Standard_EXPORT int NbItems() const;

  Standard_EXPORT const StepVisual_TessellatedEdgeOrVertex& ItemsValue(const int theNum) const;

  Standard_EXPORT StepVisual_PathOrCompositeCurve GeometricModelLink() const;

  Standard_EXPORT void SetGeometricModelLink(
    const StepVisual_PathOrCompositeCurve& theGeometricModelLink);

  Standard_EXPORT bool HasGeometricModelLink() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedWire, StepVisual_TessellatedItem)

private:
  occ::handle<NCollection_HArray1<StepVisual_TessellatedEdgeOrVertex>> myItems;
  StepVisual_PathOrCompositeCurve                                      myGeometricModelLink;
  bool                                                                 myHasGeometricModelLink;
};
