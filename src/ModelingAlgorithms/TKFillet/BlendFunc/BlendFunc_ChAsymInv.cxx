#include <Adaptor2d_Curve2d.hpp>
#include <BlendFunc.hpp>
#include <BlendFunc_ChAsymInv.hpp>
#include <math_Matrix.hpp>
#include <Precision.hpp>

BlendFunc_ChAsymInv::BlendFunc_ChAsymInv(const occ::handle<Adaptor3d_Surface>& S1,
                                         const occ::handle<Adaptor3d_Surface>& S2,
                                         const occ::handle<Adaptor3d_Curve>&   C)
    : surf1(S1),
      surf2(S2),
      dist1(RealLast()),
      angle(RealLast()),
      tgang(RealLast()),
      curv(C),
      choix(0),
      first(false),
      FX(1, 4),
      DX(1, 4, 1, 4)
{
}

void BlendFunc_ChAsymInv::Set(const double Dist1, const double Angle, const int Choix)
{
  dist1 = std::abs(Dist1);
  angle = Angle;
  tgang = std::tan(Angle);
  choix = Choix;
}

int BlendFunc_ChAsymInv::NbEquations() const
{
  return 4;
}

void BlendFunc_ChAsymInv::Set(const bool OnFirst, const occ::handle<Adaptor2d_Curve2d>& C)
{
  first = OnFirst;
  csurf = C;
}

void BlendFunc_ChAsymInv::GetTolerance(math_Vector& Tolerance, const double Tol) const
{
  Tolerance(1) = csurf->Resolution(Tol);
  Tolerance(2) = curv->Resolution(Tol);
  if (first)
  {
    Tolerance(3) = surf2->UResolution(Tol);
    Tolerance(4) = surf2->VResolution(Tol);
  }
  else
  {
    Tolerance(3) = surf1->UResolution(Tol);
    Tolerance(4) = surf1->VResolution(Tol);
  }
}

void BlendFunc_ChAsymInv::GetBounds(math_Vector& InfBound, math_Vector& SupBound) const
{
  InfBound(1) = csurf->FirstParameter();
  InfBound(2) = curv->FirstParameter();
  SupBound(1) = csurf->LastParameter();
  SupBound(2) = curv->LastParameter();

  if (first)
  {
    InfBound(3) = surf2->FirstUParameter();
    InfBound(4) = surf2->FirstVParameter();
    SupBound(3) = surf2->LastUParameter();
    SupBound(4) = surf2->LastVParameter();
    if (!Precision::IsInfinite(InfBound(3)) && !Precision::IsInfinite(SupBound(3)))
    {
      const double range = (SupBound(3) - InfBound(3));
      InfBound(3) -= range;
      SupBound(3) += range;
    }
    if (!Precision::IsInfinite(InfBound(4)) && !Precision::IsInfinite(SupBound(4)))
    {
      const double range = (SupBound(4) - InfBound(4));
      InfBound(4) -= range;
      SupBound(4) += range;
    }
  }
  else
  {
    InfBound(3) = surf1->FirstUParameter();
    InfBound(4) = surf1->FirstVParameter();
    SupBound(3) = surf1->LastUParameter();
    SupBound(4) = surf1->LastVParameter();
    if (!Precision::IsInfinite(InfBound(3)) && !Precision::IsInfinite(SupBound(3)))
    {
      const double range = (SupBound(3) - InfBound(3));
      InfBound(3) -= range;
      SupBound(3) += range;
    }
    if (!Precision::IsInfinite(InfBound(4)) && !Precision::IsInfinite(SupBound(4)))
    {
      const double range = (SupBound(4) - InfBound(4));
      InfBound(4) -= range;
      SupBound(4) += range;
    }
  }
}

