

#include <gp_Circ2d.hpp>
#include <gp_Vec2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_Conic.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <StdFail_NotDone.hpp>

void IntAna2d_AnaIntersection::Perform(const gp_Circ2d& C1, const gp_Circ2d& C2)
{

  done       = false;
  double d   = C1.Location().Distance(C2.Location());
  double R1  = C1.Radius();
  double R2  = C2.Radius();
  double sum = R1 + R2;
  double dif = std::abs(R1 - R2);

  if (d <= RealEpsilon())
  {
    para = true;
    nbp  = 0;
    if (dif <= RealEpsilon())
    {
      empt = false;
      iden = true;
    }
    else
    {
      empt = true;
      iden = false;
    }
  }
  else if ((d - sum) > Epsilon(sum))
  {

    empt = true;
    para = false;
    iden = false;
    nbp  = 0;
  }
  else if (std::abs(d - sum) <= Epsilon(sum))
  {
    empt = false;
    para = false;
    iden = false;
    nbp  = 1;
    gp_Vec2d ax(C1.Location(), C2.Location());
    gp_Vec2d Ox1(C1.XAxis().Direction());
    gp_Vec2d Ox2(C2.XAxis().Direction());

    double XS   = (C1.Location().X() * R2 + C2.Location().X() * R1) / sum;
    double YS   = (C1.Location().Y() * R2 + C2.Location().Y() * R1) / sum;
    double ang1 = Ox1.Angle(ax);
    double ang2 = Ox2.Angle(ax) + M_PI;
    if (ang1 < 0)
    {
      ang1 = 2 * M_PI + ang1;
    }
    lpnt[0].SetValue(XS, YS, ang1, ang2);
  }
  else if (((sum - d) > Epsilon(sum)) && ((d - dif) > Epsilon(d + dif)))
  {
    empt = false;
    para = false;
    iden = false;
    nbp  = 2;
    gp_Vec2d ax(C1.Location(), C2.Location());
    gp_Vec2d Ox1(C1.XAxis().Direction());
    gp_Vec2d Ox2(C2.XAxis().Direction());
    double   ref1 = Ox1.Angle(ax);
    double   ref2 = Ox2.Angle(ax);

    double l1 = (d * d + R1 * R1 - R2 * R2) / (2.0 * d);
    if (R1 * R1 - l1 * l1 < 0.)
    {
      l1 = (l1 > 0 ? R1 : -R1);
    }
    double h = std::sqrt(R1 * R1 - l1 * l1);

    double XS1 = C1.Location().X() + l1 * ax.X() / d - h * ax.Y() / d;
    double YS1 = C1.Location().Y() + l1 * ax.Y() / d + h * ax.X() / d;

    double XS2 = C1.Location().X() + l1 * ax.X() / d + h * ax.Y() / d;
    double YS2 = C1.Location().Y() + l1 * ax.Y() / d - h * ax.X() / d;

    double sint1 = h / R1;
    double cost1 = l1 / R1;

    double sint2 = h / R2;
    double cost2 = (l1 - d) / R2;

    double ang1, ang2;

    if (std::abs(cost1) <= 0.707)
    {
      ang1 = std::acos(cost1);
    }
    else
    {
      ang1 = std::asin(sint1);
      if (cost1 < 0.0)
      {
        ang1 = M_PI - ang1;
      }
    }
    if (std::abs(cost2) <= 0.707)
    {
      ang2 = std::acos(cost2);
    }
    else
    {
      ang2 = std::asin(sint2);
      if (cost2 < 0.0)
      {
        ang2 = M_PI - ang2;
      }
    }
    double ang11 = ref1 + ang1;
    double ang21 = ref2 + ang2;
    double ang12 = ref1 - ang1;
    double ang22 = ref2 - ang2;
    if (ang11 < 0.)
    {
      ang11 = 2 * M_PI + ang11;
    }
    else if (ang11 >= 2 * M_PI)
    {
      ang11 = ang11 - 2 * M_PI;
    }
    if (ang21 < 0.)
    {
      ang21 = 2 * M_PI + ang21;
    }
    else if (ang21 >= 2 * M_PI)
    {
      ang21 = ang21 - 2 * M_PI;
    }
    if (ang12 < 0.)
    {
      ang12 = 2 * M_PI + ang12;
    }
    else if (ang12 >= 2 * M_PI)
    {
      ang12 = ang12 - 2 * M_PI;
    }
    if (ang22 < 0.)
    {
      ang22 = 2 * M_PI + ang22;
    }
    else if (ang22 >= 2 * M_PI)
    {
      ang22 = ang22 - 2 * M_PI;
    }
    lpnt[0].SetValue(XS1, YS1, ang11, ang21);
    lpnt[1].SetValue(XS2, YS2, ang12, ang22);
  }
  else if (std::abs(d - dif) <= Epsilon(sum))
  {
    empt = false;
    para = false;
    iden = false;
    nbp  = 1;
    gp_Vec2d ax(C1.Location(), C2.Location());
    if (C1.Radius() < C2.Radius())
      ax.Reverse();

    gp_Vec2d Ox1(C1.XAxis().Direction());
    gp_Vec2d Ox2(C2.XAxis().Direction());
    double   ang1 = Ox1.Angle(ax);
    double   ang2 = Ox2.Angle(ax);
    if (ang1 < 0)
    {
      ang1 = 2 * M_PI + ang1;
    }
    if (ang2 < 0)
    {
      ang2 = 2 * M_PI + ang2;
    }
    double XS = (C1.Location().X() * R2 - C2.Location().X() * R1) / (R2 - R1);
    double YS = (C1.Location().Y() * R2 - C2.Location().Y() * R1) / (R2 - R1);
    lpnt[0].SetValue(XS, YS, ang1, ang2);
  }
  else
  {

    empt = true;
    para = false;
    iden = false;
    nbp  = 0;
  }
  done = true;
}
