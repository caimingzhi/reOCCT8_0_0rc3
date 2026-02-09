#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class Geom_BSplineSurface;

class GeomConvert_BSplineSurfaceKnotSplitting
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomConvert_BSplineSurfaceKnotSplitting(
    const occ::handle<Geom_BSplineSurface>& BasisSurface,
    const int                               UContinuityRange,
    const int                               VContinuityRange);

  Standard_EXPORT int NbUSplits() const;

  Standard_EXPORT int NbVSplits() const;

  Standard_EXPORT void Splitting(NCollection_Array1<int>& USplit,
                                 NCollection_Array1<int>& VSplit) const;

  Standard_EXPORT int USplitValue(const int UIndex) const;

  Standard_EXPORT int VSplitValue(const int VIndex) const;

private:
  occ::handle<NCollection_HArray1<int>> usplitIndexes;
  occ::handle<NCollection_HArray1<int>> vsplitIndexes;
};
