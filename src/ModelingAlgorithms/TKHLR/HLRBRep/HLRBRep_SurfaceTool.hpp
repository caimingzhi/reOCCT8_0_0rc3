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

#ifndef _HLRBRep_SurfaceTool_HeaderFile
#define _HLRBRep_SurfaceTool_HeaderFile

#include <Adaptor3d_Curve.hpp>
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

class gp_Pnt;
class gp_Vec;
class Geom_BezierSurface;
class Geom_BSplineSurface;
class HLRBRep_Surface;

class HLRBRep_SurfaceTool
{
public:
  DEFINE_STANDARD_ALLOC

  static double FirstUParameter(const HLRBRep_Surface* theSurf);

  static double FirstVParameter(const HLRBRep_Surface* theSurf);

  static double LastUParameter(const HLRBRep_Surface* theSurf);

  static double LastVParameter(const HLRBRep_Surface* theSurf);

  static int NbUIntervals(const HLRBRep_Surface* theSurf, const GeomAbs_Shape theSh);

  static int NbVIntervals(const HLRBRep_Surface* theSurf, const GeomAbs_Shape theSh);

  static void UIntervals(const HLRBRep_Surface*      theSurf,
                         NCollection_Array1<double>& theT,
                         const GeomAbs_Shape         theSh);

  static void VIntervals(const HLRBRep_Surface*      theSurf,
                         NCollection_Array1<double>& theT,
                         const GeomAbs_Shape         theSh);

  //! If <theFirst> >= <theLast>
  static occ::handle<Adaptor3d_Surface> UTrim(const HLRBRep_Surface* theSurf,
                                              const double           theFirst,
                                              const double           theLast,
                                              const double           theTol);

  //! If <theFirst> >= <theLast>
  static occ::handle<Adaptor3d_Surface> VTrim(const HLRBRep_Surface* theSurf,
                                              const double           theFirst,
                                              const double           theLast,
                                              const double           theTol);

  static bool IsUClosed(const HLRBRep_Surface* theSurf);

  static bool IsVClosed(const HLRBRep_Surface* theSurf);

  static bool IsUPeriodic(const HLRBRep_Surface* theSurf);

  static double UPeriod(const HLRBRep_Surface* theSurf);

  static bool IsVPeriodic(const HLRBRep_Surface* theSurf);

  static double VPeriod(const HLRBRep_Surface* theSurf);

  static gp_Pnt Value(const HLRBRep_Surface* theSurf, const double theU, const double theV);

  static void D0(const HLRBRep_Surface* theSurf,
                 const double           theU,
                 const double           theV,
                 gp_Pnt&                theP);

  static void D1(const HLRBRep_Surface* theSurf,
                 const double           theU,
                 const double           theV,
                 gp_Pnt&                theP,
                 gp_Vec&                theD1U,
                 gp_Vec&                theD1V);

  static void D2(const HLRBRep_Surface* theSurf,
                 const double           theU,
                 const double           theV,
                 gp_Pnt&                theP,
                 gp_Vec&                theD1U,
                 gp_Vec&                theD1V,
                 gp_Vec&                theD2U,
                 gp_Vec&                theD2V,
                 gp_Vec&                theD2UV);

  static void D3(const HLRBRep_Surface* theSurf,
                 const double           theU,
                 const double           theV,
                 gp_Pnt&                theP,
                 gp_Vec&                theD1U,
                 gp_Vec&                theD1V,
                 gp_Vec&                theD2U,
                 gp_Vec&                theD2V,
                 gp_Vec&                theD2UV,
                 gp_Vec&                theD3U,
                 gp_Vec&                theD3V,
                 gp_Vec&                theD3UUV,
                 gp_Vec&                theD3UVV);

  static gp_Vec DN(const HLRBRep_Surface* theSurf,
                   const double           theU,
                   const double           theV,
                   const int              theNu,
                   const int              theNv);

  static double UResolution(const HLRBRep_Surface* theSurf, const double theR3d);

  static double VResolution(const HLRBRep_Surface* theSurf, const double theR3d);

  static GeomAbs_SurfaceType GetType(const HLRBRep_Surface* theSurf);

  static gp_Pln Plane(const HLRBRep_Surface* theSurf);

  static gp_Cylinder Cylinder(const HLRBRep_Surface* theSurf);

  static gp_Cone Cone(const HLRBRep_Surface* theSurf);

  static gp_Torus Torus(const HLRBRep_Surface* theSurf);

  static gp_Sphere Sphere(const HLRBRep_Surface* theSurf);

  static occ::handle<Geom_BezierSurface> Bezier(const HLRBRep_Surface* theSurf);

  static occ::handle<Geom_BSplineSurface> BSpline(const HLRBRep_Surface* theSurf);

  static gp_Ax1 AxeOfRevolution(const HLRBRep_Surface* theSurf);

