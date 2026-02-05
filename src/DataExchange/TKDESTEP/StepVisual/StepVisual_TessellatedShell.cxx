// Created on : Thu Mar 24 18:30:12 2022

#include <StepVisual_TessellatedShell.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TessellatedShell, StepVisual_TessellatedItem)

//=================================================================================================

StepVisual_TessellatedShell::StepVisual_TessellatedShell()
{
  myHasTopologicalLink = false;
}

//=================================================================================================

void StepVisual_TessellatedShell::Init(
  const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>&
                                                 theItems,
  const bool                                     theHasTopologicalLink,
  const occ::handle<StepShape_ConnectedFaceSet>& theTopologicalLink)
{
  StepVisual_TessellatedItem::Init(theRepresentationItem_Name);

  myItems = theItems;

  myHasTopologicalLink = theHasTopologicalLink;
  if (myHasTopologicalLink)
  {
    myTopologicalLink = theTopologicalLink;
  }
  else
  {
    myTopologicalLink.Nullify();
  }
}

//=================================================================================================

occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>
  StepVisual_TessellatedShell::Items() const
{
  return myItems;
}

//=================================================================================================

void StepVisual_TessellatedShell::SetItems(
  const occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>&
    theItems)
{
  myItems = theItems;
}

//=================================================================================================

int StepVisual_TessellatedShell::NbItems() const
{
  if (myItems.IsNull())
  {
    return 0;
  }
  return myItems->Length();
}

//=================================================================================================

occ::handle<StepVisual_TessellatedStructuredItem> StepVisual_TessellatedShell::ItemsValue(
  const int theNum) const
{
  return myItems->Value(theNum);
}

//=================================================================================================

occ::handle<StepShape_ConnectedFaceSet> StepVisual_TessellatedShell::TopologicalLink() const
{
  return myTopologicalLink;
}

//=================================================================================================

void StepVisual_TessellatedShell::SetTopologicalLink(
  const occ::handle<StepShape_ConnectedFaceSet>& theTopologicalLink)
{
  myTopologicalLink = theTopologicalLink;
}

//=================================================================================================

bool StepVisual_TessellatedShell::HasTopologicalLink() const
{
  return myHasTopologicalLink;
}
