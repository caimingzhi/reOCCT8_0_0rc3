#pragma once

#include <gp_Ax1.hpp>
#include <gp_Ax3.hpp>

class gp_Cylinder
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Cylinder() noexcept
      : radius(RealLast())
  {
  }

  constexpr gp_Cylinder(const gp_Ax3& theA3, const double theRadius)
      : pos(theA3),
        radius(theRadius)
  {
    Standard_ConstructionError_Raise_if(theRadius < 0.0,
                                        "gp_Cylinder() - radius should be positive number");
  }

  void SetAxis(const gp_Ax1& theA1) { pos.SetAxis(theA1); }

  constexpr void SetLocation(const gp_Pnt& theLoc) noexcept { pos.SetLocation(theLoc); }

  constexpr void SetPosition(const gp_Ax3& theA3) noexcept { pos = theA3; }

  void SetRadius(const double theR)
  {
    Standard_ConstructionError_Raise_if(
      theR < 0.0,
      "gp_Cylinder::SetRadius() - radius should be positive number");
    radius = theR;
  }

  constexpr void UReverse() noexcept { pos.YReverse(); }

  constexpr void VReverse() noexcept { pos.ZReverse(); }

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

  constexpr double Radius() const noexcept { return radius; }

  constexpr gp_Ax1 XAxis() const noexcept { return gp_Ax1(pos.Location(), pos.XDirection()); }

  constexpr gp_Ax1 YAxis() const noexcept { return gp_Ax1(pos.Location(), pos.YDirection()); }

  Standard_EXPORT void Mirror(const gp_Pnt& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Cylinder Mirrored(const gp_Pnt& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& theA1) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Cylinder Mirrored(const gp_Ax1& theA1) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2& theA2) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Cylinder Mirrored(const gp_Ax2& theA2) const noexcept;

  void Rotate(const gp_Ax1& theA1, const double theAng) { pos.Rotate(theA1, theAng); }

  [[nodiscard]] gp_Cylinder Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Cylinder aCyl = *this;
    aCyl.pos.Rotate(theA1, theAng);
    return aCyl;
  }

  void Scale(const gp_Pnt& theP, const double theS);

  [[nodiscard]] gp_Cylinder Scaled(const gp_Pnt& theP, const double theS) const;

  void Transform(const gp_Trsf& theT);

  [[nodiscard]] gp_Cylinder Transformed(const gp_Trsf& theT) const;

  constexpr void Translate(const gp_Vec& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Cylinder Translated(const gp_Vec& theV) const noexcept
  {
    gp_Cylinder aCyl = *this;
    aCyl.pos.Translate(theV);
    return aCyl;
  }

  constexpr void Translate(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Cylinder Translated(const gp_Pnt& theP1,
                                                 const gp_Pnt& theP2) const noexcept
  {
    gp_Cylinder aCyl = *this;
    aCyl.pos.Translate(theP1, theP2);
    return aCyl;
  }

private:
  gp_Ax3 pos;
  double radius;
};

inline void gp_Cylinder::Scale(const gp_Pnt& theP, const double theS)
{
  pos.Scale(theP, theS);
  radius *= theS;
  if (radius < 0)
  {
    radius = -radius;
  }
}

inline gp_Cylinder gp_Cylinder::Scaled(const gp_Pnt& theP, const double theS) const
{
  gp_Cylinder aCyl = *this;
  aCyl.pos.Scale(theP, theS);
  aCyl.radius *= theS;
  if (aCyl.radius < 0)
  {
    aCyl.radius = -aCyl.radius;
  }
  return aCyl;
}

inline void gp_Cylinder::Transform(const gp_Trsf& theT)
{
  pos.Transform(theT);
  radius *= theT.ScaleFactor();
  if (radius < 0)
  {
    radius = -radius;
  }
}

inline gp_Cylinder gp_Cylinder::Transformed(const gp_Trsf& theT) const
{
  gp_Cylinder aCyl = *this;
  aCyl.pos.Transform(theT);
  aCyl.radius *= theT.ScaleFactor();
  if (aCyl.radius < 0)
  {
    aCyl.radius = -aCyl.radius;
  }
  return aCyl;
}