  static gp_Dir Direction(const HLRBRep_Surface* theSurf);

  static occ::handle<Adaptor3d_Curve> BasisCurve(const HLRBRep_Surface* theSurf);

  static occ::handle<Adaptor3d_Surface> BasisSurface(const HLRBRep_Surface* theSurf);

  static double OffsetValue(const HLRBRep_Surface* theSurf);

  Standard_EXPORT static int NbSamplesU(const HLRBRep_Surface* theSurf);

  Standard_EXPORT static int NbSamplesV(const HLRBRep_Surface* theSurf);

  Standard_EXPORT static int NbSamplesU(const HLRBRep_Surface* theSurf,
                                        const double           theU1,
                                        const double           theU2);

  Standard_EXPORT static int NbSamplesV(const HLRBRep_Surface* theSurf,
                                        const double           theV1,
                                        const double           theV2);
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

#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Geom_BezierSurface.hpp>
#include <Geom_BSplineSurface.hpp>
#include <gp_Ax1.hpp>
#include <gp_Cone.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>
#include <gp_Vec.hpp>
#include <HLRBRep_Surface.hpp>

inline double HLRBRep_SurfaceTool::FirstUParameter(const HLRBRep_Surface* theSurf)
{
  return theSurf->FirstUParameter();
}

inline double HLRBRep_SurfaceTool::FirstVParameter(const HLRBRep_Surface* theSurf)
{
  return theSurf->FirstVParameter();
}

inline double HLRBRep_SurfaceTool::LastUParameter(const HLRBRep_Surface* theSurf)
{
  return theSurf->LastUParameter();
}

inline double HLRBRep_SurfaceTool::LastVParameter(const HLRBRep_Surface* theSurf)
{
  return theSurf->LastVParameter();
}

inline int HLRBRep_SurfaceTool::NbUIntervals(const HLRBRep_Surface* theSurf,
                                             const GeomAbs_Shape    theSh)
{
  return theSurf->NbUIntervals(theSh);
}

inline int HLRBRep_SurfaceTool::NbVIntervals(const HLRBRep_Surface* theSurf,
                                             const GeomAbs_Shape    theSh)
{
  return theSurf->NbVIntervals(theSh);
}

inline void HLRBRep_SurfaceTool::UIntervals(const HLRBRep_Surface*      theSurf,
                                            NCollection_Array1<double>& theTab,
                                            const GeomAbs_Shape         theSh)
{
  theSurf->Surface().UIntervals(theTab, theSh);
}

inline void HLRBRep_SurfaceTool::VIntervals(const HLRBRep_Surface*      theSurf,
                                            NCollection_Array1<double>& theTab,
                                            const GeomAbs_Shape         theSh)
{
  theSurf->Surface().VIntervals(theTab, theSh);
}

inline occ::handle<Adaptor3d_Surface> HLRBRep_SurfaceTool::UTrim(const HLRBRep_Surface* theSurf,
                                                                 const double           theFirst,
                                                                 const double           theLast,
                                                                 const double           theTol)
{
  return theSurf->Surface().UTrim(theFirst, theLast, theTol);
}

inline occ::handle<Adaptor3d_Surface> HLRBRep_SurfaceTool::VTrim(const HLRBRep_Surface* theSurf,
                                                                 const double           theFirst,
                                                                 const double           theLast,
                                                                 const double           theTol)
{
  return theSurf->Surface().VTrim(theFirst, theLast, theTol);
}

inline bool HLRBRep_SurfaceTool::IsUClosed(const HLRBRep_Surface* theSurf)
{
  return theSurf->IsUClosed();
}

inline bool HLRBRep_SurfaceTool::IsVClosed(const HLRBRep_Surface* theSurf)
{
  return theSurf->IsVClosed();
}

inline bool HLRBRep_SurfaceTool::IsUPeriodic(const HLRBRep_Surface* theSurf)
{
  return theSurf->IsUPeriodic();
}

inline double HLRBRep_SurfaceTool::UPeriod(const HLRBRep_Surface* theSurf)
{
  return theSurf->UPeriod();
}

inline bool HLRBRep_SurfaceTool::IsVPeriodic(const HLRBRep_Surface* theSurf)
{
  return theSurf->IsVPeriodic();
}

inline double HLRBRep_SurfaceTool::VPeriod(const HLRBRep_Surface* theSurf)
{
  return theSurf->VPeriod();
}

inline gp_Pnt HLRBRep_SurfaceTool::Value(const HLRBRep_Surface* theSurf,
                                         const double           theU,
                                         const double           theV)
{
  return theSurf->Surface().Value(theU, theV);
}

inline void HLRBRep_SurfaceTool::D0(const HLRBRep_Surface* theSurf,
                                    const double           theU,
                                    const double           theV,
                                    gp_Pnt&                theP)
{
  theSurf->Surface().D0(theU, theV, theP);
}

inline void HLRBRep_SurfaceTool::D1(const HLRBRep_Surface* theSurf,
                                    const double           theU,
                                    const double           theV,
                                    gp_Pnt&                theP,
                                    gp_Vec&                theD1U,
                                    gp_Vec&                theD1V)
{
  theSurf->Surface().D1(theU, theV, theP, theD1U, theD1V);
}

inline void HLRBRep_SurfaceTool::D2(const HLRBRep_Surface* theSurf,
                                    const double           theU,
                                    const double           theV,
                                    gp_Pnt&                theP,
                                    gp_Vec&                theD1U,
                                    gp_Vec&                theD1V,
                                    gp_Vec&                theD2U,
                                    gp_Vec&                theD2V,
                                    gp_Vec&                theD2UV)
{
  theSurf->Surface().D2(theU, theV, theP, theD1U, theD1V, theD2U, theD2V, theD2UV);
}

inline void HLRBRep_SurfaceTool::D3(const HLRBRep_Surface* theSurf,
                                    const double           theU,
                                    const double           theV,
                                    gp_Pnt&                theP,
                                    gp_Vec&                theD1U,
                                    gp_Vec&                theD1V,
                                    gp_Vec&                theD2U,
                                    gp_Vec&                theD2V,
                                    gp_Vec&                theD2UV,
                                    gp_Vec&                theD3U,
                                    gp_Vec&                theD3V,
                                    gp_Vec&                theD3UUV,
                                    gp_Vec&                theD3UVV)
{
  theSurf->Surface().D3(theU,
                        theV,
                        theP,
                        theD1U,
                        theD1V,
                        theD2U,
                        theD2V,
                        theD2UV,
                        theD3U,
                        theD3V,
                        theD3UUV,
                        theD3UVV);
}

inline gp_Vec HLRBRep_SurfaceTool::DN(const HLRBRep_Surface* theSurf,
                                      const double           theU,
                                      const double           theV,
                                      const int              theNu,
                                      const int              theNv)
{
  return theSurf->Surface().DN(theU, theV, theNu, theNv);
}

inline double HLRBRep_SurfaceTool::UResolution(const HLRBRep_Surface* theSurf, const double theR3d)
{
  return theSurf->Surface().UResolution(theR3d);
}

inline double HLRBRep_SurfaceTool::VResolution(const HLRBRep_Surface* theSurf, const double theR3d)
{
  return theSurf->Surface().VResolution(theR3d);
}

inline GeomAbs_SurfaceType HLRBRep_SurfaceTool::GetType(const HLRBRep_Surface* theSurf)
{
  return theSurf->GetType();
}

inline gp_Pln HLRBRep_SurfaceTool::Plane(const HLRBRep_Surface* theSurf)
{
  return theSurf->Plane();
}

inline gp_Cylinder HLRBRep_SurfaceTool::Cylinder(const HLRBRep_Surface* theSurf)
{
  return theSurf->Cylinder();
}

inline gp_Cone HLRBRep_SurfaceTool::Cone(const HLRBRep_Surface* theSurf)
{
  return theSurf->Cone();
}

inline gp_Sphere HLRBRep_SurfaceTool::Sphere(const HLRBRep_Surface* theSurf)
{
  return theSurf->Sphere();
}

inline gp_Torus HLRBRep_SurfaceTool::Torus(const HLRBRep_Surface* theSurf)
{
  return theSurf->Torus();
}

inline occ::handle<Geom_BezierSurface> HLRBRep_SurfaceTool::Bezier(const HLRBRep_Surface* theSurf)
{
  return theSurf->Surface().Bezier();
}

inline occ::handle<Geom_BSplineSurface> HLRBRep_SurfaceTool::BSpline(const HLRBRep_Surface* theSurf)
{
  return theSurf->Surface().BSpline();
}

inline gp_Ax1 HLRBRep_SurfaceTool::AxeOfRevolution(const HLRBRep_Surface* theSurf)
{
  return theSurf->Axis();
}

inline gp_Dir HLRBRep_SurfaceTool::Direction(const HLRBRep_Surface* theSurf)
{
  return theSurf->Surface().Direction();
}

inline occ::handle<Adaptor3d_Curve> HLRBRep_SurfaceTool::BasisCurve(const HLRBRep_Surface* theSurf)
{
  return theSurf->Surface().BasisCurve();
}

inline occ::handle<Adaptor3d_Surface> HLRBRep_SurfaceTool::BasisSurface(
  const HLRBRep_Surface* theSurf)
{
  return theSurf->Surface().BasisSurface();
}

inline double HLRBRep_SurfaceTool::OffsetValue(const HLRBRep_Surface* theSurf)
{
  return theSurf->Surface().OffsetValue();
}


#endif // _HLRBRep_SurfaceTool_HeaderFile
