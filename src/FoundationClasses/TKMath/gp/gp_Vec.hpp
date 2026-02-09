#pragma once

#include <gp_VectorWithNullMagnitude.hpp>
#include <gp_XYZ.hpp>
#include <Standard_DomainError.hpp>

class gp_Dir;
class gp_Pnt;
class gp_Ax1;
class gp_Ax2;
class gp_Trsf;

class gp_Vec
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Vec() noexcept = default;

  constexpr gp_Vec(const gp_Dir& theV);

  constexpr gp_Vec(const gp_XYZ& theCoord) noexcept
      : coord(theCoord)
  {
  }

  constexpr gp_Vec(const double theXv, const double theYv, const double theZv) noexcept
      : coord(theXv, theYv, theZv)
  {
  }

  constexpr gp_Vec(const gp_Pnt& theP1, const gp_Pnt& theP2);

  constexpr void SetCoord(const int theIndex, const double theXi)
  {
    coord.SetCoord(theIndex, theXi);
  }

  constexpr void SetCoord(const double theXv, const double theYv, const double theZv) noexcept
  {
    coord.SetX(theXv);
    coord.SetY(theYv);
    coord.SetZ(theZv);
  }

  constexpr void SetX(const double theX) noexcept { coord.SetX(theX); }

  constexpr void SetY(const double theY) noexcept { coord.SetY(theY); }

  constexpr void SetZ(const double theZ) noexcept { coord.SetZ(theZ); }

  constexpr void SetXYZ(const gp_XYZ& theCoord) noexcept { coord = theCoord; }

  constexpr double Coord(const int theIndex) const { return coord.Coord(theIndex); }

  constexpr void Coord(double& theXv, double& theYv, double& theZv) const noexcept
  {
    theXv = coord.X();
    theYv = coord.Y();
    theZv = coord.Z();
  }

  constexpr double X() const noexcept { return coord.X(); }

  constexpr double Y() const noexcept { return coord.Y(); }

  constexpr double Z() const noexcept { return coord.Z(); }

  constexpr const gp_XYZ& XYZ() const noexcept { return coord; }

  Standard_EXPORT bool IsEqual(const gp_Vec& theOther,
                               const double  theLinearTolerance,
                               const double  theAngularTolerance) const;

  bool IsNormal(const gp_Vec& theOther, const double theAngularTolerance) const;

  bool IsOpposite(const gp_Vec& theOther, const double theAngularTolerance) const
  {
    const double anAng = M_PI - Angle(theOther);
    return anAng <= theAngularTolerance;
  }

  bool IsParallel(const gp_Vec& theOther, const double theAngularTolerance) const
  {
    const double anAng = Angle(theOther);
    return anAng <= theAngularTolerance || M_PI - anAng <= theAngularTolerance;
  }

  double Angle(const gp_Vec& theOther) const;

  double AngleWithRef(const gp_Vec& theOther, const gp_Vec& theVRef) const;

  double Magnitude() const { return coord.Modulus(); }

  constexpr double SquareMagnitude() const noexcept { return coord.SquareModulus(); }

  constexpr void Add(const gp_Vec& theOther) noexcept { coord.Add(theOther.coord); }

  constexpr void operator+=(const gp_Vec& theOther) noexcept { Add(theOther); }

  [[nodiscard]] constexpr gp_Vec Added(const gp_Vec& theOther) const noexcept
  {
    gp_Vec aV = *this;
    aV.coord.Add(theOther.coord);
    return aV;
  }

  [[nodiscard]] constexpr gp_Vec operator+(const gp_Vec& theOther) const noexcept
  {
    return Added(theOther);
  }

  constexpr void Subtract(const gp_Vec& theRight) noexcept { coord.Subtract(theRight.coord); }

  constexpr void operator-=(const gp_Vec& theRight) noexcept { Subtract(theRight); }

  [[nodiscard]] constexpr gp_Vec Subtracted(const gp_Vec& theRight) const noexcept
  {
    gp_Vec aV = *this;
    aV.coord.Subtract(theRight.coord);
    return aV;
  }

  [[nodiscard]] constexpr gp_Vec operator-(const gp_Vec& theRight) const noexcept
  {
    return Subtracted(theRight);
  }

  constexpr void Multiply(const double theScalar) noexcept { coord.Multiply(theScalar); }

  constexpr void operator*=(const double theScalar) noexcept { Multiply(theScalar); }

  [[nodiscard]] constexpr gp_Vec Multiplied(const double theScalar) const noexcept
  {
    gp_Vec aV = *this;
    aV.coord.Multiply(theScalar);
    return aV;
  }

  [[nodiscard]] constexpr gp_Vec operator*(const double theScalar) const noexcept
  {
    return Multiplied(theScalar);
  }

  constexpr void Divide(const double theScalar) { coord.Divide(theScalar); }

  constexpr void operator/=(const double theScalar) { Divide(theScalar); }

  [[nodiscard]] constexpr gp_Vec Divided(const double theScalar) const
  {
    gp_Vec aV = *this;
    aV.coord.Divide(theScalar);
    return aV;
  }

  [[nodiscard]] constexpr gp_Vec operator/(const double theScalar) const
  {
    return Divided(theScalar);
  }

  constexpr void Cross(const gp_Vec& theRight) noexcept { coord.Cross(theRight.coord); }

  constexpr void operator^=(const gp_Vec& theRight) noexcept { Cross(theRight); }

  [[nodiscard]] constexpr gp_Vec Crossed(const gp_Vec& theRight) const noexcept
  {
    gp_Vec aV = *this;
    aV.coord.Cross(theRight.coord);
    return aV;
  }

  [[nodiscard]] constexpr gp_Vec operator^(const gp_Vec& theRight) const noexcept
  {
    return Crossed(theRight);
  }

  double CrossMagnitude(const gp_Vec& theRight) const
  {
    return coord.CrossMagnitude(theRight.coord);
  }

  constexpr double CrossSquareMagnitude(const gp_Vec& theRight) const noexcept
  {
    return coord.CrossSquareMagnitude(theRight.coord);
  }

  constexpr void CrossCross(const gp_Vec& theV1, const gp_Vec& theV2) noexcept
  {
    coord.CrossCross(theV1.coord, theV2.coord);
  }

  [[nodiscard]] constexpr gp_Vec CrossCrossed(const gp_Vec& theV1,
                                              const gp_Vec& theV2) const noexcept
  {
    gp_Vec aV = *this;
    aV.coord.CrossCross(theV1.coord, theV2.coord);
    return aV;
  }

  constexpr double Dot(const gp_Vec& theOther) const noexcept { return coord.Dot(theOther.coord); }

  constexpr double operator*(const gp_Vec& theOther) const noexcept { return Dot(theOther); }

  constexpr double DotCross(const gp_Vec& theV1, const gp_Vec& theV2) const noexcept
  {
    return coord.DotCross(theV1.coord, theV2.coord);
  }

  void Normalize()
  {
    const double aD = coord.Modulus();
    Standard_ConstructionError_Raise_if(aD <= gp::Resolution(),
                                        "gp_Vec::Normalize() - vector has zero norm");
    coord.Divide(aD);
  }

  [[nodiscard]] gp_Vec Normalized() const;

  constexpr void Reverse() noexcept { coord.Reverse(); }

  [[nodiscard]] constexpr gp_Vec Reversed() const noexcept
  {
    gp_Vec aV = *this;
    aV.coord.Reverse();
    return aV;
  }

  [[nodiscard]] constexpr gp_Vec operator-() const noexcept { return Reversed(); }

  constexpr void SetLinearForm(const double  theA1,
                               const gp_Vec& theV1,
                               const double  theA2,
                               const gp_Vec& theV2,
                               const double  theA3,
                               const gp_Vec& theV3,
                               const gp_Vec& theV4) noexcept
  {
    coord.SetLinearForm(theA1, theV1.coord, theA2, theV2.coord, theA3, theV3.coord, theV4.coord);
  }

  constexpr void SetLinearForm(const double  theA1,
                               const gp_Vec& theV1,
                               const double  theA2,
                               const gp_Vec& theV2,
                               const double  theA3,
                               const gp_Vec& theV3) noexcept
  {
    coord.SetLinearForm(theA1, theV1.coord, theA2, theV2.coord, theA3, theV3.coord);
  }

  constexpr void SetLinearForm(const double  theA1,
                               const gp_Vec& theV1,
                               const double  theA2,
                               const gp_Vec& theV2,
                               const gp_Vec& theV3) noexcept
  {
    coord.SetLinearForm(theA1, theV1.coord, theA2, theV2.coord, theV3.coord);
  }

  constexpr void SetLinearForm(const double  theA1,
                               const gp_Vec& theV1,
                               const double  theA2,
                               const gp_Vec& theV2) noexcept
  {
    coord.SetLinearForm(theA1, theV1.coord, theA2, theV2.coord);
  }

  constexpr void SetLinearForm(const double  theA1,
                               const gp_Vec& theV1,
                               const gp_Vec& theV2) noexcept
  {
    coord.SetLinearForm(theA1, theV1.coord, theV2.coord);
  }

  constexpr void SetLinearForm(const gp_Vec& theV1, const gp_Vec& theV2) noexcept
  {
    coord.SetLinearForm(theV1.coord, theV2.coord);
  }

  Standard_EXPORT void Mirror(const gp_Vec& theV) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Vec Mirrored(const gp_Vec& theV) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& theA1) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Vec Mirrored(const gp_Ax1& theA1) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2& theA2) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Vec Mirrored(const gp_Ax2& theA2) const noexcept;

  void Rotate(const gp_Ax1& theA1, const double theAng);

  [[nodiscard]] gp_Vec Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Vec aVres = *this;
    aVres.Rotate(theA1, theAng);
    return aVres;
  }

  constexpr void Scale(const double theS) noexcept { coord.Multiply(theS); }

  [[nodiscard]] constexpr gp_Vec Scaled(const double theS) const noexcept
  {
    gp_Vec aV = *this;
    aV.coord.Multiply(theS);
    return aV;
  }

  Standard_EXPORT void Transform(const gp_Trsf& theT);

  [[nodiscard]] gp_Vec Transformed(const gp_Trsf& theT) const
  {
    gp_Vec aV = *this;
    aV.Transform(theT);
    return aV;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  gp_XYZ coord;
};