bool BlendFunc_ChAsymInv::IsSolution(const math_Vector& Sol, const double Tol)
{
  math_Vector valsol(1, 4);
  gp_Pnt      pts1, pts2, ptgui;
  gp_Vec      nplan, d1gui, Nsurf1, tsurf1;
  gp_Vec      d1u1, d1v1;

  curv->D1(Sol(2), ptgui, d1gui);
  nplan = d1gui.Normalized();

  gp_Pnt2d pt2d(csurf->Value(Sol(1)));

  if (first)
  {
    surf1->D1(pt2d.X(), pt2d.Y(), pts1, d1u1, d1v1);
    pts2 = surf2->Value(Sol(3), Sol(4));
  }
  else
  {
    surf1->D1(Sol(3), Sol(4), pts1, d1u1, d1v1);
    pts2 = surf2->Value(pt2d.X(), pt2d.Y());
  }

  Nsurf1 = d1u1.Crossed(d1v1);
  tsurf1 = Nsurf1.Crossed(nplan);

  gp_Vec s1s2(pts1, pts2);
  double PScaInv = 1. / tsurf1.Dot(s1s2), temp;
  double Nordu1 = d1u1.Magnitude(), Nordv1 = d1v1.Magnitude();

  temp = 2. * (Nordu1 + Nordv1) * s1s2.Magnitude() + 2. * Nordu1 * Nordv1;

  Value(Sol, valsol);

  return std::abs(valsol(1)) < Tol && std::abs(valsol(2)) < Tol
         && std::abs(valsol(3)) < 2. * dist1 * Tol
         && std::abs(valsol(4)) < Tol * (1. + tgang) * std::abs(PScaInv) * temp;
}

