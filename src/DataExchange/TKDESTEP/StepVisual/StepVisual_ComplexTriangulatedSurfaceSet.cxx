

#include <StepVisual_ComplexTriangulatedSurfaceSet.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_ComplexTriangulatedSurfaceSet,
                           StepVisual_TessellatedSurfaceSet)

StepVisual_ComplexTriangulatedSurfaceSet::StepVisual_ComplexTriangulatedSurfaceSet() = default;

void StepVisual_ComplexTriangulatedSurfaceSet::Init(
  const occ::handle<TCollection_HAsciiString>&    theRepresentationItem_Name,
  const occ::handle<StepVisual_CoordinatesList>&  theTessellatedSurfaceSet_Coordinates,
  const int                                       theTessellatedSurfaceSet_Pnmax,
  const occ::handle<NCollection_HArray2<double>>& theTessellatedSurfaceSet_Normals,
  const occ::handle<NCollection_HArray1<int>>&    thePnindex,
  const occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& theTriangleStrips,
  const occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& theTriangleFans)
{
  StepVisual_TessellatedSurfaceSet::Init(theRepresentationItem_Name,
                                         theTessellatedSurfaceSet_Coordinates,
                                         theTessellatedSurfaceSet_Pnmax,
                                         theTessellatedSurfaceSet_Normals);

  myPnindex = thePnindex;

  myTriangleStrips = theTriangleStrips;

  myTriangleFans = theTriangleFans;
}

occ::handle<NCollection_HArray1<int>> StepVisual_ComplexTriangulatedSurfaceSet::Pnindex() const
{
  return myPnindex;
}

void StepVisual_ComplexTriangulatedSurfaceSet::SetPnindex(
  const occ::handle<NCollection_HArray1<int>>& thePnindex)
{
  myPnindex = thePnindex;
}

int StepVisual_ComplexTriangulatedSurfaceSet::NbPnindex() const
{
  if (myPnindex.IsNull())
  {
    return 0;
  }
  return myPnindex->Length();
}

int StepVisual_ComplexTriangulatedSurfaceSet::PnindexValue(const int theNum) const
{
  return myPnindex->Value(theNum);
}

occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>
  StepVisual_ComplexTriangulatedSurfaceSet::TriangleStrips() const
{
  return myTriangleStrips;
}

void StepVisual_ComplexTriangulatedSurfaceSet::SetTriangleStrips(
  const occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& theTriangleStrips)
{
  myTriangleStrips = theTriangleStrips;
}

int StepVisual_ComplexTriangulatedSurfaceSet::NbTriangleStrips() const
{
  if (myTriangleStrips.IsNull())
  {
    return 0;
  }
  return myTriangleStrips->Length();
}

occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>
  StepVisual_ComplexTriangulatedSurfaceSet::TriangleFans() const
{
  return myTriangleFans;
}

void StepVisual_ComplexTriangulatedSurfaceSet::SetTriangleFans(
  const occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& theTriangleFans)
{
  myTriangleFans = theTriangleFans;
}

int StepVisual_ComplexTriangulatedSurfaceSet::NbTriangleFans() const
{
  if (myTriangleFans.IsNull())
  {
    return 0;
  }
  return myTriangleFans->Length();
}
