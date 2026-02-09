#pragma once

#include <gp_XYZ.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>

class gp_Vec;
class gp_Ax1;
class gp_Ax2;
class gp_Trsf;

class gp_Dir
{
public:
  enum class D
  {
    X,
    Y,
    Z,
    NX,
    NY,
    NZ
  };

  DEFINE_STANDARD_ALLOC

  constexpr gp_Dir() noexcept
      : coord(1., 0., 0.)
  {
  }

  constexpr explicit gp_Dir(const D theDir) noexcept
      : coord(theDir == D::X    ? 1.0
              : theDir == D::NX ? -1.0
                                : 0.0,
              theDir == D::Y    ? 1.0
              : theDir == D::NY ? -1.0
                                : 0.0,
              theDir == D::Z    ? 1.0
              : theDir == D::NZ ? -1.0
                                : 0.0)
  {
  }

  constexpr gp_Dir(const gp_Vec& theV);

  constexpr gp_Dir(const gp_XYZ& theCoord);

  constexpr gp_Dir(const double theXv, const double theYv, const double theZv);

  constexpr gp_Dir(const gp_Dir&) noexcept = default;
  constexpr gp_Dir(gp_Dir&&) noexcept      = default;

  constexpr gp_Dir& operator=(const gp_Dir&) noexcept = default;
  constexpr gp_Dir& operator=(gp_Dir&&) noexcept      = default;

  constexpr void SetCoord(const int theIndex, const double theXi);

  constexpr void SetCoord(const double theXv, const double theYv, const double theZv);

  constexpr void SetX(const double theX);

  constexpr void SetY(const double theY);

  constexpr void SetZ(const double theZ);

  constexpr void SetXYZ(const gp_XYZ& theCoord);

  constexpr double Coord(const int theIndex) const { return coord.Coord(theIndex); }

  constexpr void Coord(double& theXv, double& theYv, double& theZv) const noexcept
  {
    coord.Coord(theXv, theYv, theZv);
  }

  constexpr double X() const noexcept { return coord.X(); }

  constexpr double Y() const noexcept { return coord.Y(); }

  constexpr double Z() const noexcept { return coord.Z(); }

  constexpr const gp_XYZ& XYZ() const noexcept { return coord; }

  bool IsEqual(const gp_Dir& theOther, const double theAngularTolerance) const
  {
    return Angle(theOther) <= theAngularTolerance;
  }

  bool IsNormal(const gp_Dir& theOther, const double theAngularTolerance) const
  {
    double anAng = M_PI / 2.0 - Angle(theOther);
    if (anAng < 0)
    {
      anAng = -anAng;
    }
    return anAng <= theAngularTolerance;
  }

  bool IsOpposite(const gp_Dir& theOther, const double theAngularTolerance) const
  {
    return M_PI - Angle(theOther) <= theAngularTolerance;
  }

  bool IsParallel(const gp_Dir& theOther, const double theAngularTolerance) const
  {
    double anAng = Angle(theOther);
    return anAng <= theAngularTolerance || M_PI - anAng <= theAngularTolerance;
  }

  Standard_EXPORT double Angle(const gp_Dir& theOther) const;

  Standard_EXPORT double AngleWithRef(const gp_Dir& theOther, const gp_Dir& theVRef) const;

  constexpr void Cross(const gp_Dir& theRight);

  constexpr void operator^=(const gp_Dir& theRight) { Cross(theRight); }

  [[nodiscard]] constexpr gp_Dir Crossed(const gp_Dir& theRight) const;

  [[nodiscard]] constexpr gp_Dir operator^(const gp_Dir& theRight) const
  {
    return Crossed(theRight);
  }

  constexpr void CrossCross(const gp_Dir& theV1, const gp_Dir& theV2);

  [[nodiscard]] constexpr gp_Dir CrossCrossed(const gp_Dir& theV1, const gp_Dir& theV2) const;

  constexpr double Dot(const gp_Dir& theOther) const noexcept { return coord.Dot(theOther.coord); }

  constexpr double operator*(const gp_Dir& theOther) const noexcept { return Dot(theOther); }

  constexpr double DotCross(const gp_Dir& theV1, const gp_Dir& theV2) const noexcept
  {
    return coord.Dot(theV1.coord.Crossed(theV2.coord));
  }

  constexpr void Reverse() noexcept { coord.Reverse(); }

  [[nodiscard]] constexpr gp_Dir Reversed() const noexcept
  {
    gp_Dir aV = *this;
    aV.coord.Reverse();
    return aV;
  }

  [[nodiscard]] constexpr gp_Dir operator-() const noexcept { return Reversed(); }

