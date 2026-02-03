// Created on: 1993-07-02
// Created by: Laurent BUCHARD
// Copyright (c) 1993-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _HLRBRep_BSurfaceTool_HeaderFile
#define _HLRBRep_BSurfaceTool_HeaderFile

#include <Adaptor3d_Surface.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <gp_Pln.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Cone.hpp>
#include <gp_Torus.hpp>
#include <gp_Sphere.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>

class BRepAdaptor_Surface;
class gp_Pnt;
class gp_Vec;
class Geom_BezierSurface;
class Geom_BSplineSurface;

class HLRBRep_BSurfaceTool
{
public:
  DEFINE_STANDARD_ALLOC

  static double FirstUParameter(const BRepAdaptor_Surface& S);

  static double FirstVParameter(const BRepAdaptor_Surface& S);

  static double LastUParameter(const BRepAdaptor_Surface& S);

  static double LastVParameter(const BRepAdaptor_Surface& S);

  static int NbUIntervals(const BRepAdaptor_Surface& S, const GeomAbs_Shape Sh);

  static int NbVIntervals(const BRepAdaptor_Surface& S, const GeomAbs_Shape Sh);

  static void UIntervals(const BRepAdaptor_Surface&  S,
                         NCollection_Array1<double>& T,
                         const GeomAbs_Shape         Sh);

  static void VIntervals(const BRepAdaptor_Surface&  S,
                         NCollection_Array1<double>& T,
                         const GeomAbs_Shape         Sh);

  //! If <First> >= <Last>
  static occ::handle<Adaptor3d_Surface> UTrim(const BRepAdaptor_Surface& S,
                                              const double               First,
                                              const double               Last,
                                              const double               Tol);

  //! If <First> >= <Last>
  static occ::handle<Adaptor3d_Surface> VTrim(const BRepAdaptor_Surface& S,
                                              const double               First,
                                              const double               Last,
                                              const double               Tol);

  static bool IsUClosed(const BRepAdaptor_Surface& S);

  static bool IsVClosed(const BRepAdaptor_Surface& S);

  static bool IsUPeriodic(const BRepAdaptor_Surface& S);

  static double UPeriod(const BRepAdaptor_Surface& S);

  static bool IsVPeriodic(const BRepAdaptor_Surface& S);

  static double VPeriod(const BRepAdaptor_Surface& S);

  static gp_Pnt Value(const BRepAdaptor_Surface& S, const double u, const double v);

  static void D0(const BRepAdaptor_Surface& S, const double u, const double v, gp_Pnt& P);

  static void D1(const BRepAdaptor_Surface& S,
                 const double               u,
                 const double               v,
                 gp_Pnt&                    P,
                 gp_Vec&                    D1u,
                 gp_Vec&                    D1v);

  static void D2(const BRepAdaptor_Surface& S,
                 const double               u,
                 const double               v,
                 gp_Pnt&                    P,
                 gp_Vec&                    D1U,
                 gp_Vec&                    D1V,
                 gp_Vec&                    D2U,
                 gp_Vec&                    D2V,
                 gp_Vec&                    D2UV);

  static void D3(const BRepAdaptor_Surface& S,
                 const double               u,
                 const double               v,
                 gp_Pnt&                    P,
                 gp_Vec&                    D1U,
                 gp_Vec&                    D1V,
                 gp_Vec&                    D2U,
                 gp_Vec&                    D2V,
                 gp_Vec&                    D2UV,
                 gp_Vec&                    D3U,
                 gp_Vec&                    D3V,
                 gp_Vec&                    D3UUV,
                 gp_Vec&                    D3UVV);

  static gp_Vec DN(const BRepAdaptor_Surface& S,
                   const double               u,
                   const double               v,
                   const int                  Nu,
                   const int                  Nv);

  static GeomAbs_Shape UContinuity(const BRepAdaptor_Surface& S);

  static GeomAbs_Shape VContinuity(const BRepAdaptor_Surface& S);

  static int UDegree(const BRepAdaptor_Surface& S);

  static int NbUPoles(const BRepAdaptor_Surface& S);

  static int NbUKnots(const BRepAdaptor_Surface& S);

