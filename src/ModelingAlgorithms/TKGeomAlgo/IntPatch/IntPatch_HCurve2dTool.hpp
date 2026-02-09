#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Boolean.hpp>
class gp_Pnt2d;
class gp_Vec2d;
class Geom2d_BezierCurve;
class Geom2d_BSplineCurve;

class IntPatch_HCurve2dTool
{
public:
  DEFINE_STANDARD_ALLOC

  static double FirstParameter(const occ::handle<Adaptor2d_Curve2d>& C);

  static double LastParameter(const occ::handle<Adaptor2d_Curve2d>& C);

  static GeomAbs_Shape Continuity(const occ::handle<Adaptor2d_Curve2d>& C);

  static int NbIntervals(const occ::handle<Adaptor2d_Curve2d>& C, const GeomAbs_Shape S);

  static void Intervals(const occ::handle<Adaptor2d_Curve2d>& C,
                        NCollection_Array1<double>&           T,
                        const GeomAbs_Shape                   S);

  static bool IsClosed(const occ::handle<Adaptor2d_Curve2d>& C);

  static bool IsPeriodic(const occ::handle<Adaptor2d_Curve2d>& C);

  static double Period(const occ::handle<Adaptor2d_Curve2d>& C);

  static gp_Pnt2d Value(const occ::handle<Adaptor2d_Curve2d>& C, const double U);

  static void D0(const occ::handle<Adaptor2d_Curve2d>& C, const double U, gp_Pnt2d& P);

  static void D1(const occ::handle<Adaptor2d_Curve2d>& C, const double U, gp_Pnt2d& P, gp_Vec2d& V);

  static void D2(const occ::handle<Adaptor2d_Curve2d>& C,
                 const double                          U,
                 gp_Pnt2d&                             P,
                 gp_Vec2d&                             V1,
                 gp_Vec2d&                             V2);

  static void D3(const occ::handle<Adaptor2d_Curve2d>& C,
                 const double                          U,
                 gp_Pnt2d&                             P,
                 gp_Vec2d&                             V1,
                 gp_Vec2d&                             V2,
                 gp_Vec2d&                             V3);

  static gp_Vec2d DN(const occ::handle<Adaptor2d_Curve2d>& C, const double U, const int N);

  static double Resolution(const occ::handle<Adaptor2d_Curve2d>& C, const double R3d);

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

#include <Adaptor2d_Curve2d.hpp>

inline double IntPatch_HCurve2dTool::FirstParameter(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->FirstParameter());
}

inline double IntPatch_HCurve2dTool::LastParameter(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->LastParameter());
}

inline GeomAbs_Shape IntPatch_HCurve2dTool::Continuity(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Continuity());
}

inline int IntPatch_HCurve2dTool::NbIntervals(const occ::handle<Adaptor2d_Curve2d>& C,
                                              const GeomAbs_Shape                   Sh)
{
  return (C->NbIntervals(Sh));
}

inline void IntPatch_HCurve2dTool::Intervals(const occ::handle<Adaptor2d_Curve2d>& C,
                                             NCollection_Array1<double>&           Tab,
                                             const GeomAbs_Shape                   Sh)
{
  C->Intervals(Tab, Sh);
}

inline bool IntPatch_HCurve2dTool::IsClosed(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->IsClosed());
}

inline bool IntPatch_HCurve2dTool::IsPeriodic(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->IsPeriodic());
}

inline double IntPatch_HCurve2dTool::Period(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Period());
}

inline gp_Pnt2d IntPatch_HCurve2dTool::Value(const occ::handle<Adaptor2d_Curve2d>& C,
                                             const double                          U)
{
  return (C->Value(U));
}

inline void IntPatch_HCurve2dTool::D0(const occ::handle<Adaptor2d_Curve2d>& C,
                                      const double                          U,
                                      gp_Pnt2d&                             P)
{
  C->D0(U, P);
}

inline void IntPatch_HCurve2dTool::D1(const occ::handle<Adaptor2d_Curve2d>& C,
                                      const double                          U,
                                      gp_Pnt2d&                             P,
                                      gp_Vec2d&                             T)
{
  C->D1(U, P, T);
}

inline void IntPatch_HCurve2dTool::D2(const occ::handle<Adaptor2d_Curve2d>& C,
                                      const double                          U,
                                      gp_Pnt2d&                             P,
                                      gp_Vec2d&                             T,
                                      gp_Vec2d&                             N)
{
  C->D2(U, P, T, N);
}

inline void IntPatch_HCurve2dTool::D3(const occ::handle<Adaptor2d_Curve2d>& C,
                                      const double                          U,
                                      gp_Pnt2d&                             P,
                                      gp_Vec2d&                             V1,
                                      gp_Vec2d&                             V2,
                                      gp_Vec2d&                             V3)
{
  C->D3(U, P, V1, V2, V3);
}

inline gp_Vec2d IntPatch_HCurve2dTool::DN(const occ::handle<Adaptor2d_Curve2d>& C,
                                          const double                          U,
                                          const int                             N)
{
  return (C->DN(U, N));
}

inline double IntPatch_HCurve2dTool::Resolution(const occ::handle<Adaptor2d_Curve2d>& C,
                                                const double                          R3d)
{
  return (C->Resolution(R3d));
}

inline GeomAbs_CurveType IntPatch_HCurve2dTool::GetType(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->GetType());
}

inline gp_Lin2d IntPatch_HCurve2dTool::Line(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Line());
}

inline gp_Circ2d IntPatch_HCurve2dTool::Circle(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Circle());
}

inline gp_Elips2d IntPatch_HCurve2dTool::Ellipse(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Ellipse());
}

inline gp_Parab2d IntPatch_HCurve2dTool::Parabola(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Parabola());
}

inline gp_Hypr2d IntPatch_HCurve2dTool::Hyperbola(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Hyperbola());
}

inline occ::handle<Geom2d_BezierCurve> IntPatch_HCurve2dTool::Bezier(
  const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->Bezier());
}

inline occ::handle<Geom2d_BSplineCurve> IntPatch_HCurve2dTool::BSpline(
  const occ::handle<Adaptor2d_Curve2d>& C)
{
  return (C->BSpline());
}
