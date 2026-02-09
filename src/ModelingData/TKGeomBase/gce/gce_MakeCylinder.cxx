#include <gce_MakeCylinder.hpp>
#include <gp.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Circ.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

gce_MakeCylinder::gce_MakeCylinder(const gp_Ax2& A2, const double Radius)
{
  if (Radius < 0.0)
  {
    TheError = gce_NegativeRadius;
  }
  else
  {
    TheCylinder = gp_Cylinder(A2, Radius);
    TheError    = gce_Done;
  }
}

gce_MakeCylinder::gce_MakeCylinder(const gp_Ax1& Axis, const double Radius)
{
  if (Radius < 0.0)
  {
    TheError = gce_NegativeRadius;
  }
  else
  {
    gp_Dir D(Axis.Direction());
    gp_Dir Direc;
    double x = D.X();
    double y = D.Y();
    double z = D.Z();
    if (std::abs(x) > gp::Resolution())
    {
      Direc = gp_Dir(-y, x, 0.0);
    }
    else if (std::abs(y) > gp::Resolution())
    {
      Direc = gp_Dir(-y, x, 0.0);
    }
    else if (std::abs(z) > gp::Resolution())
    {
      Direc = gp_Dir(0.0, -z, y);
    }
    TheCylinder = gp_Cylinder(gp_Ax2(Axis.Location(), D, Direc), Radius);
    TheError    = gce_Done;
  }
}

gce_MakeCylinder::gce_MakeCylinder(const gp_Circ& Circ)
{
  TheCylinder = gp_Cylinder(Circ.Position(), Circ.Radius());
  TheError    = gce_Done;
}

gce_MakeCylinder::gce_MakeCylinder(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3)
{
  if (P1.Distance(P2) < gp::Resolution())
  {
    TheError = gce_ConfusedPoints;
  }
  else
  {
    gp_Dir D1(P2.XYZ() - P1.XYZ());
    gp_Dir D2;
    double x = D1.X();
    double y = D1.Y();
    double z = D1.Z();
    if (std::abs(x) > gp::Resolution())
    {
      D2 = gp_Dir(-y, x, 0.0);
    }
    else if (std::abs(y) > gp::Resolution())
    {
      D2 = gp_Dir(-y, x, 0.0);
    }
    else if (std::abs(z) > gp::Resolution())
    {
      D2 = gp_Dir(0.0, -z, y);
    }
    TheCylinder = gp_Cylinder(gp_Ax2(P1, D1, D2), gp_Lin(P1, D1).Distance(P3));
    TheError    = gce_Done;
  }
}

gce_MakeCylinder::gce_MakeCylinder(const gp_Cylinder& Cyl, const double Dist)
{
  double Rad = Cyl.Radius() + Dist;
  if (Rad < 0.)
  {
    TheError = gce_NegativeRadius;
  }
  else
  {
    TheCylinder = gp_Cylinder(Cyl);
    TheCylinder.SetRadius(Rad);
    TheError = gce_Done;
  }
}

gce_MakeCylinder::gce_MakeCylinder(const gp_Cylinder& Cyl, const gp_Pnt& P)
{
  gp_Lin L(Cyl.Axis());
  double Rad  = L.Distance(P);
  TheCylinder = gp_Cylinder(Cyl);
  TheCylinder.SetRadius(Rad);
  TheError = gce_Done;
}

const gp_Cylinder& gce_MakeCylinder::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "gce_MakeCylinder::Value() - no result");
  return TheCylinder;
}

const gp_Cylinder& gce_MakeCylinder::Operator() const
{
  return Value();
}

gce_MakeCylinder::operator gp_Cylinder() const
{
  return Value();
}
