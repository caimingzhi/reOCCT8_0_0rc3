#include <ElCLib.hpp>
#include <gce_MakeCirc2d.hpp>
#include <gp.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <StdFail_NotDone.hpp>

gce_MakeCirc2d::gce_MakeCirc2d(const gp_Pnt2d& P1, const gp_Pnt2d& P2, const gp_Pnt2d& P3)
{
  gp_Dir2d dirx(gp_Dir2d::D::X);

  double dist1 = P1.Distance(P2);
  double dist2 = P1.Distance(P3);
  double dist3 = P2.Distance(P3);

  if ((dist1 < gp::Resolution()) && (dist2 < gp::Resolution()) && (dist3 < gp::Resolution()))
  {
    TheCirc2d = gp_Circ2d(gp_Ax2d(P1, dirx), 0.0);
    TheError  = gce_Done;
  }
  else
  {
    gp_Lin2d L1;
    gp_Lin2d L2;
    double   x1, y1, x2, y2, x3, y3;
    P1.Coord(x1, y1);
    P2.Coord(x2, y2);
    P3.Coord(x3, y3);
    if (dist1 >= RealEpsilon())
    {
      L1 =
        gp_Lin2d(gp_Pnt2d((P1.XY() + P2.XY()) / 2.0), gp_Dir2d(P1.Y() - P2.Y(), P2.X() - P1.X()));
    }
    if (dist2 >= RealEpsilon())
    {
      L2 =
        gp_Lin2d(gp_Pnt2d((P1.XY() + P3.XY()) / 2.0), gp_Dir2d(P1.Y() - P3.Y(), P3.X() - P1.X()));
    }
    if (dist2 <= RealEpsilon())
    {
      L2 = gp_Lin2d(P1, gp_Dir2d(P1.Y() - P2.Y(), P2.X() - P1.X()));
    }
    else if (dist1 <= RealEpsilon())
    {
      L1 = gp_Lin2d(P1, gp_Dir2d(P1.Y() - P3.Y(), P3.X() - P1.X()));
    }
    else if (dist3 <= RealEpsilon())
    {
      L2 = gp_Lin2d(P1, gp_Dir2d(P1.Y() - P2.Y(), P2.X() - P1.X()));
    }
    IntAna2d_AnaIntersection Intp(L1, L2);
    if (Intp.IsDone())
    {
      if (!Intp.IsEmpty())
      {
        gp_Pnt2d pInt(Intp.Point(1).Value());
        dist1 = P1.Distance(pInt);
        dist2 = P2.Distance(pInt);
        dist3 = P3.Distance(pInt);
        double xc, yc;
        pInt.Coord(xc, yc);
        gp_Dir2d d1(x1 - xc, y1 - yc);
        gp_Dir2d d2(xc - x3, yc - y3);
        TheCirc2d     = gp_Circ2d(gp_Ax22d(pInt, d1, d2), (dist1 + dist2 + dist3) / 3.);
        double Alpha1 = ElCLib::Parameter(TheCirc2d, P1);
        double Alpha2 = ElCLib::Parameter(TheCirc2d, P2);
        double Alpha3 = ElCLib::Parameter(TheCirc2d, P3);
        if ((Alpha1 > Alpha2) || (Alpha2 > Alpha3))
        {
          TheCirc2d.Reverse();
        }
        TheError = gce_Done;
      }
    }
    else
    {
      TheError = gce_IntersectionError;
    }
  }
}

gce_MakeCirc2d::gce_MakeCirc2d(const gp_Ax2d& XAxis, const double Radius, const bool Sense)
{
  if (Radius >= 0.)
  {
    TheCirc2d = gp_Circ2d(XAxis, Radius, Sense);
    TheError  = gce_Done;
  }
  else
  {
    TheError = gce_NegativeRadius;
  }
}

gce_MakeCirc2d::gce_MakeCirc2d(const gp_Ax22d& Axis, const double Radius)
{
  if (Radius >= 0.)
  {
    TheCirc2d = gp_Circ2d(Axis, Radius);
    TheError  = gce_Done;
  }
  else
  {
    TheError = gce_NegativeRadius;
  }
}

gce_MakeCirc2d::gce_MakeCirc2d(const gp_Pnt2d& Center, const double Radius, const bool Sense)
{
  if (Radius >= 0.)
  {
    TheCirc2d = gp_Circ2d(gp_Ax2d(Center, gp_Dir2d(gp_Dir2d::D::X)), Radius, Sense);
    TheError  = gce_Done;
  }
  else
  {
    TheError = gce_NegativeRadius;
  }
}

gce_MakeCirc2d::gce_MakeCirc2d(const gp_Pnt2d& Center, const gp_Pnt2d& Point, const bool Sense)
{
  TheCirc2d = gp_Circ2d(gp_Ax2d(Center, gp_Dir2d(gp_Dir2d::D::X)), Point.Distance(Center), Sense);
  TheError  = gce_Done;
}

gce_MakeCirc2d::gce_MakeCirc2d(const gp_Circ2d& Circ, const gp_Pnt2d& Point)
{
  TheCirc2d = gp_Circ2d(Circ.Axis(), Point.Distance(Circ.Location()));
  TheError  = gce_Done;
}

gce_MakeCirc2d::gce_MakeCirc2d(const gp_Circ2d& Circ, const double Dist1)
{
  TheCirc2d = gp_Circ2d(Circ.Axis(), std::abs(Circ.Radius() + Dist1));
  TheError  = gce_Done;
}

const gp_Circ2d& gce_MakeCirc2d::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "gce_MakeCirc2d::Value() - no result");
  return TheCirc2d;
}

const gp_Circ2d& gce_MakeCirc2d::Operator() const
{
  return Value();
}

gce_MakeCirc2d::operator gp_Circ2d() const
{
  return Value();
}
