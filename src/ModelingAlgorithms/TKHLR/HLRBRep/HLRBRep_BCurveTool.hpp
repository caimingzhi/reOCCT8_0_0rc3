// Created on: 1995-07-17
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

#ifndef _HLRBRep_BCurveTool_HeaderFile
#define _HLRBRep_BCurveTool_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <GeomAbs_CurveType.hpp>
#include <gp_Lin.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Parab.hpp>
class BRepAdaptor_Curve;
class gp_Pnt;
class gp_Vec;
class Geom_BezierCurve;
class Geom_BSplineCurve;

class HLRBRep_BCurveTool
{
public:
  DEFINE_STANDARD_ALLOC

  static double FirstParameter(const BRepAdaptor_Curve& C);

  static double LastParameter(const BRepAdaptor_Curve& C);

  static GeomAbs_Shape Continuity(const BRepAdaptor_Curve& C);

  //! Returns the number of intervals for continuity
  //! <S>. May be one if Continuity(myclass) >= <S>
  static int NbIntervals(const BRepAdaptor_Curve& C, const GeomAbs_Shape S);

  //! Stores in <T> the parameters bounding the intervals
  //! of continuity <S>.
  //!
  //! The array must provide enough room to accommodate
  //! for the parameters. i.e. T.Length() > NbIntervals()
  static void Intervals(const BRepAdaptor_Curve&    C,
                        NCollection_Array1<double>& T,
                        const GeomAbs_Shape         S);

  static bool IsClosed(const BRepAdaptor_Curve& C);

  static bool IsPeriodic(const BRepAdaptor_Curve& C);

  static double Period(const BRepAdaptor_Curve& C);

  //! Computes the point of parameter U on the curve.
  static gp_Pnt Value(const BRepAdaptor_Curve& C, const double U);

  //! Computes the point of parameter U on the curve.
  static void D0(const BRepAdaptor_Curve& C, const double U, gp_Pnt& P);

  //! Computes the point of parameter U on the curve with its
  //! first derivative.
  //! Raised if the continuity of the current interval
  //! is not C1.
  static void D1(const BRepAdaptor_Curve& C, const double U, gp_Pnt& P, gp_Vec& V);

  //! Returns the point P of parameter U, the first and second
  //! derivatives V1 and V2.
  //! Raised if the continuity of the current interval
  //! is not C2.
  static void D2(const BRepAdaptor_Curve& C, const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2);

  //! Returns the point P of parameter U, the first, the second
  //! and the third derivative.
  //! Raised if the continuity of the current interval
  //! is not C3.
  static void D3(const BRepAdaptor_Curve& C,
                 const double             U,
                 gp_Pnt&                  P,
                 gp_Vec&                  V1,
                 gp_Vec&                  V2,
                 gp_Vec&                  V3);

  //! The returned vector gives the value of the derivative for the
  //! order of derivation N.
  //! Raised if the continuity of the current interval
  //! is not CN.
  //! Raised if N < 1.
  static gp_Vec DN(const BRepAdaptor_Curve& C, const double U, const int N);

  //! Returns the parametric resolution corresponding
  //! to the real space resolution <R3d>.
  static double Resolution(const BRepAdaptor_Curve& C, const double R3d);

  //! Returns the type of the curve in the current
  //! interval: Line, Circle, Ellipse, Hyperbola,
  //! Parabola, BezierCurve, BSplineCurve, OtherCurve.
  static GeomAbs_CurveType GetType(const BRepAdaptor_Curve& C);

  static gp_Lin Line(const BRepAdaptor_Curve& C);

  static gp_Circ Circle(const BRepAdaptor_Curve& C);

  static gp_Elips Ellipse(const BRepAdaptor_Curve& C);

  static gp_Hypr Hyperbola(const BRepAdaptor_Curve& C);

  static gp_Parab Parabola(const BRepAdaptor_Curve& C);

  Standard_EXPORT static occ::handle<Geom_BezierCurve> Bezier(const BRepAdaptor_Curve& C);

  Standard_EXPORT static occ::handle<Geom_BSplineCurve> BSpline(const BRepAdaptor_Curve& C);

  static int Degree(const BRepAdaptor_Curve& C);

  static bool IsRational(const BRepAdaptor_Curve& C);

  static int NbPoles(const BRepAdaptor_Curve& C);

  static int NbKnots(const BRepAdaptor_Curve& C);

  Standard_EXPORT static void Poles(const BRepAdaptor_Curve& C, NCollection_Array1<gp_Pnt>& T);

  Standard_EXPORT static void PolesAndWeights(const BRepAdaptor_Curve&    C,
                                              NCollection_Array1<gp_Pnt>& T,
                                              NCollection_Array1<double>& W);

  Standard_EXPORT static int NbSamples(const BRepAdaptor_Curve& C,
                                       const double             U0,
                                       const double             U1);
};
// Created on: 1992-10-22
// Created by: Laurent BUCHARD
// Copyright (c) 1992-1999 Matra Datavision
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

