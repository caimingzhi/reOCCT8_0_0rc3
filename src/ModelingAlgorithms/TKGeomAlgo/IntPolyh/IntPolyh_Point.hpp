#pragma once

#include <Adaptor3d_Surface.hpp>

class IntPolyh_Point
{
public:
  DEFINE_STANDARD_ALLOC

  IntPolyh_Point()
      : myX(0.),
        myY(0.),
        myZ(0.),
        myU(0.),
        myV(0.),
        myPOC(1),
        myDegenerated(false)
  {
  }

  IntPolyh_Point(const double x, const double y, const double z, const double u, const double v)
      : myX(x),
        myY(y),
        myZ(z),
        myU(u),
        myV(v),
        myPOC(1),
        myDegenerated(false)
  {
  }

  double X() const { return myX; }

  double Y() const { return myY; }

  double Z() const { return myZ; }

  double U() const { return myU; }

  double V() const { return myV; }

  int PartOfCommon() const { return myPOC; }

  void Set(const double x,
           const double y,
           const double z,
           const double u,
           const double v,
           const int    II = 1)
  {
    myX   = x;
    myY   = y;
    myZ   = z;
    myU   = u;
    myV   = v;
    myPOC = II;
  }

  void SetX(const double x) { myX = x; }

  void SetY(const double y) { myY = y; }

  void SetZ(const double z) { myZ = z; }

  void SetU(const double u) { myU = u; }

  void SetV(const double v) { myV = v; }

  void SetPartOfCommon(const int ii) { myPOC = ii; }

  Standard_EXPORT void Middle(const occ::handle<Adaptor3d_Surface>& MySurface,
                              const IntPolyh_Point&                 P1,
                              const IntPolyh_Point&                 P2);

  Standard_EXPORT IntPolyh_Point Add(const IntPolyh_Point& P1) const;

  IntPolyh_Point operator+(const IntPolyh_Point& P1) const { return Add(P1); }

  Standard_EXPORT IntPolyh_Point Sub(const IntPolyh_Point& P1) const;

  IntPolyh_Point operator-(const IntPolyh_Point& P1) const { return Sub(P1); }

  Standard_EXPORT IntPolyh_Point Divide(const double rr) const;

  IntPolyh_Point operator/(const double rr) const { return Divide(rr); }

  Standard_EXPORT IntPolyh_Point Multiplication(const double rr) const;

  IntPolyh_Point operator*(const double rr) const { return Multiplication(rr); }

  Standard_EXPORT double SquareModulus() const;

  Standard_EXPORT double SquareDistance(const IntPolyh_Point& P2) const;

  Standard_EXPORT double Dot(const IntPolyh_Point& P2) const;

  Standard_EXPORT void Cross(const IntPolyh_Point& P1, const IntPolyh_Point& P2);

  Standard_EXPORT void Dump() const;

  Standard_EXPORT void Dump(const int i) const;

  void SetDegenerated(const bool theFlag) { myDegenerated = theFlag; }

  bool Degenerated() const { return myDegenerated; }

private:
  double myX;
  double myY;
  double myZ;
  double myU;
  double myV;
  int    myPOC;
  bool   myDegenerated;
};
