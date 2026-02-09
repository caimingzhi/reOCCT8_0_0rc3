#pragma once

#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>

class gp_Lin
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Lin() noexcept = default;

  constexpr gp_Lin(const gp_Ax1& theA1) noexcept
      : pos(theA1)
  {
  }

  constexpr gp_Lin(const gp_Pnt& theP, const gp_Dir& theV) noexcept
      : pos(theP, theV)
  {
  }

  constexpr void Reverse() noexcept { pos.Reverse(); }

  [[nodiscard]] constexpr gp_Lin Reversed() const noexcept
  {
    gp_Lin aL = *this;
    aL.pos.Reverse();
    return aL;
  }

  constexpr void SetDirection(const gp_Dir& theV) noexcept { pos.SetDirection(theV); }

  constexpr void SetLocation(const gp_Pnt& theP) noexcept { pos.SetLocation(theP); }

  constexpr void SetPosition(const gp_Ax1& theA1) noexcept { pos = theA1; }

  constexpr const gp_Dir& Direction() const noexcept { return pos.Direction(); }

  constexpr const gp_Pnt& Location() const noexcept { return pos.Location(); }

  constexpr const gp_Ax1& Position() const noexcept { return pos; }

  double Angle(const gp_Lin& theOther) const noexcept
  {
    return pos.Direction().Angle(theOther.pos.Direction());
  }

  bool Contains(const gp_Pnt& theP, const double theLinearTolerance) const noexcept
  {
    return Distance(theP) <= theLinearTolerance;
  }

  double Distance(const gp_Pnt& theP) const noexcept;

  Standard_EXPORT double Distance(const gp_Lin& theOther) const;

  double SquareDistance(const gp_Pnt& theP) const noexcept;

  double SquareDistance(const gp_Lin& theOther) const noexcept
  {
    double aD = Distance(theOther);
    return aD * aD;
  }

  gp_Lin Normal(const gp_Pnt& theP) const;

  Standard_EXPORT void Mirror(const gp_Pnt& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Lin Mirrored(const gp_Pnt& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& theA1) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Lin Mirrored(const gp_Ax1& theA1) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2& theA2) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Lin Mirrored(const gp_Ax2& theA2) const noexcept;

  void Rotate(const gp_Ax1& theA1, const double theAng) { pos.Rotate(theA1, theAng); }

  [[nodiscard]] gp_Lin Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Lin aL = *this;
    aL.pos.Rotate(theA1, theAng);
    return aL;
  }

  void Scale(const gp_Pnt& theP, const double theS) { pos.Scale(theP, theS); }

  [[nodiscard]] gp_Lin Scaled(const gp_Pnt& theP, const double theS) const
  {
    gp_Lin aL = *this;
    aL.pos.Scale(theP, theS);
    return aL;
  }

  void Transform(const gp_Trsf& theT) { pos.Transform(theT); }

  [[nodiscard]] gp_Lin Transformed(const gp_Trsf& theT) const
  {
    gp_Lin aL = *this;
    aL.pos.Transform(theT);
    return aL;
  }

  constexpr void Translate(const gp_Vec& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Lin Translated(const gp_Vec& theV) const noexcept
  {
    gp_Lin aL = *this;
    aL.pos.Translate(theV);
    return aL;
  }

  constexpr void Translate(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Lin Translated(const gp_Pnt& theP1, const gp_Pnt& theP2) const noexcept
  {
    gp_Lin aL = *this;
    aL.pos.Translate(gp_Vec(theP1, theP2));
    return aL;
  }

private:
  gp_Ax1 pos;
};

inline double gp_Lin::Distance(const gp_Pnt& theP) const noexcept
{
  gp_XYZ aCoord = theP.XYZ();
  aCoord.Subtract((pos.Location()).XYZ());
  aCoord.Cross((pos.Direction()).XYZ());
  return aCoord.Modulus();
}

inline double gp_Lin::SquareDistance(const gp_Pnt& theP) const noexcept
{
  const gp_Pnt& aLoc = pos.Location();
  gp_Vec        aV(theP.X() - aLoc.X(), theP.Y() - aLoc.Y(), theP.Z() - aLoc.Z());
  aV.Cross(pos.Direction());
  return aV.SquareMagnitude();
}

inline gp_Lin gp_Lin::Normal(const gp_Pnt& theP) const
{
  const gp_Pnt& aLoc = pos.Location();
  gp_Dir        aV(theP.X() - aLoc.X(), theP.Y() - aLoc.Y(), theP.Z() - aLoc.Z());
  aV = pos.Direction().CrossCrossed(aV, pos.Direction());
  return gp_Lin(theP, aV);
}
