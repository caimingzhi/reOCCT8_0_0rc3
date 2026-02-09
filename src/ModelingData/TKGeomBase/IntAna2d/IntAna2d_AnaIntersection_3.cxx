

#include <ElCLib.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Lin2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_Conic.hpp>
#include <IntAna2d_IntPoint.hpp>

void IntAna2d_AnaIntersection::Perform(const gp_Lin2d& L, const gp_Circ2d& C)
{

  done = false;

  iden = false;
  para = false;

  double   A, B, C0, d;
  gp_Pnt2d aP2D, aP2D1, aP2D2;

  L.Coefficients(A, B, C0);
  d = A * C.Location().X() + B * C.Location().Y() + C0;

  if (std::abs(d) - C.Radius() > Epsilon(C.Radius()))
  {
    empt = true;
    nbp  = 0;
  }
  else
  {
    empt = false;

    if (std::abs(std::abs(d) - C.Radius()) <= Epsilon(C.Radius()))
    {

      double u, XS, YS, ang;

      nbp = 1;
      XS  = C.Location().X() - d * A;
      YS  = C.Location().Y() - d * B;

      aP2D.SetCoord(XS, YS);
      u   = ElCLib::Parameter(L, aP2D);
      ang = ElCLib::Parameter(C, aP2D);

      lpnt[0].SetValue(XS, YS, u, ang);
    }
    else
    {

      double h, XS1, YS1, XS2, YS2, ang1, ang2, u1, u2;

      nbp = 2;
      h   = std::sqrt(C.Radius() * C.Radius() - d * d);

      XS1 = C.Location().X() - d * A - h * B;
      YS1 = C.Location().Y() - d * B + h * A;
      XS2 = C.Location().X() - d * A + h * B;
      YS2 = C.Location().Y() - d * B - h * A;

      aP2D1.SetCoord(XS1, YS1);
      aP2D2.SetCoord(XS2, YS2);
      u1   = ElCLib::Parameter(L, aP2D1);
      u2   = ElCLib::Parameter(L, aP2D2);
      ang1 = ElCLib::Parameter(C, aP2D1);
      ang2 = ElCLib::Parameter(C, aP2D2);

      lpnt[0].SetValue(XS1, YS1, u1, ang1);
      lpnt[1].SetValue(XS2, YS2, u2, ang2);
    }
  }
  done = true;
}
