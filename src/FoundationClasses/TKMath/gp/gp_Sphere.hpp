#pragma once

#include <gp_Ax1.hpp>
#include <gp_Ax3.hpp>
#include <Standard_ConstructionError.hpp>

class gp_Sphere
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Sphere() noexcept
      : radius(RealLast())
  {
  }

  constexpr gp_Sphere(const gp_Ax3& theA3, const double theRadius)
      : pos(theA3),
        radius(theRadius)
  {
    Standard_ConstructionError_Raise_if(theRadius < 0.0, "gp_Sphere() - radius should be >= 0");
  }

  constexpr void SetLocation(const gp_Pnt& theLoc) noexcept { pos.SetLocation(theLoc); }

  constexpr void SetPosition(const gp_Ax3& theA3) noexcept { pos = theA3; }

  void SetRadius(const double theR)
  {
    Standard_ConstructionError_Raise_if(theR < 0.0,
                                        "gp_Sphere::SetRadius() - radius should be >= 0");
    radius = theR;
  }

  constexpr double Area() const noexcept { return 4.0 * M_PI * radius * radius; }

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

  constexpr void UReverse() noexcept { pos.YReverse(); }

  constexpr void VReverse() noexcept { pos.ZReverse(); }

  bool Direct() const { return pos.Direct(); }

  constexpr const gp_Pnt& Location() const noexcept { return pos.Location(); }

  constexpr const gp_Ax3& Position() const noexcept { return pos; }

  constexpr double Radius() const noexcept { return radius; }

  constexpr double Volume() const noexcept { return (4.0 * M_PI * radius * radius * radius) / 3.0; }

  constexpr gp_Ax1 XAxis() const noexcept { return gp_Ax1(pos.Location(), pos.XDirection()); }

  constexpr gp_Ax1 YAxis() const noexcept { return gp_Ax1(pos.Location(), pos.YDirection()); }

  Standard_EXPORT void Mirror(const gp_Pnt& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Sphere Mirrored(const gp_Pnt& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& theA1) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Sphere Mirrored(const gp_Ax1& theA1) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2& theA2) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Sphere Mirrored(const gp_Ax2& theA2) const noexcept;

  void Rotate(const gp_Ax1& theA1, const double theAng) { pos.Rotate(theA1, theAng); }

  [[nodiscard]] gp_Sphere Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Sphere aC = *this;
    aC.pos.Rotate(theA1, theAng);
    return aC;
  }

  void Scale(const gp_Pnt& theP, const double theS);

  [[nodiscard]] gp_Sphere Scaled(const gp_Pnt& theP, const double theS) const;

  void Transform(const gp_Trsf& theT);

  [[nodiscard]] gp_Sphere Transformed(const gp_Trsf& theT) const;

  constexpr void Translate(const gp_Vec& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Sphere Translated(const gp_Vec& theV) const noexcept
  {
    gp_Sphere aC = *this;
    aC.pos.Translate(theV);
    return aC;
  }

  constexpr void Translate(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Sphere Translated(const gp_Pnt& theP1,
                                               const gp_Pnt& theP2) const noexcept
  {
    gp_Sphere aC = *this;
    aC.pos.Translate(theP1, theP2);
    return aC;
  }

private:
  gp_Ax3 pos;
  double radius;
};

inline void gp_Sphere::Scale(const gp_Pnt& theP, const double theS)
{
  pos.Scale(theP, theS);
  radius *= theS;
  if (radius < 0)
  {
    radius = -radius;
  }
}

inline gp_Sphere gp_Sphere::Scaled(const gp_Pnt& theP, const double theS) const
{
  gp_Sphere aC = *this;
  aC.pos.Scale(theP, theS);
  aC.radius *= theS;
  if (aC.radius < 0)
  {
    aC.radius = -aC.radius;
  }
  return aC;
}

inline void gp_Sphere::Transform(const gp_Trsf& theT)
{
  pos.Transform(theT);
  radius *= theT.ScaleFactor();
  if (radius < 0)
  {
    radius = -radius;
  }
}

inline gp_Sphere gp_Sphere::Transformed(const gp_Trsf& theT) const
{
  gp_Sphere aC = *this;
  aC.pos.Transform(theT);
  aC.radius *= theT.ScaleFactor();
  if (aC.radius < 0)
  {
    aC.radius = -aC.radius;
  }
  return aC;
}
