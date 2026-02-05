#include <BRep_Tool.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Standard_ProgramError.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRep_GeomTool.hpp>
#include <TopOpeBRep_LineInter.hpp>
#include <TopOpeBRep_TypeLineCurve.hpp>
#include <TopOpeBRep_WPointInter.hpp>
#include <TopOpeBRep_WPointInterIterator.hpp>
#include <TopOpeBRepDS_Curve.hpp>
#include <TopOpeBRepTool_CurveTool.hpp>

//=================================================================================================

void TopOpeBRep_GeomTool::MakeCurves(const double                min,
                                     const double                max,
                                     const TopOpeBRep_LineInter& L,
                                     const TopoDS_Shape& /*S1*/,
                                     const TopoDS_Shape& /*S2*/,
                                     TopOpeBRepDS_Curve&        C,
                                     occ::handle<Geom2d_Curve>& PC1,
                                     occ::handle<Geom2d_Curve>& PC2)
{
  bool                     IsWalk = false;
  occ::handle<Geom_Curve>  C3D;
  TopOpeBRep_TypeLineCurve typeline = L.TypeLineCurve();

  switch (typeline)
  {

    case TopOpeBRep_WALKING:
    {
      // make BSplines of degree 1
      C3D = MakeBSpline1fromWALKING3d(L);
      PC1 = MakeBSpline1fromWALKING2d(L, 1);
      PC2 = MakeBSpline1fromWALKING2d(L, 2);
      if (!PC1.IsNull())
        C.Curve1(PC1);
      if (!PC2.IsNull())
        C.Curve2(PC2);
      IsWalk = true;
      break;
    }
    case TopOpeBRep_LINE:
    case TopOpeBRep_CIRCLE:
    case TopOpeBRep_ELLIPSE:
    {
      C3D = L.Curve();
      break;
    }
    case TopOpeBRep_PARABOLA:
    case TopOpeBRep_HYPERBOLA:
    {
      C3D = L.Curve(min, max); // Trimmed
      break;
    }
    case TopOpeBRep_ANALYTIC:
    case TopOpeBRep_RESTRICTION:
    case TopOpeBRep_OTHERTYPE:
    default:
      throw Standard_ProgramError("TopOpeBRep_GeomTool::MakePrivateCurves");
      break;
  }

  double tol = C.Tolerance();
  C.DefineCurve(C3D, tol, IsWalk);
  C.SetRange(min, max);
}

//=================================================================================================

void TopOpeBRep_GeomTool::MakeCurve(const double                min,
                                    const double                max,
                                    const TopOpeBRep_LineInter& L,
                                    occ::handle<Geom_Curve>&    C3D)
{
  TopOpeBRep_TypeLineCurve typeline = L.TypeLineCurve();

  switch (typeline)
  {

    case TopOpeBRep_WALKING:
      C3D = MakeBSpline1fromWALKING3d(L);
      break;

    case TopOpeBRep_LINE:
      C3D = L.Curve();
      break;

    case TopOpeBRep_CIRCLE:
    case TopOpeBRep_ELLIPSE:
    case TopOpeBRep_PARABOLA:
    case TopOpeBRep_HYPERBOLA:

      if (typeline == TopOpeBRep_CIRCLE)
        C3D = L.Curve();
      else if (typeline == TopOpeBRep_ELLIPSE)
        C3D = L.Curve();
      else if (typeline == TopOpeBRep_PARABOLA)
        C3D = L.Curve(min, max); // Trimmed
      else if (typeline == TopOpeBRep_HYPERBOLA)
        C3D = L.Curve(min, max); // Trimmed

      break;

    case TopOpeBRep_ANALYTIC:
    case TopOpeBRep_RESTRICTION:
    case TopOpeBRep_OTHERTYPE:
    default:
      throw Standard_ProgramError("TopOpeBRep_GeomTool::MakePrivateCurves");
      break;
  }
}

//=================================================================================================

occ::handle<Geom_Curve> TopOpeBRep_GeomTool::MakeBSpline1fromWALKING3d(
  const TopOpeBRep_LineInter& L)
{
  int                            ip;
  TopOpeBRep_WPointInterIterator itW(L);
  int                            nbpoints = L.NbWPoint();
  // Define points3d with the walking 3d points of <L>
  NCollection_Array1<gp_Pnt> points3d(1, nbpoints);
  for (ip = 1, itW.Init(); itW.More(); ip++, itW.Next())
  {
    points3d.SetValue(ip, itW.CurrentWP().Value());
  }
  occ::handle<Geom_Curve> C = TopOpeBRepTool_CurveTool::MakeBSpline1fromPnt(points3d);
  return C;
}

//=================================================================================================

occ::handle<Geom2d_Curve> TopOpeBRep_GeomTool::MakeBSpline1fromWALKING2d(
  const TopOpeBRep_LineInter& L,
  const int                   SI)
{
  int                            ip;
  TopOpeBRep_WPointInterIterator itW(L);
  int                            nbpoints = L.NbWPoint();
  // Define points2d with the walking 2d points of <L>
  NCollection_Array1<gp_Pnt2d> points2d(1, nbpoints);
  for (ip = 1, itW.Init(); itW.More(); ip++, itW.Next())
  {
    if (SI == 1)
      points2d.SetValue(ip, itW.CurrentWP().ValueOnS1());
    else if (SI == 2)
      points2d.SetValue(ip, itW.CurrentWP().ValueOnS2());
  }
  occ::handle<Geom2d_Curve> C = TopOpeBRepTool_CurveTool::MakeBSpline1fromPnt2d(points2d);
  return C;
}
