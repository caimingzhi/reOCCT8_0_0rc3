// Created on : Thu Mar 24 18:30:12 2022

#include <StepVisual_TessellatedEdge.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TessellatedEdge, StepVisual_TessellatedStructuredItem)

//=================================================================================================

StepVisual_TessellatedEdge::StepVisual_TessellatedEdge()
{
  myHasGeometricLink = false;
}

//=================================================================================================

void StepVisual_TessellatedEdge::Init(
  const occ::handle<TCollection_HAsciiString>&   theRepresentationItem_Name,
  const occ::handle<StepVisual_CoordinatesList>& theCoordinates,
  const bool                                     theHasGeometricLink,
  const StepVisual_EdgeOrCurve&                  theGeometricLink,
  const occ::handle<NCollection_HArray1<int>>&   theLineStrip)
{
  StepVisual_TessellatedStructuredItem::Init(theRepresentationItem_Name);

  myCoordinates = theCoordinates;

  myHasGeometricLink = theHasGeometricLink;
  if (myHasGeometricLink)
  {
    myGeometricLink = theGeometricLink;
  }
  else
  {
    myGeometricLink = StepVisual_EdgeOrCurve();
  }

  myLineStrip = theLineStrip;
}

//=================================================================================================

occ::handle<StepVisual_CoordinatesList> StepVisual_TessellatedEdge::Coordinates() const
{
  return myCoordinates;
}

//=================================================================================================

void StepVisual_TessellatedEdge::SetCoordinates(
  const occ::handle<StepVisual_CoordinatesList>& theCoordinates)
{
  myCoordinates = theCoordinates;
}

//=================================================================================================

StepVisual_EdgeOrCurve StepVisual_TessellatedEdge::GeometricLink() const
{
  return myGeometricLink;
}

//=================================================================================================

void StepVisual_TessellatedEdge::SetGeometricLink(const StepVisual_EdgeOrCurve& theGeometricLink)
{
  myGeometricLink = theGeometricLink;
}

//=================================================================================================

bool StepVisual_TessellatedEdge::HasGeometricLink() const
{
  return myHasGeometricLink;
}

//=================================================================================================

occ::handle<NCollection_HArray1<int>> StepVisual_TessellatedEdge::LineStrip() const
{
  return myLineStrip;
}

//=================================================================================================

void StepVisual_TessellatedEdge::SetLineStrip(
  const occ::handle<NCollection_HArray1<int>>& theLineStrip)
{
  myLineStrip = theLineStrip;
}

//=================================================================================================

int StepVisual_TessellatedEdge::NbLineStrip() const
{
  if (myLineStrip.IsNull())
  {
    return 0;
  }
  return myLineStrip->Length();
}

//=================================================================================================

int StepVisual_TessellatedEdge::LineStripValue(const int theNum) const
{
  return myLineStrip->Value(theNum);
}