  static bool IsURational(const BRepAdaptor_Surface& S);

  static int VDegree(const BRepAdaptor_Surface& S);

  static int NbVPoles(const BRepAdaptor_Surface& S);

  static int NbVKnots(const BRepAdaptor_Surface& S);

  static bool IsVRational(const BRepAdaptor_Surface& S);

  static double UResolution(const BRepAdaptor_Surface& S, const double R3d);

  static double VResolution(const BRepAdaptor_Surface& S, const double R3d);

  static GeomAbs_SurfaceType GetType(const BRepAdaptor_Surface& S);

  static gp_Pln Plane(const BRepAdaptor_Surface& S);

  static gp_Cylinder Cylinder(const BRepAdaptor_Surface& S);

  static gp_Cone Cone(const BRepAdaptor_Surface& S);

  static gp_Torus Torus(const BRepAdaptor_Surface& S);

  static gp_Sphere Sphere(const BRepAdaptor_Surface& S);

  static occ::handle<Geom_BezierSurface> Bezier(const BRepAdaptor_Surface& S);

  static occ::handle<Geom_BSplineSurface> BSpline(const BRepAdaptor_Surface& S);

  static gp_Ax1 AxeOfRevolution(const BRepAdaptor_Surface& S);

  static gp_Dir Direction(const BRepAdaptor_Surface& S);

  static occ::handle<Adaptor3d_Curve> BasisCurve(const BRepAdaptor_Surface& S);

  static gp_Ax1 Axis(const BRepAdaptor_Surface& S);

  Standard_EXPORT static int NbSamplesU(const BRepAdaptor_Surface& S);

  Standard_EXPORT static int NbSamplesV(const BRepAdaptor_Surface& S);

  Standard_EXPORT static int NbSamplesU(const BRepAdaptor_Surface& S,
                                        const double               u1,
                                        const double               u2);

  Standard_EXPORT static int NbSamplesV(const BRepAdaptor_Surface& S,
                                        const double               v1,
                                        const double               v2);
};
// Created by: Laurent BUCHARD
// Copyright (c) 1993-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Pln.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Cone.hpp>
#include <gp_Torus.hpp>
#include <gp_Sphere.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <Geom_BezierSurface.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_Curve.hpp>
#include <BRepAdaptor_Surface.hpp>

//=================================================================================================

inline double HLRBRep_BSurfaceTool::FirstUParameter(const BRepAdaptor_Surface& Surf)
{
  return Surf.FirstUParameter();
}

//=================================================================================================

inline double HLRBRep_BSurfaceTool::FirstVParameter(const BRepAdaptor_Surface& Surf)
{
  return Surf.FirstVParameter();
}

//=================================================================================================

inline double HLRBRep_BSurfaceTool::LastUParameter(const BRepAdaptor_Surface& Surf)
{
  return Surf.LastUParameter();
}

//=================================================================================================

inline double HLRBRep_BSurfaceTool::LastVParameter(const BRepAdaptor_Surface& Surf)
{
  return Surf.LastVParameter();
}

//=================================================================================================

inline int HLRBRep_BSurfaceTool::NbUIntervals(const BRepAdaptor_Surface& Surf,
                                              const GeomAbs_Shape        S)
{
  return Surf.NbUIntervals(S);
}

//=================================================================================================

inline int HLRBRep_BSurfaceTool::NbVIntervals(const BRepAdaptor_Surface& Surf,
                                              const GeomAbs_Shape        S)
{
  return Surf.NbVIntervals(S);
}

//=================================================================================================

inline void HLRBRep_BSurfaceTool::UIntervals(const BRepAdaptor_Surface&  Surf,
                                             NCollection_Array1<double>& Tab,
                                             const GeomAbs_Shape         S)
{
  Surf.UIntervals(Tab, S);
}

//=================================================================================================

inline void HLRBRep_BSurfaceTool::VIntervals(const BRepAdaptor_Surface&  Surf,
                                             NCollection_Array1<double>& Tab,
                                             const GeomAbs_Shape         S)
{
  Surf.VIntervals(Tab, S);
}

//=================================================================================================

