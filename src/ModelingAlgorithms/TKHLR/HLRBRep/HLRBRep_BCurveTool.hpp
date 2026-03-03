#pragma once

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
namespace model { namespace adapter {
class BRepAdaptor_Curve;
}} // namespace model::adapter

class gp_Pnt;
class gp_Vec;
class Geom_BezierCurve;
class Geom_BSplineCurve;

class HLRBRep_BCurveTool
{
public:
  DEFINE_STANDARD_ALLOC

  static double FirstParameter(const ::model::adapter::BRepAdaptor_Curve& C);

  static double LastParameter(const ::model::adapter::BRepAdaptor_Curve& C);

  static GeomAbs_Shape Continuity(const ::model::adapter::BRepAdaptor_Curve& C);

  static int NbIntervals(const ::model::adapter::BRepAdaptor_Curve& C, const GeomAbs_Shape S);

  static void Intervals(const ::model::adapter::BRepAdaptor_Curve&    C,
                        NCollection_Array1<double>& T,
                        const GeomAbs_Shape         S);

  static bool IsClosed(const ::model::adapter::BRepAdaptor_Curve& C);

  static bool IsPeriodic(const ::model::adapter::BRepAdaptor_Curve& C);

  static double Period(const ::model::adapter::BRepAdaptor_Curve& C);

  static gp_Pnt Value(const ::model::adapter::BRepAdaptor_Curve& C, const double U);

  static void D0(const ::model::adapter::BRepAdaptor_Curve& C, const double U, gp_Pnt& P);

  static void D1(const ::model::adapter::BRepAdaptor_Curve& C, const double U, gp_Pnt& P, gp_Vec& V);

  static void D2(const ::model::adapter::BRepAdaptor_Curve& C, const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2);

  static void D3(const ::model::adapter::BRepAdaptor_Curve& C,
                 const double             U,
                 gp_Pnt&                  P,
                 gp_Vec&                  V1,
                 gp_Vec&                  V2,
                 gp_Vec&                  V3);

  static gp_Vec DN(const ::model::adapter::BRepAdaptor_Curve& C, const double U, const int N);

  static double Resolution(const ::model::adapter::BRepAdaptor_Curve& C, const double R3d);

  static GeomAbs_CurveType GetType(const ::model::adapter::BRepAdaptor_Curve& C);

  static gp_Lin Line(const ::model::adapter::BRepAdaptor_Curve& C);

  static gp_Circ Circle(const ::model::adapter::BRepAdaptor_Curve& C);

  static gp_Elips Ellipse(const ::model::adapter::BRepAdaptor_Curve& C);

  static gp_Hypr Hyperbola(const ::model::adapter::BRepAdaptor_Curve& C);

  static gp_Parab Parabola(const ::model::adapter::BRepAdaptor_Curve& C);

  Standard_EXPORT static occ::handle<Geom_BezierCurve> Bezier(const ::model::adapter::BRepAdaptor_Curve& C);

  Standard_EXPORT static occ::handle<Geom_BSplineCurve> BSpline(const ::model::adapter::BRepAdaptor_Curve& C);

  static int Degree(const ::model::adapter::BRepAdaptor_Curve& C);

  static bool IsRational(const ::model::adapter::BRepAdaptor_Curve& C);

  static int NbPoles(const ::model::adapter::BRepAdaptor_Curve& C);

  static int NbKnots(const ::model::adapter::BRepAdaptor_Curve& C);

  Standard_EXPORT static void Poles(const ::model::adapter::BRepAdaptor_Curve& C, NCollection_Array1<gp_Pnt>& T);

  Standard_EXPORT static void PolesAndWeights(const ::model::adapter::BRepAdaptor_Curve&    C,
                                              NCollection_Array1<gp_Pnt>& T,
                                              NCollection_Array1<double>& W);

