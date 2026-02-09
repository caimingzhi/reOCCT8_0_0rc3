

#include <gp_Circ2d.hpp>
#include <gp_Hypr2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_Conic.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <IntAna2d_Outils.hpp>
#include <StdFail_NotDone.hpp>

void IntAna2d_AnaIntersection::Perform(const gp_Hypr2d& H, const IntAna2d_Conic& Conic)
{
  bool   HIsDirect = H.IsDirect();
  double A, B, C, D, E, F;
  double px0, px1, px2, px3, px4;
  double minor_radius = H.MinorRadius();
  double major_radius = H.MajorRadius();
  int    i;
  double tx, ty, S;

  done = false;
  nbp  = 0;
  para = false;
  iden = false;
  empt = false;

  gp_Ax2d Axe_rep(H.XAxis());
  Conic.Coefficients(A, B, C, D, E, F);
  Conic.NewCoefficients(A, B, C, D, E, F, Axe_rep);

  double A_major_radiusP2       = A * major_radius * major_radius;
  double B_minor_radiusP2       = B * minor_radius * minor_radius;
  double C_2_major_minor_radius = C * 2.0 * major_radius * minor_radius;

  px0 = A_major_radiusP2 - C_2_major_minor_radius + B_minor_radiusP2;
  px1 = 4.0 * (D * major_radius - E * minor_radius);
  px2 = 2.0 * (A_major_radiusP2 + 2.0 * F - B_minor_radiusP2);
  px3 = 4.0 * (D * major_radius + E * minor_radius);
  px4 = A_major_radiusP2 + C_2_major_minor_radius + B_minor_radiusP2;

  MyDirectPolynomialRoots Sol(px4, px3, px2, px1, px0);

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

    nbp                = Sol.NbSolutions();
    int nb_sol_valides = 0;
    for (i = 1; i <= nbp; i++)
    {
      S = Sol.Value(i);
      if (S > RealEpsilon())
      {
        tx = 0.5 * major_radius * (S + 1 / S);
        ty = 0.5 * minor_radius * (S - 1 / S);

        nb_sol_valides++;
        Coord_Ancien_Repere(tx, ty, Axe_rep);
        S = std::log(S);
        if (!HIsDirect)
          S = -S;
        lpnt[nb_sol_valides - 1].SetValue(tx, ty, S);
      }
    }
    nbp = nb_sol_valides;
    Traitement_Points_Confondus(nbp, lpnt);
  }
  done = true;
}
