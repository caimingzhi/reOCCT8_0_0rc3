#pragma once

#include <gp_Ax22d.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_ConstructionError.hpp>

class gp_Circ2d
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Circ2d() noexcept
      : radius(RealLast())
  {
  }

  constexpr gp_Circ2d(const gp_Ax2d& theXAxis, const double theRadius, const bool theIsSense = true)
      : pos(theXAxis, theIsSense),
        radius(theRadius)
  {
    Standard_ConstructionError_Raise_if(theRadius < 0.0,
                                        "gp_Circ2d() - radius should be positive number");
  }

  constexpr gp_Circ2d(const gp_Ax22d& theAxis, const double theRadius)
      : pos(theAxis),
        radius(theRadius)
  {
    Standard_ConstructionError_Raise_if(theRadius < 0.0,
                                        "gp_Circ2d() - radius should be positive number");
  }

  constexpr void SetLocation(const gp_Pnt2d& theP) noexcept { pos.SetLocation(theP); }

  constexpr void SetXAxis(const gp_Ax2d& theA) { pos.SetXAxis(theA); }

  constexpr void SetAxis(const gp_Ax22d& theA) noexcept { pos.SetAxis(theA); }

  constexpr void SetYAxis(const gp_Ax2d& theA) { pos.SetYAxis(theA); }

  void SetRadius(const double theRadius)
  {
    Standard_ConstructionError_Raise_if(
      theRadius < 0.0,
      "gp_Circ2d::SetRadius() - radius should be positive number");
    radius = theRadius;
  }

  constexpr double Area() const noexcept { return M_PI * radius * radius; }

  constexpr void Coefficients(double& theA,
                              double& theB,
                              double& theC,
                              double& theD,
                              double& theE,
                              double& theF) const noexcept;

  bool Contains(const gp_Pnt2d& theP, const double theLinearTolerance) const noexcept
  {
    return Distance(theP) <= theLinearTolerance;
  }

  double Distance(const gp_Pnt2d& theP) const noexcept;

  double SquareDistance(const gp_Pnt2d& theP) const noexcept;

  constexpr double Length() const noexcept { return 2. * M_PI * radius; }

  constexpr const gp_Pnt2d& Location() const noexcept { return pos.Location(); }

  constexpr double Radius() const noexcept { return radius; }

  constexpr const gp_Ax22d& Axis() const noexcept { return pos; }

  constexpr const gp_Ax22d& Position() const noexcept { return pos; }

  gp_Ax2d XAxis() const noexcept { return gp_Ax2d(pos.XAxis()); }

  gp_Ax2d YAxis() const noexcept { return gp_Ax2d(pos.YAxis()); }

  void Reverse() noexcept
  {
    gp_Dir2d aTemp = pos.YDirection();
    aTemp.Reverse();
    pos.SetAxis(gp_Ax22d(pos.Location(), pos.XDirection(), aTemp));
  }

  [[nodiscard]] gp_Circ2d Reversed() const noexcept;

  constexpr bool IsDirect() const noexcept
  {
    return (pos.XDirection().Crossed(pos.YDirection())) >= 0.0;
  }

  Standard_EXPORT void Mirror(const gp_Pnt2d& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Circ2d Mirrored(const gp_Pnt2d& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2d& theA) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Circ2d Mirrored(const gp_Ax2d& theA) const noexcept;

  void Rotate(const gp_Pnt2d& theP, const double theAng) { pos.Rotate(theP, theAng); }

  [[nodiscard]] gp_Circ2d Rotated(const gp_Pnt2d& theP, const double theAng) const
  {
    gp_Circ2d aCirc = *this;
    aCirc.pos.Rotate(theP, theAng);
    return aCirc;
  }

  void Scale(const gp_Pnt2d& theP, const double theS);

  [[nodiscard]] gp_Circ2d Scaled(const gp_Pnt2d& theP, const double theS) const;

  void Transform(const gp_Trsf2d& theT);

  [[nodiscard]] gp_Circ2d Transformed(const gp_Trsf2d& theT) const;

  constexpr void Translate(const gp_Vec2d& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Circ2d Translated(const gp_Vec2d& theV) const noexcept
  {
    gp_Circ2d aCirc = *this;
    aCirc.pos.Translate(theV);
    return aCirc;
  }

  constexpr void Translate(const gp_Pnt2d& theP1, const gp_Pnt2d& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Circ2d Translated(const gp_Pnt2d& theP1,
                                               const gp_Pnt2d& theP2) const noexcept
  {
    gp_Circ2d aCirc = *this;
    aCirc.pos.Translate(theP1, theP2);
    return aCirc;
  }

private:
  gp_Ax22d pos;
  double   radius;
};

constexpr inline void gp_Circ2d::Coefficients(double& theA,
                                              double& theB,
                                              double& theC,
                                              double& theD,
                                              double& theE,
                                              double& theF) const noexcept
{
  double aXc  = pos.Location().X();
  double anYc = pos.Location().Y();
  theA        = 1.0;
  theB        = 1.0;
  theC        = 0.0;
  theD        = -aXc;
  theE        = -anYc;
  theF        = aXc * aXc + anYc * anYc - radius * radius;
}

inline double gp_Circ2d::Distance(const gp_Pnt2d& theP) const noexcept
{
  gp_XY aCoord = theP.XY();
  aCoord.Subtract(pos.Location().XY());
  double aD = radius - aCoord.Modulus();
  if (aD < 0)
  {
    aD = -aD;
  }
  return aD;
}

inline gp_Circ2d gp_Circ2d::Reversed() const noexcept
{
  gp_Circ2d aCirc = *this;
  gp_Dir2d  aTemp = pos.YDirection();
  aTemp.Reverse();
  aCirc.pos.SetAxis(gp_Ax22d(pos.Location(), pos.XDirection(), aTemp));
  return aCirc;
}

inline double gp_Circ2d::SquareDistance(const gp_Pnt2d& theP) const noexcept
{
  gp_XY aCoord = theP.XY();
  aCoord.Subtract(pos.Location().XY());
  double aD = radius - aCoord.Modulus();
  return aD * aD;
}

inline void gp_Circ2d::Scale(const gp_Pnt2d& theP, const double theS)
{
  radius *= theS;
  if (radius < 0)
  {
    radius = -radius;
  }
  pos.Scale(theP, theS);
}

inline gp_Circ2d gp_Circ2d::Scaled(const gp_Pnt2d& theP, const double theS) const
{
  gp_Circ2d aCirc = *this;
  aCirc.radius *= theS;
  if (aCirc.radius < 0)
  {
    aCirc.radius = -aCirc.radius;
  }
  aCirc.pos.Scale(theP, theS);
  return aCirc;
}

inline void gp_Circ2d::Transform(const gp_Trsf2d& theT)
{
  radius *= theT.ScaleFactor();
  if (radius < 0)
  {
    radius = -radius;
  }
  pos.Transform(theT);
}

inline gp_Circ2d gp_Circ2d::Transformed(const gp_Trsf2d& theT) const
{
  gp_Circ2d aCirc = *this;
  aCirc.radius *= theT.ScaleFactor();
  if (aCirc.radius < 0)
  {
    aCirc.radius = -aCirc.radius;
  }
  aCirc.pos.Transform(theT);
  return aCirc;
}
