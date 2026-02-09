#pragma once

#include <gp_XY.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>

class gp_Vec2d;
class gp_Ax2d;
class gp_Trsf2d;

class gp_Dir2d
{
public:
  enum class D
  {
    X,
    Y,
    NX,
    NY
  };

  DEFINE_STANDARD_ALLOC

  constexpr gp_Dir2d() noexcept
      : coord(1., 0.)
  {
  }

  constexpr explicit gp_Dir2d(const D theDir) noexcept
      : coord(theDir == D::X    ? 1.0
              : theDir == D::NX ? -1.0
                                : 0.0,
              theDir == D::Y    ? 1.0
              : theDir == D::NY ? -1.0
                                : 0.0)
  {
  }

  constexpr gp_Dir2d(const gp_Vec2d& theV);

  constexpr gp_Dir2d(const gp_XY& theCoord);

  constexpr gp_Dir2d(const double theXv, const double theYv);

  constexpr void SetCoord(const int theIndex, const double theXi);

  constexpr void SetCoord(const double theXv, const double theYv);

  constexpr void SetX(const double theX);

  constexpr void SetY(const double theY);

  constexpr void SetXY(const gp_XY& theCoord);

  constexpr double Coord(const int theIndex) const { return coord.Coord(theIndex); }

  constexpr void Coord(double& theXv, double& theYv) const noexcept { coord.Coord(theXv, theYv); }

  constexpr double X() const noexcept { return coord.X(); }

  constexpr double Y() const noexcept { return coord.Y(); }

  constexpr const gp_XY& XY() const noexcept { return coord; }

  bool IsEqual(const gp_Dir2d& theOther, const double theAngularTolerance) const;

  bool IsNormal(const gp_Dir2d& theOther, const double theAngularTolerance) const;

  bool IsOpposite(const gp_Dir2d& theOther, const double theAngularTolerance) const;

  bool IsParallel(const gp_Dir2d& theOther, const double theAngularTolerance) const;

  Standard_EXPORT double Angle(const gp_Dir2d& theOther) const;

  [[nodiscard]] constexpr double Crossed(const gp_Dir2d& theRight) const noexcept
  {
    return coord.Crossed(theRight.coord);
  }

  [[nodiscard]] constexpr double operator^(const gp_Dir2d& theRight) const noexcept
  {
    return Crossed(theRight);
  }

  constexpr double Dot(const gp_Dir2d& theOther) const noexcept
  {
    return coord.Dot(theOther.coord);
  }

  constexpr double operator*(const gp_Dir2d& theOther) const noexcept { return Dot(theOther); }

  constexpr void Reverse() noexcept { coord.Reverse(); }

  [[nodiscard]] constexpr gp_Dir2d Reversed() const noexcept
  {
    gp_Dir2d aV = *this;
    aV.coord.Reverse();
    return aV;
  }

  [[nodiscard]] constexpr gp_Dir2d operator-() const noexcept { return Reversed(); }

  Standard_EXPORT void Mirror(const gp_Dir2d& theV) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Dir2d Mirrored(const gp_Dir2d& theV) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2d& theA) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Dir2d Mirrored(const gp_Ax2d& theA) const noexcept;

  void Rotate(const double Ang);

  [[nodiscard]] gp_Dir2d Rotated(const double theAng) const
  {
    gp_Dir2d aV = *this;
    aV.Rotate(theAng);
    return aV;
  }

  Standard_EXPORT void Transform(const gp_Trsf2d& theT) noexcept;

  [[nodiscard]] gp_Dir2d Transformed(const gp_Trsf2d& theT) const
  {
    gp_Dir2d aV = *this;
    aV.Transform(theT);
    return aV;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  gp_XY coord;
};

#include <gp_Ax2d.hpp>
#include <gp_Trsf2d.hpp>

inline constexpr gp_Dir2d::gp_Dir2d(const gp_Vec2d& theV)
    : gp_Dir2d(theV.XY())
{
}

inline constexpr gp_Dir2d::gp_Dir2d(const gp_XY& theXY)
    : gp_Dir2d(theXY.X(), theXY.Y())
{
}

inline constexpr gp_Dir2d::gp_Dir2d(const double theXv, const double theYv)
{
  const double aSqMod = theXv * theXv + theYv * theYv;

  if (aSqMod >= (1.0 - gp::Resolution()) && aSqMod <= (1.0 + gp::Resolution()))
  {
    coord.SetCoord(theXv, theYv);
    return;
  }

  Standard_ConstructionError_Raise_if(aSqMod <= gp::Resolution() * gp::Resolution(),
                                      "gp_Dir2d() - input vector has zero norm");
  const double aD = sqrt(aSqMod);
  coord.SetCoord(theXv / aD, theYv / aD);
}

inline constexpr void gp_Dir2d::SetCoord(const int theIndex, const double theXi)
{
  Standard_OutOfRange_Raise_if(theIndex < 1 || theIndex > 2,
                               "gp_Dir2d::SetCoord() - index is out of range [1, 2]");
  if (theIndex == 1)
  {
    SetX(theXi);
  }
  else
  {
    SetY(theXi);
  }
}

inline constexpr void gp_Dir2d::SetCoord(const double theXv, const double theYv)
{
  const double aSqMod = theXv * theXv + theYv * theYv;

  if (aSqMod >= (1.0 - gp::Resolution()) && aSqMod <= (1.0 + gp::Resolution()))
  {
    coord.SetCoord(theXv, theYv);
    return;
  }

  Standard_ConstructionError_Raise_if(aSqMod <= gp::Resolution() * gp::Resolution(),
                                      "gp_Dir2d::SetCoord() - result vector has zero norm");
  const double aD = sqrt(aSqMod);
  coord.SetCoord(theXv / aD, theYv / aD);
}

inline constexpr void gp_Dir2d::SetX(const double theX)
{
  SetCoord(theX, coord.Y());
}

inline constexpr void gp_Dir2d::SetY(const double theY)
{
  SetCoord(coord.X(), theY);
}

inline constexpr void gp_Dir2d::SetXY(const gp_XY& theXY)
{
  SetCoord(theXY.X(), theXY.Y());
}

inline bool gp_Dir2d::IsEqual(const gp_Dir2d& theOther, const double theAngularTolerance) const
{
  double anAng = Angle(theOther);
  if (anAng < 0)
  {
    anAng = -anAng;
  }
  return anAng <= theAngularTolerance;
}

inline bool gp_Dir2d::IsNormal(const gp_Dir2d& theOther, const double theAngularTolerance) const
{
  double anAng = Angle(theOther);
  if (anAng < 0)
  {
    anAng = -anAng;
  }
  anAng = M_PI / 2.0 - anAng;
  if (anAng < 0)
  {
    anAng = -anAng;
  }
  return anAng <= theAngularTolerance;
}

inline bool gp_Dir2d::IsOpposite(const gp_Dir2d& theOther, const double theAngularTolerance) const
{
  double anAng = Angle(theOther);
  if (anAng < 0)
  {
    anAng = -anAng;
  }
  return M_PI - anAng <= theAngularTolerance;
}

inline bool gp_Dir2d::IsParallel(const gp_Dir2d& theOther, const double theAngularTolerance) const
{
  double anAng = Angle(theOther);
  if (anAng < 0)
  {
    anAng = -anAng;
  }
  return anAng <= theAngularTolerance || M_PI - anAng <= theAngularTolerance;
}

inline void gp_Dir2d::Rotate(const double theAng)
{
  gp_Trsf2d aT;
  aT.SetRotation(gp_Pnt2d(0.0, 0.0), theAng);
  coord.Multiply(aT.HVectorialPart());
}
