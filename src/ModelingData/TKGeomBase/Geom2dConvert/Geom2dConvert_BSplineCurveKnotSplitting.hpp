#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class Geom2d_BSplineCurve;

class Geom2dConvert_BSplineCurveKnotSplitting
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dConvert_BSplineCurveKnotSplitting(
    const occ::handle<Geom2d_BSplineCurve>& BasisCurve,
    const int                               ContinuityRange);

  Standard_EXPORT int NbSplits() const;

  Standard_EXPORT void Splitting(NCollection_Array1<int>& SplitValues) const;

  Standard_EXPORT int SplitValue(const int Index) const;

private:
  occ::handle<NCollection_HArray1<int>> splitIndexes;
};