  Standard_EXPORT static int NbSamples(const ::model::adapter::BRepAdaptor_Curve& C,
                                       const double             U0,
                                       const double             U1);
};

#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Vec.hpp>
#include <gp_Lin.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Parab.hpp>
#include <gp_Hypr.hpp>
#include <BRepAdaptor_Curve.hpp>

inline double HLRBRep_BCurveTool::FirstParameter(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.FirstParameter());
}

inline double HLRBRep_BCurveTool::LastParameter(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.LastParameter());
}

inline GeomAbs_Shape HLRBRep_BCurveTool::Continuity(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.Continuity());
}

inline int HLRBRep_BCurveTool::NbIntervals(const ::model::adapter::BRepAdaptor_Curve& C, const GeomAbs_Shape Sh)
{
  return (C.NbIntervals(Sh));
}

inline void HLRBRep_BCurveTool::Intervals(const ::model::adapter::BRepAdaptor_Curve&    C,
                                          NCollection_Array1<double>& Tab,
                                          const GeomAbs_Shape         Sh)
{
  C.Intervals(Tab, Sh);
}

inline bool HLRBRep_BCurveTool::IsClosed(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.IsClosed());
}

inline bool HLRBRep_BCurveTool::IsPeriodic(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.IsPeriodic());
}

inline double HLRBRep_BCurveTool::Period(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.Period());
}

inline gp_Pnt HLRBRep_BCurveTool::Value(const ::model::adapter::BRepAdaptor_Curve& C, const double U)
{
  return (C.Value(U));
}

inline void HLRBRep_BCurveTool::D0(const ::model::adapter::BRepAdaptor_Curve& C, const double U, gp_Pnt& P)
{
  C.D0(U, P);
}

inline void HLRBRep_BCurveTool::D1(const ::model::adapter::BRepAdaptor_Curve& C, const double U, gp_Pnt& P, gp_Vec& T)
{
  C.D1(U, P, T);
}

inline void HLRBRep_BCurveTool::D2(const ::model::adapter::BRepAdaptor_Curve& C,
                                   const double             U,
                                   gp_Pnt&                  P,
                                   gp_Vec&                  T,
                                   gp_Vec&                  N)
{
  C.D2(U, P, T, N);
}

inline void HLRBRep_BCurveTool::D3(const ::model::adapter::BRepAdaptor_Curve& C,
                                   const double             U,
                                   gp_Pnt&                  P,
                                   gp_Vec&                  V1,
                                   gp_Vec&                  V2,
                                   gp_Vec&                  V3)
{
  C.D3(U, P, V1, V2, V3);
}

inline gp_Vec HLRBRep_BCurveTool::DN(const ::model::adapter::BRepAdaptor_Curve& C, const double U, const int N)
{
  return (C.DN(U, N));
}

inline double HLRBRep_BCurveTool::Resolution(const ::model::adapter::BRepAdaptor_Curve& C, const double R3d)
{
  return (C.Resolution(R3d));
}

inline GeomAbs_CurveType HLRBRep_BCurveTool::GetType(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.GetType());
}

inline gp_Lin HLRBRep_BCurveTool::Line(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.Line());
}

inline gp_Circ HLRBRep_BCurveTool::Circle(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.Circle());
}

inline gp_Elips HLRBRep_BCurveTool::Ellipse(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.Ellipse());
}

inline gp_Parab HLRBRep_BCurveTool::Parabola(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.Parabola());
}

inline gp_Hypr HLRBRep_BCurveTool::Hyperbola(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.Hyperbola());
}

inline int HLRBRep_BCurveTool::Degree(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.Degree());
}

inline bool HLRBRep_BCurveTool::IsRational(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.IsRational());
}

inline int HLRBRep_BCurveTool::NbPoles(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.NbPoles());
}

inline int HLRBRep_BCurveTool::NbKnots(const ::model::adapter::BRepAdaptor_Curve& C)
{
  return (C.NbKnots());
}