#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Vec.hpp>
#include <gp_Lin.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Parab.hpp>
#include <gp_Hypr.hpp>
#include <BRepAdaptor_Curve.hpp>

//=================================================================================================

inline double HLRBRep_BCurveTool::FirstParameter(const BRepAdaptor_Curve& C)
{
  return (C.FirstParameter());
}

//=================================================================================================

inline double HLRBRep_BCurveTool::LastParameter(const BRepAdaptor_Curve& C)
{
  return (C.LastParameter());
}

//=================================================================================================

inline GeomAbs_Shape HLRBRep_BCurveTool::Continuity(const BRepAdaptor_Curve& C)
{
  return (C.Continuity());
}

//=================================================================================================

inline int HLRBRep_BCurveTool::NbIntervals(const BRepAdaptor_Curve& C, const GeomAbs_Shape Sh)
{
  return (C.NbIntervals(Sh));
}

//=================================================================================================

inline void HLRBRep_BCurveTool::Intervals(const BRepAdaptor_Curve&    C,
                                          NCollection_Array1<double>& Tab,
                                          const GeomAbs_Shape         Sh)
{
  C.Intervals(Tab, Sh);
}

//=================================================================================================

inline bool HLRBRep_BCurveTool::IsClosed(const BRepAdaptor_Curve& C)
{
  return (C.IsClosed());
}

//=================================================================================================

inline bool HLRBRep_BCurveTool::IsPeriodic(const BRepAdaptor_Curve& C)
{
  return (C.IsPeriodic());
}

//=================================================================================================

inline double HLRBRep_BCurveTool::Period(const BRepAdaptor_Curve& C)
{
  return (C.Period());
}

//=================================================================================================

inline gp_Pnt HLRBRep_BCurveTool::Value(const BRepAdaptor_Curve& C, const double U)
{
  return (C.Value(U));
}

//=================================================================================================

inline void HLRBRep_BCurveTool::D0(const BRepAdaptor_Curve& C, const double U, gp_Pnt& P)
{
  C.D0(U, P);
}

//=================================================================================================

inline void HLRBRep_BCurveTool::D1(const BRepAdaptor_Curve& C, const double U, gp_Pnt& P, gp_Vec& T)
{
  C.D1(U, P, T);
}

inline void HLRBRep_BCurveTool::D2(const BRepAdaptor_Curve& C,
                                   const double             U,
                                   gp_Pnt&                  P,
                                   gp_Vec&                  T,
                                   gp_Vec&                  N)
{
  C.D2(U, P, T, N);
}

//=================================================================================================

inline void HLRBRep_BCurveTool::D3(const BRepAdaptor_Curve& C,
                                   const double             U,
                                   gp_Pnt&                  P,
                                   gp_Vec&                  V1,
                                   gp_Vec&                  V2,
                                   gp_Vec&                  V3)
{
  C.D3(U, P, V1, V2, V3);
}

//=================================================================================================

inline gp_Vec HLRBRep_BCurveTool::DN(const BRepAdaptor_Curve& C, const double U, const int N)
{
  return (C.DN(U, N));
}

//=================================================================================================

inline double HLRBRep_BCurveTool::Resolution(const BRepAdaptor_Curve& C, const double R3d)
{
  return (C.Resolution(R3d));
}

//=================================================================================================

inline GeomAbs_CurveType HLRBRep_BCurveTool::GetType(const BRepAdaptor_Curve& C)
{
  return (C.GetType());
}

//=================================================================================================

inline gp_Lin HLRBRep_BCurveTool::Line(const BRepAdaptor_Curve& C)
{
  return (C.Line());
}

//=================================================================================================

inline gp_Circ HLRBRep_BCurveTool::Circle(const BRepAdaptor_Curve& C)
{
  return (C.Circle());
}

//=================================================================================================

inline gp_Elips HLRBRep_BCurveTool::Ellipse(const BRepAdaptor_Curve& C)
{
  return (C.Ellipse());
}

//=================================================================================================

inline gp_Parab HLRBRep_BCurveTool::Parabola(const BRepAdaptor_Curve& C)
{
  return (C.Parabola());
}

//=================================================================================================

inline gp_Hypr HLRBRep_BCurveTool::Hyperbola(const BRepAdaptor_Curve& C)
{
  return (C.Hyperbola());
}

//=================================================================================================

inline int HLRBRep_BCurveTool::Degree(const BRepAdaptor_Curve& C)
{
  return (C.Degree());
}

//=================================================================================================

inline bool HLRBRep_BCurveTool::IsRational(const BRepAdaptor_Curve& C)
{
  return (C.IsRational());
}

//=================================================================================================

inline int HLRBRep_BCurveTool::NbPoles(const BRepAdaptor_Curve& C)
{
  return (C.NbPoles());
}

//=================================================================================================

inline int HLRBRep_BCurveTool::NbKnots(const BRepAdaptor_Curve& C)
{
  return (C.NbKnots());
}


#endif // _HLRBRep_BCurveTool_HeaderFile
