#include <IntAna2d_IntPoint.hpp>

IntAna2d_IntPoint::IntAna2d_IntPoint(const double X,
                                     const double Y,
                                     const double U1,
                                     const double U2)
    : myu1(U1),
      myu2(U2),
      myp(X, Y),
      myimplicit(false)
{
}

IntAna2d_IntPoint::IntAna2d_IntPoint(const double X, const double Y, const double U1)
    : myu1(U1),
      myu2(RealLast()),
      myp(X, Y),
      myimplicit(true)
{
}

IntAna2d_IntPoint::IntAna2d_IntPoint()
    :

      myu1(RealLast()),
      myu2(RealLast()),
      myp(RealLast(), RealLast()),
      myimplicit(false)
{
}

void IntAna2d_IntPoint::SetValue(const double X, const double Y, const double U1, const double U2)
{

  myimplicit = false;
  myp.SetCoord(X, Y);
  myu1 = U1;
  myu2 = U2;
}

void IntAna2d_IntPoint::SetValue(const double X, const double Y, const double U1)
{

  myimplicit = true;
  myp.SetCoord(X, Y);
  myu1 = U1;
  myu2 = RealLast();
}
