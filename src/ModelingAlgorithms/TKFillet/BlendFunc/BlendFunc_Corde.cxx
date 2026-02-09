#include <BlendFunc.hpp>
#include <BlendFunc_Corde.hpp>
#include <ElCLib.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <math_Gauss.hpp>
#include <math_Matrix.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_NotImplemented.hpp>

BlendFunc_Corde::BlendFunc_Corde(const occ::handle<Adaptor3d_Surface>& S,
                                 const occ::handle<Adaptor3d_Curve>&   CG)
    : surf(S),
      guide(CG),
      dis(0.0),
      normtg(0.0),
      theD(0.0),
      istangent(false)
{
}

void BlendFunc_Corde::SetDist(const double Dist)
{
  dis = Dist;
}

void BlendFunc_Corde::SetParam(const double Param)
{
  guide->D2(Param, ptgui, d1gui, d2gui);
  normtg = d1gui.Magnitude();
  nplan  = d1gui.Normalized();
  theD   = -(nplan.XYZ().Dot(ptgui.XYZ()));
}

bool BlendFunc_Corde::Value(const math_Vector& X, math_Vector& F)
{
  gp_Vec d1u, d1v;
  surf->D1(X(1), X(2), pts, d1u, d1v);

  F(1) = nplan.XYZ().Dot(pts.XYZ()) + theD;
  const gp_Vec vref(ptgui, pts);
  F(2) = vref.SquareMagnitude() - dis * dis;

  return true;
}

bool BlendFunc_Corde::Derivatives(const math_Vector& X, math_Matrix& D)
{
  gp_Vec d1u, d1v;
  surf->D1(X(1), X(2), pts, d1u, d1v);

  D(1, 1) = nplan.Dot(d1u);
  D(1, 2) = nplan.Dot(d1v);
  D(2, 1) = 2. * gp_Vec(ptgui, pts).Dot(d1u);
  D(2, 2) = 2. * gp_Vec(ptgui, pts).Dot(d1v);

  return true;
}

const gp_Pnt& BlendFunc_Corde::PointOnS() const
{
  return pts;
}

const gp_Pnt& BlendFunc_Corde::PointOnGuide() const
{
  return ptgui;
}

const gp_Vec& BlendFunc_Corde::NPlan() const
{
  return nplan;
}

bool BlendFunc_Corde::IsTangencyPoint() const
{
  return istangent;
}

const gp_Vec& BlendFunc_Corde::TangentOnS() const
{
  if (istangent)
    throw Standard_DomainError("BlendFunc_Corde::TangentOnS");
  return tgs;
}

const gp_Vec2d& BlendFunc_Corde::Tangent2dOnS() const
{
  if (istangent)
    throw Standard_DomainError("BlendFunc_Corde::Tangent2dOnS");
  return tg2d;
}

void BlendFunc_Corde::DerFguide(const math_Vector& Sol, gp_Vec2d& DerF)
{
  gp_Vec d1u, d1v;
  surf->D1(Sol(1), Sol(2), pts, d1u, d1v);

  gp_Vec dnplan;
  dnplan.SetLinearForm(1. / normtg, d2gui, -1. / normtg * (nplan.Dot(d2gui)), nplan);

  const gp_Vec temp(pts.XYZ() - ptgui.XYZ());

  DerF.SetX(dnplan.Dot(temp) - nplan.Dot(d1gui));
  DerF.SetY(-2. * d1gui.Dot(temp));
}

bool BlendFunc_Corde::IsSolution(const math_Vector& Sol, const double Tol)
{
  math_Vector secmember(1, 2), valsol(1, 2);
  math_Matrix gradsol(1, 2, 1, 2);

  gp_Vec dnplan, temp, d1u, d1v;

  Value(Sol, valsol);
  Derivatives(Sol, gradsol);
  if (std::abs(valsol(1)) <= Tol && std::abs(valsol(2)) <= Tol * Tol)
  {

    surf->D1(Sol(1), Sol(2), pts, d1u, d1v);
    dnplan.SetLinearForm(1. / normtg, d2gui, -1. / normtg * (nplan.Dot(d2gui)), nplan);

    temp.SetXYZ(pts.XYZ() - ptgui.XYZ());

    secmember(1) = nplan.Dot(d1gui) - dnplan.Dot(temp);
    secmember(2) = 2. * d1gui.Dot(temp);

    math_Gauss Resol(gradsol);
    if (Resol.IsDone())
    {
      Resol.Solve(secmember);
      tgs.SetLinearForm(secmember(1), d1u, secmember(2), d1v);
      tg2d.SetCoord(secmember(1), secmember(2));
      istangent = false;
    }
    else
    {
      istangent = true;
    }
    return true;
  }

  return false;
}
