#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRBRep_TypeDef.hpp>
#include <Standard_Real.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Boolean.hpp>
#include <GeomAbs_CurveType.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Parab2d.hpp>
class gp_Pnt2d;
class gp_Vec2d;
class Geom2d_BezierCurve;
class Geom2d_BSplineCurve;

class HLRBRep_CurveTool
{
public:
  DEFINE_STANDARD_ALLOC

  static double FirstParameter(const HLRBRep_CurvePtr C);

  static double LastParameter(const HLRBRep_CurvePtr C);

  static GeomAbs_Shape Continuity(const HLRBRep_CurvePtr C);

  static int NbIntervals(const HLRBRep_CurvePtr C);

  static void Intervals(const HLRBRep_CurvePtr C, NCollection_Array1<double>& T);

  static void GetInterval(const HLRBRep_CurvePtr            C,
                          const int                         Index,
                          const NCollection_Array1<double>& Tab,
                          double&                           U1,
                          double&                           U2);

  static bool IsClosed(const HLRBRep_CurvePtr C);

  static bool IsPeriodic(const HLRBRep_CurvePtr C);

  static double Period(const HLRBRep_CurvePtr C);

  static gp_Pnt2d Value(const HLRBRep_CurvePtr C, const double U);

  static void D0(const HLRBRep_CurvePtr C, const double U, gp_Pnt2d& P);

  static void D1(const HLRBRep_CurvePtr C, const double U, gp_Pnt2d& P, gp_Vec2d& V);

  static void D2(const HLRBRep_CurvePtr C, const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2);

  static void D3(const HLRBRep_CurvePtr C,
                 const double           U,
                 gp_Pnt2d&              P,
                 gp_Vec2d&              V1,
                 gp_Vec2d&              V2,
                 gp_Vec2d&              V3);

  static gp_Vec2d DN(const HLRBRep_CurvePtr C, const double U, const int N);

  static double Resolution(const HLRBRep_CurvePtr C, const double R3d);

  static GeomAbs_CurveType GetType(const HLRBRep_CurvePtr C);

  static GeomAbs_CurveType TheType(const HLRBRep_CurvePtr C);

  static gp_Lin2d Line(const HLRBRep_CurvePtr C);

  static gp_Circ2d Circle(const HLRBRep_CurvePtr C);

  static gp_Elips2d Ellipse(const HLRBRep_CurvePtr C);

  static gp_Hypr2d Hyperbola(const HLRBRep_CurvePtr C);

  static gp_Parab2d Parabola(const HLRBRep_CurvePtr C);

  static occ::handle<Geom2d_BezierCurve> Bezier(const HLRBRep_CurvePtr C);

  static occ::handle<Geom2d_BSplineCurve> BSpline(const HLRBRep_CurvePtr C);

  static double EpsX(const HLRBRep_CurvePtr C);

  Standard_EXPORT static int NbSamples(const HLRBRep_CurvePtr C, const double U0, const double U1);

  Standard_EXPORT static int NbSamples(const HLRBRep_CurvePtr C);

  static int Degree(const HLRBRep_CurvePtr C);
};

#include <HLRBRep_Curve.hpp>
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

#define IS_C2_COMPOSITE 0

inline double HLRBRep_CurveTool::FirstParameter(const HLRBRep_CurvePtr C)
{
  return (((HLRBRep_Curve*)C)->FirstParameter());
}

inline double HLRBRep_CurveTool::LastParameter(const HLRBRep_CurvePtr C)
{
  return (((HLRBRep_Curve*)C)->LastParameter());
}

inline GeomAbs_Shape HLRBRep_CurveTool::Continuity(const HLRBRep_CurvePtr C)
{
  return (((HLRBRep_Curve*)C)->Continuity());
}

inline int HLRBRep_CurveTool::NbIntervals(const HLRBRep_CurvePtr C)
{
#if IS_C2_COMPOSITE
  return (((HLRBRep_Curve*)C)->NbIntervals(GeomAbs_C2));
#else
  return (((HLRBRep_Curve*)C)->NbIntervals(GeomAbs_C1));
#endif
}

inline void HLRBRep_CurveTool::Intervals(const HLRBRep_CurvePtr C, NCollection_Array1<double>& Tab)
{
#if IS_C2_COMPOSITE
  ((HLRBRep_Curve*)C)->Intervals(Tab, GeomAbs_C2);
#else
  ((HLRBRep_Curve*)C)->Intervals(Tab, GeomAbs_C1);
#endif
}

inline void HLRBRep_CurveTool::GetInterval(const HLRBRep_CurvePtr,
                                           const int                         i,
                                           const NCollection_Array1<double>& Tab,
                                           double&                           a,
                                           double&                           b)
{
  a = Tab.Value(i);
  b = Tab.Value(i + 1);
}

