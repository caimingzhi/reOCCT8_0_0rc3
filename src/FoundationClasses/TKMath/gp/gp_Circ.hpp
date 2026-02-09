#pragma once

#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <Standard_ConstructionError.hpp>

class gp_Circ
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Circ() noexcept
      : radius(RealLast())
  {
  }

  constexpr gp_Circ(const gp_Ax2& theA2, const double theRadius)
      : pos(theA2),
        radius(theRadius)
  {
    Standard_ConstructionError_Raise_if(theRadius < 0.0,
                                        "gp_Circ() - radius should be positive number");
  }

  void SetAxis(const gp_Ax1& theA1) { pos.SetAxis(theA1); }

  constexpr void SetLocation(const gp_Pnt& theP) noexcept { pos.SetLocation(theP); }

  constexpr void SetPosition(const gp_Ax2& theA2) noexcept { pos = theA2; }

  void SetRadius(const double theRadius)
  {
    Standard_ConstructionError_Raise_if(theRadius < 0.0,
                                        "gp_Circ::SetRadius() - radius should be positive number");
    radius = theRadius;
  }

  constexpr double Area() const noexcept { return M_PI * radius * radius; }

  constexpr const gp_Ax1& Axis() const noexcept { return pos.Axis(); }

  constexpr double Length() const noexcept { return 2. * M_PI * radius; }

  constexpr const gp_Pnt& Location() const noexcept { return pos.Location(); }

  constexpr const gp_Ax2& Position() const noexcept { return pos; }

  constexpr double Radius() const noexcept { return radius; }

  constexpr gp_Ax1 XAxis() const noexcept { return gp_Ax1(pos.Location(), pos.XDirection()); }

  constexpr gp_Ax1 YAxis() const noexcept { return gp_Ax1(pos.Location(), pos.YDirection()); }

  double Distance(const gp_Pnt& theP) const noexcept { return sqrt(SquareDistance(theP)); }

  double SquareDistance(const gp_Pnt& theP) const noexcept
  {
    gp_Vec aV(Location(), theP);
    double aX  = aV.Dot(pos.XDirection());
    double anY = aV.Dot(pos.YDirection());
    double aZ  = aV.Dot(pos.Direction());
    double aT  = sqrt(aX * aX + anY * anY) - radius;
    return (aT * aT + aZ * aZ);
  }

  bool Contains(const gp_Pnt& theP, const double theLinearTolerance) const noexcept
  {
    return Distance(theP) <= theLinearTolerance;
  }

  Standard_EXPORT void Mirror(const gp_Pnt& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Circ Mirrored(const gp_Pnt& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& theA1);

  [[nodiscard]] Standard_EXPORT gp_Circ Mirrored(const gp_Ax1& theA1) const;

  Standard_EXPORT void Mirror(const gp_Ax2& theA2);

  [[nodiscard]] Standard_EXPORT gp_Circ Mirrored(const gp_Ax2& theA2) const;

  void Rotate(const gp_Ax1& theA1, const double theAng) { pos.Rotate(theA1, theAng); }

  [[nodiscard]] gp_Circ Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Circ aC = *this;
    aC.pos.Rotate(theA1, theAng);
    return aC;
  }

  void Scale(const gp_Pnt& theP, const double theS);

  [[nodiscard]] gp_Circ Scaled(const gp_Pnt& theP, const double theS) const;

  void Transform(const gp_Trsf& theT);

  [[nodiscard]] gp_Circ Transformed(const gp_Trsf& theT) const;

  constexpr void Translate(const gp_Vec& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Circ Translated(const gp_Vec& theV) const noexcept
  {
    gp_Circ aC = *this;
    aC.pos.Translate(theV);
    return aC;
  }

  constexpr void Translate(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Circ Translated(const gp_Pnt& theP1,
                                             const gp_Pnt& theP2) const noexcept
  {
    gp_Circ aC = *this;
    aC.pos.Translate(theP1, theP2);
    return aC;
  }

private:
  gp_Ax2 pos;
  double radius;
};

inline void gp_Circ::Scale(const gp_Pnt& theP, const double theS)
{
  radius *= theS;
  if (radius < 0)
  {
    radius = -radius;
  }
  pos.Scale(theP, theS);
}

inline gp_Circ gp_Circ::Scaled(const gp_Pnt& theP, const double theS) const
{
  gp_Circ aC = *this;
  aC.radius *= theS;
  if (aC.radius < 0)
  {
    aC.radius = -aC.radius;
  }
  aC.pos.Scale(theP, theS);
  return aC;
}

inline void gp_Circ::Transform(const gp_Trsf& theT)
{
  radius *= theT.ScaleFactor();
  if (radius < 0)
  {
    radius = -radius;
  }
  pos.Transform(theT);
}

inline gp_Circ gp_Circ::Transformed(const gp_Trsf& theT) const
{
  gp_Circ aC = *this;
  aC.radius *= theT.ScaleFactor();
  if (aC.radius < 0)
  {
    aC.radius = -aC.radius;
  }
  aC.pos.Transform(theT);
  return aC;
}
