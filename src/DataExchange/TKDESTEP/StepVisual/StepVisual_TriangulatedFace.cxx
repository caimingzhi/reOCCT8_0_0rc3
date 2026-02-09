

#include <StepVisual_TriangulatedFace.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TriangulatedFace, StepVisual_TessellatedFace)

StepVisual_TriangulatedFace::StepVisual_TriangulatedFace()

  = default;

void StepVisual_TriangulatedFace::Init(
  const occ::handle<TCollection_HAsciiString>&    theRepresentationItem_Name,
  const occ::handle<StepVisual_CoordinatesList>&  theTessellatedFace_Coordinates,
  const int                                       theTessellatedFace_Pnmax,
  const occ::handle<NCollection_HArray2<double>>& theTessellatedFace_Normals,
  const bool                                      theHasTessellatedFace_GeometricLink,
  const StepVisual_FaceOrSurface&                 theTessellatedFace_GeometricLink,
  const occ::handle<NCollection_HArray1<int>>&    thePnindex,
  const occ::handle<NCollection_HArray2<int>>&    theTriangles)
{
  StepVisual_TessellatedFace::Init(theRepresentationItem_Name,
                                   theTessellatedFace_Coordinates,
                                   theTessellatedFace_Pnmax,
                                   theTessellatedFace_Normals,
                                   theHasTessellatedFace_GeometricLink,
                                   theTessellatedFace_GeometricLink);

  myPnindex = thePnindex;

  myTriangles = theTriangles;
}

occ::handle<NCollection_HArray1<int>> StepVisual_TriangulatedFace::Pnindex() const
{
  return myPnindex;
}

void StepVisual_TriangulatedFace::SetPnindex(
  const occ::handle<NCollection_HArray1<int>>& thePnindex)
{
  myPnindex = thePnindex;
}

int StepVisual_TriangulatedFace::NbPnindex() const
{
  if (myPnindex.IsNull())
  {
    return 0;
  }
  return myPnindex->Length();
}

int StepVisual_TriangulatedFace::PnindexValue(const int theNum) const
{
  return myPnindex->Value(theNum);
}

occ::handle<NCollection_HArray2<int>> StepVisual_TriangulatedFace::Triangles() const
{
  return myTriangles;
}

int StepVisual_TriangulatedFace::NbTriangles() const
{
  if (myTriangles.IsNull())
  {
    return 0;
  }
  return myTriangles->ColLength();
}

void StepVisual_TriangulatedFace::SetTriangles(
  const occ::handle<NCollection_HArray2<int>>& theTriangles)
{
  myTriangles = theTriangles;
}