  Standard_EXPORT void Mirror(const gp_Dir& theV) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Dir Mirrored(const gp_Dir& theV) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& theA1) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Dir Mirrored(const gp_Ax1& theA1) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2& theA2) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Dir Mirrored(const gp_Ax2& theA2) const noexcept;

  void Rotate(const gp_Ax1& theA1, const double theAng);

  [[nodiscard]] gp_Dir Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Dir aV = *this;
    aV.Rotate(theA1, theAng);
    return aV;
  }

  Standard_EXPORT void Transform(const gp_Trsf& theT);

  [[nodiscard]] gp_Dir Transformed(const gp_Trsf& theT) const
  {
    gp_Dir aV = *this;
    aV.Transform(theT);
    return aV;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  Standard_EXPORT bool InitFromJson(const Standard_SStream& theSStream, int& theStreamPos);

private:
  gp_XYZ coord;
};

#include <gp_Trsf.hpp>

inline constexpr gp_Dir::gp_Dir(const gp_Vec& theV)
    : gp_Dir(theV.XYZ())
{
}

inline constexpr gp_Dir::gp_Dir(const gp_XYZ& theXYZ)
    : gp_Dir(theXYZ.X(), theXYZ.Y(), theXYZ.Z())
{
}

inline constexpr gp_Dir::gp_Dir(const double theXv, const double theYv, const double theZv)
{
  const double aSqMod = theXv * theXv + theYv * theYv + theZv * theZv;

  if (aSqMod >= (1.0 - gp::Resolution()) && aSqMod <= (1.0 + gp::Resolution()))
  {
    coord.SetCoord(theXv, theYv, theZv);
    return;
  }

  Standard_ConstructionError_Raise_if(aSqMod <= gp::Resolution() * gp::Resolution(),
                                      "gp_Dir() - input vector has zero norm");
  const double aD = sqrt(aSqMod);
  coord.SetCoord(theXv / aD, theYv / aD, theZv / aD);
}

inline constexpr void gp_Dir::SetCoord(const int theIndex, const double theXi)
{
  Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > 3,
                               "gp_Dir::SetCoord() - index is out of range [1, 3]");
  if (theIndex == 1)
  {
    SetX(theXi);
  }
  else if (theIndex == 2)
  {
    SetY(theXi);
  }
  else
  {
    SetZ(theXi);
  }
}

inline constexpr void gp_Dir::SetCoord(const double theXv, const double theYv, const double theZv)
{
  const double aSqMod = theXv * theXv + theYv * theYv + theZv * theZv;

  if (aSqMod >= (1.0 - gp::Resolution()) && aSqMod <= (1.0 + gp::Resolution()))
  {
    coord.SetCoord(theXv, theYv, theZv);
    return;
  }

  Standard_ConstructionError_Raise_if(aSqMod <= gp::Resolution() * gp::Resolution(),
                                      "gp_Dir::SetCoord() - input vector has zero norm");
  const double aD = sqrt(aSqMod);
  coord.SetCoord(theXv / aD, theYv / aD, theZv / aD);
}

inline constexpr void gp_Dir::SetX(const double theX)
{
  SetCoord(theX, coord.Y(), coord.Z());
}

inline constexpr void gp_Dir::SetY(const double theY)
{
  SetCoord(coord.X(), theY, coord.Z());
}

inline constexpr void gp_Dir::SetZ(const double theZ)
{
  SetCoord(coord.X(), coord.Y(), theZ);
}

inline constexpr void gp_Dir::SetXYZ(const gp_XYZ& theXYZ)
{
  SetCoord(theXYZ.X(), theXYZ.Y(), theXYZ.Z());
}

inline constexpr void gp_Dir::Cross(const gp_Dir& theRight)
{
  coord.Cross(theRight.coord);
  const double aSqMod = coord.SquareModulus();

  if (aSqMod >= (1.0 - gp::Resolution()) && aSqMod <= (1.0 + gp::Resolution()))
  {
    return;
  }

  Standard_ConstructionError_Raise_if(aSqMod <= gp::Resolution() * gp::Resolution(),
                                      "gp_Dir::Cross() - result vector has zero norm");
  coord.Divide(sqrt(aSqMod));
}

inline constexpr gp_Dir gp_Dir::Crossed(const gp_Dir& theRight) const
{
  gp_Dir aV = *this;
  aV.Cross(theRight);
  return aV;
}

inline constexpr void gp_Dir::CrossCross(const gp_Dir& theV1, const gp_Dir& theV2)
{
  coord.CrossCross(theV1.coord, theV2.coord);
  const double aSqMod = coord.SquareModulus();

  if (aSqMod >= (1.0 - gp::Resolution()) && aSqMod <= (1.0 + gp::Resolution()))
  {
    return;
  }

  Standard_ConstructionError_Raise_if(aSqMod <= gp::Resolution() * gp::Resolution(),
                                      "gp_Dir::CrossCross() - result vector has zero norm");
  coord.Divide(sqrt(aSqMod));
}

inline constexpr gp_Dir gp_Dir::CrossCrossed(const gp_Dir& theV1, const gp_Dir& theV2) const
{
  gp_Dir aV = *this;
  aV.CrossCross(theV1, theV2);
  return aV;
}

inline void gp_Dir::Rotate(const gp_Ax1& theA1, const double theAng)
{
  gp_Trsf aT;
  aT.SetRotation(theA1, theAng);
  coord.Multiply(aT.HVectorialPart());
}
