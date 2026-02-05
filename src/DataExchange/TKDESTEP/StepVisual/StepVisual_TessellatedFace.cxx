// Created on : Thu Mar 24 18:30:12 2022

#include <StepVisual_TessellatedFace.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TessellatedFace, StepVisual_TessellatedStructuredItem)

//=================================================================================================

StepVisual_TessellatedFace::StepVisual_TessellatedFace()
{
  myHasGeometricLink = false;
}

//=================================================================================================

void StepVisual_TessellatedFace::Init(
  const occ::handle<TCollection_HAsciiString>&    theRepresentationItem_Name,
  const occ::handle<StepVisual_CoordinatesList>&  theCoordinates,
  const int                                       thePnmax,
  const occ::handle<NCollection_HArray2<double>>& theNormals,
  const bool                                      theHasGeometricLink,
  const StepVisual_FaceOrSurface&                 theGeometricLink)
{
  StepVisual_TessellatedStructuredItem::Init(theRepresentationItem_Name);

  myCoordinates = theCoordinates;

  myPnmax = thePnmax;

  myNormals = theNormals;

  myHasGeometricLink = theHasGeometricLink;
  if (myHasGeometricLink)
  {
    myGeometricLink = theGeometricLink;
  }
  else
  {
    myGeometricLink = StepVisual_FaceOrSurface();
  }
}

//=================================================================================================

occ::handle<StepVisual_CoordinatesList> StepVisual_TessellatedFace::Coordinates() const
{
  return myCoordinates;
}

//=================================================================================================

void StepVisual_TessellatedFace::SetCoordinates(
  const occ::handle<StepVisual_CoordinatesList>& theCoordinates)
{
  myCoordinates = theCoordinates;
}

//=================================================================================================

int StepVisual_TessellatedFace::Pnmax() const
{
  return myPnmax;
}

//=================================================================================================

void StepVisual_TessellatedFace::SetPnmax(const int thePnmax)
{
  myPnmax = thePnmax;
}

//=================================================================================================

occ::handle<NCollection_HArray2<double>> StepVisual_TessellatedFace::Normals() const
{
  return myNormals;
}

//=================================================================================================

void StepVisual_TessellatedFace::SetNormals(
  const occ::handle<NCollection_HArray2<double>>& theNormals)
{
  myNormals = theNormals;
}

//=================================================================================================

int StepVisual_TessellatedFace::NbNormals() const
{
  if (myNormals.IsNull())
  {
    return 0;
  }
  return myNormals->ColLength();
}

//=================================================================================================

StepVisual_FaceOrSurface StepVisual_TessellatedFace::GeometricLink() const
{
  return myGeometricLink;
}

//=================================================================================================

void StepVisual_TessellatedFace::SetGeometricLink(const StepVisual_FaceOrSurface& theGeometricLink)
{
  myGeometricLink = theGeometricLink;
}

//=================================================================================================

bool StepVisual_TessellatedFace::HasGeometricLink() const
{
  return myHasGeometricLink;
}
