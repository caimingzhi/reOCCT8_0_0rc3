#include <IntPatch_PolyLine.hpp>
#include <IntPatch_RLine.hpp>
#include <IntPatch_WLine.hpp>
#include <Precision.hpp>

#define INITDEFLE Precision::PConfusion() * 100.

IntPatch_PolyLine::IntPatch_PolyLine()
    : IntPatch_Polygo(INITDEFLE),
      onfirst(false)
{
}

IntPatch_PolyLine::IntPatch_PolyLine(const double InitDefle)
    : IntPatch_Polygo(InitDefle),
      onfirst(false)
{
}

void IntPatch_PolyLine::SetWLine(const bool OnFirst, const occ::handle<IntPatch_WLine>& Line)
{
  typ     = IntPatch_Walking;
  wpoly   = Line;
  onfirst = OnFirst;
  Prepare();
}

void IntPatch_PolyLine::SetRLine(const bool OnFirst, const occ::handle<IntPatch_RLine>& Line)
{
  typ     = IntPatch_Restriction;
  rpoly   = Line;
  onfirst = OnFirst;
  Prepare();
}

void IntPatch_PolyLine::Prepare()
{
  int i;
  myBox.SetVoid();
  int          n     = NbPoints();
  const double eps_2 = myError * myError;

  gp_Pnt2d P1, P2;
  if (n >= 3)
  {
    P1 = Point(1);
    P2 = Point(2);
  }
  for (i = 1; i <= n; i++)
  {
    const gp_Pnt2d& P3 = Point(i);
    if (i >= 3)
    {
      gp_XY  V13   = P3.XY() - P1.XY();
      gp_XY  V12   = P2.XY() - P1.XY();
      double d13_2 = V13.SquareModulus(), d_2;
      if (d13_2 > eps_2)
        d_2 = V13.CrossSquareMagnitude(V12) / d13_2;
      else
        d_2 = eps_2;
      if (d_2 > myError * myError)
      {

        gp_XY  V23 = P3.XY() - P2.XY();
        double d12 = V12.Modulus(), d23 = V23.Modulus();

        double tm = d12 / (d12 + d23);
        if (tm > 0.1 && tm < 0.9)
        {
          tm -= (tm - 0.5) * 0.6;
          double tm1mtm = tm * (1 - tm);

          double Ax = (tm * V13.X() - V12.X()) / tm1mtm;
          double Bx = (V12.X() - tm * tm * V13.X()) / tm1mtm;
          double Cx = P1.X();
          double Ay = (tm * V13.Y() - V12.Y()) / tm1mtm;
          double By = (V12.Y() - tm * tm * V13.Y()) / tm1mtm;
          double Cy = P1.Y();

          double A1 = V12.Y() / d12;
          double B1 = -V12.X() / d12;
          double C1 = (P2.X() * P1.Y() - P1.X() * P2.Y()) / d12;
          double A2 = V23.Y() / d23;
          double B2 = -V23.X() / d23;
          double C2 = (P3.X() * P2.Y() - P2.X() * P3.Y()) / d23;

          double t1  = -0.5 * (A1 * Bx + B1 * By) / (A1 * Ax + B1 * Ay);
          double t2  = -0.5 * (A2 * Bx + B2 * By) / (A2 * Ax + B2 * Ay);
          double xt1 = Ax * t1 * t1 + Bx * t1 + Cx;
          double yt1 = Ay * t1 * t1 + By * t1 + Cy;
          double xt2 = Ax * t2 * t2 + Bx * t2 + Cx;
          double yt2 = Ay * t2 * t2 + By * t2 + Cy;

          double d1 = std::abs(A1 * xt1 + B1 * yt1 + C1);
          double d2 = std::abs(A2 * xt2 + B2 * yt2 + C2);
          if (d2 > d1)
            d1 = d2;

          if (d1 * d1 < d_2)
            d_2 = d1 * d1;
        }
        if (d_2 > myError * myError)
          myError = std::sqrt(d_2);
      }
      P1 = P2;
      P2 = P3;
    }
    myBox.Add(P3);
  }
  myBox.Enlarge(myError);
}

void IntPatch_PolyLine::ResetError()
{
  myError = INITDEFLE;
}

int IntPatch_PolyLine::NbPoints() const
{
  return (typ == IntPatch_Walking ? wpoly->NbPnts() : rpoly->NbPnts());
}

gp_Pnt2d IntPatch_PolyLine::Point(const int Index) const
{
  double X, Y, X1, Y1, DX, DY;
  DX = DY = 0;
  if (onfirst)
  {
    if (typ == IntPatch_Walking)
    {
      wpoly->Point(Index).ParametersOnS1(X, Y);
      if (Index == 1)
      {
        wpoly->Point(2).ParametersOnS1(X1, Y1);
        DX = 0.0000001 * (X - X1);
        DY = 0.0000001 * (Y - Y1);
      }
      else if (Index == wpoly->NbPnts())
      {
        wpoly->Point(Index - 1).ParametersOnS1(X1, Y1);
        DX = 0.0000001 * (X - X1);
        DY = 0.0000001 * (Y - Y1);
      }
    }
    else
    {
      rpoly->Point(Index).ParametersOnS1(X, Y);
    }
  }
  else
  {
    if (typ == IntPatch_Walking)
    {
      wpoly->Point(Index).ParametersOnS2(X, Y);
      if (Index == 1)
      {
        wpoly->Point(2).ParametersOnS2(X1, Y1);
        DX = 0.0000001 * (X - X1);
        DY = 0.0000001 * (Y - Y1);
      }
      else if (Index == wpoly->NbPnts())
      {
        wpoly->Point(Index - 1).ParametersOnS2(X1, Y1);
        DX = 0.0000001 * (X - X1);
        DY = 0.0000001 * (Y - Y1);
      }
    }
    else
    {
      rpoly->Point(Index).ParametersOnS2(X, Y);
    }
  }

  return (gp_Pnt2d(X + DX, Y + DY));
}
