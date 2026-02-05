#pragma once

#include <Adaptor3d_Curve.hpp>
#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Lin.hpp>
#include <gp_Parab.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Hypr.hpp>
#include <NCollection_Array1.hpp>

class BRepBlend_HCurveTool
{
public:
  DEFINE_STANDARD_ALLOC

  static double FirstParameter(const occ::handle<Adaptor3d_Curve>& C);

  static double LastParameter(const occ::handle<Adaptor3d_Curve>& C);

  static GeomAbs_Shape Continuity(const occ::handle<Adaptor3d_Curve>& C);

  //! Returns the number of intervals for continuity
  //! <S>. May be one if Continuity(myclass) >= <S>
  static int NbIntervals(const occ::handle<Adaptor3d_Curve>& C, const GeomAbs_Shape S);

  //! Stores in <T> the parameters bounding the intervals
  //! of continuity <S>.
  //!
  //! The array must provide enough room to accommodate
  //! for the parameters. i.e. T.Length() > NbIntervals()
  static void Intervals(const occ::handle<Adaptor3d_Curve>& C,
                        NCollection_Array1<double>&         T,
                        const GeomAbs_Shape                 S);

  static bool IsClosed(const occ::handle<Adaptor3d_Curve>& C);

  static bool IsPeriodic(const occ::handle<Adaptor3d_Curve>& C);

  static double Period(const occ::handle<Adaptor3d_Curve>& C);

  //! Computes the point of parameter U on the curve.
  static gp_Pnt Value(const occ::handle<Adaptor3d_Curve>& C, const double U);

  //! Computes the point of parameter U on the curve.
  static void D0(const occ::handle<Adaptor3d_Curve>& C, const double U, gp_Pnt& P);

  //! Computes the point of parameter U on the curve with its
  //! first derivative.
  //! Raised if the continuity of the current interval
  //! is not C1.
  static void D1(const occ::handle<Adaptor3d_Curve>& C, const double U, gp_Pnt& P, gp_Vec& V);

  //! Returns the point P of parameter U, the first and second
  //! derivatives V1 and V2.
  //! Raised if the continuity of the current interval
  //! is not C2.
  static void D2(const occ::handle<Adaptor3d_Curve>& C,
                 const double                        U,
                 gp_Pnt&                             P,
                 gp_Vec&                             V1,
                 gp_Vec&                             V2);

  //! Returns the point P of parameter U, the first, the second
  //! and the third derivative.
  //! Raised if the continuity of the current interval
  //! is not C3.
  static void D3(const occ::handle<Adaptor3d_Curve>& C,
                 const double                        U,
                 gp_Pnt&                             P,
                 gp_Vec&                             V1,
                 gp_Vec&                             V2,
                 gp_Vec&                             V3);

  //! The returned vector gives the value of the derivative for the
  //! order of derivation N.
  //! Raised if the continuity of the current interval
  //! is not CN.
  //! Raised if N < 1.
  static gp_Vec DN(const occ::handle<Adaptor3d_Curve>& C, const double U, const int N);

  //! Returns the parametric resolution corresponding
  //! to the real space resolution <R3d>.
  static double Resolution(const occ::handle<Adaptor3d_Curve>& C, const double R3d);

  //! Returns the type of the curve in the current
  //! interval: Line, Circle, Ellipse, Hyperbola,
  //! Parabola, BezierCurve, BSplineCurve, OtherCurve.
  static GeomAbs_CurveType GetType(const occ::handle<Adaptor3d_Curve>& C);

  static gp_Lin Line(const occ::handle<Adaptor3d_Curve>& C);

  static gp_Circ Circle(const occ::handle<Adaptor3d_Curve>& C);

  static gp_Elips Ellipse(const occ::handle<Adaptor3d_Curve>& C);

  static gp_Hypr Hyperbola(const occ::handle<Adaptor3d_Curve>& C);

  static gp_Parab Parabola(const occ::handle<Adaptor3d_Curve>& C);

  static occ::handle<Geom_BezierCurve> Bezier(const occ::handle<Adaptor3d_Curve>& C);

  static occ::handle<Geom_BSplineCurve> BSpline(const occ::handle<Adaptor3d_Curve>& C);

  Standard_EXPORT static int NbSamples(const occ::handle<Adaptor3d_Curve>& C,
                                       const double                        U0,
                                       const double                        U1);
};

#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_Shape.hpp>

#include <gp_Vec.hpp>
#include <gp_Lin.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Parab.hpp>
#include <gp_Hypr.hpp>

#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>

#include <NCollection_Array1.hpp>

//============================================================
inline double BRepBlend_HCurveTool::FirstParameter(const occ::handle<Adaptor3d_Curve>& C)
{
  return (C->FirstParameter());
}

