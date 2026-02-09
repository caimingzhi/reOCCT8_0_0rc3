

#include <gp_Circ2d.hpp>
#include <gp_Lin2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_Conic.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <IntAna2d_Outils.hpp>
#include <StdFail_NotDone.hpp>

void IntAna2d_AnaIntersection::Perform(const gp_Lin2d& L, const IntAna2d_Conic& Conic)
{
  double A, B, C, D, E, F;
  double px0, px1, px2;
  double DR_A, DR_B, DR_C, X0, Y0;
  int    i;
  double tx, ty, S;

  done = false;
  nbp  = 0;
  para = false;
  iden = false;

  Conic.Coefficients(A, B, C, D, E, F);
  L.Coefficients(DR_A, DR_B, DR_C);
  X0 = L.Location().X();
  Y0 = L.Location().Y();

  px0 = F + X0 * (D + D + A * X0 + 2.0 * C * Y0) + Y0 * (E + E + B * Y0);
  px1 = 2.0 * (E * DR_A - D * DR_B + X0 * (C * DR_A - A * DR_B) + Y0 * (B * DR_A - C * DR_B));
  px2 = DR_A * (B * DR_A - 2.0 * C * DR_B) + A * (DR_B * DR_B);

  MyDirectPolynomialRoots Sol(px2, px1, px0);

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
      tx = X0 - S * DR_B;
      ty = Y0 + S * DR_A;
      lpnt[i - 1].SetValue(tx, ty, S);
    }
    Traitement_Points_Confondus(nbp, lpnt);
  }
  done = true;
}
