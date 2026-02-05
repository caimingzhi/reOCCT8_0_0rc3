#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <NCollection_Array1.hpp>

class gp_Pnt2d;
class gp_Vec2d;
class Geom2d_BezierCurve;
class Geom2d_BSplineCurve;

class Contap_HCurve2dTool
{
public:
  DEFINE_STANDARD_ALLOC

  static double FirstParameter(const occ::handle<Adaptor2d_Curve2d>& C);

  static double LastParameter(const occ::handle<Adaptor2d_Curve2d>& C);

  static GeomAbs_Shape Continuity(const occ::handle<Adaptor2d_Curve2d>& C);

  //! Returns the number of intervals for continuity
  //! <S>. May be one if Continuity(myclass) >= <S>
  static int NbIntervals(const occ::handle<Adaptor2d_Curve2d>& C, const GeomAbs_Shape S);

  //! Stores in <T> the parameters bounding the intervals
  //! of continuity <S>.
  //!
  //! The array must provide enough room to accommodate
  //! for the parameters. i.e. T.Length() > NbIntervals()
  static void Intervals(const occ::handle<Adaptor2d_Curve2d>& C,
                        NCollection_Array1<double>&           T,
                        const GeomAbs_Shape                   S);

  static bool IsClosed(const occ::handle<Adaptor2d_Curve2d>& C);

  static bool IsPeriodic(const occ::handle<Adaptor2d_Curve2d>& C);

  static double Period(const occ::handle<Adaptor2d_Curve2d>& C);

  //! Computes the point of parameter U on the curve.
  static gp_Pnt2d Value(const occ::handle<Adaptor2d_Curve2d>& C, const double U);

  //! Computes the point of parameter U on the curve.
  static void D0(const occ::handle<Adaptor2d_Curve2d>& C, const double U, gp_Pnt2d& P);

  //! Computes the point of parameter U on the curve with its
  //! first derivative.
  //! Raised if the continuity of the current interval
  //! is not C1.
  static void D1(const occ::handle<Adaptor2d_Curve2d>& C, const double U, gp_Pnt2d& P, gp_Vec2d& V);

  //! Returns the point P of parameter U, the first and second
  //! derivatives V1 and V2.
  //! Raised if the continuity of the current interval
  //! is not C2.
  static void D2(const occ::handle<Adaptor2d_Curve2d>& C,
                 const double                          U,
                 gp_Pnt2d&                             P,
                 gp_Vec2d&                             V1,
                 gp_Vec2d&                             V2);

  //! Returns the point P of parameter U, the first, the second
  //! and the third derivative.
  //! Raised if the continuity of the current interval
  //! is not C3.
  static void D3(const occ::handle<Adaptor2d_Curve2d>& C,
                 const double                          U,
                 gp_Pnt2d&                             P,
                 gp_Vec2d&                             V1,
                 gp_Vec2d&                             V2,
                 gp_Vec2d&                             V3);

  //! The returned vector gives the value of the derivative for the
  //! order of derivation N.
  //! Raised if the continuity of the current interval
  //! is not CN.
  //! Raised if N < 1.
  static gp_Vec2d DN(const occ::handle<Adaptor2d_Curve2d>& C, const double U, const int N);

  //! Returns the parametric resolution corresponding
  //! to the real space resolution <R3d>.
  static double Resolution(const occ::handle<Adaptor2d_Curve2d>& C, const double R3d);

  //! Returns the type of the curve in the current
  //! interval: Line, Circle, Ellipse, Hyperbola,
  //! Parabola, BezierCurve, BSplineCurve, OtherCurve.
  static GeomAbs_CurveType GetType(const occ::handle<Adaptor2d_Curve2d>& C);

  static gp_Lin2d Line(const occ::handle<Adaptor2d_Curve2d>& C);

  static gp_Circ2d Circle(const occ::handle<Adaptor2d_Curve2d>& C);

  static gp_Elips2d Ellipse(const occ::handle<Adaptor2d_Curve2d>& C);

  static gp_Hypr2d Hyperbola(const occ::handle<Adaptor2d_Curve2d>& C);

  static gp_Parab2d Parabola(const occ::handle<Adaptor2d_Curve2d>& C);

  static occ::handle<Geom2d_BezierCurve> Bezier(const occ::handle<Adaptor2d_Curve2d>& C);

  static occ::handle<Geom2d_BSplineCurve> BSpline(const occ::handle<Adaptor2d_Curve2d>& C);

