#include <ChFiKPart_ComputeData_Fcts.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <ProjLib_ProjectedCurve.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Line.hpp>
#include <gp_Pnt2d.hpp>

#include <TopOpeBRepDS_Curve.hpp>
#include <TopOpeBRepDS_Surface.hpp>

#include <Standard_NotImplemented.hpp>

#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>

//=================================================================================================

double ChFiKPart_InPeriod(const double U, const double UFirst, const double ULast, const double Eps)
{
  double u = U, period = ULast - UFirst;
  while (Eps < (UFirst - u))
    u += period;
  while (Eps > (ULast - u))
    u -= period;
  if (u < UFirst)
    u = UFirst;
  return u;
}

//=======================================================================
// function : PCurve
// purpose  : Calculate a straight line in form of BSpline to guarantee
//           the parameters.
//=======================================================================

occ::handle<Geom2d_BSplineCurve> ChFiKPart_PCurve(const gp_Pnt2d& UV1,
                                                  const gp_Pnt2d& UV2,
                                                  const double    Pardeb,
                                                  const double    Parfin)
{
  NCollection_Array1<gp_Pnt2d> p(1, 2);
  NCollection_Array1<double>   k(1, 2);
  NCollection_Array1<int>      m(1, 2);
  m.Init(2);
  k(1)                                   = Pardeb;
  k(2)                                   = Parfin;
  p(1)                                   = UV1;
  p(2)                                   = UV2;
  occ::handle<Geom2d_BSplineCurve> Pcurv = new Geom2d_BSplineCurve(p, k, m, 1);
  return Pcurv;
}

//=======================================================================
// function : ProjPC
// purpose  : For spherical corners the contours which of are not
//           isos the circle is projected.
//=======================================================================

void ChFiKPart_ProjPC(const GeomAdaptor_Curve&   Cg,
                      const GeomAdaptor_Surface& Sg,
                      occ::handle<Geom2d_Curve>& Pcurv)
{
  if (Sg.GetType() < GeomAbs_BezierSurface)
  {
    occ::handle<GeomAdaptor_Curve>   HCg = new GeomAdaptor_Curve(Cg);
    occ::handle<GeomAdaptor_Surface> HSg = new GeomAdaptor_Surface(Sg);
    ProjLib_ProjectedCurve           Projc(HSg, HCg);
    switch (Projc.GetType())
    {
      case GeomAbs_Line:
      {
        Pcurv = new Geom2d_Line(Projc.Line());
      }
      break;
      case GeomAbs_BezierCurve:
      {
        occ::handle<Geom2d_BezierCurve> BezProjc = Projc.Bezier();
        NCollection_Array1<gp_Pnt2d>    TP(1, BezProjc->NbPoles());
        if (BezProjc->IsRational())
        {
          NCollection_Array1<double> TW(1, BezProjc->NbPoles());
          BezProjc->Poles(TP);
          BezProjc->Weights(TW);
          Pcurv = new Geom2d_BezierCurve(TP, TW);
        }
        else
        {
          BezProjc->Poles(TP);
          Pcurv = new Geom2d_BezierCurve(TP);
        }
      }
      break;
      case GeomAbs_BSplineCurve:
      {
        occ::handle<Geom2d_BSplineCurve> BspProjc = Projc.BSpline();
        NCollection_Array1<gp_Pnt2d>     TP(1, BspProjc->NbPoles());
        NCollection_Array1<double>       TK(1, BspProjc->NbKnots());
        NCollection_Array1<int>          TM(1, BspProjc->NbKnots());

        BspProjc->Knots(TK);
        BspProjc->Multiplicities(TM);
        if (BspProjc->IsRational())
        {
          NCollection_Array1<double> TW(1, BspProjc->NbPoles());
          BspProjc->Poles(TP);
          BspProjc->Weights(TW);
          Pcurv = new Geom2d_BSplineCurve(TP, TW, TK, TM, BspProjc->Degree());
        }
        else
        {
          BspProjc->Poles(TP);
          Pcurv = new Geom2d_BSplineCurve(TP, TK, TM, BspProjc->Degree());
        }
      }
      break;
      default:
        throw Standard_NotImplemented("failed approximation of the pcurve ");
    }
  }
  else
  {
    throw Standard_NotImplemented("approximate pcurve on the left surface");
  }
}

//=======================================================================
// function : IndexCurveInDS
// purpose  : Place a Curve in the DS and return its index.
//=======================================================================

int ChFiKPart_IndexCurveInDS(const occ::handle<Geom_Curve>& C, TopOpeBRepDS_DataStructure& DStr)
{
  return DStr.AddCurve(TopOpeBRepDS_Curve(C, 0.));
}

//=======================================================================
// function : IndexSurfaceInDS
// purpose  : Place a Surface in the DS and return its index.
//=======================================================================

int ChFiKPart_IndexSurfaceInDS(const occ::handle<Geom_Surface>& S, TopOpeBRepDS_DataStructure& DStr)
{
  return DStr.AddSurface(TopOpeBRepDS_Surface(S, 0.));
}
