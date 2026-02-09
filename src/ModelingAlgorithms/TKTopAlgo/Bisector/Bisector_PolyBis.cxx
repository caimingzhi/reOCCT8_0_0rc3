#include <Bisector_PolyBis.hpp>
#include <ElCLib.hpp>
#include <gp.hpp>
#include <gp_Trsf2d.hpp>

Bisector_PolyBis::Bisector_PolyBis()
{
  nbPoints = 0;
}

void Bisector_PolyBis::Append(const Bisector_PointOnBis& P)
{
  nbPoints++;
  thePoints[nbPoints] = P;
}

int Bisector_PolyBis::Length() const
{
  return nbPoints;
}

bool Bisector_PolyBis::IsEmpty() const
{
  return (nbPoints == 0);
}

const Bisector_PointOnBis& Bisector_PolyBis::Value(const int Index) const
{
  return thePoints[Index];
}

const Bisector_PointOnBis& Bisector_PolyBis::First() const
{
  return thePoints[1];
}

const Bisector_PointOnBis& Bisector_PolyBis::Last() const
{
  return thePoints[nbPoints];
}

int Bisector_PolyBis::Interval(const double U) const
{
  if (Last().ParamOnBis() - U < gp::Resolution())
  {
    return nbPoints - 1;
  }
  double dU = (Last().ParamOnBis() - First().ParamOnBis()) / (nbPoints - 1);
  if (dU <= gp::Resolution())
    return 1;

  int IntU = int(std::abs(U - First().ParamOnBis()) / dU);
  IntU++;

  if (thePoints[IntU].ParamOnBis() >= U)
  {
    for (int i = IntU; i >= 1; i--)
    {
      if (thePoints[i].ParamOnBis() <= U)
      {
        IntU = i;
        break;
      }
    }
  }
  else
  {
    for (int i = IntU; i <= nbPoints - 1; i++)
    {
      if (thePoints[i].ParamOnBis() >= U)
      {
        IntU = i - 1;
        break;
      }
    }
  }
  return IntU;
}

void Bisector_PolyBis::Transform(const gp_Trsf2d& T)
{
  for (int i = 1; i <= nbPoints; i++)
  {
    gp_Pnt2d P = thePoints[i].Point();
    P.Transform(T);
    thePoints[i].Point(P);
  }
}
