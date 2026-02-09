#include <gce_MakeCone.hpp>
#include <gp.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Cone.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

gce_MakeCone::gce_MakeCone(const gp_Ax2& A2, const double Ang, const double Radius)
{
  if (Radius < 0.0)
  {
    TheError = gce_NegativeRadius;
  }
  else
  {
    if (Ang <= gp::Resolution() || M_PI / 2 - Ang <= gp::Resolution())
    {
      TheError = gce_BadAngle;
    }
    else
    {
      TheError = gce_Done;
      TheCone  = gp_Cone(A2, Ang, Radius);
    }
  }
}

gce_MakeCone::gce_MakeCone(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3, const gp_Pnt& P4)
{
  if (P1.Distance(P2) < RealEpsilon() || P3.Distance(P4) < RealEpsilon())
  {
    TheError = gce_ConfusedPoints;
    return;
  }

  gp_Dir D1(P2.XYZ() - P1.XYZ());
  double cos  = D1.Dot(gp_Dir(P4.XYZ() - P1.XYZ()));
  double dist = P1.Distance(P4);
  gp_Pnt PP4(P1.XYZ() + cos * dist * D1.XYZ());
  cos  = D1.Dot(gp_Dir(P3.XYZ() - P1.XYZ()));
  dist = P1.Distance(P3);
  gp_Pnt PP3(P1.XYZ() + cos * dist * D1.XYZ());

  double Dist13 = PP3.Distance(P1);
  double Dist14 = PP4.Distance(P1);
  if (std::abs(Dist13 - Dist14) < RealEpsilon())
  {
    TheError = gce_NullAngle;
    return;
  }
  gp_Lin L1(P1, D1);
  double Dist3  = L1.Distance(P3);
  double Dist4  = L1.Distance(P4);
  double DifRad = Dist3 - Dist4;
  double angle  = std::abs(std::atan(DifRad / (Dist13 - Dist14)));
  if (std::abs(M_PI / 2. - angle) < RealEpsilon() || std::abs(angle) < RealEpsilon())
  {
    TheError = gce_NullRadius;
    return;
  }
  double R1 = PP3.Distance(P3);
  double R2 = PP4.Distance(P4);
  if (R1 < 0.0 || R2 < 0.0)
  {
    TheError = gce_NegativeRadius;
    return;
  }
  gp_Dir DD1(PP4.XYZ() - PP3.XYZ());
  gp_Dir D2;
  double x = DD1.X();
  double y = DD1.Y();
  double z = DD1.Z();
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
  if (R1 > R2)
  {
    angle *= -1;
  }
  TheCone  = gp_Cone(gp_Ax2(PP3, DD1, D2), angle, R1);
  TheError = gce_Done;
}

gce_MakeCone::gce_MakeCone(const gp_Ax1& Axis, const gp_Pnt& P1, const gp_Pnt& P2)
{
  gp_Pnt       P3(Axis.Location());
  gp_Pnt       P4(P3.XYZ() + Axis.Direction().XYZ());
  gce_MakeCone Cone(P3, P4, P1, P2);
  if (Cone.IsDone())
  {
    TheCone  = Cone.Value();
    TheError = gce_Done;
  }
  else
  {
    TheError = Cone.Status();
  }
}

gce_MakeCone::gce_MakeCone(const gp_Cone&, const gp_Pnt&)
{
  TheError = gce_ConfusedPoints;
}

gce_MakeCone::gce_MakeCone(const gp_Cone&, const double)
{
  TheError = gce_Done;
}

gce_MakeCone::gce_MakeCone(const gp_Lin& Axis, const gp_Pnt& P1, const gp_Pnt& P2)
{
  gp_Pnt       P3(Axis.Location());
  gp_Pnt       P4(P3.XYZ() + Axis.Direction().XYZ());
  gce_MakeCone Cone(P3, P4, P1, P2);
  if (Cone.IsDone())
  {
    TheCone  = Cone.Value();
    TheError = gce_Done;
  }
  else
  {
    TheError = Cone.Status();
  }
}

gce_MakeCone::gce_MakeCone(const gp_Pnt& P1, const gp_Pnt& P2, const double R1, const double R2)
{
  double dist = P1.Distance(P2);
  if (dist < RealEpsilon())
  {
    TheError = gce_NullAxis;
  }
  else
  {
    if (R1 < 0.0 || R2 < 0.0)
    {
      TheError = gce_NegativeRadius;
    }
    else
    {
      double Angle = std::abs(atan((R1 - R2) / dist));
      if (std::abs(M_PI / 2. - Angle) < RealEpsilon() || std::abs(Angle) < RealEpsilon())
      {
        TheError = gce_NullAngle;
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
        if (R1 > R2)
        {
          Angle *= -1;
        }
        TheCone  = gp_Cone(gp_Ax2(P1, D1, D2), Angle, R1);
        TheError = gce_Done;
      }
    }
  }
}

const gp_Cone& gce_MakeCone::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "gce_MakeCone::Value() - no result");
  return TheCone;
}

const gp_Cone& gce_MakeCone::Operator() const
{
  return Value();
}

gce_MakeCone::operator gp_Cone() const
{
  return Value();
}
