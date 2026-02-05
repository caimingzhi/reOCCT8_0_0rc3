#include <BiTgte_CurveOnEdge.hpp>

#include <Adaptor3d_Curve.hpp>
#include <BRep_Tool.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAPI_ProjectPointOnCurve.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Lin.hpp>
#include <gp_Parab.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_NotImplemented.hpp>
#include <TopoDS_Edge.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BiTgte_CurveOnEdge, Adaptor3d_Curve)

//=================================================================================================

BiTgte_CurveOnEdge::BiTgte_CurveOnEdge()
    : myType(GeomAbs_OtherCurve)
{
}

//=================================================================================================

BiTgte_CurveOnEdge::BiTgte_CurveOnEdge(const TopoDS_Edge& theEonF, const TopoDS_Edge& theEdge)
    : myEdge(theEdge),
      myEonF(theEonF),
      myType(GeomAbs_OtherCurve)
{
  Init(theEonF, theEdge);
}

//=================================================================================================

occ::handle<Adaptor3d_Curve> BiTgte_CurveOnEdge::ShallowCopy() const
{
  occ::handle<BiTgte_CurveOnEdge> aCopy = new BiTgte_CurveOnEdge();

  aCopy->myEdge = myEdge;
  aCopy->myEonF = myEonF;
  aCopy->myCurv = myCurv;
  aCopy->myConF = myConF;
  aCopy->myType = myType;
  aCopy->myCirc = myCirc;

  return aCopy;
}

//=================================================================================================

void BiTgte_CurveOnEdge::Init(const TopoDS_Edge& EonF, const TopoDS_Edge& Edge)
{
  double f, l;

  myEdge = Edge;
  myCurv = BRep_Tool::Curve(myEdge, f, l);
  myCurv = new Geom_TrimmedCurve(myCurv, f, l);

  myEonF = EonF;
  myConF = BRep_Tool::Curve(myEonF, f, l);
  myConF = new Geom_TrimmedCurve(myConF, f, l);

  // peut on generer un cercle de rayon nul
  GeomAdaptor_Curve Curv(myCurv);
  GeomAdaptor_Curve ConF(myConF);

  myType = GeomAbs_OtherCurve;
  if (Curv.GetType() == GeomAbs_Line && ConF.GetType() == GeomAbs_Circle)
  {
    gp_Ax1 a1 = Curv.Line().Position();
    gp_Ax1 a2 = ConF.Circle().Axis();
    if (a1.IsCoaxial(a2, Precision::Angular(), Precision::Confusion()))
    {
      myType = GeomAbs_Circle;
      myCirc = gp_Circ(ConF.Circle().Position(), 0.);
    }
  }
}

//=================================================================================================

double BiTgte_CurveOnEdge::FirstParameter() const
{
  return myConF->FirstParameter();
}

//=================================================================================================

double BiTgte_CurveOnEdge::LastParameter() const
{
  return myConF->LastParameter();
}

//=================================================================================================

GeomAbs_Shape BiTgte_CurveOnEdge::Continuity() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

int BiTgte_CurveOnEdge::NbIntervals(const GeomAbs_Shape) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

void BiTgte_CurveOnEdge::Intervals(NCollection_Array1<double>&, const GeomAbs_Shape) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

occ::handle<Adaptor3d_Curve> BiTgte_CurveOnEdge::Trim(const double,
                                                      const double,
                                                      const double) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

bool BiTgte_CurveOnEdge::IsClosed() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

bool BiTgte_CurveOnEdge::IsPeriodic() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

double BiTgte_CurveOnEdge::Period() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

gp_Pnt BiTgte_CurveOnEdge::Value(const double U) const
{
  gp_Pnt P;
  D0(U, P);
  return P;
}

//=================================================================================================

void BiTgte_CurveOnEdge::D0(const double U, gp_Pnt& P) const
{
  GeomAPI_ProjectPointOnCurve Projector;
  P = myConF->Value(U);
  Projector.Init(P, myCurv);
  P = Projector.NearestPoint();
}

//=================================================================================================

void BiTgte_CurveOnEdge::D1(const double, gp_Pnt&, gp_Vec&) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

void BiTgte_CurveOnEdge::D2(const double, gp_Pnt&, gp_Vec&, gp_Vec&) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

void BiTgte_CurveOnEdge::D3(const double, gp_Pnt&, gp_Vec&, gp_Vec&, gp_Vec&) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

gp_Vec BiTgte_CurveOnEdge::DN(const double, const int) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

double BiTgte_CurveOnEdge::Resolution(const double) const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

GeomAbs_CurveType BiTgte_CurveOnEdge::GetType() const
{
  return myType;
}

//=================================================================================================

gp_Lin BiTgte_CurveOnEdge::Line() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

gp_Circ BiTgte_CurveOnEdge::Circle() const
{
  if (myType != GeomAbs_Circle)
  {
    throw Standard_NoSuchObject("BiTgte_CurveOnEdge::Circle");
  }

  return myCirc;
}

//=================================================================================================

gp_Elips BiTgte_CurveOnEdge::Ellipse() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

gp_Hypr BiTgte_CurveOnEdge::Hyperbola() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

gp_Parab BiTgte_CurveOnEdge::Parabola() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

int BiTgte_CurveOnEdge::Degree() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

bool BiTgte_CurveOnEdge::IsRational() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

int BiTgte_CurveOnEdge::NbPoles() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

int BiTgte_CurveOnEdge::NbKnots() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

occ::handle<Geom_BezierCurve> BiTgte_CurveOnEdge::Bezier() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}

//=================================================================================================

occ::handle<Geom_BSplineCurve> BiTgte_CurveOnEdge::BSpline() const
{
  throw Standard_NotImplemented("BiTgte_CurveOnEdge");
}
