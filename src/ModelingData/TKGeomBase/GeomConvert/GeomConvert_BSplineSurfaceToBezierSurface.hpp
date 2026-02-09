#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Geom_BezierSurface.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_Array1.hpp>
class Geom_BSplineSurface;
class Geom_BezierSurface;

class GeomConvert_BSplineSurfaceToBezierSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomConvert_BSplineSurfaceToBezierSurface(
    const occ::handle<Geom_BSplineSurface>& BasisSurface);

  Standard_EXPORT GeomConvert_BSplineSurfaceToBezierSurface(
    const occ::handle<Geom_BSplineSurface>& BasisSurface,
    const double                            U1,
    const double                            U2,
    const double                            V1,
    const double                            V2,
    const double                            ParametricTolerance);

  Standard_EXPORT occ::handle<Geom_BezierSurface> Patch(const int UIndex, const int VIndex);

  Standard_EXPORT void Patches(NCollection_Array2<occ::handle<Geom_BezierSurface>>& Surfaces);

  Standard_EXPORT void UKnots(NCollection_Array1<double>& TKnots) const;

  Standard_EXPORT void VKnots(NCollection_Array1<double>& TKnots) const;

  Standard_EXPORT int NbUPatches() const;

  Standard_EXPORT int NbVPatches() const;

private:
  occ::handle<Geom_BSplineSurface> mySurface;
};
