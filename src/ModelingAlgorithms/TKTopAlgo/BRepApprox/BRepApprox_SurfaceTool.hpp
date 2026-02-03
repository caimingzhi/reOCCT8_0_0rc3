// Created on: 1995-07-20
// Created by: Modelistation
// Copyright (c) 1995-1999 Matra Datavision
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

#ifndef _BRepApprox_SurfaceTool_HeaderFile
#define _BRepApprox_SurfaceTool_HeaderFile

#include <BRepAdaptor_Surface.hpp>
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

class Geom_BezierSurface;
class Geom_BSplineSurface;

class BRepApprox_SurfaceTool
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

  Standard_EXPORT static int NbSamplesU(const BRepAdaptor_Surface& S);

  Standard_EXPORT static int NbSamplesV(const BRepAdaptor_Surface& S);

  Standard_EXPORT static int NbSamplesU(const BRepAdaptor_Surface& S,
                                        const double               u1,
                                        const double               u2);

  Standard_EXPORT static int NbSamplesV(const BRepAdaptor_Surface& S,
                                        const double               v1,
                                        const double               v2);
};
// Created on: 1995-07-20
// Created by: Modelistation
// Copyright (c) 1995-1999 Matra Datavision
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

inline double BRepApprox_SurfaceTool::FirstUParameter(const BRepAdaptor_Surface& Surf)
{
  return Surf.FirstUParameter();
}

inline double BRepApprox_SurfaceTool::FirstVParameter(const BRepAdaptor_Surface& Surf)
{
  return Surf.FirstVParameter();
}

inline double BRepApprox_SurfaceTool::LastUParameter(const BRepAdaptor_Surface& Surf)
{
  return Surf.LastUParameter();
}

inline double BRepApprox_SurfaceTool::LastVParameter(const BRepAdaptor_Surface& Surf)
{
  return Surf.LastVParameter();
}

inline int BRepApprox_SurfaceTool::NbUIntervals(const BRepAdaptor_Surface& Surf,
                                                const GeomAbs_Shape        S)
{
  return Surf.NbUIntervals(S);
}

inline int BRepApprox_SurfaceTool::NbVIntervals(const BRepAdaptor_Surface& Surf,
                                                const GeomAbs_Shape        S)
{
  return Surf.NbVIntervals(S);
}

inline void BRepApprox_SurfaceTool::UIntervals(const BRepAdaptor_Surface&  Surf,
                                               NCollection_Array1<double>& Tab,
                                               const GeomAbs_Shape         S)
{
  Surf.UIntervals(Tab, S);
}

inline void BRepApprox_SurfaceTool::VIntervals(const BRepAdaptor_Surface&  Surf,
                                               NCollection_Array1<double>& Tab,
                                               const GeomAbs_Shape         S)
{
  Surf.VIntervals(Tab, S);
}

inline occ::handle<Adaptor3d_Surface> BRepApprox_SurfaceTool::UTrim(const BRepAdaptor_Surface& Surf,
                                                                    const double               F,
                                                                    const double               L,
                                                                    const double               Tol)
{
  return Surf.UTrim(F, L, Tol);
}

inline occ::handle<Adaptor3d_Surface> BRepApprox_SurfaceTool::VTrim(const BRepAdaptor_Surface& Surf,
                                                                    const double               F,
                                                                    const double               L,
                                                                    const double               Tol)
{
  return Surf.VTrim(F, L, Tol);
}

inline bool BRepApprox_SurfaceTool::IsUClosed(const BRepAdaptor_Surface& S)
{
  return S.IsUClosed();
}

inline bool BRepApprox_SurfaceTool::IsVClosed(const BRepAdaptor_Surface& S)
{
  return S.IsVClosed();
}

inline bool BRepApprox_SurfaceTool::IsUPeriodic(const BRepAdaptor_Surface& S)
{
  return S.IsUPeriodic();
}

inline double BRepApprox_SurfaceTool::UPeriod(const BRepAdaptor_Surface& S)
{
  return S.UPeriod();
}

inline bool BRepApprox_SurfaceTool::IsVPeriodic(const BRepAdaptor_Surface& S)
{
  return S.IsVPeriodic();
}

inline double BRepApprox_SurfaceTool::VPeriod(const BRepAdaptor_Surface& S)
{
  return S.VPeriod();
}

inline gp_Pnt BRepApprox_SurfaceTool::Value(const BRepAdaptor_Surface& S,
                                            const double               U,
                                            const double               V)
{
  return S.Value(U, V);
}

inline void BRepApprox_SurfaceTool::D0(const BRepAdaptor_Surface& S,
                                       const double               U,
                                       const double               V,
                                       gp_Pnt&                    P)
{
  S.D0(U, V, P);
}

inline void BRepApprox_SurfaceTool::D1(const BRepAdaptor_Surface& S,
                                       const double               U,
                                       const double               V,
                                       gp_Pnt&                    P,
                                       gp_Vec&                    D1U,
                                       gp_Vec&                    D1V)
{
  S.D1(U, V, P, D1U, D1V);
}

inline void BRepApprox_SurfaceTool::D2(const BRepAdaptor_Surface& S,
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

inline void BRepApprox_SurfaceTool::D3(const BRepAdaptor_Surface& S,
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

inline gp_Vec BRepApprox_SurfaceTool::DN(const BRepAdaptor_Surface& S,
                                         const double               U,
                                         const double               V,
                                         const int                  Nu,
                                         const int                  Nv)
{
  return S.DN(U, V, Nu, Nv);
}

inline double BRepApprox_SurfaceTool::UResolution(const BRepAdaptor_Surface& S, const double R3d)
{
  return S.UResolution(R3d);
}

inline double BRepApprox_SurfaceTool::VResolution(const BRepAdaptor_Surface& S, const double R3d)
{
  return S.VResolution(R3d);
}

inline GeomAbs_SurfaceType BRepApprox_SurfaceTool::GetType(const BRepAdaptor_Surface& S)
{
  return S.GetType();
}

inline gp_Pln BRepApprox_SurfaceTool::Plane(const BRepAdaptor_Surface& S)
{
  return S.Plane();
}

inline gp_Cylinder BRepApprox_SurfaceTool::Cylinder(const BRepAdaptor_Surface& S)
{
  return S.Cylinder();
}

inline gp_Cone BRepApprox_SurfaceTool::Cone(const BRepAdaptor_Surface& S)
{
  return S.Cone();
}

inline gp_Sphere BRepApprox_SurfaceTool::Sphere(const BRepAdaptor_Surface& S)
{
  return S.Sphere();
}

inline gp_Torus BRepApprox_SurfaceTool::Torus(const BRepAdaptor_Surface& S)
{
  return S.Torus();
}

inline occ::handle<Geom_BezierSurface> BRepApprox_SurfaceTool::Bezier(const BRepAdaptor_Surface& S)
{
  return (S.Bezier());
}

inline occ::handle<Geom_BSplineSurface> BRepApprox_SurfaceTool::BSpline(
  const BRepAdaptor_Surface& S)
{
  return (S.BSpline());
}

inline gp_Ax1 BRepApprox_SurfaceTool::AxeOfRevolution(const BRepAdaptor_Surface& S)
{
  return (S.AxeOfRevolution());
}

inline gp_Dir BRepApprox_SurfaceTool::Direction(const BRepAdaptor_Surface& S)
{
  return (S.Direction());
}

inline occ::handle<Adaptor3d_Curve> BRepApprox_SurfaceTool::BasisCurve(const BRepAdaptor_Surface& S)
{
  return (S.BasisCurve());
}


#endif // _BRepApprox_SurfaceTool_HeaderFile
