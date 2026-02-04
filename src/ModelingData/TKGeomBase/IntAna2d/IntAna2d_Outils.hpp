#pragma once


#include <math_TrigonometricFunctionRoots.hpp>
#include <IntAna2d_IntPoint.hpp>

class MyDirectPolynomialRoots
{
public:
  MyDirectPolynomialRoots(const double A4,
                          const double A3,
                          const double A2,
                          const double A1,
                          const double A0);

  MyDirectPolynomialRoots(const double A2, const double A1, const double A0);

  int NbSolutions() const { return (nbsol); }

  double Value(const int i) const { return (sol[i - 1]); }

  double IsDone() const { return (nbsol > -1); }

  bool InfiniteRoots() const { return (same); }

private:
  double sol[16];
  double val[16];
  int    nbsol;
  bool   same;
};

bool Points_Confondus(const double xa, const double ya, const double xb, const double yb);

void Traitement_Points_Confondus(int& nb_pts, IntAna2d_IntPoint* pts);

void Coord_Ancien_Repere(double& Ancien_X, double& Ancien_Y, const gp_Ax2d& Axe_Nouveau_Repere);

