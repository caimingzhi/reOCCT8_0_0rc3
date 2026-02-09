#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Boolean.hpp>
#include <GeomAbs_CurveType.hpp>
#include <gp_Lin.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Parab.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_HArray1.hpp>
class Standard_OutOfRange;
class Standard_NoSuchObject;
class Standard_DomainError;
class gp_Pnt;
class gp_Vec;
class Geom_BezierCurve;
class Geom_BSplineCurve;

class HLRBRep_LineTool
{
public:
  DEFINE_STANDARD_ALLOC

  static double FirstParameter(const gp_Lin& C);

  static double LastParameter(const gp_Lin& C);

  static GeomAbs_Shape Continuity(const gp_Lin& C);

  static int NbIntervals(const gp_Lin& C, const GeomAbs_Shape S);

  static void Intervals(const gp_Lin& C, NCollection_Array1<double>& T, const GeomAbs_Shape Sh);

  static double IntervalFirst(const gp_Lin& C);

  static double IntervalLast(const gp_Lin& C);

  static GeomAbs_Shape IntervalContinuity(const gp_Lin& C);

  static bool IsClosed(const gp_Lin& C);

  static bool IsPeriodic(const gp_Lin& C);

  static double Period(const gp_Lin& C);

  static gp_Pnt Value(const gp_Lin& C, const double U);

  static void D0(const gp_Lin& C, const double U, gp_Pnt& P);

  static void D1(const gp_Lin& C, const double U, gp_Pnt& P, gp_Vec& V);

  static void D2(const gp_Lin& C, const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2);

  static void D3(const gp_Lin& C, const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3);

  static gp_Vec DN(const gp_Lin& C, const double U, const int N);

  static double Resolution(const gp_Lin& C, const double R3d);

  static GeomAbs_CurveType GetType(const gp_Lin& C);

  static gp_Lin Line(const gp_Lin& C);

  static gp_Circ Circle(const gp_Lin& C);

  static gp_Elips Ellipse(const gp_Lin& C);

  static gp_Hypr Hyperbola(const gp_Lin& C);

  static gp_Parab Parabola(const gp_Lin& C);

  static occ::handle<Geom_BezierCurve> Bezier(const gp_Lin& C);

  static occ::handle<Geom_BSplineCurve> BSpline(const gp_Lin& C);

  static int Degree(const gp_Lin& C);

  static int NbPoles(const gp_Lin& C);

  static void Poles(const gp_Lin& C, NCollection_Array1<gp_Pnt>& TP);

  static bool IsRational(const gp_Lin& C);

  static void PolesAndWeights(const gp_Lin&               C,
                              NCollection_Array1<gp_Pnt>& TP,
                              NCollection_Array1<double>& TW);

  static int NbKnots(const gp_Lin& C);

  static void KnotsAndMultiplicities(const gp_Lin&               C,
                                     NCollection_Array1<double>& TK,
                                     NCollection_Array1<int>&    TM);

  static int NbSamples(const gp_Lin& C, const double U0, const double U1);

  static void SamplePars(const gp_Lin&                             C,
                         const double                              U0,
                         const double                              U1,
                         const double                              Defl,
                         const int                                 NbMin,
                         occ::handle<NCollection_HArray1<double>>& Pars);
};

#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Lin.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Parab.hpp>
#include <ElCLib.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

inline double HLRBRep_LineTool::FirstParameter(const gp_Lin&)
{
  return RealFirst();
}

inline double HLRBRep_LineTool::LastParameter(const gp_Lin&)
{
  return RealLast();
}

inline GeomAbs_Shape HLRBRep_LineTool::Continuity(const gp_Lin&)
{
  return GeomAbs_CN;
}

inline int HLRBRep_LineTool::NbIntervals(const gp_Lin&, const GeomAbs_Shape)
{
  return 1;
}

inline void HLRBRep_LineTool::Intervals(const gp_Lin&,
                                        NCollection_Array1<double>&,
                                        const GeomAbs_Shape)
{
}

inline double HLRBRep_LineTool::IntervalFirst(const gp_Lin&)
{
  return RealFirst();
}

inline double HLRBRep_LineTool::IntervalLast(const gp_Lin&)
{
  return RealLast();
}

inline GeomAbs_Shape HLRBRep_LineTool::IntervalContinuity(const gp_Lin&)
{
  return GeomAbs_CN;
}

