#pragma once

#include <gp_Ax1.hpp>
#include <gp_Ax3.hpp>
#include <gp_Pnt.hpp>

class gp_Cone
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Cone() noexcept
      : radius(RealLast()),
        semiAngle(M_PI * 0.25)
  {
  }

  constexpr gp_Cone(const gp_Ax3& theA3, const double theAng, const double theRadius);

  void SetAxis(const gp_Ax1& theA1) { pos.SetAxis(theA1); }

  constexpr void SetLocation(const gp_Pnt& theLoc) noexcept { pos.SetLocation(theLoc); }

  constexpr void SetPosition(const gp_Ax3& theA3) noexcept { pos = theA3; }

  void SetRadius(const double theR)
  {
    Standard_ConstructionError_Raise_if(theR < 0.0,
                                        "gp_Cone::SetRadius() - radius should be positive number");
    radius = theR;
  }

  void SetSemiAngle(const double theAng);

  gp_Pnt Apex() const
  {
    gp_XYZ aCoord = pos.Direction().XYZ();
    aCoord.Multiply(-radius / std::tan(semiAngle));
    aCoord.Add(pos.Location().XYZ());
    return gp_Pnt(aCoord);
  }

  constexpr void UReverse() noexcept { pos.YReverse(); }

  constexpr void VReverse() noexcept
  {
    pos.ZReverse();
    semiAngle = -semiAngle;
  }

  bool Direct() const { return pos.Direct(); }

  constexpr const gp_Ax1& Axis() const noexcept { return pos.Axis(); }

  Standard_EXPORT void Coefficients(double& theA1,
                                    double& theA2,
                                    double& theA3,
                                    double& theB1,
                                    double& theB2,
                                    double& theB3,
                                    double& theC1,
                                    double& theC2,
                                    double& theC3,
                                    double& theD) const;

  constexpr const gp_Pnt& Location() const noexcept { return pos.Location(); }

  constexpr const gp_Ax3& Position() const noexcept { return pos; }

  constexpr double RefRadius() const noexcept { return radius; }

  constexpr double SemiAngle() const noexcept { return semiAngle; }

  constexpr gp_Ax1 XAxis() const noexcept { return gp_Ax1(pos.Location(), pos.XDirection()); }

  constexpr gp_Ax1 YAxis() const noexcept { return gp_Ax1(pos.Location(), pos.YDirection()); }

  Standard_EXPORT void Mirror(const gp_Pnt& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Cone Mirrored(const gp_Pnt& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& theA1) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Cone Mirrored(const gp_Ax1& theA1) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2& theA2) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Cone Mirrored(const gp_Ax2& theA2) const noexcept;

  void Rotate(const gp_Ax1& theA1, const double theAng) { pos.Rotate(theA1, theAng); }

  [[nodiscard]] gp_Cone Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Cone aCone = *this;
    aCone.pos.Rotate(theA1, theAng);
    return aCone;
  }

  void Scale(const gp_Pnt& theP, const double theS);

  [[nodiscard]] gp_Cone Scaled(const gp_Pnt& theP, const double theS) const;

  void Transform(const gp_Trsf& theT);

  [[nodiscard]] gp_Cone Transformed(const gp_Trsf& theT) const;

  constexpr void Translate(const gp_Vec& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Cone Translated(const gp_Vec& theV) const noexcept
  {
    gp_Cone aCone = *this;
    aCone.pos.Translate(theV);
    return aCone;
  }

  constexpr void Translate(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Cone Translated(const gp_Pnt& theP1,
                                             const gp_Pnt& theP2) const noexcept
  {
    gp_Cone aCone = *this;
    aCone.pos.Translate(theP1, theP2);
    return aCone;
  }

private:
  gp_Ax3 pos;
  double radius;
  double semiAngle;
};

inline constexpr gp_Cone::gp_Cone(const gp_Ax3& theA3, const double theAng, const double theRadius)
    : pos(theA3),
      radius(theRadius),
      semiAngle(theAng)
{
  [[maybe_unused]] const double anAbsAng = theAng < 0. ? -theAng : theAng;
  Standard_ConstructionError_Raise_if(theRadius < 0. || anAbsAng <= gp::Resolution()
                                        || M_PI * 0.5 - anAbsAng <= gp::Resolution(),
                                      "gp_Cone() - invalid construction parameters");
}

inline void gp_Cone::SetSemiAngle(const double theAng)
{
  Standard_ConstructionError_Raise_if(std::abs(theAng) <= gp::Resolution()
                                        || M_PI * 0.5 - std::abs(theAng) <= gp::Resolution(),
                                      "gp_Cone::SetSemiAngle() - invalid angle range");
  semiAngle = theAng;
}

inline void gp_Cone::Scale(const gp_Pnt& theP, const double theS)
{
  pos.Scale(theP, theS);
  radius *= theS;
  if (radius < 0)
  {
    radius = -radius;
  }
}

inline gp_Cone gp_Cone::Scaled(const gp_Pnt& theP, const double theS) const
{
  gp_Cone aC = *this;
  aC.pos.Scale(theP, theS);
  aC.radius *= theS;
  if (aC.radius < 0)
  {
    aC.radius = -aC.radius;
  }
  return aC;
}

inline void gp_Cone::Transform(const gp_Trsf& theT)
{
  pos.Transform(theT);
  radius *= theT.ScaleFactor();
  if (radius < 0)
  {
    radius = -radius;
  }
}

inline gp_Cone gp_Cone::Transformed(const gp_Trsf& theT) const
{
  gp_Cone aC = *this;
  aC.pos.Transform(theT);
  aC.radius *= theT.ScaleFactor();
  if (aC.radius < 0)
  {
    aC.radius = -aC.radius;
  }
  return aC;
}