//============================================================
inline double BRepBlend_HCurveTool::LastParameter(const occ::handle<Adaptor3d_Curve>& C)
{
  return (C->LastParameter());
}

//============================================================
inline GeomAbs_Shape BRepBlend_HCurveTool::Continuity(const occ::handle<Adaptor3d_Curve>& C)
{
  return (C->Continuity());
}

//============================================================
inline int BRepBlend_HCurveTool::NbIntervals(const occ::handle<Adaptor3d_Curve>& C,
                                             const GeomAbs_Shape                 Sh)
{
  return (C->NbIntervals(Sh));
}

//============================================================
inline void BRepBlend_HCurveTool::Intervals(const occ::handle<Adaptor3d_Curve>& C,
                                            NCollection_Array1<double>&         Tab,
                                            const GeomAbs_Shape                 Sh)
{
  C->Intervals(Tab, Sh);
}

//============================================================
inline bool BRepBlend_HCurveTool::IsClosed(const occ::handle<Adaptor3d_Curve>& C)
{
  return (C->IsClosed());
}

//============================================================
inline bool BRepBlend_HCurveTool::IsPeriodic(const occ::handle<Adaptor3d_Curve>& C)
{
  return (C->IsPeriodic());
}

//============================================================
inline double BRepBlend_HCurveTool::Period(const occ::handle<Adaptor3d_Curve>& C)
{
  return (C->Period());
}

//============================================================
inline gp_Pnt BRepBlend_HCurveTool::Value(const occ::handle<Adaptor3d_Curve>& C, const double U)
{
  return (C->Value(U));
}

//============================================================
inline void BRepBlend_HCurveTool::D0(const occ::handle<Adaptor3d_Curve>& C,
                                     const double                        U,
                                     gp_Pnt&                             P)
{
  C->D0(U, P);
}

//============================================================
inline void BRepBlend_HCurveTool::D1(const occ::handle<Adaptor3d_Curve>& C,
                                     const double                        U,
                                     gp_Pnt&                             P,
                                     gp_Vec&                             T)
{
  C->D1(U, P, T);
}

//============================================================
inline void BRepBlend_HCurveTool::D2(const occ::handle<Adaptor3d_Curve>& C,
                                     const double                        U,
                                     gp_Pnt&                             P,
                                     gp_Vec&                             T,
                                     gp_Vec&                             N)
{

  C->D2(U, P, T, N);
}

//============================================================
inline void BRepBlend_HCurveTool::D3(const occ::handle<Adaptor3d_Curve>& C,
                                     const double                        U,
                                     gp_Pnt&                             P,
                                     gp_Vec&                             V1,
                                     gp_Vec&                             V2,
                                     gp_Vec&                             V3)
{

  C->D3(U, P, V1, V2, V3);
}

//============================================================
inline gp_Vec BRepBlend_HCurveTool::DN(const occ::handle<Adaptor3d_Curve>& C,
                                       const double                        U,
                                       const int                           N)
{

  return (C->DN(U, N));
}

//============================================================
inline double BRepBlend_HCurveTool::Resolution(const occ::handle<Adaptor3d_Curve>& C,
                                               const double                        R3d)
{
  return (C->Resolution(R3d));
}

//============================================================
inline GeomAbs_CurveType BRepBlend_HCurveTool::GetType(const occ::handle<Adaptor3d_Curve>& C)
{
  return (C->GetType());
}

//============================================================
inline gp_Lin BRepBlend_HCurveTool::Line(const occ::handle<Adaptor3d_Curve>& C)
{
  return (C->Line());
}

//============================================================
inline gp_Circ BRepBlend_HCurveTool::Circle(const occ::handle<Adaptor3d_Curve>& C)
{
  return (C->Circle());
}

//============================================================
inline gp_Elips BRepBlend_HCurveTool::Ellipse(const occ::handle<Adaptor3d_Curve>& C)
{
  return (C->Ellipse());
}

//============================================================
inline gp_Parab BRepBlend_HCurveTool::Parabola(const occ::handle<Adaptor3d_Curve>& C)
{
  return (C->Parabola());
}

//============================================================
inline gp_Hypr BRepBlend_HCurveTool::Hyperbola(const occ::handle<Adaptor3d_Curve>& C)
{
  return (C->Hyperbola());
}

//============================================================
inline occ::handle<Geom_BezierCurve> BRepBlend_HCurveTool::Bezier(
  const occ::handle<Adaptor3d_Curve>& C)
{
  return (C->Bezier());
}

//============================================================
inline occ::handle<Geom_BSplineCurve> BRepBlend_HCurveTool::BSpline(
  const occ::handle<Adaptor3d_Curve>& C)
{
  return (C->BSpline());
}

//============================================================
