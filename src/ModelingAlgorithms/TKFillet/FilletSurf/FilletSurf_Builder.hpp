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

//! API giving the following geometric information about fillets
//! list of corresponding NUBS surfaces
//! for each surface:
//! the 2 support faces
//! on each face: the 3d curve and the corresponding 2d curve
//! the 2d curves on the fillet
//! status of start and end section of the fillet
//! first and last parameter on edge of the fillet.
class FilletSurf_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  //! initialize of the information necessary for the
  //! computation of the fillet on the
  //! Shape S from a list of edges E and a radius R.
  //!
  //! Ta is the angular tolerance
  //! Tapp3d is the 3d approximation tolerance
  //! Tapp2d is the 2d approximation tolerance
  Standard_EXPORT FilletSurf_Builder(const TopoDS_Shape&                   S,
                                     const NCollection_List<TopoDS_Shape>& E,
                                     const double                          R,
                                     const double                          Ta     = 1.0e-2,
                                     const double                          Tapp3d = 1.0e-4,
                                     const double                          Tapp2d = 1.0e-5);

  //! ---Purpose computation of the fillet (list of NUBS)
  Standard_EXPORT void Perform();

  Standard_EXPORT void Simulate();

  //! gives the status about the computation of the fillet
  //! returns:
  //! IsOK :no problem during the computation
  //! IsNotOk: no result is produced
  //! IsPartial: the result is partial
  Standard_EXPORT FilletSurf_StatusDone IsDone() const;

  //! gives information about error status if
  //! IsDone=IsNotOk
  //! returns
  //! EdgeNotG1: the edges are not G1
  //! FacesNotG1 : two connected faces on a same support are
  //! not G1
  //! EdgeNotOnShape: the edge is not on shape
  //! NotSharpEdge: the edge is not sharp
  //! PbFilletCompute: problem during the computation of the fillet
  Standard_EXPORT FilletSurf_ErrorTypeStatus StatusError() const;

  //! gives the number of NUBS surfaces of the Fillet.
  Standard_EXPORT int NbSurface() const;

  //! gives the NUBS surface of index Index.
  Standard_EXPORT const occ::handle<Geom_Surface>& SurfaceFillet(const int Index) const;

  //! gives the 3d tolerance reached during approximation
  //! of surface of index Index
  Standard_EXPORT double TolApp3d(const int Index) const;

  //! gives the first support face relative to SurfaceFillet(Index);
  Standard_EXPORT const TopoDS_Face& SupportFace1(const int Index) const;

  //! gives the second support face relative to SurfaceFillet(Index);
  Standard_EXPORT const TopoDS_Face& SupportFace2(const int Index) const;

  //! gives the 3d curve of SurfaceFillet(Index) on SupportFace1(Index)
  Standard_EXPORT const occ::handle<Geom_Curve>& CurveOnFace1(const int Index) const;

  //! gives the 3d curve of SurfaceFillet(Index) on SupportFace2(Index)
  Standard_EXPORT const occ::handle<Geom_Curve>& CurveOnFace2(const int Index) const;

  //! gives the PCurve associated to CurvOnSup1(Index) on the support face
  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurveOnFace1(const int Index) const;

  //! gives the PCurve associated to CurveOnFace1(Index) on the Fillet
  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurve1OnFillet(const int Index) const;

  //! gives the PCurve associated to CurveOnSup2(Index) on the support face
  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurveOnFace2(const int Index) const;

  //! gives the PCurve associated to CurveOnSup2(Index) on the fillet
  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurve2OnFillet(const int Index) const;

  //! gives the parameter of the fillet on the first edge.
  Standard_EXPORT double FirstParameter() const;

  //! gives the parameter of the fillet on the last edge
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
