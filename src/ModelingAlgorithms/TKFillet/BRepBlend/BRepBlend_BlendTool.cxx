#include <BRepBlend_BlendTool.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Surface.hpp>
#include <BRep_Tool.hpp>
#include <BRepBlend_HCurve2dTool.hpp>
#include <Extrema_EPCOfExtPC2d.hpp>
#include <Extrema_POnCurv2d.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dInt_GInter.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <IntRes2d_IntersectionPoint.hpp>

bool BRepBlend_BlendTool::Project(const gp_Pnt2d& P,
                                  const occ::handle<Adaptor3d_Surface>&,
                                  const occ::handle<Adaptor2d_Curve2d>& C,
                                  double&                               Paramproj,
                                  double&                               Dist)
{
  Paramproj = BRepBlend_HCurve2dTool::FirstParameter(C);
  gp_Pnt2d P2d;
  BRepBlend_HCurve2dTool::D0(C, Paramproj, P2d);
  Dist = P2d.Distance(P);

  const double t = BRepBlend_HCurve2dTool::LastParameter(C);
  BRepBlend_HCurve2dTool::D0(C, t, P2d);
  if (P2d.Distance(P) < Dist)
  {
    Paramproj = t;
    Dist      = P2d.Distance(P);
  }

  const double         epsX = 1.e-8;
  const int            Nbu  = 20;
  const double         Tol  = 1.e-5;
  Extrema_EPCOfExtPC2d extrema(P, *C, Nbu, epsX, Tol);
  if (!extrema.IsDone())
    return true;

  const int Nbext  = extrema.NbExt();
  double    aDist2 = Dist * Dist;
  for (int i = 1; i <= Nbext; i++)
  {
    if (extrema.SquareDistance(i) < aDist2)
    {
      aDist2    = extrema.SquareDistance(i);
      Paramproj = extrema.Point(i).Parameter();
    }
  }
  Dist = sqrt(aDist2);

  return true;
}

bool BRepBlend_BlendTool::Inters(const gp_Pnt2d& P1,
                                 const gp_Pnt2d& P2,
                                 const occ::handle<Adaptor3d_Surface>&,
                                 const occ::handle<Adaptor2d_Curve2d>& C,
                                 double&                               Param,
                                 double&                               Dist)
{
  const double   Tol = 1.e-8;
  const gp_Vec2d v(P1, P2);
  const double   mag = v.Magnitude();
  if (mag < Tol)
    return false;

  gp_Dir2d                 d(v);
  occ::handle<Geom2d_Line> bid = new Geom2d_Line(P1, d);
  Geom2dAdaptor_Curve      seg(bid, -0.01 * mag, 1.01 * mag);

  Geom2dInt_GInter inter(seg, *C, Tol, Tol);
  if (!inter.IsDone())
    return false;

  const int Nbint = inter.NbPoints();
  if (Nbint == 0)
    return false;

  IntRes2d_IntersectionPoint ip = inter.Point(1);
  Param                         = ip.ParamOnSecond();
  Dist                          = P1.Distance(ip.Value());
  return true;
}

int BRepBlend_BlendTool::NbSamplesV(const occ::handle<Adaptor3d_Surface>&,
                                    const double,
                                    const double)
{
  return 10;
}

int BRepBlend_BlendTool::NbSamplesU(const occ::handle<Adaptor3d_Surface>&,
                                    const double,
                                    const double)
{
  return 10;
}

void BRepBlend_BlendTool::Bounds(const occ::handle<Adaptor2d_Curve2d>& A,
                                 double&                               Ufirst,
                                 double&                               Ulast)
{
  Ufirst = BRepBlend_HCurve2dTool::FirstParameter(A);
  Ulast  = BRepBlend_HCurve2dTool::LastParameter(A);
}
