#pragma once

#include <gp_VectorWithNullMagnitude.hpp>
#include <gp_XY.hpp>

class gp_Dir2d;
class gp_Pnt2d;
class gp_Ax2d;
class gp_Trsf2d;

class gp_Vec2d
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Vec2d() noexcept

    = default;

  constexpr gp_Vec2d(const gp_Dir2d& theV);

  constexpr gp_Vec2d(const gp_XY& theCoord) noexcept
      : coord(theCoord)
  {
  }

  constexpr gp_Vec2d(const double theXv, const double theYv) noexcept
      : coord(theXv, theYv)
  {
  }

  constexpr gp_Vec2d(const gp_Pnt2d& theP1, const gp_Pnt2d& theP2);

  constexpr void SetCoord(const int theIndex, const double theXi)
  {
    coord.SetCoord(theIndex, theXi);
  }

  constexpr void SetCoord(const double theXv, const double theYv) noexcept
  {
    coord.SetCoord(theXv, theYv);
  }

  constexpr void SetX(const double theX) noexcept { coord.SetX(theX); }

  constexpr void SetY(const double theY) noexcept { coord.SetY(theY); }

  constexpr void SetXY(const gp_XY& theCoord) noexcept { coord = theCoord; }

  constexpr double Coord(const int theIndex) const { return coord.Coord(theIndex); }

  constexpr void Coord(double& theXv, double& theYv) const noexcept { coord.Coord(theXv, theYv); }

  constexpr double X() const noexcept { return coord.X(); }

  constexpr double Y() const noexcept { return coord.Y(); }

  constexpr const gp_XY& XY() const noexcept { return coord; }

  Standard_EXPORT bool IsEqual(const gp_Vec2d& theOther,
                               const double    theLinearTolerance,
                               const double    theAngularTolerance) const;

  bool IsNormal(const gp_Vec2d& theOther, const double theAngularTolerance) const
  {
    const double anAng = std::abs(M_PI_2 - std::abs(Angle(theOther)));
    return !(anAng > theAngularTolerance);
  }

  bool IsOpposite(const gp_Vec2d& theOther, const double theAngularTolerance) const;

  bool IsParallel(const gp_Vec2d& theOther, const double theAngularTolerance) const;

  Standard_EXPORT double Angle(const gp_Vec2d& theOther) const;

  double Magnitude() const { return coord.Modulus(); }

  double SquareMagnitude() const { return coord.SquareModulus(); }

  void Add(const gp_Vec2d& theOther) { coord.Add(theOther.coord); }

  void operator+=(const gp_Vec2d& theOther) { Add(theOther); }

  [[nodiscard]] gp_Vec2d Added(const gp_Vec2d& theOther) const
  {
    gp_Vec2d aV = *this;
    aV.coord.Add(theOther.coord);
    return aV;
  }

  [[nodiscard]] gp_Vec2d operator+(const gp_Vec2d& theOther) const { return Added(theOther); }

  [[nodiscard]] double Crossed(const gp_Vec2d& theRight) const
  {
    return coord.Crossed(theRight.coord);
  }

  [[nodiscard]] double operator^(const gp_Vec2d& theRight) const { return Crossed(theRight); }

  double CrossMagnitude(const gp_Vec2d& theRight) const
  {
    return coord.CrossMagnitude(theRight.coord);
  }

  double CrossSquareMagnitude(const gp_Vec2d& theRight) const
  {
    return coord.CrossSquareMagnitude(theRight.coord);
  }

  void Divide(const double theScalar) { coord.Divide(theScalar); }

  void operator/=(const double theScalar) { Divide(theScalar); }

  [[nodiscard]] gp_Vec2d Divided(const double theScalar) const
  {
    gp_Vec2d aV = *this;
    aV.coord.Divide(theScalar);
    return aV;
  }

  [[nodiscard]] gp_Vec2d operator/(const double theScalar) const { return Divided(theScalar); }

  double Dot(const gp_Vec2d& theOther) const { return coord.Dot(theOther.coord); }

  double operator*(const gp_Vec2d& theOther) const { return Dot(theOther); }

  gp_Vec2d GetNormal() const { return gp_Vec2d(this->Y(), (-1) * this->X()); }

  void Multiply(const double theScalar) { coord.Multiply(theScalar); }

  void operator*=(const double theScalar) { Multiply(theScalar); }

  [[nodiscard]] gp_Vec2d Multiplied(const double theScalar) const
  {
    gp_Vec2d aV = *this;
    aV.coord.Multiply(theScalar);
    return aV;
  }

  [[nodiscard]] gp_Vec2d operator*(const double theScalar) const { return Multiplied(theScalar); }

  void Normalize()
  {
    double aD = coord.Modulus();
    Standard_ConstructionError_Raise_if(aD <= gp::Resolution(),
                                        "gp_Vec2d::Normalize() - vector has zero norm");
    coord.Divide(aD);
  }

  [[nodiscard]] gp_Vec2d Normalized() const;

  void Reverse() { coord.Reverse(); }

  [[nodiscard]] gp_Vec2d Reversed() const
  {
    gp_Vec2d aV = *this;
    aV.coord.Reverse();
    return aV;
  }

  [[nodiscard]] gp_Vec2d operator-() const { return Reversed(); }

  void Subtract(const gp_Vec2d& theRight) { coord.Subtract(theRight.coord); }

  void operator-=(const gp_Vec2d& theRight) { Subtract(theRight); }

  [[nodiscard]] gp_Vec2d Subtracted(const gp_Vec2d& theRight) const
  {
    gp_Vec2d aV = *this;
    aV.coord.Subtract(theRight.coord);
    return aV;
  }

  [[nodiscard]] gp_Vec2d operator-(const gp_Vec2d& theRight) const { return Subtracted(theRight); }

  void SetLinearForm(const double    theA1,
                     const gp_Vec2d& theV1,
                     const double    theA2,
                     const gp_Vec2d& theV2,
                     const gp_Vec2d& theV3)
  {
    coord.SetLinearForm(theA1, theV1.coord, theA2, theV2.coord, theV3.coord);
  }

  void SetLinearForm(const double    theA1,
                     const gp_Vec2d& theV1,
                     const double    theA2,
                     const gp_Vec2d& theV2)
  {
    coord.SetLinearForm(theA1, theV1.coord, theA2, theV2.coord);
  }

  void SetLinearForm(const double theA1, const gp_Vec2d& theV1, const gp_Vec2d& theV2)
  {
    coord.SetLinearForm(theA1, theV1.coord, theV2.coord);
  }

  void SetLinearForm(const gp_Vec2d& theV1, const gp_Vec2d& theV2)
  {
    coord.SetLinearForm(theV1.coord, theV2.coord);
  }

  Standard_EXPORT void Mirror(const gp_Vec2d& theV);

  [[nodiscard]] Standard_EXPORT gp_Vec2d Mirrored(const gp_Vec2d& theV) const;

  Standard_EXPORT void Mirror(const gp_Ax2d& theA1);

  [[nodiscard]] Standard_EXPORT gp_Vec2d Mirrored(const gp_Ax2d& theA1) const;

  void Rotate(const double theAng);

  [[nodiscard]] gp_Vec2d Rotated(const double theAng) const
  {
    gp_Vec2d aV = *this;
    aV.Rotate(theAng);
    return aV;
  }

  void Scale(const double theS) { coord.Multiply(theS); }

  [[nodiscard]] gp_Vec2d Scaled(const double theS) const
  {
    gp_Vec2d aV = *this;
    aV.coord.Multiply(theS);
    return aV;
  }

  Standard_EXPORT void Transform(const gp_Trsf2d& theT) noexcept;

  [[nodiscard]] gp_Vec2d Transformed(const gp_Trsf2d& theT) const
  {
    gp_Vec2d aV = *this;
    aV.Transform(theT);
    return aV;
  }

