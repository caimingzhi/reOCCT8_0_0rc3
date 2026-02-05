#pragma once

#include <Adaptor3d_Surface.hpp>

//! The class represents the point on the surface with
//! both 3D and 2D points.
class IntPolyh_Point
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor
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

  //! Constructor
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

  //! Returns X coordinate of the 3D point
  double X() const { return myX; }

  //! Returns Y coordinate of the 3D point
  double Y() const { return myY; }

  //! Returns the Z coordinate of the 3D point
  double Z() const { return myZ; }

  //! Returns the U coordinate of the 2D point
  double U() const { return myU; }

  //! Returns the V coordinate of the 2D point
  double V() const { return myV; }

  //! Returns 0 if the point is not common with the other surface
  int PartOfCommon() const { return myPOC; }

  //! Sets the point
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

  //! Sets the X coordinate for the 3D point
  void SetX(const double x) { myX = x; }

  //! Sets the Y coordinate for the 3D point
  void SetY(const double y) { myY = y; }

  //! Sets the Z coordinate for the 3D point
  void SetZ(const double z) { myZ = z; }

  //! Sets the U coordinate for the 2D point
  void SetU(const double u) { myU = u; }

  //! Sets the V coordinate for the 2D point
  void SetV(const double v) { myV = v; }

  //! Sets the part of common
  void SetPartOfCommon(const int ii) { myPOC = ii; }

  //! Creates middle point from P1 and P2 and stores it to this
  Standard_EXPORT void Middle(const occ::handle<Adaptor3d_Surface>& MySurface,
                              const IntPolyh_Point&                 P1,
                              const IntPolyh_Point&                 P2);
  //! Addition
  Standard_EXPORT IntPolyh_Point Add(const IntPolyh_Point& P1) const;

  IntPolyh_Point operator+(const IntPolyh_Point& P1) const { return Add(P1); }

  //! Subtraction
  Standard_EXPORT IntPolyh_Point Sub(const IntPolyh_Point& P1) const;

  IntPolyh_Point operator-(const IntPolyh_Point& P1) const { return Sub(P1); }

  //! Division
  Standard_EXPORT IntPolyh_Point Divide(const double rr) const;

  IntPolyh_Point operator/(const double rr) const { return Divide(rr); }

  //! Multiplication
  Standard_EXPORT IntPolyh_Point Multiplication(const double rr) const;

  IntPolyh_Point operator*(const double rr) const { return Multiplication(rr); }

  //! Square modulus
  Standard_EXPORT double SquareModulus() const;
  //! Square distance to the other point
  Standard_EXPORT double SquareDistance(const IntPolyh_Point& P2) const;
  //! Dot
  Standard_EXPORT double Dot(const IntPolyh_Point& P2) const;
  //! Cross
  Standard_EXPORT void Cross(const IntPolyh_Point& P1, const IntPolyh_Point& P2);
  //! Dump
  Standard_EXPORT void Dump() const;
  //! Dump
  Standard_EXPORT void Dump(const int i) const;

  //! Sets the degenerated flag
  void SetDegenerated(const bool theFlag) { myDegenerated = theFlag; }

  //! Returns the degenerated flag
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