inline bool HLRBRep_LineTool::IsClosed(const gp_Lin&)
{
  return false;
}

inline bool HLRBRep_LineTool::IsPeriodic(const gp_Lin&)
{
  return false;
}

inline double HLRBRep_LineTool::Period(const gp_Lin&)
{
  return 0.;
}

inline gp_Pnt HLRBRep_LineTool::Value(const gp_Lin& C, const double U)
{
  return ElCLib::Value(U, C);
}

inline void HLRBRep_LineTool::D0(const gp_Lin& C, const double U, gp_Pnt& P)
{
  P = ElCLib::Value(U, C);
}

inline void HLRBRep_LineTool::D1(const gp_Lin& C, const double U, gp_Pnt& P, gp_Vec& V)
{
  ElCLib::D1(U, C, P, V);
}

inline void HLRBRep_LineTool::D2(const gp_Lin& C, const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2)
{
  ElCLib::D1(U, C, P, V1);
  V2 = gp_Vec(0, 0, 0);
}

inline void HLRBRep_LineTool::D3(const gp_Lin& C,
                                 const double  U,
                                 gp_Pnt&       P,
                                 gp_Vec&       V1,
                                 gp_Vec&       V2,
                                 gp_Vec&       V3)
{
  ElCLib::D1(U, C, P, V1);
  V2 = V3 = gp_Vec(0, 0, 0);
}

inline gp_Vec HLRBRep_LineTool::DN(const gp_Lin& C, const double U, const int N)
{
  return ElCLib::DN(U, C, N);
}

inline double HLRBRep_LineTool::Resolution(const gp_Lin&, const double R3D)
{
  return R3D;
}

inline GeomAbs_CurveType HLRBRep_LineTool::GetType(const gp_Lin&)
{
  return GeomAbs_Line;
}

inline gp_Lin HLRBRep_LineTool::Line(const gp_Lin& C)
{
  return C;
}

inline gp_Circ HLRBRep_LineTool::Circle(const gp_Lin&)
{
  return gp_Circ();
}

inline gp_Elips HLRBRep_LineTool::Ellipse(const gp_Lin&)
{
  return gp_Elips();
}

inline gp_Hypr HLRBRep_LineTool::Hyperbola(const gp_Lin&)
{
  return gp_Hypr();
}

inline gp_Parab HLRBRep_LineTool::Parabola(const gp_Lin&)
{
  return gp_Parab();
}

inline occ::handle<Geom_BezierCurve> HLRBRep_LineTool::Bezier(const gp_Lin&)
{
  occ::handle<Geom_BezierCurve> NullCurve;
  return NullCurve;
}

inline occ::handle<Geom_BSplineCurve> HLRBRep_LineTool::BSpline(const gp_Lin&)
{
  occ::handle<Geom_BSplineCurve> NullCurve;
  return NullCurve;
}

inline int HLRBRep_LineTool::Degree(const gp_Lin&)
{
  return 1;
}

inline int HLRBRep_LineTool::NbPoles(const gp_Lin&)
{
  return 0;
}

inline void HLRBRep_LineTool::Poles(const gp_Lin&, NCollection_Array1<gp_Pnt>&) {}

inline bool HLRBRep_LineTool::IsRational(const gp_Lin&)
{
  return false;
}

inline void HLRBRep_LineTool::PolesAndWeights(const gp_Lin&,
                                              NCollection_Array1<gp_Pnt>&,
                                              NCollection_Array1<double>&)
{
}

inline int HLRBRep_LineTool::NbKnots(const gp_Lin&)
{
  return 0;
}

inline void HLRBRep_LineTool::KnotsAndMultiplicities(const gp_Lin&,
                                                     NCollection_Array1<double>&,
                                                     NCollection_Array1<int>&)
{
}

inline int HLRBRep_LineTool::NbSamples(const gp_Lin&, const double, const double)
{
  return 3;
}

inline void HLRBRep_LineTool::SamplePars(const gp_Lin&,
                                         const double U0,
                                         const double U1,
                                         const double,
                                         const int,
                                         occ::handle<NCollection_HArray1<double>>& Pars)
{

  Pars = new NCollection_HArray1<double>(1, 3);
  Pars->SetValue(1, U0);
  Pars->SetValue(2, (U0 + U1) * 0.5);
  Pars->SetValue(3, U1);
}