inline occ::handle<Adaptor3d_Surface> HLRBRep_BSurfaceTool::UTrim(const BRepAdaptor_Surface& Surf,
                                                                  const double               F,
                                                                  const double               L,
                                                                  const double               Tol)
{
  return Surf.UTrim(F, L, Tol);
}

//=================================================================================================

inline occ::handle<Adaptor3d_Surface> HLRBRep_BSurfaceTool::VTrim(const BRepAdaptor_Surface& Surf,
                                                                  const double               F,
                                                                  const double               L,
                                                                  const double               Tol)
{
  return Surf.VTrim(F, L, Tol);
}

//=================================================================================================

inline bool HLRBRep_BSurfaceTool::IsUClosed(const BRepAdaptor_Surface& S)
{
  return S.IsUClosed();
}

//=================================================================================================

inline bool HLRBRep_BSurfaceTool::IsVClosed(const BRepAdaptor_Surface& S)
{
  return S.IsVClosed();
}

//=================================================================================================

inline bool HLRBRep_BSurfaceTool::IsUPeriodic(const BRepAdaptor_Surface& S)
{
  return S.IsUPeriodic();
}

//=================================================================================================

inline double HLRBRep_BSurfaceTool::UPeriod(const BRepAdaptor_Surface& S)
{
  return S.UPeriod();
}

//=================================================================================================

inline bool HLRBRep_BSurfaceTool::IsVPeriodic(const BRepAdaptor_Surface& S)
{
  return S.IsVPeriodic();
}

//=================================================================================================

inline double HLRBRep_BSurfaceTool::VPeriod(const BRepAdaptor_Surface& S)
{
  return S.VPeriod();
}

//=================================================================================================

inline gp_Pnt HLRBRep_BSurfaceTool::Value(const BRepAdaptor_Surface& S,
                                          const double               U,
                                          const double               V)
{
  return S.Value(U, V);
}

//=================================================================================================

inline void HLRBRep_BSurfaceTool::D0(const BRepAdaptor_Surface& S,
                                     const double               U,
                                     const double               V,
                                     gp_Pnt&                    P)
{
  S.D0(U, V, P);
}

//=================================================================================================

inline void HLRBRep_BSurfaceTool::D1(const BRepAdaptor_Surface& S,
                                     const double               U,
                                     const double               V,
                                     gp_Pnt&                    P,
                                     gp_Vec&                    D1U,
                                     gp_Vec&                    D1V)
{
  S.D1(U, V, P, D1U, D1V);
}

//=================================================================================================

inline void HLRBRep_BSurfaceTool::D2(const BRepAdaptor_Surface& S,
                                     const double               U,
                                     const double               V,
                                     gp_Pnt&                    P,
                                     gp_Vec&                    D1U,
                                     gp_Vec&                    D1V,
                                     gp_Vec&                    D2U,
                                     gp_Vec&                    D2V,
                                     gp_Vec&                    D2UV)
{
  S.D2(U, V, P, D1U, D1V, D2U, D2V, D2UV);
}

//=================================================================================================

inline void HLRBRep_BSurfaceTool::D3(const BRepAdaptor_Surface& S,
                                     const double               U,
                                     const double               V,
                                     gp_Pnt&                    P,
                                     gp_Vec&                    D1U,
                                     gp_Vec&                    D1V,
                                     gp_Vec&                    D2U,
                                     gp_Vec&                    D2V,
                                     gp_Vec&                    D2UV,
                                     gp_Vec&                    D3U,
                                     gp_Vec&                    D3V,
                                     gp_Vec&                    D3UUV,
                                     gp_Vec&                    D3UVV)
{
  S.D3(U, V, P, D1U, D1V, D2U, D2V, D2UV, D3U, D3V, D3UUV, D3UVV);
}

//=================================================================================================

inline gp_Vec HLRBRep_BSurfaceTool::DN(const BRepAdaptor_Surface& S,
                                       const double               U,
                                       const double               V,
                                       const int                  Nu,
                                       const int                  Nv)
{
  return S.DN(U, V, Nu, Nv);
}

//=================================================================================================

inline double HLRBRep_BSurfaceTool::UResolution(const BRepAdaptor_Surface& S, const double R3d)
{
  return S.UResolution(R3d);
}

