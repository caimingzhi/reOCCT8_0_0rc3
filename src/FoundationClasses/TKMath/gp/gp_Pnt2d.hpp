#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_XY.hpp>
#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>

class gp_Ax2d;
class gp_Trsf2d;
class gp_Vec2d;

class gp_Pnt2d
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Pnt2d() noexcept

    = default;

  constexpr gp_Pnt2d(const gp_XY& theCoord) noexcept
      : coord(theCoord)
  {
  }

  constexpr gp_Pnt2d(const double theXp, const double theYp) noexcept
      : coord(theXp, theYp)
  {
  }

  constexpr void SetCoord(const int theIndex, const double theXi)
  {
    coord.SetCoord(theIndex, theXi);
  }

  constexpr void SetCoord(const double theXp, const double theYp) noexcept
  {
    coord.SetCoord(theXp, theYp);
  }

  constexpr void SetX(const double theX) noexcept { coord.SetX(theX); }

  constexpr void SetY(const double theY) noexcept { coord.SetY(theY); }

  constexpr void SetXY(const gp_XY& theCoord) noexcept { coord = theCoord; }

  constexpr double Coord(const int theIndex) const { return coord.Coord(theIndex); }

  constexpr void Coord(double& theXp, double& theYp) const noexcept { coord.Coord(theXp, theYp); }

  constexpr double X() const noexcept { return coord.X(); }

  constexpr double Y() const noexcept { return coord.Y(); }

  constexpr const gp_XY& XY() const noexcept { return coord; }

  constexpr const gp_XY& Coord() const noexcept { return coord; }

  constexpr gp_XY& ChangeCoord() noexcept { return coord; }

  bool IsEqual(const gp_Pnt2d& theOther, const double theLinearTolerance) const
  {
    return Distance(theOther) <= theLinearTolerance;
  }

  double Distance(const gp_Pnt2d& theOther) const;

  constexpr double SquareDistance(const gp_Pnt2d& theOther) const noexcept;

  Standard_EXPORT void Mirror(const gp_Pnt2d& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Pnt2d Mirrored(const gp_Pnt2d& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2d& theA) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Pnt2d Mirrored(const gp_Ax2d& theA) const noexcept;

  void Rotate(const gp_Pnt2d& theP, const double theAng);

  [[nodiscard]] gp_Pnt2d Rotated(const gp_Pnt2d& theP, const double theAng) const
  {
    gp_Pnt2d aPres = *this;
    aPres.Rotate(theP, theAng);
    return aPres;
  }

  constexpr void Scale(const gp_Pnt2d& theP, const double theS) noexcept;

  [[nodiscard]] constexpr gp_Pnt2d Scaled(const gp_Pnt2d& theP, const double theS) const noexcept
  {
    gp_Pnt2d aPres = *this;
    aPres.Scale(theP, theS);
    return aPres;
  }

  Standard_EXPORT void Transform(const gp_Trsf2d& theT) noexcept;

  [[nodiscard]] gp_Pnt2d Transformed(const gp_Trsf2d& theT) const
  {
    gp_Pnt2d aPres = *this;
    aPres.Transform(theT);
    return aPres;
  }

  constexpr void Translate(const gp_Vec2d& theV) noexcept;

  [[nodiscard]] constexpr gp_Pnt2d Translated(const gp_Vec2d& theV) const noexcept;

  constexpr void Translate(const gp_Pnt2d& theP1, const gp_Pnt2d& theP2) noexcept
  {
    coord.Add(theP2.coord);
    coord.Subtract(theP1.coord);
  }

  [[nodiscard]] constexpr gp_Pnt2d Translated(const gp_Pnt2d& theP1,
                                              const gp_Pnt2d& theP2) const noexcept
  {
    gp_Pnt2d aP = *this;
    aP.Translate(theP1, theP2);
    return aP;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  gp_XY coord;
};

#include <gp_Vec2d.hpp>
#include <gp_Trsf2d.hpp>

inline double gp_Pnt2d::Distance(const gp_Pnt2d& theOther) const
{
  const gp_XY& aXY = theOther.coord;
  double       aX  = coord.X() - aXY.X();
  double       aY  = coord.Y() - aXY.Y();
  return sqrt(aX * aX + aY * aY);
}

inline constexpr double gp_Pnt2d::SquareDistance(const gp_Pnt2d& theOther) const noexcept
{
  const gp_XY& aXY = theOther.coord;
  double       aX  = coord.X() - aXY.X();
  double       aY  = coord.Y() - aXY.Y();
  return (aX * aX + aY * aY);
}

inline void gp_Pnt2d::Rotate(const gp_Pnt2d& theP, const double theAng)
{
  gp_Trsf2d aT;
  aT.SetRotation(theP, theAng);
  aT.Transforms(coord);
}

inline constexpr void gp_Pnt2d::Scale(const gp_Pnt2d& theP, const double theS) noexcept
{
  gp_XY aXY = theP.coord;
  aXY.Multiply(1.0 - theS);
  coord.Multiply(theS);
  coord.Add(aXY);
}

inline constexpr void gp_Pnt2d::Translate(const gp_Vec2d& theV) noexcept
{
  coord.Add(theV.XY());
}

inline constexpr gp_Pnt2d gp_Pnt2d::Translated(const gp_Vec2d& theV) const noexcept
{
  gp_Pnt2d aP = *this;
  aP.coord.Add(theV.XY());
  return aP;
}
