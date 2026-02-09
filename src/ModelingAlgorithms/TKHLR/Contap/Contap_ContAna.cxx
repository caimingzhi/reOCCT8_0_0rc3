#include <Contap_ContAna.hpp>
#include <gp_Cone.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Sphere.hpp>
#include <gp_XYZ.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>

static const double Tolpetit = 1.e-8;

Contap_ContAna::Contap_ContAna()
    : done(false),
      nbSol(0),
      typL(GeomAbs_OtherCurve),
      prm(0.0)
{
}

void Contap_ContAna::Perform(const gp_Sphere& S, const gp_Dir& D)
{
  done = false;
  typL = GeomAbs_Circle;
  pt1  = S.Location();
  dir1 = D;
  if (std::abs(D.Dot(S.XAxis().Direction())) < 0.9999999999999)
  {
    dir2 = D.Crossed(S.XAxis().Direction());
  }
  else
  {
    dir2 = D.Crossed(S.YAxis().Direction());
  }
  prm   = S.Radius();
  nbSol = 1;
  done  = true;
}

void Contap_ContAna::Perform(const gp_Sphere& S, const gp_Dir& D, const double Angle)
{
  done = false;
  typL = GeomAbs_Circle;

  dir1 = D;
  if (std::abs(D.Dot(S.XAxis().Direction())) < 0.9999999999999)
  {
    dir2 = D.Crossed(S.XAxis().Direction());
  }
  else
  {
    dir2 = D.Crossed(S.YAxis().Direction());
  }
  double alpha = (S.Direct() ? Angle : -Angle);
  pt1.SetXYZ(S.Location().XYZ() - S.Radius() * sin(alpha) * D.XYZ());
  prm   = S.Radius() * cos(alpha);
  nbSol = 1;
  done  = true;
}

void Contap_ContAna::Perform(const gp_Sphere& S, const gp_Pnt& Eye)
{
  done = false;

  double radius = S.Radius();
  double dist   = Eye.Distance(S.Location());
  if (dist <= radius)
  {
    nbSol = 0;
  }
  else
  {
    prm = radius * sqrt(1. - radius * radius / (dist * dist));
    if (prm < Tolpetit)
    {
      nbSol = 0;
    }
    else
    {
      gp_XYZ locxyz(S.Location().XYZ());
      dir1.SetXYZ(Eye.XYZ() - locxyz);
      pt1.SetXYZ(locxyz + (radius * radius / dist) * dir1.XYZ());
      if (std::abs(dir1.Dot(S.XAxis().Direction())) < 0.9999999999999)
      {
        dir2 = dir1.Crossed(S.XAxis().Direction());
      }
      else
      {
        dir2 = dir1.Crossed(S.YAxis().Direction());
      }
      nbSol = 1;
      typL  = GeomAbs_Circle;
    }
  }
  done = true;
}

void Contap_ContAna::Perform(const gp_Cylinder& C, const gp_Dir& D)
{
  done = false;

  gp_XYZ normale(C.Position().Direction().XYZ());
  normale.Cross(D.XYZ());
  if (normale.Modulus() <= 1e-15)
  {
    nbSol = 0;
  }
  else
  {
    normale.Normalize();
    typL = GeomAbs_Line;
    dir1 = C.Position().Direction();
    dir2 = dir1;
    pt1.SetXYZ(C.Location().XYZ() + C.Radius() * normale);
    pt2.SetXYZ(C.Location().XYZ() - C.Radius() * normale);
    nbSol = 2;
  }

  done = true;
}

void Contap_ContAna::Perform(const gp_Cylinder& C, const gp_Dir& D, const double Angle)
{
  done = false;

  double Coefcos = D.Dot(C.Position().XDirection());
  double Coefsin = D.Dot(C.Position().YDirection());
  double Coefcst = cos(M_PI * 0.5 + Angle);

  double norm1 = Coefcos * Coefcos + Coefsin * Coefsin;
  double norm2 = sqrt(norm1);

  if (std::abs(Coefcst) < norm2)
  {
    typL  = GeomAbs_Line;
    nbSol = 2;
    dir1 = dir2 = C.Position().Direction();

    if (!C.Direct())
    {
      Coefcos = -Coefcos;
      Coefsin = -Coefsin;
    }

    prm = std::sqrt(norm1 - Coefcst * Coefcst);
    double cost0, sint0, cost1, sint1;

    cost0 = (Coefcos * Coefcst - Coefsin * prm) / norm1;
    cost1 = (Coefcos * Coefcst + Coefsin * prm) / norm1;

    sint0 = (Coefcos * prm + Coefsin * Coefcst) / norm1;
    sint1 = (-Coefcos * prm + Coefsin * Coefcst) / norm1;

    gp_XYZ Xdir(C.Position().XDirection().XYZ());
    gp_XYZ Ydir(C.Position().YDirection().XYZ());
    gp_XYZ dirxyz;

    dirxyz.SetLinearForm(cost0, Xdir, sint0, Ydir);
    dirxyz.Multiply(C.Radius());
    pt1.SetXYZ(C.Location().XYZ().Added(dirxyz));

    dirxyz.SetLinearForm(cost1, Xdir, sint1, Ydir);
    dirxyz.Multiply(C.Radius());
    pt2.SetXYZ(C.Location().XYZ().Added(dirxyz));
  }
  else
  {
    nbSol = 0;
  }

  done = true;
}

