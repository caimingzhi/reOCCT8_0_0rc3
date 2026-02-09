#pragma once

#include <gp_Ax1.hpp>
#include <gp_Ax3.hpp>
#include <Standard_ConstructionError.hpp>
#include <NCollection_Array1.hpp>

class gp_Torus
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Torus() noexcept
      : majorRadius(RealLast()),
        minorRadius(RealSmall())
  {
  }

  constexpr gp_Torus(const gp_Ax3& theA3, const double theMajorRadius, const double theMinorRadius)
      : pos(theA3),
        majorRadius(theMajorRadius),
        minorRadius(theMinorRadius)
  {
    Standard_ConstructionError_Raise_if(theMinorRadius < 0.0 || theMajorRadius < 0.0,
                                        "gp_Torus() - invalid construction parameters");
  }

  void SetAxis(const gp_Ax1& theA1) { pos.SetAxis(theA1); }

  constexpr void SetLocation(const gp_Pnt& theLoc) noexcept { pos.SetLocation(theLoc); }

  void SetMajorRadius(const double theMajorRadius)
  {
    Standard_ConstructionError_Raise_if(theMajorRadius - minorRadius <= gp::Resolution(),
                                        "gp_Torus::SetMajorRadius() - invalid input parameters");
    majorRadius = theMajorRadius;
  }

  void SetMinorRadius(const double theMinorRadius)
  {
    Standard_ConstructionError_Raise_if(theMinorRadius < 0.0
                                          || majorRadius - theMinorRadius <= gp::Resolution(),
                                        "gp_Torus::SetMinorRadius() - invalid input parameters");
    minorRadius = theMinorRadius;
  }

  constexpr void SetPosition(const gp_Ax3& theA3) noexcept { pos = theA3; }

  constexpr double Area() const noexcept { return 4.0 * M_PI * M_PI * minorRadius * majorRadius; }

  constexpr void UReverse() noexcept { pos.YReverse(); }

  constexpr void VReverse() noexcept { pos.ZReverse(); }

  bool Direct() const { return pos.Direct(); }

  constexpr const gp_Ax1& Axis() const noexcept { return pos.Axis(); }

  Standard_EXPORT void Coefficients(NCollection_Array1<double>& theCoef) const;

  constexpr const gp_Pnt& Location() const noexcept { return pos.Location(); }

  constexpr const gp_Ax3& Position() const noexcept { return pos; }

  constexpr double MajorRadius() const noexcept { return majorRadius; }

  constexpr double MinorRadius() const noexcept { return minorRadius; }

  constexpr double Volume() const noexcept
  {
    return (M_PI * minorRadius * minorRadius) * (2.0 * M_PI * majorRadius);
  }

  constexpr gp_Ax1 XAxis() const noexcept { return gp_Ax1(pos.Location(), pos.XDirection()); }

  constexpr gp_Ax1 YAxis() const noexcept { return gp_Ax1(pos.Location(), pos.YDirection()); }

  Standard_EXPORT void Mirror(const gp_Pnt& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Torus Mirrored(const gp_Pnt& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& theA1) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Torus Mirrored(const gp_Ax1& theA1) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2& theA2) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Torus Mirrored(const gp_Ax2& theA2) const noexcept;

  void Rotate(const gp_Ax1& theA1, const double theAng) { pos.Rotate(theA1, theAng); }

  [[nodiscard]] gp_Torus Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Torus aC = *this;
    aC.pos.Rotate(theA1, theAng);
    return aC;
  }

  void Scale(const gp_Pnt& theP, const double theS);

  [[nodiscard]] gp_Torus Scaled(const gp_Pnt& theP, const double theS) const;

  void Transform(const gp_Trsf& theT);

  [[nodiscard]] gp_Torus Transformed(const gp_Trsf& theT) const;

  constexpr void Translate(const gp_Vec& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Torus Translated(const gp_Vec& theV) const noexcept
  {
    gp_Torus aC = *this;
    aC.pos.Translate(theV);
    return aC;
  }

  constexpr void Translate(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Torus Translated(const gp_Pnt& theP1,
                                              const gp_Pnt& theP2) const noexcept
  {
    gp_Torus aC = *this;
    aC.pos.Translate(theP1, theP2);
    return aC;
  }

private:
  gp_Ax3 pos;
  double majorRadius;
  double minorRadius;
};

inline void gp_Torus::Scale(const gp_Pnt& theP, const double theS)
{
  pos.Scale(theP, theS);
  double s = theS;
  if (s < 0)
  {
    s = -s;
  }
  majorRadius *= s;
  minorRadius *= s;
}

inline gp_Torus gp_Torus::Scaled(const gp_Pnt& theP, const double theS) const
{
  gp_Torus aC = *this;
  aC.pos.Scale(theP, theS);
  aC.majorRadius *= theS;
  if (aC.majorRadius < 0)
  {
    aC.majorRadius = -aC.majorRadius;
  }
  aC.minorRadius *= theS;
  if (aC.minorRadius < 0)
  {
    aC.minorRadius = -aC.minorRadius;
  }
  return aC;
}

inline void gp_Torus::Transform(const gp_Trsf& theT)
{
  pos.Transform(theT);
  double aT = theT.ScaleFactor();
  if (aT < 0)
  {
    aT = -aT;
  }
  minorRadius *= aT;
  majorRadius *= aT;
}

inline gp_Torus gp_Torus::Transformed(const gp_Trsf& theT) const
{
  gp_Torus aC = *this;
  aC.pos.Transform(theT);
  aC.majorRadius *= theT.ScaleFactor();
  if (aC.majorRadius < 0)
  {
    aC.majorRadius = -aC.majorRadius;
  }
  aC.minorRadius *= theT.ScaleFactor();
  if (aC.minorRadius < 0)
  {
    aC.minorRadius = -aC.minorRadius;
  }
  return aC;
}
