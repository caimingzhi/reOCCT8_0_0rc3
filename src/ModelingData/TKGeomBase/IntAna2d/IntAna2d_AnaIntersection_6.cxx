

#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_Conic.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <IntAna2d_Outils.hpp>
#include <StdFail_NotDone.hpp>

void IntAna2d_AnaIntersection::Perform(const gp_Elips2d& Elips, const IntAna2d_Conic& Conic)
{
  bool   EIsDirect = Elips.IsDirect();
  double A, B, C, D, E, F;
  double pcte, ps, pc, p2sc, pcc, pss;
  double minor_radius = Elips.MinorRadius();
  double major_radius = Elips.MajorRadius();
  int    i;
  double tx, ty, S;

  done = false;
  nbp  = 0;
  para = false;
  iden = false;
  empt = false;

  gp_Ax2d Axe_rep(Elips.XAxis());

  Conic.Coefficients(A, B, C, D, E, F);
  Conic.NewCoefficients(A, B, C, D, E, F, Axe_rep);

  pss  = B * minor_radius * minor_radius;
  pcc  = A * major_radius * major_radius - pss;
  p2sc = C * major_radius * minor_radius;
  pc   = 2.0 * D * major_radius;
  ps   = 2.0 * E * minor_radius;
  pcte = F + pss;

  math_TrigonometricFunctionRoots Sol(pcc, p2sc, pc, ps, pcte, 0.0, 2.0 * M_PI);

  if (!Sol.IsDone())
  {
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
      tx = major_radius * std::cos(S);
      ty = minor_radius * std::sin(S);
      Coord_Ancien_Repere(tx, ty, Axe_rep);
      if (!EIsDirect)
        S = M_PI + M_PI - S;
      lpnt[i - 1].SetValue(tx, ty, S);
    }
    Traitement_Points_Confondus(nbp, lpnt);
  }
  done = true;
}