void Contap_ContAna::Perform(const gp_Cylinder& C, const gp_Pnt& Eye)
{
  done = false;

  double radius = C.Radius();
  gp_Lin theaxis(C.Axis());
  double dist = theaxis.Distance(Eye);
  if (dist <= radius)
  {
    nbSol = 0;
  }
  else
  {
    typL = GeomAbs_Line;
    prm  = radius * sqrt(1. - radius * radius / (dist * dist));
    dir1 = C.Axis().Direction();
    dir2 = dir1;
    gp_XYZ axeye(theaxis.Normal(Eye).Direction().XYZ());
    gp_XYZ normale((theaxis.Direction().Crossed(axeye)).XYZ());

    pt1.SetXYZ(C.Location().XYZ() + (radius * radius / dist) * axeye);
    pt2.SetXYZ(pt1.XYZ() - prm * normale);
    pt1.SetXYZ(pt1.XYZ() + prm * normale);
    nbSol = 2;
  }
  done = true;
}

void Contap_ContAna::Perform(const gp_Cone& C, const gp_Dir& D)
{
  done = false;

  double Tgtalpha = std::tan(C.SemiAngle());

  double Coefcos = D.Dot(C.Position().XDirection());
  double Coefsin = D.Dot(C.Position().YDirection());
  double Coefcst = D.Dot(C.Axis().Direction()) * Tgtalpha;

  double norm1 = Coefcos * Coefcos + Coefsin * Coefsin;
  double norm2 = std::sqrt(norm1);

  if (std::abs(Coefcst) < norm2)
  {
    typL  = GeomAbs_Line;
    nbSol = 2;
    pt1   = C.Apex();
    pt2   = pt1;

    prm = std::sqrt(norm1 - Coefcst * Coefcst);
    double cost0, sint0, cost1, sint1;

    cost0 = (Coefcos * Coefcst - Coefsin * prm) / norm1;
    cost1 = (Coefcos * Coefcst + Coefsin * prm) / norm1;

    sint0 = (Coefcos * prm + Coefsin * Coefcst) / norm1;
    sint1 = (-Coefcos * prm + Coefsin * Coefcst) / norm1;

    gp_XYZ Xdir(C.Position().XDirection().XYZ());
    gp_XYZ Ydir(C.Position().YDirection().XYZ());
    gp_XYZ Zdir(C.Axis().Direction().XYZ());
    gp_XYZ dirxyz;
    dirxyz.SetLinearForm(cost0, Xdir, sint0, Ydir, 1. / Tgtalpha, Zdir);
    dir1.SetXYZ(dirxyz);
    pt1.SetXYZ(pt1.XYZ() + dirxyz);
    dirxyz.SetLinearForm(cost1, Xdir, sint1, Ydir, 1. / Tgtalpha, Zdir);
    dir2.SetXYZ(dirxyz);
    pt2.SetXYZ(pt2.XYZ() + dirxyz);
  }
  else
  {
    nbSol = 0;
  }
  done = true;
}

