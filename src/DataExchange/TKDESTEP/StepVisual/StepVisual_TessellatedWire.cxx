

#include <StepVisual_TessellatedWire.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TessellatedWire, StepVisual_TessellatedItem)

StepVisual_TessellatedWire::StepVisual_TessellatedWire()
{
  myHasGeometricModelLink = false;
}

void StepVisual_TessellatedWire::Init(
  const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
  const occ::handle<NCollection_HArray1<StepVisual_TessellatedEdgeOrVertex>>& theItems,
  const bool                             theHasGeometricModelLink,
  const StepVisual_PathOrCompositeCurve& theGeometricModelLink)
{
  StepVisual_TessellatedItem::Init(theRepresentationItem_Name);

  myItems = theItems;

  myHasGeometricModelLink = theHasGeometricModelLink;
  if (myHasGeometricModelLink)
  {
    myGeometricModelLink = theGeometricModelLink;
  }
  else
  {
    myGeometricModelLink = StepVisual_PathOrCompositeCurve();
  }
}

occ::handle<NCollection_HArray1<StepVisual_TessellatedEdgeOrVertex>> StepVisual_TessellatedWire::
  Items() const
{
  return myItems;
}

void StepVisual_TessellatedWire::SetItems(
  const occ::handle<NCollection_HArray1<StepVisual_TessellatedEdgeOrVertex>>& theItems)
{
  myItems = theItems;
}

int StepVisual_TessellatedWire::NbItems() const
{
  if (myItems.IsNull())
  {
    return 0;
  }
  return myItems->Length();
}

const StepVisual_TessellatedEdgeOrVertex& StepVisual_TessellatedWire::ItemsValue(
  const int theNum) const
{
  return myItems->Value(theNum);
}

StepVisual_PathOrCompositeCurve StepVisual_TessellatedWire::GeometricModelLink() const
{
  return myGeometricModelLink;
}

void StepVisual_TessellatedWire::SetGeometricModelLink(
  const StepVisual_PathOrCompositeCurve& theGeometricModelLink)
{
  myGeometricModelLink = theGeometricModelLink;
}

bool StepVisual_TessellatedWire::HasGeometricModelLink() const
{
  return myHasGeometricModelLink;
}
