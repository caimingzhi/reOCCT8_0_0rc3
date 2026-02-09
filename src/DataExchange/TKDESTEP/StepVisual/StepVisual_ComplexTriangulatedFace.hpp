#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedFace.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>

class StepVisual_ComplexTriangulatedFace : public StepVisual_TessellatedFace
{

public:
  Standard_EXPORT StepVisual_ComplexTriangulatedFace();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&    theRepresentationItem_Name,
    const occ::handle<StepVisual_CoordinatesList>&  theTessellatedFace_Coordinates,
    const int                                       theTessellatedFace_Pnmax,
    const occ::handle<NCollection_HArray2<double>>& theTessellatedFace_Normals,
    const bool                                      theHasTessellatedFace_GeometricLink,
    const StepVisual_FaceOrSurface&                 theTessellatedFace_GeometricLink,
    const occ::handle<NCollection_HArray1<int>>&    thePnindex,
    const occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& theTriangleStrips,
    const occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& theTriangleFans);

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> Pnindex() const;

  Standard_EXPORT void SetPnindex(const occ::handle<NCollection_HArray1<int>>& thePnindex);

  Standard_EXPORT int NbPnindex() const;

  Standard_EXPORT int PnindexValue(const int theNum) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> TriangleStrips()
    const;

  Standard_EXPORT void SetTriangleStrips(
    const occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& theTriangleStrips);

  Standard_EXPORT int NbTriangleStrips() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> TriangleFans()
    const;

  Standard_EXPORT void SetTriangleFans(
    const occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& theTriangleFans);

  Standard_EXPORT int NbTriangleFans() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_ComplexTriangulatedFace, StepVisual_TessellatedFace)

private:
  occ::handle<NCollection_HArray1<int>>                             myPnindex;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> myTriangleStrips;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> myTriangleFans;
};
