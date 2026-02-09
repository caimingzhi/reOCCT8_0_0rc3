#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2d_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <MAT_Side.hpp>
#include <Standard_Integer.hpp>
class Geom2d_Curve;
class Geom2d_TrimmedCurve;

class MAT2d_CutCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT MAT2d_CutCurve();

  Standard_EXPORT MAT2d_CutCurve(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT void Perform(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT void Perform(const occ::handle<Geom2d_Curve>& C, const MAT_Side aSide);

  Standard_EXPORT void PerformInf(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT bool UnModified() const;

  Standard_EXPORT int NbCurves() const;

  Standard_EXPORT occ::handle<Geom2d_TrimmedCurve> Value(const int Index) const;

private:
  NCollection_Sequence<occ::handle<Geom2d_Curve>> theCurves;
};
