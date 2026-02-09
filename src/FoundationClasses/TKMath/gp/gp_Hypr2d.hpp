#pragma once

#include <gp.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_ConstructionError.hpp>

class gp_Hypr2d
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Hypr2d() noexcept
      : majorRadius(RealLast()),
        minorRadius(RealLast())
  {
  }

  constexpr gp_Hypr2d(const gp_Ax2d& theMajorAxis,
                      const double   theMajorRadius,
                      const double   theMinorRadius,
                      const bool     theIsSense = true)
      : pos(theMajorAxis, theIsSense),
        majorRadius(theMajorRadius),
        minorRadius(theMinorRadius)
  {
    Standard_ConstructionError_Raise_if(theMinorRadius < 0.0 || theMajorRadius < 0.0,
                                        "gp_Hypr2d() - invalid construction parameters");
  }

  constexpr gp_Hypr2d(const gp_Ax22d& theA,
                      const double    theMajorRadius,
                      const double    theMinorRadius)
      : pos(theA),
        majorRadius(theMajorRadius),
        minorRadius(theMinorRadius)
  {
    Standard_ConstructionError_Raise_if(theMinorRadius < 0.0 || theMajorRadius < 0.0,
                                        "gp_Hypr2d() - invalid construction parameters");
  }

  constexpr void SetLocation(const gp_Pnt2d& theP) noexcept { pos.SetLocation(theP); }

  void SetMajorRadius(const double theMajorRadius)
  {
    Standard_ConstructionError_Raise_if(
      theMajorRadius < 0.0,
      "gp_Hypr2d::SetMajorRadius() - major radius should be greater or equal zero");
    majorRadius = theMajorRadius;
  }

  void SetMinorRadius(const double theMinorRadius)
  {
    Standard_ConstructionError_Raise_if(
      theMinorRadius < 0.0,
      "gp_Hypr2d::SetMinorRadius() - minor radius should be greater or equal zero");
    minorRadius = theMinorRadius;
  }

  constexpr void SetAxis(const gp_Ax22d& theA) noexcept { pos.SetAxis(theA); }

  constexpr void SetXAxis(const gp_Ax2d& theA) { pos.SetXAxis(theA); }

  constexpr void SetYAxis(const gp_Ax2d& theA) { pos.SetYAxis(theA); }

  gp_Ax2d Asymptote1() const;

  gp_Ax2d Asymptote2() const;

  Standard_EXPORT void Coefficients(double& theA,
                                    double& theB,
                                    double& theC,
                                    double& theD,
                                    double& theE,
                                    double& theF) const;

  gp_Hypr2d ConjugateBranch1() const noexcept
  {
    gp_Dir2d aV(pos.YDirection());
    bool     isSign = (pos.XDirection().Crossed(pos.YDirection())) >= 0.0;
    return gp_Hypr2d(gp_Ax2d(pos.Location(), aV), minorRadius, majorRadius, isSign);
  }

  gp_Hypr2d ConjugateBranch2() const noexcept
  {
    gp_Dir2d aV(pos.YDirection().Reversed());
    bool     isSign = (pos.XDirection().Crossed(pos.YDirection())) >= 0.0;
    return gp_Hypr2d(gp_Ax2d(pos.Location(), aV), minorRadius, majorRadius, isSign);
  }

  gp_Ax2d Directrix1() const;

  gp_Ax2d Directrix2() const;

  double Eccentricity() const
  {
    Standard_DomainError_Raise_if(majorRadius <= gp::Resolution(),
                                  "gp_Hypr2d::Eccentricity() - major radius is zero");
    return sqrt(majorRadius * majorRadius + minorRadius * minorRadius) / majorRadius;
  }

  double Focal() const noexcept
  {
    return 2.0 * sqrt(majorRadius * majorRadius + minorRadius * minorRadius);
  }

  gp_Pnt2d Focus1() const noexcept
  {
    double aC = sqrt(majorRadius * majorRadius + minorRadius * minorRadius);
    return gp_Pnt2d(pos.Location().X() + aC * pos.XDirection().X(),
                    pos.Location().Y() + aC * pos.XDirection().Y());
  }

  gp_Pnt2d Focus2() const noexcept
  {
    double aC = sqrt(majorRadius * majorRadius + minorRadius * minorRadius);
    return gp_Pnt2d(pos.Location().X() - aC * pos.XDirection().X(),
                    pos.Location().Y() - aC * pos.XDirection().Y());
  }

  constexpr const gp_Pnt2d& Location() const noexcept { return pos.Location(); }

  constexpr double MajorRadius() const noexcept { return majorRadius; }

  constexpr double MinorRadius() const noexcept { return minorRadius; }

  gp_Hypr2d OtherBranch() const noexcept
  {
    bool isSign = (pos.XDirection().Crossed(pos.YDirection())) >= 0.0;
    return gp_Hypr2d(gp_Ax2d(pos.Location(), pos.XDirection().Reversed()),
                     majorRadius,
                     minorRadius,
                     isSign);
  }

  double Parameter() const
  {
    Standard_DomainError_Raise_if(majorRadius <= gp::Resolution(),
                                  "gp_Hypr2d::Parameter() - major radius is zero");
    return (minorRadius * minorRadius) / majorRadius;
  }

  constexpr const gp_Ax22d& Axis() const noexcept { return pos; }

  gp_Ax2d XAxis() const noexcept { return pos.XAxis(); }

  gp_Ax2d YAxis() const noexcept { return pos.YAxis(); }

  void Reverse() noexcept
  {
    gp_Dir2d aTemp = pos.YDirection();
    aTemp.Reverse();
    pos.SetAxis(gp_Ax22d(pos.Location(), pos.XDirection(), aTemp));
  }

  [[nodiscard]] gp_Hypr2d Reversed() const noexcept;

  constexpr bool IsDirect() const noexcept
  {
    return (pos.XDirection().Crossed(pos.YDirection())) >= 0.0;
  }

  Standard_EXPORT void Mirror(const gp_Pnt2d& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Hypr2d Mirrored(const gp_Pnt2d& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2d& theA) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Hypr2d Mirrored(const gp_Ax2d& theA) const noexcept;

  void Rotate(const gp_Pnt2d& theP, const double theAng) { pos.Rotate(theP, theAng); }

  [[nodiscard]] gp_Hypr2d Rotated(const gp_Pnt2d& theP, const double theAng) const
  {
    gp_Hypr2d aH = *this;
    aH.pos.Rotate(theP, theAng);
    return aH;
  }

  void Scale(const gp_Pnt2d& theP, const double theS);

  [[nodiscard]] gp_Hypr2d Scaled(const gp_Pnt2d& theP, const double theS) const;

  void Transform(const gp_Trsf2d& theT);

  [[nodiscard]] gp_Hypr2d Transformed(const gp_Trsf2d& theT) const;

  constexpr void Translate(const gp_Vec2d& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Hypr2d Translated(const gp_Vec2d& theV) const noexcept
  {
    gp_Hypr2d aH = *this;
    aH.pos.Translate(theV);
    return aH;
  }

  constexpr void Translate(const gp_Pnt2d& theP1, const gp_Pnt2d& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Hypr2d Translated(const gp_Pnt2d& theP1,
                                               const gp_Pnt2d& theP2) const noexcept
  {
    gp_Hypr2d aH = *this;
    aH.pos.Translate(theP1, theP2);
    return aH;
  }

private:
  gp_Ax22d pos;
  double   majorRadius;
  double   minorRadius;
};

inline gp_Ax2d gp_Hypr2d::Asymptote1() const
{
  Standard_ConstructionError_Raise_if(majorRadius <= gp::Resolution(),
                                      "gp_Hypr2d::Asymptote1() - major radius is zero");
  gp_Dir2d aVdir = pos.XDirection();
  gp_XY    aCoord1(pos.YDirection().XY());
  gp_XY    aCoord2 = aCoord1.Multiplied(minorRadius / majorRadius);
  aCoord1.Add(aCoord2);
  aVdir.SetXY(aCoord1);
  return gp_Ax2d(pos.Location(), aVdir);
}

inline gp_Ax2d gp_Hypr2d::Asymptote2() const
{
  Standard_ConstructionError_Raise_if(majorRadius <= gp::Resolution(),
                                      "gp_Hypr2d::Asymptote2() - major radius is zero");
  gp_Vec2d aVdir = pos.XDirection();
  gp_XY    aCoord1(pos.YDirection().XY());
  gp_XY    aCoord2 = aCoord1.Multiplied(-minorRadius / majorRadius);
  aCoord1.Add(aCoord2);
  aVdir.SetXY(aCoord1);
  return gp_Ax2d(pos.Location(), aVdir);
}

inline gp_Ax2d gp_Hypr2d::Directrix1() const
{
  double anE    = Eccentricity();
  gp_XY  anOrig = pos.XDirection().XY();
  anOrig.Multiply(majorRadius / anE);
  anOrig.Add(pos.Location().XY());
  return gp_Ax2d(gp_Pnt2d(anOrig), gp_Dir2d(pos.YDirection()));
}

inline gp_Ax2d gp_Hypr2d::Directrix2() const
{
  double anE    = Eccentricity();
  gp_XY  anOrig = pos.XDirection().XY();
  anOrig.Multiply(Parameter() / anE);
  anOrig.Add(Focus1().XY());
  return gp_Ax2d(gp_Pnt2d(anOrig), gp_Dir2d(pos.YDirection()));
}

inline gp_Hypr2d gp_Hypr2d::Reversed() const noexcept
{
  gp_Hypr2d aH    = *this;
  gp_Dir2d  aTemp = pos.YDirection();
  aTemp.Reverse();
  aH.pos.SetAxis(gp_Ax22d(pos.Location(), pos.XDirection(), aTemp));
  return aH;
}

inline void gp_Hypr2d::Scale(const gp_Pnt2d& theP, const double theS)
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

inline gp_Hypr2d gp_Hypr2d::Scaled(const gp_Pnt2d& theP, const double theS) const
{
  gp_Hypr2d aH = *this;
  aH.majorRadius *= theS;
  if (aH.majorRadius < 0)
  {
    aH.majorRadius = -aH.majorRadius;
  }
  aH.minorRadius *= theS;
  if (aH.minorRadius < 0)
  {
    aH.minorRadius = -aH.minorRadius;
  }
  aH.pos.Scale(theP, theS);
  return aH;
}

inline void gp_Hypr2d::Transform(const gp_Trsf2d& theT)
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

inline gp_Hypr2d gp_Hypr2d::Transformed(const gp_Trsf2d& theT) const
{
  gp_Hypr2d aH = *this;
  aH.majorRadius *= theT.ScaleFactor();
  if (aH.majorRadius < 0)
  {
    aH.majorRadius = -aH.majorRadius;
  }
  aH.minorRadius *= theT.ScaleFactor();
  if (aH.minorRadius < 0)
  {
    aH.minorRadius = -aH.minorRadius;
  }
  aH.pos.Transform(theT);
  return aH;
}