private:
  gp_XY coord;
};

#include <gp_Dir2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Pnt2d.hpp>

inline constexpr gp_Vec2d::gp_Vec2d(const gp_Dir2d& theV)
    : coord(theV.XY())
{
}

inline constexpr gp_Vec2d::gp_Vec2d(const gp_Pnt2d& theP1, const gp_Pnt2d& theP2)
    : coord(theP2.XY().Subtracted(theP1.XY()))
{
}

inline bool gp_Vec2d::IsOpposite(const gp_Vec2d& theOther, const double theAngularTolerance) const
{
  const double anAng = std::abs(Angle(theOther));
  return M_PI - anAng <= theAngularTolerance;
}

inline bool gp_Vec2d::IsParallel(const gp_Vec2d& theOther, const double theAngularTolerance) const
{
  const double anAng = std::abs(Angle(theOther));
  return anAng <= theAngularTolerance || M_PI - anAng <= theAngularTolerance;
}

inline gp_Vec2d gp_Vec2d::Normalized() const
{
  double aD = coord.Modulus();
  Standard_ConstructionError_Raise_if(aD <= gp::Resolution(),
                                      "gp_Vec2d::Normalized() - vector has zero norm");
  gp_Vec2d aV = *this;
  aV.coord.Divide(aD);
  return aV;
}

inline void gp_Vec2d::Rotate(const double theAng)
{
  gp_Trsf2d aT;
  aT.SetRotation(gp_Pnt2d(0.0, 0.0), theAng);
  coord.Multiply(aT.VectorialPart());
}

inline gp_Vec2d operator*(const double theScalar, const gp_Vec2d& theV)
{
  return theV.Multiplied(theScalar);
}