bool BlendFunc_ChAsymInv::ComputeValues(const math_Vector& X, const int DegF, const int DegL)
{
  if (DegF > DegL)
    return false;

  gp_Vec   nplan, dnplan, d1gui, d2gui, d1u1, d1v1, d2u1, d2v1, d2uv1, d1u2, d1v2;
  gp_Vec   Nsurf1, tsurf1;
  gp_Pnt   pts1, pts2, ptgui;
  double   PScaInv, F4;
  double   Normg = 0.;
  gp_Pnt2d pt2d;
  gp_Vec2d v2d;

  if ((DegF == 0) && (DegL == 0))
  {
    curv->D1(X(2), ptgui, d1gui);
    nplan = d1gui.Normalized();

    if (choix % 2 != 0)
      nplan.Reverse();
    pt2d = csurf->Value(X(1));

    if (first)
    {
      surf1->D1(pt2d.X(), pt2d.Y(), pts1, d1u1, d1v1);
      pts2 = surf2->Value(X(3), X(4));
    }
    else
    {
      surf1->D1(X(3), X(4), pts1, d1u1, d1v1);
      pts2 = surf2->Value(pt2d.X(), pt2d.Y());
    }
  }
  else
  {
    curv->D2(X(2), ptgui, d1gui, d2gui);
    nplan  = d1gui.Normalized();
    Normg  = d1gui.Magnitude();
    dnplan = (d2gui - nplan.Dot(d2gui) * nplan) / Normg;

    if (choix % 2 != 0)
    {
      nplan.Reverse();
      dnplan.Reverse();
      Normg = -Normg;
    }

    csurf->D1(X(1), pt2d, v2d);

    if (first)
    {
      surf1->D2(pt2d.X(), pt2d.Y(), pts1, d1u1, d1v1, d2u1, d2v1, d2uv1);
      surf2->D1(X(3), X(4), pts2, d1u2, d1v2);
    }
    else
    {
      surf1->D2(X(3), X(4), pts1, d1u1, d1v1, d2u1, d2v1, d2uv1);
      surf2->D1(pt2d.X(), pt2d.Y(), pts2, d1u2, d1v2);
    }
  }

  gp_Vec nps1(ptgui, pts1), s1s2(pts1, pts2);
  Nsurf1  = d1u1.Crossed(d1v1);
  tsurf1  = Nsurf1.Crossed(nplan);
  PScaInv = 1. / s1s2.Dot(tsurf1);
  F4      = nplan.Dot(tsurf1.Crossed(s1s2)) * PScaInv;

  if (DegF == 0)
  {
    double Dist;
    Dist  = ptgui.XYZ().Dot(nplan.XYZ());
    FX(1) = pts1.XYZ().Dot(nplan.XYZ()) - Dist;
    FX(2) = pts2.XYZ().Dot(nplan.XYZ()) - Dist;
    FX(3) = dist1 * dist1 - nps1.SquareMagnitude();
    FX(4) = tgang - F4;
  }

  if (DegL == 1)
  {
    gp_Vec dwtsurf1, tempVec;
    double temp;
    gp_Vec nps2(ptgui, pts2);

    if (first)
    {
      gp_Vec dw1du1, dw1dv1, dw1csurf, dw1pts1;
      dw1pts1  = v2d.X() * d1u1 + v2d.Y() * d1v1;
      dw1du1   = v2d.X() * d2u1 + v2d.Y() * d2uv1;
      dw1dv1   = v2d.X() * d2uv1 + v2d.Y() * d2v1;
      dw1csurf = (dw1du1.Crossed(d1v1) + d1u1.Crossed(dw1dv1)).Crossed(nplan);
      dwtsurf1 = Nsurf1.Crossed(dnplan);

      DX(1, 1) = nplan.Dot(dw1pts1);
      DX(1, 2) = dnplan.Dot(nps1) - Normg;
      DX(1, 3) = 0.;
      DX(1, 4) = 0.;

      DX(2, 1) = 0.;
      DX(2, 2) = dnplan.Dot(nps2) - Normg;
      DX(2, 3) = nplan.Dot(d1u2);
      DX(2, 4) = nplan.Dot(d1v2);

      tempVec  = 2. * nps1;
      DX(3, 1) = -dw1pts1.Dot(tempVec);
      DX(3, 2) = d1gui.Dot(tempVec);
      DX(3, 3) = 0.;
      DX(3, 4) = 0.;

      temp = F4 * (dw1csurf.Dot(s1s2) - tsurf1.Dot(dw1pts1));
      temp += nplan.Dot(tsurf1.Crossed(dw1pts1) - dw1csurf.Crossed(s1s2));
      DX(4, 1) = PScaInv * temp;

      temp = F4 * dwtsurf1.Dot(s1s2);
      temp -= dnplan.Dot(tempVec) + nplan.Dot(dwtsurf1.Crossed(s1s2));
      DX(4, 2) = PScaInv * temp;
      temp     = F4 * tsurf1.Dot(d1u2) - nplan.Dot(tsurf1.Crossed(d1u2));
      DX(4, 3) = PScaInv * temp;

      temp     = F4 * tsurf1.Dot(d1v2) - nplan.Dot(tsurf1.Crossed(d1v2));
      DX(4, 4) = PScaInv * temp;
    }
    else
    {
      gp_Vec d1utsurf1, d1vtsurf1, dw2pts2;
      d1utsurf1 = (d2u1.Crossed(d1v1) + d1u1.Crossed(d2uv1)).Crossed(nplan);
      d1vtsurf1 = (d2uv1.Crossed(d1v1) + d1u1.Crossed(d2v1)).Crossed(nplan);
      dw2pts2   = v2d.X() * d1u2 + v2d.Y() * d1v2;
      dwtsurf1  = Nsurf1.Crossed(dnplan);

      DX(1, 1) = 0.;
      DX(1, 2) = dnplan.Dot(nps1) - Normg;
      DX(1, 3) = nplan.Dot(d1u1);
      DX(1, 4) = nplan.Dot(d1v1);

      DX(2, 1) = nplan.Dot(dw2pts2);
      DX(2, 2) = dnplan.Dot(nps2) - Normg;
      DX(2, 3) = 0.;
      DX(2, 4) = 0.;

      tempVec  = 2. * nps1;
      DX(3, 1) = 0.;
      DX(3, 2) = d1gui.Dot(tempVec);

      tempVec.Reverse();
      DX(3, 3) = d1u1.Dot(tempVec);
      DX(3, 4) = d1v1.Dot(tempVec);

      temp     = F4 * tsurf1.Dot(dw2pts2) - nplan.Dot(tsurf1.Crossed(dw2pts2));
      DX(4, 1) = PScaInv * temp;

      temp = F4 * dwtsurf1.Dot(s1s2);
      temp -= dnplan.Dot(tempVec) + nplan.Dot(dwtsurf1.Crossed(s1s2));
      DX(4, 2) = PScaInv * temp;

      temp = F4 * (d1utsurf1.Dot(s1s2) - tsurf1.Dot(d1u1));
      temp += nplan.Dot(tsurf1.Crossed(d1u1) - d1utsurf1.Crossed(s1s2));
      DX(4, 3) = PScaInv * temp;

      temp = F4 * (d1vtsurf1.Dot(s1s2) - tsurf1.Dot(d1v1));
      temp += nplan.Dot(tsurf1.Crossed(d1v1) - d1vtsurf1.Crossed(s1s2));
      DX(4, 4) = PScaInv * temp;
    }
  }

  return true;
}

bool BlendFunc_ChAsymInv::Value(const math_Vector& X, math_Vector& F)
{
  const bool Error = ComputeValues(X, 0, 0);
  F                = FX;
  return Error;
}

bool BlendFunc_ChAsymInv::Derivatives(const math_Vector& X, math_Matrix& D)
{
  const bool Error = ComputeValues(X, 1, 1);
  D                = DX;
  return Error;
}

bool BlendFunc_ChAsymInv::Values(const math_Vector& X, math_Vector& F, math_Matrix& D)
{
  const bool Error = ComputeValues(X, 0, 1);
  F                = FX;
  D                = DX;
  return Error;
}
