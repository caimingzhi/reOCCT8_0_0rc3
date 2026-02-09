#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedItem.hpp>

#include <StepVisual_TessellatedStructuredItem.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_ManifoldSolidBrep.hpp>

class StepVisual_TessellatedSolid : public StepVisual_TessellatedItem
{

public:
  Standard_EXPORT StepVisual_TessellatedSolid();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>&
                                                    theItems,
    const bool                                      theHasGeometricLink,
    const occ::handle<StepShape_ManifoldSolidBrep>& theGeometricLink);

  Standard_EXPORT occ::handle<
    NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>
    Items() const;

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>&
      theItems);

  Standard_EXPORT int NbItems() const;

  Standard_EXPORT occ::handle<StepVisual_TessellatedStructuredItem> ItemsValue(
    const int theNum) const;

  Standard_EXPORT occ::handle<StepShape_ManifoldSolidBrep> GeometricLink() const;

  Standard_EXPORT void SetGeometricLink(
    const occ::handle<StepShape_ManifoldSolidBrep>& theGeometricLink);

  Standard_EXPORT bool HasGeometricLink() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedSolid, StepVisual_TessellatedItem)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>> myItems;
  occ::handle<StepShape_ManifoldSolidBrep> myGeometricLink;
  bool                                     myHasGeometricLink;
};
