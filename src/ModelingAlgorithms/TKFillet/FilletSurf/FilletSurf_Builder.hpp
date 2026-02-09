#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <FilletSurf_InternalBuilder.hpp>

enum FilletSurf_StatusDone
{
  FilletSurf_IsOk,
  FilletSurf_IsNotOk,
  FilletSurf_IsPartial
};

#include <FilletSurf_ErrorTypeStatus.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <FilletSurf_StatusType.hpp>
class TopoDS_Shape;
class Geom_Surface;
class TopoDS_Face;
class Geom_Curve;
class Geom2d_Curve;
class Geom_TrimmedCurve;

class FilletSurf_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT FilletSurf_Builder(const TopoDS_Shape&                   S,
                                     const NCollection_List<TopoDS_Shape>& E,
                                     const double                          R,
                                     const double                          Ta     = 1.0e-2,
                                     const double                          Tapp3d = 1.0e-4,
                                     const double                          Tapp2d = 1.0e-5);

  Standard_EXPORT void Perform();

  Standard_EXPORT void Simulate();

  Standard_EXPORT FilletSurf_StatusDone IsDone() const;

  Standard_EXPORT FilletSurf_ErrorTypeStatus StatusError() const;

  Standard_EXPORT int NbSurface() const;

  Standard_EXPORT const occ::handle<Geom_Surface>& SurfaceFillet(const int Index) const;

  Standard_EXPORT double TolApp3d(const int Index) const;

  Standard_EXPORT const TopoDS_Face& SupportFace1(const int Index) const;

  Standard_EXPORT const TopoDS_Face& SupportFace2(const int Index) const;

  Standard_EXPORT const occ::handle<Geom_Curve>& CurveOnFace1(const int Index) const;

  Standard_EXPORT const occ::handle<Geom_Curve>& CurveOnFace2(const int Index) const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurveOnFace1(const int Index) const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurve1OnFillet(const int Index) const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurveOnFace2(const int Index) const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurve2OnFillet(const int Index) const;

  Standard_EXPORT double FirstParameter() const;

  Standard_EXPORT double LastParameter() const;

  Standard_EXPORT FilletSurf_StatusType StartSectionStatus() const;

  Standard_EXPORT FilletSurf_StatusType EndSectionStatus() const;

  Standard_EXPORT int NbSection(const int IndexSurf) const;

  Standard_EXPORT void Section(const int                       IndexSurf,
                               const int                       IndexSec,
                               occ::handle<Geom_TrimmedCurve>& Circ) const;

private:
  FilletSurf_InternalBuilder myIntBuild;
  FilletSurf_StatusDone      myisdone;
  FilletSurf_ErrorTypeStatus myerrorstatus;
};
