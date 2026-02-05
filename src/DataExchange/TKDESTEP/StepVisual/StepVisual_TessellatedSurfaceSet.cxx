// Created on : Thu Mar 24 18:30:12 2022

#include <StepVisual_TessellatedSurfaceSet.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TessellatedSurfaceSet, StepVisual_TessellatedItem)

//=================================================================================================

StepVisual_TessellatedSurfaceSet::StepVisual_TessellatedSurfaceSet() = default;

//=================================================================================================

void StepVisual_TessellatedSurfaceSet::Init(
  const occ::handle<TCollection_HAsciiString>&    theRepresentationItem_Name,
  const occ::handle<StepVisual_CoordinatesList>&  theCoordinates,
  const int                                       thePnmax,
  const occ::handle<NCollection_HArray2<double>>& theNormals)
{
  StepVisual_TessellatedItem::Init(theRepresentationItem_Name);

  myCoordinates = theCoordinates;

  myPnmax = thePnmax;

  myNormals = theNormals;
}

//=================================================================================================

occ::handle<StepVisual_CoordinatesList> StepVisual_TessellatedSurfaceSet::Coordinates() const
{
  return myCoordinates;
}

//=================================================================================================

void StepVisual_TessellatedSurfaceSet::SetCoordinates(
  const occ::handle<StepVisual_CoordinatesList>& theCoordinates)
{
  myCoordinates = theCoordinates;
}

//=================================================================================================

int StepVisual_TessellatedSurfaceSet::Pnmax() const
{
  return myPnmax;
}

//=================================================================================================

void StepVisual_TessellatedSurfaceSet::SetPnmax(const int thePnmax)
{
  myPnmax = thePnmax;
}

//=================================================================================================

occ::handle<NCollection_HArray2<double>> StepVisual_TessellatedSurfaceSet::Normals() const
{
  return myNormals;
}

//=================================================================================================

void StepVisual_TessellatedSurfaceSet::SetNormals(
  const occ::handle<NCollection_HArray2<double>>& theNormals)
{
  myNormals = theNormals;
}

//=================================================================================================

int StepVisual_TessellatedSurfaceSet::NbNormals() const
{
  if (myNormals.IsNull())
  {
    return 0;
  }
  return myNormals->ColLength();
}
