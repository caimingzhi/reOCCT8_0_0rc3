#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedItem.hpp>

#include <StepVisual_TessellatedStructuredItem.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_ConnectedFaceSet.hpp>

class StepVisual_TessellatedShell : public StepVisual_TessellatedItem
{

public:
  Standard_EXPORT StepVisual_TessellatedShell();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>&
                                                   theItems,
    const bool                                     theHasTopologicalLink,
    const occ::handle<StepShape_ConnectedFaceSet>& theTopologicalLink);

  Standard_EXPORT occ::handle<
    NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>
    Items() const;

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>&
      theItems);

  Standard_EXPORT int NbItems() const;

  Standard_EXPORT occ::handle<StepVisual_TessellatedStructuredItem> ItemsValue(
    const int theNum) const;

  Standard_EXPORT occ::handle<StepShape_ConnectedFaceSet> TopologicalLink() const;

  Standard_EXPORT void SetTopologicalLink(
    const occ::handle<StepShape_ConnectedFaceSet>& theTopologicalLink);

  Standard_EXPORT bool HasTopologicalLink() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedShell, StepVisual_TessellatedItem)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>> myItems;
  occ::handle<StepShape_ConnectedFaceSet> myTopologicalLink;
  bool                                    myHasTopologicalLink;
};
