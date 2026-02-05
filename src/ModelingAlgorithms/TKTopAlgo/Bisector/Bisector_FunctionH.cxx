#include <Bisector_FunctionH.hpp>
#include <Geom2d_Curve.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

//=================================================================================================

Bisector_FunctionH::Bisector_FunctionH(const occ::handle<Geom2d_Curve>& C2,
                                       const gp_Pnt2d&                  P1,
                                       const gp_Vec2d&                  T1)
    : p1(P1),
      t1(T1)
{
  t1.Normalize();
  curve2 = C2;
}

//=============================================================================
// function : Value
// purpose :
//                F = P1P2.(||T2||T1 + T2)
//=============================================================================
bool Bisector_FunctionH::Value(const double X, double& F)
{
  gp_Pnt2d P2; // point sur C2.
  gp_Vec2d T2; // tangente a C2 en V.
  curve2->D1(X, P2, T2);

  double NormT2 = T2.Magnitude();
  double Ax     = NormT2 * t1.X() - T2.X();
  double Ay     = NormT2 * t1.Y() - T2.Y();

  F = (p1.X() - P2.X()) * Ax + (p1.Y() - P2.Y()) * Ay;

  return true;
}

//=================================================================================================

bool Bisector_FunctionH::Derivative(const double X, double& D)
{
  double F;
  return Values(X, F, D);
}

//=================================================================================================

bool Bisector_FunctionH::Values(const double X, double& F, double& D)
{
  gp_Pnt2d P2;  // point sur C2.
  gp_Vec2d T2;  // tangente a C2 en V.
  gp_Vec2d T2v; // derivee seconde a C2 en V.

  curve2->D2(X, P2, T2, T2v);

  double NormT2 = T2.Magnitude();
  double Ax     = NormT2 * t1.X() - T2.X();
  double Ay     = NormT2 * t1.Y() - T2.Y();

  F = (p1.X() - P2.X()) * Ax + (p1.Y() - P2.Y()) * Ay;

  double Scal = T2.Dot(T2v) / NormT2;
  double dAx  = Scal * t1.X() - T2v.X();
  double dAy  = Scal * t1.Y() - T2v.Y();

  D = -T2.X() * Ax - T2.Y() * Ay + (p1.X() - P2.X()) * dAx + (p1.Y() - P2.Y()) * dAy;

  return true;
}
