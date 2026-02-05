#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GeomAbs_CurveType.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Hypr2d.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <NCollection_Array1.hpp>
class Adaptor2d_Curve2d;
class gp_Pnt2d;
class gp_Vec2d;

//! This class provides a Geom2dCurveTool as < Geom2dCurveTool from IntCurve >
//! from a Tool as < Geom2dCurveTool from Adaptor3d > .
class Geom2dInt_Geom2dCurveTool
{
public:
  DEFINE_STANDARD_ALLOC

  static GeomAbs_CurveType GetType(const Adaptor2d_Curve2d& C);

  static bool IsComposite(const Adaptor2d_Curve2d& C);

  //! Returns the Lin2d from gp corresponding to the curve C.
  //! This method is called only when TheType returns
  //! GeomAbs_Line.
  static gp_Lin2d Line(const Adaptor2d_Curve2d& C);

  //! Returns the Circ2d from gp corresponding to the curve C.
  //! This method is called only when TheType returns
  //! GeomAbs_Circle.
  static gp_Circ2d Circle(const Adaptor2d_Curve2d& C);

  //! Returns the Elips2d from gp corresponding to the curve C.
  //! This method is called only when TheType returns
  //! GeomAbs_Ellipse.
  static gp_Elips2d Ellipse(const Adaptor2d_Curve2d& C);

  //! Returns the Parab2d from gp corresponding to the curve C.
  //! This method is called only when TheType returns
  //! GeomAbs_Parabola.
  static gp_Parab2d Parabola(const Adaptor2d_Curve2d& C);

  //! Returns the Hypr2d from gp corresponding to the curve C.
  //! This method is called only when TheType returns
  //! GeomAbs_Hyperbola.
  static gp_Hypr2d Hyperbola(const Adaptor2d_Curve2d& C);

  static double EpsX(const Adaptor2d_Curve2d& C);

  static double EpsX(const Adaptor2d_Curve2d& C, const double Eps_XYZ);

  Standard_EXPORT static int NbSamples(const Adaptor2d_Curve2d& C);

  Standard_EXPORT static int NbSamples(const Adaptor2d_Curve2d& C,
                                       const double             U0,
                                       const double             U1);

  static double FirstParameter(const Adaptor2d_Curve2d& C);

  static double LastParameter(const Adaptor2d_Curve2d& C);

  static gp_Pnt2d Value(const Adaptor2d_Curve2d& C, const double X);

  static void D0(const Adaptor2d_Curve2d& C, const double U, gp_Pnt2d& P);

  static void D1(const Adaptor2d_Curve2d& C, const double U, gp_Pnt2d& P, gp_Vec2d& T);

  static void D2(const Adaptor2d_Curve2d& C, const double U, gp_Pnt2d& P, gp_Vec2d& T, gp_Vec2d& N);

  static void D3(const Adaptor2d_Curve2d& C,
                 const double             U,
                 gp_Pnt2d&                P,
                 gp_Vec2d&                T,
                 gp_Vec2d&                N,
                 gp_Vec2d&                V);

  static gp_Vec2d DN(const Adaptor2d_Curve2d& C, const double U, const int N);

  //! output the number of interval of continuity C2 of
  //! the curve
  static int NbIntervals(const Adaptor2d_Curve2d& C);

  //! compute Tab.
  static void Intervals(const Adaptor2d_Curve2d& C, NCollection_Array1<double>& Tab);

  //! output the bounds of interval of index <Index>
  //! used if Type == Composite.
  static void GetInterval(const Adaptor2d_Curve2d&          C,
                          const int                         Index,
                          const NCollection_Array1<double>& Tab,
                          double&                           U1,
                          double&                           U2);

  static int Degree(const Adaptor2d_Curve2d& C);
};

#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_Shape.hpp>

#include <gp_Lin2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Hypr2d.hpp>

#include <NCollection_Array1.hpp>
#include <Adaptor2d_Curve2d.hpp>

#define IS_C2_COMPOSITE 0

//============================================================
inline GeomAbs_CurveType Geom2dInt_Geom2dCurveTool::GetType(const Adaptor2d_Curve2d& C)
{
  return (C.GetType());
}

//============================================================
inline gp_Lin2d Geom2dInt_Geom2dCurveTool::Line(const Adaptor2d_Curve2d& C)
{
  return (C.Line());
}