void Contap_ContAna::Perform(const gp_Cone& C, const gp_Dir& D, const double Angle)
{
  done  = false;
  nbSol = 0;

  double Ang  = C.SemiAngle();
  double Cosa = cos(Ang);
  double Sina = sin(Ang);

  double Coefcos = D.Dot(C.Position().XDirection());
  double Coefsin = D.Dot(C.Position().YDirection());

  double Coefcst1 = cos(M_PI * 0.5 + Angle);

  double norm1 = Coefcos * Coefcos + Coefsin * Coefsin;
  double norm2 = std::sqrt(norm1);

  double Coefnz  = D.Dot(C.Axis().Direction()) * Sina;
  double Coefcst = (Coefcst1 + Coefnz) / Cosa;

  if (std::abs(Coefcst) < norm2)
  {
    typL = GeomAbs_Line;
    nbSol += 2;
    pt1 = C.Apex();
    pt2 = pt1;

    prm = std::sqrt(norm1 - Coefcst * Coefcst);
    double cost0, sint0, cost1, sint1;

    cost0 = (Coefcos * Coefcst - Coefsin * prm) / norm1;
    cost1 = (Coefcos * Coefcst + Coefsin * prm) / norm1;

    sint0 = (Coefcos * prm + Coefsin * Coefcst) / norm1;
    sint1 = (-Coefcos * prm + Coefsin * Coefcst) / norm1;

    gp_XYZ Xdir(C.Position().XDirection().XYZ());
    gp_XYZ Ydir(C.Position().YDirection().XYZ());
    gp_XYZ Zdir(C.Axis().Direction().XYZ());
    if (!C.Direct())
    {
      Zdir.Reverse();
    }
    gp_XYZ dirxyz;
    dirxyz.SetLinearForm(cost0, Xdir, sint0, Ydir, Cosa / Sina, Zdir);
    dir1.SetXYZ(dirxyz);
    pt1.SetXYZ(pt1.XYZ() + dirxyz);
    dirxyz.SetLinearForm(cost1, Xdir, sint1, Ydir, Cosa / Sina, Zdir);
    dir2.SetXYZ(dirxyz);
    pt2.SetXYZ(pt2.XYZ() + dirxyz);
  }

  Coefcst = (Coefcst1 - Coefnz) / Cosa;

  if (std::abs(Coefcst) < norm2)
  {
    typL = GeomAbs_Line;
    nbSol += 2;
    pt3 = C.Apex();
    pt4 = pt3;

    prm = std::sqrt(norm1 - Coefcst * Coefcst);
    double cost0, sint0, cost1, sint1;

    cost0 = (Coefcos * Coefcst - Coefsin * prm) / norm1;
    cost1 = (Coefcos * Coefcst + Coefsin * prm) / norm1;

    sint0 = (Coefcos * prm + Coefsin * Coefcst) / norm1;
    sint1 = (-Coefcos * prm + Coefsin * Coefcst) / norm1;

    gp_XYZ Xdir(C.Position().XDirection().XYZ());
    gp_XYZ Ydir(C.Position().YDirection().XYZ());
    gp_XYZ Zdir(C.Axis().Direction().XYZ());
    if (!C.Direct())
    {
      Zdir.Reverse();
    }
    gp_XYZ dirxyz;
    dirxyz.SetLinearForm(cost0, Xdir, sint0, Ydir, -Cosa / Sina, Zdir);
    dir3.SetXYZ(dirxyz);
    pt3.SetXYZ(pt3.XYZ() + dirxyz);
    dirxyz.SetLinearForm(cost1, Xdir, sint1, Ydir, -Cosa / Sina, Zdir);
    dir4.SetXYZ(dirxyz);
    pt4.SetXYZ(pt4.XYZ() + dirxyz);
    if (nbSol == 2)
    {
      pt1  = pt3;
      pt2  = pt4;
      dir1 = dir3;
      dir2 = dir4;
    }
  }

  done = true;
}

void Contap_ContAna::Perform(const gp_Cone& C, const gp_Pnt& Eye)
{
  done = false;

  double Tgtalpha = std::tan(C.SemiAngle());

  gp_XYZ apexeye(Eye.XYZ());
  apexeye.Subtract(C.Apex().XYZ());

  double Coefcos = apexeye.Dot(C.Position().XDirection().XYZ());
  double Coefsin = apexeye.Dot(C.Position().YDirection().XYZ());
  double Coefcst = apexeye.Dot(C.Axis().Direction().XYZ()) * Tgtalpha;

  double norm1 = Coefcos * Coefcos + Coefsin * Coefsin;
  double norm2 = std::sqrt(Coefcos * Coefcos + Coefsin * Coefsin);

  if (std::abs(Coefcst) < norm2)
  {
    typL  = GeomAbs_Line;
    nbSol = 2;
    pt1   = C.Apex();
    pt2   = pt1;

    prm = std::sqrt(norm1 - Coefcst * Coefcst);
    double cost0, sint0, cost1, sint1;

    cost0 = (Coefcos * Coefcst - Coefsin * prm) / norm1;
    cost1 = (Coefcos * Coefcst + Coefsin * prm) / norm1;

    sint0 = (Coefcos * prm + Coefsin * Coefcst) / norm1;
    sint1 = (-Coefcos * prm + Coefsin * Coefcst) / norm1;

    gp_XYZ Xdir(C.Position().XDirection().XYZ());
    gp_XYZ Ydir(C.Position().YDirection().XYZ());
    gp_XYZ Zdir(C.Axis().Direction().XYZ());
    gp_XYZ dirxyz;
    dirxyz.SetLinearForm(cost0, Xdir, sint0, Ydir, 1. / Tgtalpha, Zdir);
    dir1.SetXYZ(dirxyz);
    pt1.SetXYZ(pt1.XYZ() + dirxyz);
    dirxyz.SetLinearForm(cost1, Xdir, sint1, Ydir, 1. / Tgtalpha, Zdir);
    dir2.SetXYZ(dirxyz);
    pt2.SetXYZ(pt2.XYZ() + dirxyz);
  }
  else
  {
    nbSol = 0;
  }
  done = true;
}

gp_Lin Contap_ContAna::Line(const int Index) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (typL != GeomAbs_Line || nbSol == 0)
  {
    throw Standard_DomainError();
  }
  if (Index <= 0 || Index > nbSol)
  {
    throw Standard_OutOfRange();
  }
  switch (Index)
  {
    case 1:
      return gp_Lin(pt1, dir1);
    case 2:
      return gp_Lin(pt2, dir2);
    case 3:
      return gp_Lin(pt3, dir3);
    case 4:
      return gp_Lin(pt4, dir4);
  }
  throw Standard_OutOfRange("Program error in Contap_ContAna");
}
