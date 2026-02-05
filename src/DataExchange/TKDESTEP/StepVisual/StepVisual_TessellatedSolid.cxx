// Created on : Thu Mar 24 18:30:12 2022

#include <StepVisual_TessellatedSolid.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TessellatedSolid, StepVisual_TessellatedItem)

//=================================================================================================

StepVisual_TessellatedSolid::StepVisual_TessellatedSolid()
{
  myHasGeometricLink = false;
}

//=================================================================================================

void StepVisual_TessellatedSolid::Init(
  const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>&
                                                  theItems,
  const bool                                      theHasGeometricLink,
  const occ::handle<StepShape_ManifoldSolidBrep>& theGeometricLink)
{
  StepVisual_TessellatedItem::Init(theRepresentationItem_Name);

  myItems = theItems;

  myHasGeometricLink = theHasGeometricLink;
  if (myHasGeometricLink)
  {
    myGeometricLink = theGeometricLink;
  }
  else
  {
    myGeometricLink.Nullify();
  }
}

//=================================================================================================

occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>
  StepVisual_TessellatedSolid::Items() const
{
  return myItems;
}

//=================================================================================================

void StepVisual_TessellatedSolid::SetItems(
  const occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>&
    theItems)
{
  myItems = theItems;
}

//=================================================================================================

int StepVisual_TessellatedSolid::NbItems() const
{
  if (myItems.IsNull())
  {
    return 0;
  }
  return myItems->Length();
}

//=================================================================================================

occ::handle<StepVisual_TessellatedStructuredItem> StepVisual_TessellatedSolid::ItemsValue(
  const int theNum) const
{
  return myItems->Value(theNum);
}

//=================================================================================================

occ::handle<StepShape_ManifoldSolidBrep> StepVisual_TessellatedSolid::GeometricLink() const
{
  return myGeometricLink;
}

//=================================================================================================

void StepVisual_TessellatedSolid::SetGeometricLink(
  const occ::handle<StepShape_ManifoldSolidBrep>& theGeometricLink)
{
  myGeometricLink = theGeometricLink;
}

//=================================================================================================

bool StepVisual_TessellatedSolid::HasGeometricLink() const
{
  return myHasGeometricLink;
}