//=================================================================================================

inline double HLRBRep_BSurfaceTool::VResolution(const BRepAdaptor_Surface& S, const double R3d)
{
  return S.VResolution(R3d);
}

//=================================================================================================

inline GeomAbs_SurfaceType HLRBRep_BSurfaceTool::GetType(const BRepAdaptor_Surface& S)
{
  return S.GetType();
}

//=================================================================================================

inline gp_Pln HLRBRep_BSurfaceTool::Plane(const BRepAdaptor_Surface& S)
{
  return S.Plane();
}

//=================================================================================================

inline gp_Cylinder HLRBRep_BSurfaceTool::Cylinder(const BRepAdaptor_Surface& S)
{
  return S.Cylinder();
}

//=================================================================================================

inline gp_Cone HLRBRep_BSurfaceTool::Cone(const BRepAdaptor_Surface& S)
{
  return S.Cone();
}

//=================================================================================================

inline gp_Sphere HLRBRep_BSurfaceTool::Sphere(const BRepAdaptor_Surface& S)
{
  return S.Sphere();
}

//=================================================================================================

inline gp_Torus HLRBRep_BSurfaceTool::Torus(const BRepAdaptor_Surface& S)
{
  return S.Torus();
}

//=================================================================================================

inline occ::handle<Geom_BezierSurface> HLRBRep_BSurfaceTool::Bezier(const BRepAdaptor_Surface& S)
{
  return (S.Bezier());
}

//=================================================================================================

inline occ::handle<Geom_BSplineSurface> HLRBRep_BSurfaceTool::BSpline(const BRepAdaptor_Surface& S)
{
  return (S.BSpline());
}

//=================================================================================================

inline gp_Ax1 HLRBRep_BSurfaceTool::AxeOfRevolution(const BRepAdaptor_Surface& S)
{
  return (S.AxeOfRevolution());
}

//=================================================================================================

inline gp_Dir HLRBRep_BSurfaceTool::Direction(const BRepAdaptor_Surface& S)
{
  return (S.Direction());
}

//=================================================================================================

inline occ::handle<Adaptor3d_Curve> HLRBRep_BSurfaceTool::BasisCurve(const BRepAdaptor_Surface& S)
{
  return (S.BasisCurve());
}

//=================================================================================================

inline GeomAbs_Shape HLRBRep_BSurfaceTool::UContinuity(const BRepAdaptor_Surface& S)
{
  return (S.UContinuity());
}

//=================================================================================================

inline GeomAbs_Shape HLRBRep_BSurfaceTool::VContinuity(const BRepAdaptor_Surface& S)
{
  return (S.VContinuity());
}

//=================================================================================================

inline int HLRBRep_BSurfaceTool::UDegree(const BRepAdaptor_Surface& S)
{
  return (S.UDegree());
}

//=================================================================================================

inline int HLRBRep_BSurfaceTool::NbUPoles(const BRepAdaptor_Surface& S)
{
  return (S.NbUPoles());
}

//=================================================================================================

inline int HLRBRep_BSurfaceTool::NbUKnots(const BRepAdaptor_Surface& S)
{
  return (S.NbUKnots());
}

//=================================================================================================

inline bool HLRBRep_BSurfaceTool::IsURational(const BRepAdaptor_Surface& S)
{
  return (S.IsURational());
}

//=================================================================================================

inline int HLRBRep_BSurfaceTool::VDegree(const BRepAdaptor_Surface& S)
{
  return (S.VDegree());
}

//=================================================================================================

inline int HLRBRep_BSurfaceTool::NbVPoles(const BRepAdaptor_Surface& S)
{
  return (S.NbVPoles());
}

//=================================================================================================

inline int HLRBRep_BSurfaceTool::NbVKnots(const BRepAdaptor_Surface& S)
{
  return (S.NbVKnots());
}

//=================================================================================================

inline bool HLRBRep_BSurfaceTool::IsVRational(const BRepAdaptor_Surface& S)
{
  return (S.IsVRational());
}


#endif // _HLRBRep_BSurfaceTool_HeaderFile
