

#include <gp_Circ2d.hpp>
#include <gp_Lin2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_Conic.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <StdFail_NotDone.hpp>

void IntAna2d_AnaIntersection::Perform(const gp_Lin2d& L1, const gp_Lin2d& L2)
{

  done = false;

  double A1, B1, C1;
  double A2, B2, C2;
  L1.Coefficients(A1, B1, C1);
  L2.Coefficients(A2, B2, C2);

  double al1, be1, ga1;
  double al2, be2, ga2;

  double Det = std::max(std::abs(A1), std::max(std::abs(A2), std::max(std::abs(B1), std::abs(B2))));

  if (std::abs(A1) == Det)
  {
    al1 = A1;
    be1 = B1;
    ga1 = C1;
    al2 = A2;
    be2 = B2;
    ga2 = C2;
  }
  else if (std::abs(B1) == Det)
  {
    al1 = B1;
    be1 = A1;
    ga1 = C1;
    al2 = B2;
    be2 = A2;
    ga2 = C2;
  }
  else if (std::abs(A2) == Det)
  {
    al1 = A2;
    be1 = B2;
    ga1 = C2;
    al2 = A1;
    be2 = B1;
    ga2 = C1;
  }
  else
  {
    al1 = B2;
    be1 = A2;
    ga1 = C2;
    al2 = B1;
    be2 = A1;
    ga2 = C1;
  }

  double rap   = al2 / al1;
  double denom = be2 - rap * be1;

  if (std::abs(denom) <= RealEpsilon())
  {
    para = true;
    nbp  = 0;
    if (std::abs(ga2 - rap * ga1) <= RealEpsilon())
    {
      iden = true;
      empt = false;
    }
    else
    {
      iden = false;
      empt = true;
    }
  }
  else
  {
    para      = false;
    iden      = false;
    empt      = false;
    nbp       = 1;
    double XS = (be1 * ga2 / al1 - be2 * ga1 / al1) / denom;
    double YS = (rap * ga1 - ga2) / denom;

    if (((std::abs(A1) != Det) && (std::abs(B1) == Det))
        || ((std::abs(A1) != Det) && (std::abs(B1) != Det) && (std::abs(A2) != Det)))
    {
      double temp = XS;
      XS          = YS;
      YS          = temp;
    }

    double La, Mu;
    if (std::abs(A1) >= std::abs(B1))
    {
      La = (YS - L1.Location().Y()) / A1;
    }
    else
    {
      La = (L1.Location().X() - XS) / B1;
    }
    if (std::abs(A2) >= std::abs(B2))
    {
      Mu = (YS - L2.Location().Y()) / A2;
    }
    else
    {
      Mu = (L2.Location().X() - XS) / B2;
    }
    lpnt[0].SetValue(XS, YS, La, Mu);
  }
  done = true;
}
