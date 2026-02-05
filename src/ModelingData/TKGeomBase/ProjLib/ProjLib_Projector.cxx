#include <ElCLib.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Lin.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Parab.hpp>
#include <ProjLib_Projector.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_NotImplemented.hpp>

//=================================================================================================

ProjLib_Projector::ProjLib_Projector()
    : myIsPeriodic(false)
{
  isDone = false;
  myType = GeomAbs_BSplineCurve;
}

//=================================================================================================

ProjLib_Projector::~ProjLib_Projector() = default;

//=================================================================================================

bool ProjLib_Projector::IsDone() const
{
  return isDone;
}

//=================================================================================================

void ProjLib_Projector::Done()
{
  isDone = true;
}

//=================================================================================================

GeomAbs_CurveType ProjLib_Projector::GetType() const
{
  return myType;
}

//=================================================================================================

void ProjLib_Projector::SetType(const GeomAbs_CurveType Type)
{
  myType = Type;
}

//=================================================================================================

bool ProjLib_Projector::IsPeriodic() const
{
  return myIsPeriodic;
}

//=================================================================================================

void ProjLib_Projector::SetPeriodic()
{
  myIsPeriodic = true;
}

//=================================================================================================

const gp_Lin2d& ProjLib_Projector::Line() const
{
  if (myType != GeomAbs_Line)
    throw Standard_NoSuchObject("ProjLib_Projector::Line");
  return myLin;
}

//=================================================================================================

const gp_Circ2d& ProjLib_Projector::Circle() const
{
  if (myType != GeomAbs_Circle)
    throw Standard_NoSuchObject("ProjLib_Projector::Circle");
  return myCirc;
}

//=================================================================================================

const gp_Elips2d& ProjLib_Projector::Ellipse() const
{
  if (myType != GeomAbs_Ellipse)
    throw Standard_NoSuchObject("ProjLib_Projector::Ellipse");
  return myElips;
}

//=================================================================================================

const gp_Hypr2d& ProjLib_Projector::Hyperbola() const
{
  if (myType != GeomAbs_Hyperbola)
    throw Standard_NoSuchObject("ProjLib_Projector::Hyperbola");
  return myHypr;
}

//=================================================================================================

const gp_Parab2d& ProjLib_Projector::Parabola() const
{
  if (myType != GeomAbs_Parabola)
    throw Standard_NoSuchObject("ProjLib_Projector::Parabola");
  return myParab;
}

//=================================================================================================

void ProjLib_Projector::Project(const gp_Lin&)
{
  myType = GeomAbs_OtherCurve;
}

//=================================================================================================

void ProjLib_Projector::Project(const gp_Circ&)
{
  myType = GeomAbs_OtherCurve;
}

//=================================================================================================

void ProjLib_Projector::Project(const gp_Elips&)
{
  myType = GeomAbs_OtherCurve;
}

//=================================================================================================

void ProjLib_Projector::Project(const gp_Parab&)
{
  myType = GeomAbs_OtherCurve;
}

//=================================================================================================

void ProjLib_Projector::Project(const gp_Hypr&)
{
  myType = GeomAbs_OtherCurve;
}

//=================================================================================================

void ProjLib_Projector::UFrame(const double CFirst,
                               //			       const double CLast,
                               const double,
                               const double UFirst,
                               const double Period)
{
  if (myType == GeomAbs_Line)
  {
    //  Modified by skv - Wed Aug 11 15:45:58 2004 OCC6272 Begin
    //     if ( myLin.Direction().Y() == 0.) {
    //  Modified by skv - Wed Aug 11 15:45:58 2004 OCC6272 End
    //      gp_Pnt2d PFirst, PLast;
    gp_Pnt2d PFirst;
    PFirst = ElCLib::Value(CFirst, myLin);
    // PLast  = ElCLib::Value(CLast ,myLin);
    // double U = std::min( PFirst.X(), PLast.X());
    double U    = PFirst.X();
    double NewU = ElCLib::InPeriod(U, UFirst, UFirst + Period);
    myLin.Translate(gp_Vec2d(NewU - U, 0.));
  }
}

//=================================================================================================

void ProjLib_Projector::VFrame(const double CFirst,
                               //			       const double CLast,
                               const double,
                               const double VFirst,
                               const double Period)
{
  if (myType == GeomAbs_Line)
  {
    //  Modified by skv - Wed Aug 11 15:45:58 2004 OCC6272 Begin
    //     if ( myLin.Direction().X() == 0.) {
    //  Modified by skv - Wed Aug 11 15:45:58 2004 OCC6272 End
    //      gp_Pnt2d PFirst, PLast;
    gp_Pnt2d PFirst;
    PFirst = ElCLib::Value(CFirst, myLin);
    // PLast  = ElCLib::Value(CLast ,myLin);
    // double V = std::min( PFirst.Y(), PLast.Y());
    double V    = PFirst.Y();
    double NewV = ElCLib::InPeriod(V, VFirst, VFirst + Period);
    myLin.Translate(gp_Vec2d(0., NewV - V));
  }
}

//=================================================================================================

void ProjLib_Projector::SetBezier(const occ::handle<Geom2d_BezierCurve>& C)
{
  myBezier = C;
}

//=================================================================================================

occ::handle<Geom2d_BezierCurve> ProjLib_Projector::Bezier() const
{
  return myBezier;
}

//=================================================================================================

void ProjLib_Projector::SetBSpline(const occ::handle<Geom2d_BSplineCurve>& C)
{
  myBSpline = C;
}

//=================================================================================================

occ::handle<Geom2d_BSplineCurve> ProjLib_Projector::BSpline() const
{
  return myBSpline;
}