//============================================================
inline gp_Circ2d Geom2dInt_Geom2dCurveTool::Circle(const Adaptor2d_Curve2d& C)
{
  return (C.Circle());
}

//============================================================
inline gp_Elips2d Geom2dInt_Geom2dCurveTool::Ellipse(const Adaptor2d_Curve2d& C)
{
  return (C.Ellipse());
}

//============================================================
inline gp_Parab2d Geom2dInt_Geom2dCurveTool::Parabola(const Adaptor2d_Curve2d& C)
{
  return (C.Parabola());
}

//============================================================
inline gp_Hypr2d Geom2dInt_Geom2dCurveTool::Hyperbola(const Adaptor2d_Curve2d& C)
{
  return (C.Hyperbola());
}

//============================================================
inline gp_Pnt2d Geom2dInt_Geom2dCurveTool::Value(const Adaptor2d_Curve2d& C, const double U)
{
  return (C.Value(U));
}

//============================================================
inline void Geom2dInt_Geom2dCurveTool::D0(const Adaptor2d_Curve2d& C, const double U, gp_Pnt2d& P)
{
  C.D0(U, P);
}

//============================================================
inline void Geom2dInt_Geom2dCurveTool::D1(const Adaptor2d_Curve2d& C,
                                          const double             U,
                                          gp_Pnt2d&                P,
                                          gp_Vec2d&                T)
{
  C.D1(U, P, T);
}

//============================================================
inline void Geom2dInt_Geom2dCurveTool::D2(const Adaptor2d_Curve2d& C,
                                          const double             U,
                                          gp_Pnt2d&                P,
                                          gp_Vec2d&                T,
                                          gp_Vec2d&                N)
{

  C.D2(U, P, T, N);
}

//============================================================
inline void Geom2dInt_Geom2dCurveTool::D3(const Adaptor2d_Curve2d& C,
                                          const double             U,
                                          gp_Pnt2d&                P,
                                          gp_Vec2d&                T,
                                          gp_Vec2d&                N,
                                          gp_Vec2d&                V)
{

  C.D3(U, P, T, N, V);
}

//============================================================
inline gp_Vec2d Geom2dInt_Geom2dCurveTool::DN(const Adaptor2d_Curve2d& C,
                                              const double             U,
                                              const int                N)
{
  return C.DN(U, N);
}

//============================================================
inline double Geom2dInt_Geom2dCurveTool::FirstParameter(const Adaptor2d_Curve2d& C)
{
  return (C.FirstParameter());
}

//============================================================
inline double Geom2dInt_Geom2dCurveTool::LastParameter(const Adaptor2d_Curve2d& C)
{
  return (C.LastParameter());
}

//============================================================
//== tolerance used by mathemetical algorithms
//==
inline double Geom2dInt_Geom2dCurveTool::EpsX(const Adaptor2d_Curve2d&)
{
  return (1.0e-10);
}

//------------------------------------------------------------
inline double Geom2dInt_Geom2dCurveTool::EpsX(const Adaptor2d_Curve2d& C, const double Eps_XYZ)
{
  return (C.Resolution(Eps_XYZ));
}

//============================================================
inline void Geom2dInt_Geom2dCurveTool::Intervals(const Adaptor2d_Curve2d&    C,
                                                 NCollection_Array1<double>& Tab)
{
#if IS_C2_COMPOSITE
  C.Intervals(Tab, GeomAbs_C2);
#else
  C.Intervals(Tab, GeomAbs_C1);
#endif
}

//============================================================
// inline void Geom2dInt_Geom2dCurveTool::GetInterval(const Adaptor2d_Curve2d& C,
inline void Geom2dInt_Geom2dCurveTool::GetInterval(const Adaptor2d_Curve2d&,
                                                   const int                         i,
                                                   const NCollection_Array1<double>& Tab,
                                                   double&                           a,
                                                   double&                           b)
{
  a = Tab.Value(i);
  b = Tab.Value(i + 1);
}

//============================================================
inline int Geom2dInt_Geom2dCurveTool::NbIntervals(const Adaptor2d_Curve2d& C)
{
  int N = 1;
#if IS_C2_COMPOSITE
  N = C.NbIntervals(GeomAbs_C2);
#else
  N = C.NbIntervals(GeomAbs_C1);
#endif
  return (N);
}

//============================================================

inline int Geom2dInt_Geom2dCurveTool::Degree(const Adaptor2d_Curve2d& C)
{
  return C.Degree();
}
