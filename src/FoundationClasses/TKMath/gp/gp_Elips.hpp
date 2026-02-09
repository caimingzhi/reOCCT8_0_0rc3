#pragma once

#include <gp.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>
#include <Standard_ConstructionError.hpp>

class gp_Elips
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Elips() noexcept
      : majorRadius(RealLast()),
        minorRadius(RealSmall())
  {
  }

  constexpr gp_Elips(const gp_Ax2& theA2, const double theMajorRadius, const double theMinorRadius)
      : pos(theA2),
        majorRadius(theMajorRadius),
        minorRadius(theMinorRadius)
  {
    Standard_ConstructionError_Raise_if(theMinorRadius < 0.0 || theMajorRadius < theMinorRadius,
                                        "gp_Elips() - invalid construction parameters");
  }

  void SetAxis(const gp_Ax1& theA1) { pos.SetAxis(theA1); }

  constexpr void SetLocation(const gp_Pnt& theP) noexcept { pos.SetLocation(theP); }

  void SetMajorRadius(const double theMajorRadius)
  {
    Standard_ConstructionError_Raise_if(
      theMajorRadius < minorRadius,
      "gp_Elips::SetMajorRadius() - major radius should be greater or equal to minor radius");
    majorRadius = theMajorRadius;
  }

  void SetMinorRadius(const double theMinorRadius)
  {
    Standard_ConstructionError_Raise_if(theMinorRadius < 0.0 || majorRadius < theMinorRadius,
                                        "gp_Elips::SetMinorRadius() - minor radius should be a "
                                        "positive number lesser or equal to major radius");
    minorRadius = theMinorRadius;
  }

  constexpr void SetPosition(const gp_Ax2& theA2) noexcept { pos = theA2; }

  constexpr double Area() const noexcept { return M_PI * majorRadius * minorRadius; }

  constexpr const gp_Ax1& Axis() const noexcept { return pos.Axis(); }

  gp_Ax1 Directrix1() const;

  gp_Ax1 Directrix2() const;

  double Eccentricity() const;

  double Focal() const { return 2.0 * sqrt(majorRadius * majorRadius - minorRadius * minorRadius); }

  gp_Pnt Focus1() const;

  gp_Pnt Focus2() const;

  constexpr const gp_Pnt& Location() const noexcept { return pos.Location(); }

  constexpr double MajorRadius() const noexcept { return majorRadius; }

  constexpr double MinorRadius() const noexcept { return minorRadius; }

  double Parameter() const;

  constexpr const gp_Ax2& Position() const noexcept { return pos; }

  constexpr gp_Ax1 XAxis() const noexcept { return gp_Ax1(pos.Location(), pos.XDirection()); }

  constexpr gp_Ax1 YAxis() const noexcept { return gp_Ax1(pos.Location(), pos.YDirection()); }

  Standard_EXPORT void Mirror(const gp_Pnt& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Elips Mirrored(const gp_Pnt& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& theA1);

  [[nodiscard]] Standard_EXPORT gp_Elips Mirrored(const gp_Ax1& theA1) const;

  Standard_EXPORT void Mirror(const gp_Ax2& theA2);

  [[nodiscard]] Standard_EXPORT gp_Elips Mirrored(const gp_Ax2& theA2) const;

  void Rotate(const gp_Ax1& theA1, const double theAng) { pos.Rotate(theA1, theAng); }

  [[nodiscard]] gp_Elips Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Elips anE = *this;
    anE.pos.Rotate(theA1, theAng);
    return anE;
  }

  void Scale(const gp_Pnt& theP, const double theS);

  [[nodiscard]] gp_Elips Scaled(const gp_Pnt& theP, const double theS) const;

  void Transform(const gp_Trsf& theT);

  [[nodiscard]] gp_Elips Transformed(const gp_Trsf& theT) const;

  constexpr void Translate(const gp_Vec& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Elips Translated(const gp_Vec& theV) const noexcept
  {
    gp_Elips anE = *this;
    anE.pos.Translate(theV);
    return anE;
  }

  constexpr void Translate(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Elips Translated(const gp_Pnt& theP1,
                                              const gp_Pnt& theP2) const noexcept
  {
    gp_Elips anE = *this;
    anE.pos.Translate(theP1, theP2);
    return anE;
  }

private:
  gp_Ax2 pos;
  double majorRadius;
  double minorRadius;
};

inline gp_Ax1 gp_Elips::Directrix1() const
{
  double anE = Eccentricity();
  Standard_ConstructionError_Raise_if(anE <= gp::Resolution(),
                                      "gp_Elips::Directrix1() - zero eccentricity");
  gp_XYZ anOrig = pos.XDirection().XYZ();
  anOrig.Multiply(majorRadius / anE);
  anOrig.Add(pos.Location().XYZ());
  return gp_Ax1(gp_Pnt(anOrig), pos.YDirection());
}

inline gp_Ax1 gp_Elips::Directrix2() const
{
  double anE = Eccentricity();
  Standard_ConstructionError_Raise_if(anE <= gp::Resolution(),
                                      "gp_Elips::Directrix2() - zero eccentricity");
  gp_XYZ anOrig = pos.XDirection().XYZ();
  anOrig.Multiply(-majorRadius / anE);
  anOrig.Add(pos.Location().XYZ());
  return gp_Ax1(gp_Pnt(anOrig), pos.YDirection());
}

inline double gp_Elips::Eccentricity() const
{
  if (majorRadius == 0.0)
  {
    return 0.0;
  }
  else
  {
    return sqrt(majorRadius * majorRadius - minorRadius * minorRadius) / majorRadius;
  }
}

inline gp_Pnt gp_Elips::Focus1() const
{
  double        aC  = sqrt(majorRadius * majorRadius - minorRadius * minorRadius);
  const gp_Pnt& aPP = pos.Location();
  const gp_Dir& aDD = pos.XDirection();
  return gp_Pnt(aPP.X() + aC * aDD.X(), aPP.Y() + aC * aDD.Y(), aPP.Z() + aC * aDD.Z());
}

inline gp_Pnt gp_Elips::Focus2() const
{
  double        aC  = sqrt(majorRadius * majorRadius - minorRadius * minorRadius);
  const gp_Pnt& aPP = pos.Location();
  const gp_Dir& aDD = pos.XDirection();
  return gp_Pnt(aPP.X() - aC * aDD.X(), aPP.Y() - aC * aDD.Y(), aPP.Z() - aC * aDD.Z());
}

inline double gp_Elips::Parameter() const
{
  if (majorRadius == 0.0)
  {
    return 0.0;
  }
  else
  {
    return (minorRadius * minorRadius) / majorRadius;
  }
}

inline void gp_Elips::Scale(const gp_Pnt& theP, const double theS)

{
  majorRadius *= theS;
  if (majorRadius < 0)
  {
    majorRadius = -majorRadius;
  }
  minorRadius *= theS;
  if (minorRadius < 0)
  {
    minorRadius = -minorRadius;
  }
  pos.Scale(theP, theS);
}

inline gp_Elips gp_Elips::Scaled(const gp_Pnt& theP, const double theS) const
{
  gp_Elips anE = *this;
  anE.majorRadius *= theS;
  if (anE.majorRadius < 0)
  {
    anE.majorRadius = -anE.majorRadius;
  }
  anE.minorRadius *= theS;
  if (anE.minorRadius < 0)
  {
    anE.minorRadius = -anE.minorRadius;
  }
  anE.pos.Scale(theP, theS);
  return anE;
}

inline void gp_Elips::Transform(const gp_Trsf& theT)
{
  majorRadius *= theT.ScaleFactor();
  if (majorRadius < 0)
  {
    majorRadius = -majorRadius;
  }
  minorRadius *= theT.ScaleFactor();
  if (minorRadius < 0)
  {
    minorRadius = -minorRadius;
  }
  pos.Transform(theT);
}

inline gp_Elips gp_Elips::Transformed(const gp_Trsf& theT) const
{
  gp_Elips anE = *this;
  anE.majorRadius *= theT.ScaleFactor();
  if (anE.majorRadius < 0)
  {
    anE.majorRadius = -anE.majorRadius;
  }
  anE.minorRadius *= theT.ScaleFactor();
  if (anE.minorRadius < 0)
  {
    anE.minorRadius = -anE.minorRadius;
  }
  anE.pos.Transform(theT);
  return anE;
}
