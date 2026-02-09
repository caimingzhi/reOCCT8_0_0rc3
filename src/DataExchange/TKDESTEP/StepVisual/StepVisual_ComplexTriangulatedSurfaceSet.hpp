#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedSurfaceSet.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>

class StepVisual_ComplexTriangulatedSurfaceSet : public StepVisual_TessellatedSurfaceSet
{

public:
  Standard_EXPORT StepVisual_ComplexTriangulatedSurfaceSet();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&    theRepresentationItem_Name,
    const occ::handle<StepVisual_CoordinatesList>&  theTessellatedSurfaceSet_Coordinates,
    const int                                       theTessellatedSurfaceSet_Pnmax,
    const occ::handle<NCollection_HArray2<double>>& theTessellatedSurfaceSet_Normals,
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

  DEFINE_STANDARD_RTTIEXT(StepVisual_ComplexTriangulatedSurfaceSet,
                          StepVisual_TessellatedSurfaceSet)

private:
  occ::handle<NCollection_HArray1<int>>                             myPnindex;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> myTriangleStrips;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> myTriangleFans;
};
