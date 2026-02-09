#include <IntPolyh_Point.hpp>

#include <cstdio>

void IntPolyh_Point::Middle(const occ::handle<Adaptor3d_Surface>& MySurface,
                            const IntPolyh_Point&                 Point1,
                            const IntPolyh_Point&                 Point2)
{
  myU = (Point1.U() + Point2.U()) * 0.5;
  myV = (Point1.V() + Point2.V()) * 0.5;

  gp_Pnt PtXYZ = (MySurface)->Value(myU, myV);

  myX = PtXYZ.X();
  myY = PtXYZ.Y();
  myZ = PtXYZ.Z();
}

IntPolyh_Point IntPolyh_Point::Add(const IntPolyh_Point& P1) const
{
  IntPolyh_Point res;

  res.SetX(myX + P1.X());
  res.SetY(myY + P1.Y());
  res.SetZ(myZ + P1.Z());
  res.SetU(myU + P1.U());
  res.SetV(myV + P1.V());
  return res;
}

IntPolyh_Point IntPolyh_Point::Sub(const IntPolyh_Point& P1) const
{
  IntPolyh_Point res;

  res.SetX(myX - P1.X());
  res.SetY(myY - P1.Y());
  res.SetZ(myZ - P1.Z());
  res.SetU(myU - P1.U());
  res.SetV(myV - P1.V());
  return res;
}

IntPolyh_Point IntPolyh_Point::Divide(const double RR) const
{
  IntPolyh_Point res;

  if (std::abs(RR) > 10.0e-20)
  {
    res.SetX(myX / RR);
    res.SetY(myY / RR);
    res.SetZ(myZ / RR);
    res.SetU(myU / RR);
    res.SetV(myV / RR);
  }
  else
  {
    printf("Division par zero RR=%f\n", RR);
  }
  return res;
}

IntPolyh_Point IntPolyh_Point::Multiplication(const double RR) const
{
  IntPolyh_Point res;

  res.SetX(myX * RR);
  res.SetY(myY * RR);
  res.SetZ(myZ * RR);
  res.SetU(myU * RR);
  res.SetV(myV * RR);
  return res;
}

double IntPolyh_Point::SquareModulus() const
{
  double res = myX * myX + myY * myY + myZ * myZ;
  return res;
}

double IntPolyh_Point::SquareDistance(const IntPolyh_Point& P2) const
{
  double res = (myX - P2.myX) * (myX - P2.myX) + (myY - P2.myY) * (myY - P2.myY)
               + (myZ - P2.myZ) * (myZ - P2.myZ);
  return res;
}

double IntPolyh_Point::Dot(const IntPolyh_Point& b) const
{
  double t = myX * b.myX + myY * b.myY + myZ * b.myZ;
  return t;
}

void IntPolyh_Point::Cross(const IntPolyh_Point& a, const IntPolyh_Point& b)
{
  myX = a.myY * b.myZ - a.myZ * b.myY;
  myY = a.myZ * b.myX - a.myX * b.myZ;
  myZ = a.myX * b.myY - a.myY * b.myX;
}

void IntPolyh_Point::Dump() const
{
  printf("\nPoint : x=%+8.3eg y=%+8.3eg z=%+8.3eg u=%+8.3eg v=%+8.3eg\n", myX, myY, myZ, myU, myV);
}

void IntPolyh_Point::Dump(const int i) const
{
  printf("\nPoint(%3d) : x=%+8.3eg y=%+8.3eg z=%+8.3eg u=%+8.3eg v=%+8.3eg poc=%3d\n",
         i,
         myX,
         myY,
         myZ,
         myU,
         myV,
         myPOC);
}
