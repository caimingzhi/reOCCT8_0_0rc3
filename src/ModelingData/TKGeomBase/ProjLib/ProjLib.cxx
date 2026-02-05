#include <ProjLib.hpp>

#include <Adaptor3d_Surface.hpp>
#include <ElSLib.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Ellipse.hpp>
#include <Geom2d_Parabola.hpp>
#include <Geom2d_Hyperbola.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <gp_Circ.hpp>
#include <gp_Cone.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Lin.hpp>
#include <gp_Parab.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>
#include <ProjLib_Cone.hpp>
#include <ProjLib_Cylinder.hpp>
#include <ProjLib_Plane.hpp>
#include <ProjLib_Sphere.hpp>
#include <ProjLib_Torus.hpp>
#include <ProjLib_ProjectedCurve.hpp>
#include <Standard_NotImplemented.hpp>

//=================================================================================================

gp_Pnt2d ProjLib::Project(const gp_Pln& Pl, const gp_Pnt& P)
{
  double U, V;
  ElSLib::Parameters(Pl, P, U, V);
  return gp_Pnt2d(U, V);
}

//=================================================================================================

gp_Lin2d ProjLib::Project(const gp_Pln& Pl, const gp_Lin& L)
{
  ProjLib_Plane Proj(Pl, L);
  return Proj.Line();
}

//=================================================================================================

gp_Circ2d ProjLib::Project(const gp_Pln& Pl, const gp_Circ& C)
{
  ProjLib_Plane Proj(Pl, C);
  return Proj.Circle();
}

//=================================================================================================

gp_Elips2d ProjLib::Project(const gp_Pln& Pl, const gp_Elips& E)
{
  ProjLib_Plane Proj(Pl, E);
  return Proj.Ellipse();
}

//=================================================================================================

gp_Parab2d ProjLib::Project(const gp_Pln& Pl, const gp_Parab& P)
{
  ProjLib_Plane Proj(Pl, P);
  return Proj.Parabola();
}

//=================================================================================================

gp_Hypr2d ProjLib::Project(const gp_Pln& Pl, const gp_Hypr& H)
{
  ProjLib_Plane Proj(Pl, H);
  return Proj.Hyperbola();
}

//=================================================================================================

gp_Pnt2d ProjLib::Project(const gp_Cylinder& Cy, const gp_Pnt& P)
{
  double U, V;
  ElSLib::Parameters(Cy, P, U, V);
  return gp_Pnt2d(U, V);
}

//=================================================================================================

gp_Lin2d ProjLib::Project(const gp_Cylinder& Cy, const gp_Lin& L)
{
  ProjLib_Cylinder Proj(Cy, L);
  return Proj.Line();
}

//=================================================================================================

gp_Lin2d ProjLib::Project(const gp_Cylinder& Cy, const gp_Circ& Ci)
{
  ProjLib_Cylinder Proj(Cy, Ci);
  return Proj.Line();
}

//=================================================================================================

gp_Pnt2d ProjLib::Project(const gp_Cone& Co, const gp_Pnt& P)
{
  double U, V;
  ElSLib::Parameters(Co, P, U, V);
  return gp_Pnt2d(U, V);
}

//=================================================================================================

gp_Lin2d ProjLib::Project(const gp_Cone& Co, const gp_Lin& L)
{
  ProjLib_Cone Proj(Co, L);
  return Proj.Line();
}

//=================================================================================================

gp_Lin2d ProjLib::Project(const gp_Cone& Co, const gp_Circ& Ci)
{
  ProjLib_Cone Proj(Co, Ci);
  return Proj.Line();
}

//=================================================================================================

gp_Pnt2d ProjLib::Project(const gp_Sphere& Sp, const gp_Pnt& P)
{
  double U, V;
  ElSLib::Parameters(Sp, P, U, V);
  return gp_Pnt2d(U, V);
}

//=================================================================================================

gp_Lin2d ProjLib::Project(const gp_Sphere& Sp, const gp_Circ& Ci)
{
  ProjLib_Sphere Proj(Sp, Ci);
  return Proj.Line();
}

//=================================================================================================

gp_Pnt2d ProjLib::Project(const gp_Torus& To, const gp_Pnt& P)
{
  double U, V;
  ElSLib::Parameters(To, P, U, V);
  return gp_Pnt2d(U, V);
}

//=================================================================================================

gp_Lin2d ProjLib::Project(const gp_Torus& To, const gp_Circ& Ci)
{
  ProjLib_Torus Proj(To, Ci);
  return Proj.Line();
}

//=================================================================================================

void ProjLib::MakePCurveOfType(const ProjLib_ProjectedCurve& PC, occ::handle<Geom2d_Curve>& C2D)
{

  switch (PC.GetType())
  {

    case GeomAbs_Line:
      C2D = new Geom2d_Line(PC.Line());
      break;
    case GeomAbs_Circle:
      C2D = new Geom2d_Circle(PC.Circle());
      break;
    case GeomAbs_Ellipse:
      C2D = new Geom2d_Ellipse(PC.Ellipse());
      break;
    case GeomAbs_Parabola:
      C2D = new Geom2d_Parabola(PC.Parabola());
      break;
    case GeomAbs_Hyperbola:
      C2D = new Geom2d_Hyperbola(PC.Hyperbola());
      break;
    case GeomAbs_BSplineCurve:
      C2D = PC.BSpline();
      break;
    case GeomAbs_BezierCurve:
    case GeomAbs_OtherCurve:
    default:
      throw Standard_NotImplemented("ProjLib::MakePCurveOfType");
      break;
  }
}

//=================================================================================================

bool ProjLib::IsAnaSurf(const occ::handle<Adaptor3d_Surface>& theAS)
{
  switch (theAS->GetType())
  {

    case GeomAbs_Plane:
    case GeomAbs_Cylinder:
    case GeomAbs_Cone:
    case GeomAbs_Sphere:
    case GeomAbs_Torus:
      return true;
      break;
    default:
      return false;
      break;
  }
}
