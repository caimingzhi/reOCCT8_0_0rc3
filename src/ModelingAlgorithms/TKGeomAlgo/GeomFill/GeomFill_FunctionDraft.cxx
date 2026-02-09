#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomFill_FunctionDraft.hpp>
#include <GeomFill_Tensor.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <math_Matrix.hpp>

GeomFill_FunctionDraft::GeomFill_FunctionDraft(const occ::handle<Adaptor3d_Surface>& S,
                                               const occ::handle<Adaptor3d_Curve>&   C)
{
  TheCurve   = C;
  TheSurface = S;
}

int GeomFill_FunctionDraft::NbVariables() const
{
  return 3;
}

int GeomFill_FunctionDraft::NbEquations() const
{
  return 3;
}

bool GeomFill_FunctionDraft::Value(const math_Vector& X, math_Vector& F)
{
  gp_Pnt P, P1;
  TheCurve->D0(X(1), P);
  TheSurface->D0(X(2), X(3), P1);

  F(1) = P.Coord(1) - P1.Coord(1);
  F(2) = P.Coord(2) - P1.Coord(2);
  F(3) = P.Coord(3) - P1.Coord(3);

  return true;
}

bool GeomFill_FunctionDraft::Derivatives(const math_Vector& X, math_Matrix& D)
{
  int    i;
  gp_Pnt P, P1;
  gp_Vec DP, DP1U, DP1V;
  TheCurve->D1(X(1), P, DP);
  TheSurface->D1(X(2), X(3), P1, DP1U, DP1V);

  for (i = 1; i <= 3; i++)
  {
    D(i, 1) = DP.Coord(i);
    D(i, 2) = -DP1U.Coord(i);
    D(i, 3) = -DP1V.Coord(i);
  }
  return true;
}

bool GeomFill_FunctionDraft::Values(const math_Vector& X, math_Vector& F, math_Matrix& D)
{
  int    i;
  gp_Pnt P, P1;
  gp_Vec DP, DP1U, DP1V;
  TheCurve->D1(X(1), P, DP);
  TheSurface->D1(X(2), X(3), P1, DP1U, DP1V);

  for (i = 1; i <= 3; i++)
  {
    F(i) = P.Coord(i) - P1.Coord(i);

    D(i, 1) = DP.Coord(i);
    D(i, 2) = -DP1U.Coord(i);
    D(i, 3) = -DP1V.Coord(i);
  }

  return true;
}

bool GeomFill_FunctionDraft::DerivT(const occ::handle<Adaptor3d_Curve>& C,
                                    const double                        Param,
                                    const double                        W,
                                    const gp_Vec&                       dN,
                                    const double                        teta,
                                    math_Vector&                        F)

{
  gp_Pnt P;
  gp_Vec DP;

  C->D1(Param, P, DP);

  F(1) = DP.Coord(1) + W * dN.Coord(1) * std::sin(teta);
  F(2) = DP.Coord(2) + W * dN.Coord(2) * std::sin(teta);
  F(3) = DP.Coord(3) + W * dN.Coord(3) * std::sin(teta);

  return true;
}

bool GeomFill_FunctionDraft::Deriv2T(const occ::handle<Adaptor3d_Curve>& C,
                                     const double                        Param,
                                     const double                        W,
                                     const gp_Vec&                       d2N,
                                     const double                        teta,
                                     math_Vector&                        F)
{
  gp_Pnt P;
  gp_Vec DP, D2P;

  C->D2(Param, P, DP, D2P);

  F(1) = D2P.Coord(1) + W * d2N.Coord(1) * std::sin(teta);
  F(2) = D2P.Coord(2) + W * d2N.Coord(2) * std::sin(teta);
  F(3) = D2P.Coord(3) + W * d2N.Coord(3) * std::sin(teta);

  return true;
}

bool GeomFill_FunctionDraft::DerivTX(const gp_Vec& dN, const double teta, math_Matrix& D)
{

  int i;
  for (i = 1; i <= 3; i++)
  {
    D(i, 1) = dN.Coord(i) * std::sin(teta);
    D(i, 2) = 0.;
    D(i, 3) = 0.;
  }

  return true;
}

bool GeomFill_FunctionDraft::Deriv2X(const math_Vector& X, GeomFill_Tensor& T)
{
  gp_Pnt P;
  gp_Vec DPu, DPv;
  gp_Vec D2Pu, D2Pv, D2Puv;
  int    i;

  TheSurface->D2(X(2), X(3), P, DPu, DPv, D2Pu, D2Pv, D2Puv);

  T.Init(0.);

  for (i = 1; i <= 3; i++)
  {
    T(i, 2, 2) = -D2Pu.Coord(i);
    T(i, 3, 2) = T(i, 2, 3) = -D2Puv.Coord(i);
    T(i, 3, 3)              = -D2Pv.Coord(i);
  }

  return true;
}