inline bool HLRBRep_CurveTool::IsClosed(const HLRBRep_CurvePtr C)
{
  return (((HLRBRep_Curve*)C)->IsClosed());
}

inline bool HLRBRep_CurveTool::IsPeriodic(const HLRBRep_CurvePtr C)
{
  return (((HLRBRep_Curve*)C)->IsPeriodic());
}

inline double HLRBRep_CurveTool::Period(const HLRBRep_CurvePtr C)
{
  return (((HLRBRep_Curve*)C)->Period());
}

inline gp_Pnt2d HLRBRep_CurveTool::Value(const HLRBRep_CurvePtr C, const double U)
{
  return (((HLRBRep_Curve*)C)->Value(U));
}

inline void HLRBRep_CurveTool::D0(const HLRBRep_CurvePtr C, const double U, gp_Pnt2d& P)
{
  ((HLRBRep_Curve*)C)->D0(U, P);
}

inline void HLRBRep_CurveTool::D1(const HLRBRep_CurvePtr C,
                                  const double           U,
                                  gp_Pnt2d&              P,
                                  gp_Vec2d&              T)
{
  ((HLRBRep_Curve*)C)->D1(U, P, T);
}

inline void HLRBRep_CurveTool::D2(const HLRBRep_CurvePtr C,
                                  const double           U,
                                  gp_Pnt2d&              P,
                                  gp_Vec2d&              T,
                                  gp_Vec2d&              N)
{
  ((HLRBRep_Curve*)C)->D2(U, P, T, N);
}

inline void HLRBRep_CurveTool::D3(const HLRBRep_CurvePtr C,
                                  const double           U,
                                  gp_Pnt2d&              P,
                                  gp_Vec2d&              V1,
                                  gp_Vec2d&              V2,
                                  gp_Vec2d&              V3)
{
  ((HLRBRep_Curve*)C)->D3(U, P, V1, V2, V3);
}

inline gp_Vec2d HLRBRep_CurveTool::DN(const HLRBRep_CurvePtr C, const double U, const int N)
{
  return (((HLRBRep_Curve*)C)->DN(U, N));
}

inline double HLRBRep_CurveTool::Resolution(const HLRBRep_CurvePtr C, const double R3d)
{
  return (((HLRBRep_Curve*)C)->Resolution(R3d));
}

inline GeomAbs_CurveType HLRBRep_CurveTool::GetType(const HLRBRep_CurvePtr C)
{
  return (((HLRBRep_Curve*)C)->GetType());
}

inline GeomAbs_CurveType HLRBRep_CurveTool::TheType(const HLRBRep_CurvePtr C)
{
  return (((HLRBRep_Curve*)C)->GetType());
}

inline gp_Lin2d HLRBRep_CurveTool::Line(const HLRBRep_CurvePtr C)
{
  return (((HLRBRep_Curve*)C)->Line());
}

inline gp_Circ2d HLRBRep_CurveTool::Circle(const HLRBRep_CurvePtr C)
{
  return (((HLRBRep_Curve*)C)->Circle());
}

inline gp_Elips2d HLRBRep_CurveTool::Ellipse(const HLRBRep_CurvePtr C)
{
  return (((HLRBRep_Curve*)C)->Ellipse());
}

inline gp_Parab2d HLRBRep_CurveTool::Parabola(const HLRBRep_CurvePtr C)
{
  return (((HLRBRep_Curve*)C)->Parabola());
}

inline gp_Hypr2d HLRBRep_CurveTool::Hyperbola(const HLRBRep_CurvePtr C)
{
  return (((HLRBRep_Curve*)C)->Hyperbola());
}

inline occ::handle<Geom2d_BezierCurve> HLRBRep_CurveTool::Bezier(const HLRBRep_CurvePtr)
{
#ifdef OCCT_DEBUG
  std::cout << "  HLRBRep_CurveTool::Bezier : Not Implemented " << std::endl;
#endif

  return (nullptr);
}

inline occ::handle<Geom2d_BSplineCurve> HLRBRep_CurveTool::BSpline(const HLRBRep_CurvePtr)
{
#ifdef OCCT_DEBUG
  std::cout << "  HLRBRep_CurveTool::BSpline : Not Implemented " << std::endl;
#endif

  return (nullptr);
}

inline double HLRBRep_CurveTool::EpsX(const HLRBRep_CurvePtr)
{
  return (1e-10);
}

inline int HLRBRep_CurveTool::Degree(const HLRBRep_CurvePtr C)
{
  return (((HLRBRep_Curve*)C)->Degree());
}
