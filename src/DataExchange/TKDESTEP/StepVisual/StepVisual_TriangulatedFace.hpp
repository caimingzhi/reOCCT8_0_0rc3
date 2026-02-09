#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedFace.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

class StepVisual_TriangulatedFace : public StepVisual_TessellatedFace
{

public:
  Standard_EXPORT StepVisual_TriangulatedFace();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&    theRepresentationItem_Name,
    const occ::handle<StepVisual_CoordinatesList>&  theTessellatedFace_Coordinates,
    const int                                       theTessellatedFace_Pnmax,
    const occ::handle<NCollection_HArray2<double>>& theTessellatedFace_Normals,
    const bool                                      theHasTessellatedFace_GeometricLink,
    const StepVisual_FaceOrSurface&                 theTessellatedFace_GeometricLink,
    const occ::handle<NCollection_HArray1<int>>&    thePnindex,
    const occ::handle<NCollection_HArray2<int>>&    theTriangles);

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> Pnindex() const;

  Standard_EXPORT void SetPnindex(const occ::handle<NCollection_HArray1<int>>& thePnindex);

  Standard_EXPORT int NbPnindex() const;

  Standard_EXPORT int PnindexValue(const int theNum) const;

  Standard_EXPORT occ::handle<NCollection_HArray2<int>> Triangles() const;

  Standard_EXPORT void SetTriangles(const occ::handle<NCollection_HArray2<int>>& theTriangles);

  Standard_EXPORT int NbTriangles() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TriangulatedFace, StepVisual_TessellatedFace)

private:
  occ::handle<NCollection_HArray1<int>> myPnindex;
  occ::handle<NCollection_HArray2<int>> myTriangles;
};
