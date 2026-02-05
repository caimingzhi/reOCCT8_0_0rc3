// Created on : Thu Mar 24 18:30:12 2022

#include <StepVisual_TessellatedVertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TessellatedVertex, StepVisual_TessellatedStructuredItem)

//=================================================================================================

StepVisual_TessellatedVertex::StepVisual_TessellatedVertex()
{
  myPointIndex         = 0;
  myHasTopologicalLink = false;
}

//=================================================================================================

void StepVisual_TessellatedVertex::Init(
  const occ::handle<TCollection_HAsciiString>&   theRepresentationItem_Name,
  const occ::handle<StepVisual_CoordinatesList>& theCoordinates,
  const bool                                     theHasTopologicalLink,
  const occ::handle<StepShape_VertexPoint>&      theTopologicalLink,
  const int                                      thePointIndex)
{
  StepVisual_TessellatedStructuredItem::Init(theRepresentationItem_Name);

  myCoordinates = theCoordinates;

  myHasTopologicalLink = theHasTopologicalLink;
  if (myHasTopologicalLink)
  {
    myTopologicalLink = theTopologicalLink;
  }
  else
  {
    myTopologicalLink.Nullify();
  }

  myPointIndex = thePointIndex;
}

//=================================================================================================

occ::handle<StepVisual_CoordinatesList> StepVisual_TessellatedVertex::Coordinates() const
{
  return myCoordinates;
}

//=================================================================================================

void StepVisual_TessellatedVertex::SetCoordinates(
  const occ::handle<StepVisual_CoordinatesList>& theCoordinates)
{
  myCoordinates = theCoordinates;
}

//=================================================================================================

occ::handle<StepShape_VertexPoint> StepVisual_TessellatedVertex::TopologicalLink() const
{
  return myTopologicalLink;
}

//=================================================================================================

void StepVisual_TessellatedVertex::SetTopologicalLink(
  const occ::handle<StepShape_VertexPoint>& theTopologicalLink)
{
  myTopologicalLink = theTopologicalLink;
}

//=================================================================================================

bool StepVisual_TessellatedVertex::HasTopologicalLink() const
{
  return myHasTopologicalLink;
}

//=================================================================================================

int StepVisual_TessellatedVertex::PointIndex() const
{
  return myPointIndex;
}

//=================================================================================================

void StepVisual_TessellatedVertex::SetPointIndex(const int thePointIndex)
{
  myPointIndex = thePointIndex;
}
