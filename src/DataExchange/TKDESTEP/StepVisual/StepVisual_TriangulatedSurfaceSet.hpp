#pragma once

#include <Standard.hpp>
#include <StepVisual_TessellatedSurfaceSet.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

class StepVisual_TriangulatedSurfaceSet : public StepVisual_TessellatedSurfaceSet
{
public:
  Standard_EXPORT StepVisual_TriangulatedSurfaceSet();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&    theRepresentationItemName,
    const occ::handle<StepVisual_CoordinatesList>&  theTessellatedFaceCoordinates,
    const int                                       theTessellatedFacePnmax,
    const occ::handle<NCollection_HArray2<double>>& theTessellatedFaceNormals,
    const occ::handle<NCollection_HArray1<int>>&    thePnindex,
    const occ::handle<NCollection_HArray2<int>>&    theTriangles);

  const occ::handle<NCollection_HArray1<int>> Pnindex() const { return myPnindex; }

  void SetPnindex(const occ::handle<NCollection_HArray1<int>>& thePnindex)
  {
    myPnindex = thePnindex;
  }

  Standard_EXPORT int NbPnindex() const;

  Standard_EXPORT int PnindexValue(const int theNum) const;

  const occ::handle<NCollection_HArray2<int>> Triangles() const { return myTriangles; }

  void SetTriangles(const occ::handle<NCollection_HArray2<int>>& theTriangles)
  {
    myTriangles = theTriangles;
  }

  Standard_EXPORT int NbTriangles() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TriangulatedSurfaceSet, StepVisual_TessellatedSurfaceSet)

private:
  occ::handle<NCollection_HArray1<int>> myPnindex;
  occ::handle<NCollection_HArray2<int>> myTriangles;
};
