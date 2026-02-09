#pragma once

#include <gp_Ax2d.hpp>

class gp_Lin2d
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Lin2d() noexcept = default;

  constexpr gp_Lin2d(const gp_Ax2d& theA) noexcept
      : pos(theA)
  {
  }

  constexpr gp_Lin2d(const gp_Pnt2d& theP, const gp_Dir2d& theV) noexcept
      : pos(theP, theV)
  {
  }

  Standard_EXPORT gp_Lin2d(const double theA, const double theB, const double theC);

  constexpr void Reverse() noexcept { pos.Reverse(); }

  [[nodiscard]] constexpr gp_Lin2d Reversed() const noexcept
  {
    gp_Lin2d aL = *this;
    aL.pos.Reverse();
    return aL;
  }

  constexpr void SetDirection(const gp_Dir2d& theV) noexcept { pos.SetDirection(theV); }

  constexpr void SetLocation(const gp_Pnt2d& theP) noexcept { pos.SetLocation(theP); }

  constexpr void SetPosition(const gp_Ax2d& theA) noexcept { pos = theA; }

  constexpr void Coefficients(double& theA, double& theB, double& theC) const noexcept
  {
    theA = pos.Direction().Y();
    theB = -pos.Direction().X();
    theC = -(theA * pos.Location().X() + theB * pos.Location().Y());
  }

  constexpr const gp_Dir2d& Direction() const noexcept { return pos.Direction(); }

  constexpr const gp_Pnt2d& Location() const noexcept { return pos.Location(); }

  constexpr const gp_Ax2d& Position() const noexcept { return pos; }

  double Angle(const gp_Lin2d& theOther) const
  {
    return pos.Direction().Angle(theOther.pos.Direction());
  }

  bool Contains(const gp_Pnt2d& theP, const double theLinearTolerance) const noexcept
  {
    return Distance(theP) <= theLinearTolerance;
  }

  double Distance(const gp_Pnt2d& theP) const noexcept;

  double Distance(const gp_Lin2d& theOther) const noexcept;

  constexpr double SquareDistance(const gp_Pnt2d& theP) const noexcept;

  double SquareDistance(const gp_Lin2d& theOther) const noexcept;

  gp_Lin2d Normal(const gp_Pnt2d& theP) const noexcept
  {
    return gp_Lin2d(gp_Ax2d(theP, gp_Dir2d(-(pos.Direction().Y()), pos.Direction().X())));
  }

  Standard_EXPORT void Mirror(const gp_Pnt2d& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Lin2d Mirrored(const gp_Pnt2d& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2d& theA) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Lin2d Mirrored(const gp_Ax2d& theA) const noexcept;

  void Rotate(const gp_Pnt2d& theP, const double theAng) { pos.Rotate(theP, theAng); }

  [[nodiscard]] gp_Lin2d Rotated(const gp_Pnt2d& theP, const double theAng) const
  {
    gp_Lin2d aL = *this;
    aL.pos.Rotate(theP, theAng);
    return aL;
  }

  void Scale(const gp_Pnt2d& theP, const double theS) { pos.Scale(theP, theS); }

  [[nodiscard]] gp_Lin2d Scaled(const gp_Pnt2d& theP, const double theS) const
  {
    gp_Lin2d aL = *this;
    aL.pos.Scale(theP, theS);
    return aL;
  }

  void Transform(const gp_Trsf2d& theT) noexcept { pos.Transform(theT); }

  [[nodiscard]] gp_Lin2d Transformed(const gp_Trsf2d& theT) const noexcept
  {
    gp_Lin2d aL = *this;
    aL.pos.Transform(theT);
    return aL;
  }

  constexpr void Translate(const gp_Vec2d& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Lin2d Translated(const gp_Vec2d& theV) const noexcept
  {
    gp_Lin2d aL = *this;
    aL.pos.Translate(theV);
    return aL;
  }

  constexpr void Translate(const gp_Pnt2d& theP1, const gp_Pnt2d& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Lin2d Translated(const gp_Pnt2d& theP1,
                                              const gp_Pnt2d& theP2) const noexcept
  {
    gp_Lin2d aL = *this;
    aL.pos.Translate(gp_Vec2d(theP1, theP2));
    return aL;
  }

private:
  gp_Ax2d pos;
};

inline double gp_Lin2d::Distance(const gp_Pnt2d& theP) const noexcept
{
  gp_XY aCoord = theP.XY();
  aCoord.Subtract((pos.Location()).XY());
  return std::abs(aCoord.Crossed(pos.Direction().XY()));
}

inline double gp_Lin2d::Distance(const gp_Lin2d& theOther) const noexcept
{
  double aD = 0.0;
  if (pos.IsParallel(theOther.pos, gp::Resolution()))
  {
    aD = theOther.Distance(pos.Location());
  }
  return aD;
}

inline constexpr double gp_Lin2d::SquareDistance(const gp_Pnt2d& theP) const noexcept
{
  gp_XY aCoord = theP.XY();
  aCoord.Subtract((pos.Location()).XY());
  double aD = aCoord.Crossed(pos.Direction().XY());
  return aD * aD;
}

inline double gp_Lin2d::SquareDistance(const gp_Lin2d& theOther) const noexcept
{
  double aD = 0.0;
  if (pos.IsParallel(theOther.pos, gp::Resolution()))
  {
    aD = theOther.SquareDistance(pos.Location());
  }
  return aD;
}
