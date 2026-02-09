#include <Adaptor2d_Curve2d.hpp>
#include <BlendFunc.hpp>
#include <BlendFunc_ConstThroatWithPenetrationInv.hpp>
#include <math_Matrix.hpp>

BlendFunc_ConstThroatWithPenetrationInv::BlendFunc_ConstThroatWithPenetrationInv(
  const occ::handle<Adaptor3d_Surface>& S1,
  const occ::handle<Adaptor3d_Surface>& S2,
  const occ::handle<Adaptor3d_Curve>&   C)
    : BlendFunc_ConstThroatInv(S1, S2, C)
{
}

bool BlendFunc_ConstThroatWithPenetrationInv::IsSolution(const math_Vector& Sol, const double Tol)
{
  math_Vector valsol(1, 4);
  Value(Sol, valsol);

  return std::abs(valsol(1)) <= Tol && std::abs(valsol(2)) <= Tol
         && std::abs(valsol(3)) <= Tol * Tol && std::abs(valsol(4)) <= Tol;
}

bool BlendFunc_ConstThroatWithPenetrationInv::Value(const math_Vector& X, math_Vector& F)
{
  gp_Pnt2d p2d;
  gp_Vec2d v2d;
  csurf->D1(X(1), p2d, v2d);
  param = X(2);
  curv->D2(param, ptgui, d1gui, d2gui);
  normtg = d1gui.Magnitude();
  nplan  = d1gui.Normalized();
  theD   = -(nplan.XYZ().Dot(ptgui.XYZ()));

  math_Vector XX(1, 4);

  if (first)
  {
    XX(1) = p2d.X();
    XX(2) = p2d.Y();
    XX(3) = X(3);
    XX(4) = X(4);
  }

  else
  {
    XX(1) = X(3);
    XX(2) = X(4);
    XX(3) = p2d.X();
    XX(4) = p2d.Y();
  }

  surf1->D0(XX(1), XX(2), pts1);
  surf2->D0(XX(3), XX(4), pts2);

  F(1) = nplan.XYZ().Dot(pts1.XYZ()) + theD;
  F(2) = nplan.XYZ().Dot(pts2.XYZ()) + theD;

  const gp_Vec vref(ptgui, pts1);

  F(3) = vref.SquareMagnitude() - Throat * Throat;

  const gp_Vec vec12(pts1, pts2);

  F(4) = vref.Dot(vec12);

  return true;
}

bool BlendFunc_ConstThroatWithPenetrationInv::Derivatives(const math_Vector& X, math_Matrix& D)
{

  gp_Pnt2d p2d;
  gp_Vec2d v2d;

  gp_Vec      dnplan, temp, temp1, temp2, temp3;
  math_Vector XX(1, 4);

  csurf->D1(X(1), p2d, v2d);

  param = X(2);
  curv->D2(param, ptgui, d1gui, d2gui);
  normtg = d1gui.Magnitude();
  nplan  = d1gui.Normalized();
  theD   = -(nplan.XYZ().Dot(ptgui.XYZ()));

  dnplan.SetLinearForm(1. / normtg, d2gui, -1. / normtg * (nplan.Dot(d2gui)), nplan);

  temp1.SetXYZ(pts1.XYZ() - ptgui.XYZ());
  temp2.SetXYZ(pts2.XYZ() - ptgui.XYZ());
  temp3.SetXYZ(pts2.XYZ() - pts1.XYZ());

  if (first)
  {
    XX(1) = p2d.X();
    XX(2) = p2d.Y();
    XX(3) = X(3);
    XX(4) = X(4);
  }
  else
  {
    XX(1) = X(3);
    XX(2) = X(4);
    XX(3) = p2d.X();
    XX(4) = p2d.Y();
  }

  surf1->D1(XX(1), XX(2), pts1, d1u1, d1v1);
  surf2->D1(XX(3), XX(4), pts2, d1u2, d1v2);

  if (first)
  {

    temp.SetLinearForm(v2d.X(), d1u1, v2d.Y(), d1v1);

    D(1, 1) = nplan.Dot(temp);
    D(2, 1) = 0.;

    D(3, 1) = 2 * temp1.Dot(temp);

    D(4, 1) = temp.Dot(temp3) - temp.Dot(temp1);

    D(1, 3) = 0.;
    D(1, 4) = 0.;
    D(2, 3) = nplan.Dot(d1u2);
    D(2, 4) = nplan.Dot(d1v2);
    D(3, 3) = 0.;
    D(3, 4) = 0.;

    D(4, 3) = temp1.Dot(d1u2);

    D(4, 4) = temp1.Dot(d1v2);
  }
  else
  {

    temp.SetLinearForm(v2d.X(), d1u2, v2d.Y(), d1v2);

    D(1, 1) = 0.;
    D(2, 1) = nplan.Dot(temp);
    D(3, 1) = 0.;

    D(4, 1) = temp1.Dot(temp);

    D(1, 3) = nplan.Dot(d1u1);
    D(1, 4) = nplan.Dot(d1v1);
    D(2, 3) = 0.;
    D(2, 4) = 0.;

    D(3, 3) = 2. * temp1.Dot(d1u1);

    D(3, 4) = 2. * temp1.Dot(d1v1);

    D(4, 3) = d1u1.Dot(temp3) - d1u1.Dot(temp1);
    D(4, 4) = d1v1.Dot(temp3) - d1v1.Dot(temp1);
  }

  D(1, 2) = dnplan.Dot(temp1) - nplan.Dot(d1gui);
  D(2, 2) = dnplan.Dot(temp2) - nplan.Dot(d1gui);

  D(3, 2) = -2. * d1gui.Dot(temp1);

  D(4, 2) = -d1gui.Dot(temp3);

  return true;
}