#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>

inline constexpr gp_Vec::gp_Vec(const gp_Dir& theV)
    : coord(theV.XYZ())
{
}

inline constexpr gp_Vec::gp_Vec(const gp_Pnt& theP1, const gp_Pnt& theP2)
    : coord(theP2.XYZ().Subtracted(theP1.XYZ()))
{
}

inline bool gp_Vec::IsNormal(const gp_Vec& theOther, const double theAngularTolerance) const
{
  const double anAng = std::abs(M_PI_2 - Angle(theOther));
  return anAng <= theAngularTolerance;
}

inline double gp_Vec::Angle(const gp_Vec& theOther) const
{
  gp_VectorWithNullMagnitude_Raise_if(coord.Modulus() <= gp::Resolution()
                                        || theOther.coord.Modulus() <= gp::Resolution(),
                                      " ");
  return (gp_Dir(coord)).Angle(theOther);
}

inline double gp_Vec::AngleWithRef(const gp_Vec& theOther, const gp_Vec& theVRef) const
{
  gp_VectorWithNullMagnitude_Raise_if(coord.Modulus() <= gp::Resolution()
                                        || theVRef.coord.Modulus() <= gp::Resolution()
                                        || theOther.coord.Modulus() <= gp::Resolution(),
                                      " ");
  return (gp_Dir(coord)).AngleWithRef(theOther, theVRef);
}

inline gp_Vec gp_Vec::Normalized() const
{
  const double aD = coord.Modulus();
  Standard_ConstructionError_Raise_if(aD <= gp::Resolution(),
                                      "gp_Vec::Normalized() - vector has zero norm");
  gp_Vec aV = *this;
  aV.coord.Divide(aD);
  return aV;
}

inline void gp_Vec::Rotate(const gp_Ax1& theA1, const double theAng)
{
  gp_Trsf aT;
  aT.SetRotation(theA1, theAng);
  coord.Multiply(aT.VectorialPart());
}

inline constexpr gp_Vec operator*(const double theScalar, const gp_Vec& theV) noexcept
{
  return theV.Multiplied(theScalar);
}
