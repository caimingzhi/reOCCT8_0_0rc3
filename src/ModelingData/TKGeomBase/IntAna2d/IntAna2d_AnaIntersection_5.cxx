

#include <gp_Circ2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_Conic.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <IntAna2d_Outils.hpp>
#include <StdFail_NotDone.hpp>

void IntAna2d_AnaIntersection::Perform(const gp_Circ2d& Circle, const IntAna2d_Conic& Conic)
{
  bool   CIsDirect = Circle.IsDirect();
  double A, B, C, D, E, F;
  double pcc, pss, p2sc, pc, ps, pcte;
  double radius    = Circle.Radius();
  double radius_P2 = radius * radius;
  int    i;
  double tx, ty, S;

  done = false;
  nbp  = 0;
  para = false;
  empt = false;
  iden = false;

  gp_Ax2d Axe_rep(Circle.XAxis());

  Conic.Coefficients(A, B, C, D, E, F);
  Conic.NewCoefficients(A, B, C, D, E, F, Axe_rep);

  pss  = B * radius_P2;
  pcc  = A * radius_P2 - pss;
  p2sc = C * radius_P2;
  pc   = 2.0 * D * radius;
  ps   = 2.0 * E * radius;
  pcte = F + pss;

  math_TrigonometricFunctionRoots Sol(pcc, p2sc, pc, ps, pcte, 0.0, 2.0 * M_PI);

  if (!Sol.IsDone())
  {
    std::cout << "\n\nmath_TrigonometricFunctionRoots -> NotDone\n\n" << std::endl;
    done = false;
    return;
  }
  else
  {
    if (Sol.InfiniteRoots())
    {
      iden = true;
      done = true;
      return;
    }
    nbp = Sol.NbSolutions();
    for (i = 1; i <= nbp; i++)
    {
      S  = Sol.Value(i);
      tx = radius * std::cos(S);
      ty = radius * std::sin(S);
      Coord_Ancien_Repere(tx, ty, Axe_rep);
      if (!CIsDirect)
        S = M_PI + M_PI - S;
      lpnt[i - 1].SetValue(tx, ty, S);
    }
    Traitement_Points_Confondus(nbp, lpnt);
  }
  done = true;
}