  Standard_EXPORT static int NbSamples(const occ::handle<Adaptor2d_Curve2d>& C,
                                       const double                          U0,
                                       const double                          U1);
};

#include <Adaptor2d_Curve2d.hpp>

#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_Shape.hpp>

#include <gp_Vec2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Hypr2d.hpp>

#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>

#include <NCollection_Array1.hpp>

//============================================================
inline double Contap_HCurve2dTool::FirstParameter(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->FirstParameter());
}

//============================================================
inline double Contap_HCurve2dTool::LastParameter(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->LastParameter());
}

//============================================================
inline GeomAbs_Shape Contap_HCurve2dTool::Continuity(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Continuity());
}

//============================================================
inline int Contap_HCurve2dTool::NbIntervals(const occ::handle<Adaptor2d_Curve2d>& C,
                                            const GeomAbs_Shape                   Sh)
{
  return (C->NbIntervals(Sh));
}

//============================================================
inline void Contap_HCurve2dTool::Intervals(const occ::handle<Adaptor2d_Curve2d>& C,
                                           NCollection_Array1<double>&           Tab,
                                           const GeomAbs_Shape                   Sh)
{
  C->Intervals(Tab, Sh);
}

//============================================================
inline bool Contap_HCurve2dTool::IsClosed(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->IsClosed());
}

//============================================================
inline bool Contap_HCurve2dTool::IsPeriodic(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->IsPeriodic());
}

//============================================================
inline double Contap_HCurve2dTool::Period(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Period());
}

//============================================================
inline gp_Pnt2d Contap_HCurve2dTool::Value(const occ::handle<Adaptor2d_Curve2d>& C, const double U)
{
  return (C->Value(U));
}

//============================================================
inline void Contap_HCurve2dTool::D0(const occ::handle<Adaptor2d_Curve2d>& C,
                                    const double                          U,
                                    gp_Pnt2d&                             P)
{
  C->D0(U, P);
}

//============================================================
inline void Contap_HCurve2dTool::D1(const occ::handle<Adaptor2d_Curve2d>& C,
                                    const double                          U,
                                    gp_Pnt2d&                             P,
                                    gp_Vec2d&                             T)
{
  C->D1(U, P, T);
}

//============================================================
inline void Contap_HCurve2dTool::D2(const occ::handle<Adaptor2d_Curve2d>& C,
                                    const double                          U,
                                    gp_Pnt2d&                             P,
                                    gp_Vec2d&                             T,
                                    gp_Vec2d&                             N)
{

  C->D2(U, P, T, N);
}

//============================================================
inline void Contap_HCurve2dTool::D3(const occ::handle<Adaptor2d_Curve2d>& C,
                                    const double                          U,
                                    gp_Pnt2d&                             P,
                                    gp_Vec2d&                             V1,
                                    gp_Vec2d&                             V2,
                                    gp_Vec2d&                             V3)
{

  C->D3(U, P, V1, V2, V3);
}

//============================================================
inline gp_Vec2d Contap_HCurve2dTool::DN(const occ::handle<Adaptor2d_Curve2d>& C,
                                        const double                          U,
                                        const int                             N)
{

  return (C->DN(U, N));
}

//============================================================
inline double Contap_HCurve2dTool::Resolution(const occ::handle<Adaptor2d_Curve2d>& C,
                                              const double                          R3d)
{
  return (C->Resolution(R3d));
}

//============================================================
inline GeomAbs_CurveType Contap_HCurve2dTool::GetType(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->GetType());
}

//============================================================
inline gp_Lin2d Contap_HCurve2dTool::Line(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Line());
}

//============================================================
inline gp_Circ2d Contap_HCurve2dTool::Circle(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Circle());
}

//============================================================
inline gp_Elips2d Contap_HCurve2dTool::Ellipse(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Ellipse());
}

//============================================================
inline gp_Parab2d Contap_HCurve2dTool::Parabola(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Parabola());
}

//============================================================
inline gp_Hypr2d Contap_HCurve2dTool::Hyperbola(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Hyperbola());
}

//============================================================
inline occ::handle<Geom2d_BezierCurve> Contap_HCurve2dTool::Bezier(
  const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Bezier());
}

//============================================================
inline occ::handle<Geom2d_BSplineCurve> Contap_HCurve2dTool::BSpline(
  const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->BSpline());
}

//============================================================
