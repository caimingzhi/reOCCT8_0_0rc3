

#include <StepVisual_TriangulatedSurfaceSet.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_TriangulatedSurfaceSet, StepVisual_TessellatedSurfaceSet)

StepVisual_TriangulatedSurfaceSet::StepVisual_TriangulatedSurfaceSet() = default;

void StepVisual_TriangulatedSurfaceSet::Init(
  const occ::handle<TCollection_HAsciiString>&    theRepresentationItemName,
  const occ::handle<StepVisual_CoordinatesList>&  theTessellatedSurfaceSetCoordinates,
  const int                                       theTessellatedSurfaceSetPnmax,
  const occ::handle<NCollection_HArray2<double>>& theTessellatedSurfaceSetNormals,
  const occ::handle<NCollection_HArray1<int>>&    thePnindex,
  const occ::handle<NCollection_HArray2<int>>&    theTriangles)
{
  StepVisual_TessellatedSurfaceSet::Init(theRepresentationItemName,
                                         theTessellatedSurfaceSetCoordinates,
                                         theTessellatedSurfaceSetPnmax,
                                         theTessellatedSurfaceSetNormals);
  myPnindex   = thePnindex;
  myTriangles = theTriangles;
}

int StepVisual_TriangulatedSurfaceSet::NbPnindex() const
{
  if (myPnindex.IsNull())
  {
    return 0;
  }
  return myPnindex->Length();
}

int StepVisual_TriangulatedSurfaceSet::PnindexValue(const int theNum) const
{
  return myPnindex->Value(theNum);
}

int StepVisual_TriangulatedSurfaceSet::NbTriangles() const
{
  if (myTriangles.IsNull())
  {
    return 0;
  }
  return myTriangles->ColLength();
}
