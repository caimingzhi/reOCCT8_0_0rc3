

#include <gp_Circ2d.hpp>
#include <gp_Parab2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_Conic.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <IntAna2d_Outils.hpp>
#include <StdFail_NotDone.hpp>

void IntAna2d_AnaIntersection::Perform(const gp_Parab2d& P, const IntAna2d_Conic& Conic)
{
  bool    PIsDirect = P.IsDirect();
  double  A, B, C, D, E, F;
  double  px4, px3, px2, px1, px0;
  int     i;
  double  tx, ty, S;
  double  un_sur_2p = 0.5 / (P.Parameter());
  gp_Ax2d Axe_rep(P.MirrorAxis());

  done = false;
  nbp  = 0;
  para = false;
  empt = false;
  iden = false;

  Conic.Coefficients(A, B, C, D, E, F);
  Conic.NewCoefficients(A, B, C, D, E, F, Axe_rep);

  px0 = F;
  px1 = E + E;
  px2 = B + un_sur_2p * (D + D);
  px3 = (C + C) * un_sur_2p;
  px4 = A * (un_sur_2p * un_sur_2p);

  MyDirectPolynomialRoots Sol(px4, px3, px2, px1, px0);

  if (!Sol.IsDone())
  {
    done = false;
  }
  else
  {
    if (Sol.InfiniteRoots())
    {
      iden = true;
      done = true;
    }
    nbp = Sol.NbSolutions();
    for (i = 1; i <= nbp; i++)
    {
      S  = Sol.Value(i);
      tx = un_sur_2p * S * S;
      ty = S;
      Coord_Ancien_Repere(tx, ty, Axe_rep);
      if (!PIsDirect)
        S = -S;
      lpnt[i - 1].SetValue(tx, ty, S);
    }
    Traitement_Points_Confondus(nbp, lpnt);
  }
  done = true;
}
