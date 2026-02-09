#pragma once

#include <gp.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_ConstructionError.hpp>

class gp_Elips2d
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Elips2d() noexcept
      : majorRadius(RealLast()),
        minorRadius(RealSmall())
  {
  }

  constexpr gp_Elips2d(const gp_Ax2d& theMajorAxis,
                       const double   theMajorRadius,
                       const double   theMinorRadius,
                       const bool     theIsSense = true)
      : pos(theMajorAxis, theIsSense),
        majorRadius(theMajorRadius),
        minorRadius(theMinorRadius)
  {
    Standard_ConstructionError_Raise_if(theMinorRadius < 0.0 || theMajorRadius < theMinorRadius,
                                        "gp_Elips2d() - invalid construction parameters");
  }

  constexpr gp_Elips2d(const gp_Ax22d& theA,
                       const double    theMajorRadius,
                       const double    theMinorRadius)
      : pos(theA),
        majorRadius(theMajorRadius),
        minorRadius(theMinorRadius)
  {
    Standard_ConstructionError_Raise_if(theMinorRadius < 0.0 || theMajorRadius < theMinorRadius,
                                        "gp_Elips2d() - invalid construction parameters");
  }

  constexpr void SetLocation(const gp_Pnt2d& theP) noexcept { pos.SetLocation(theP); }

  void SetMajorRadius(const double theMajorRadius)
  {
    Standard_ConstructionError_Raise_if(
      theMajorRadius < minorRadius,
      "gp_Elips2d::SetMajorRadius() - major radius should be greater or equal to minor radius");
    majorRadius = theMajorRadius;
  }

  void SetMinorRadius(const double theMinorRadius)
  {
    Standard_ConstructionError_Raise_if(theMinorRadius < 0.0 || majorRadius < theMinorRadius,
                                        "gp_Elips2d::SetMinorRadius() - minor radius should be a "
                                        "positive number lesser or equal to major radius");
    minorRadius = theMinorRadius;
  }

  constexpr void SetAxis(const gp_Ax22d& theA) noexcept { pos.SetAxis(theA); }

  constexpr void SetXAxis(const gp_Ax2d& theA) { pos.SetXAxis(theA); }

  constexpr void SetYAxis(const gp_Ax2d& theA) { pos.SetYAxis(theA); }

  constexpr double Area() const noexcept { return M_PI * majorRadius * minorRadius; }

  Standard_EXPORT void Coefficients(double& theA,
                                    double& theB,
                                    double& theC,
                                    double& theD,
                                    double& theE,
                                    double& theF) const;

  gp_Ax2d Directrix1() const;

  gp_Ax2d Directrix2() const;

  double Eccentricity() const;

  double Focal() const { return 2.0 * sqrt(majorRadius * majorRadius - minorRadius * minorRadius); }

  gp_Pnt2d Focus1() const;

  gp_Pnt2d Focus2() const;

  constexpr const gp_Pnt2d& Location() const noexcept { return pos.Location(); }

  constexpr double MajorRadius() const noexcept { return majorRadius; }

  constexpr double MinorRadius() const noexcept { return minorRadius; }

  constexpr double Parameter() const noexcept;

  constexpr const gp_Ax22d& Axis() const noexcept { return pos; }

  gp_Ax2d XAxis() const noexcept { return pos.XAxis(); }

  gp_Ax2d YAxis() const noexcept { return pos.YAxis(); }

  void Reverse() noexcept
  {
    gp_Dir2d aTemp = pos.YDirection();
    aTemp.Reverse();
    pos.SetAxis(gp_Ax22d(pos.Location(), pos.XDirection(), aTemp));
  }

  [[nodiscard]] gp_Elips2d Reversed() const noexcept;

  constexpr bool IsDirect() const noexcept
  {
    return (pos.XDirection().Crossed(pos.YDirection())) >= 0.0;
  }

  Standard_EXPORT void Mirror(const gp_Pnt2d& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Elips2d Mirrored(const gp_Pnt2d& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2d& theA) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Elips2d Mirrored(const gp_Ax2d& theA) const noexcept;

  void Rotate(const gp_Pnt2d& theP, const double theAng) { pos.Rotate(theP, theAng); }

  [[nodiscard]] gp_Elips2d Rotated(const gp_Pnt2d& theP, const double theAng) const
  {
    gp_Elips2d anE = *this;
    anE.pos.Rotate(theP, theAng);
    return anE;
  }

  void Scale(const gp_Pnt2d& theP, const double theS);

  [[nodiscard]] gp_Elips2d Scaled(const gp_Pnt2d& theP, const double theS) const;

  void Transform(const gp_Trsf2d& theT);

  [[nodiscard]] gp_Elips2d Transformed(const gp_Trsf2d& theT) const;

  constexpr void Translate(const gp_Vec2d& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Elips2d Translated(const gp_Vec2d& theV) const noexcept
  {
    gp_Elips2d anE = *this;
    anE.pos.Translate(theV);
    return anE;
  }

  constexpr void Translate(const gp_Pnt2d& theP1, const gp_Pnt2d& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Elips2d Translated(const gp_Pnt2d& theP1,
                                                const gp_Pnt2d& theP2) const noexcept
  {
    gp_Elips2d anE = *this;
    anE.pos.Translate(theP1, theP2);
    return anE;
  }

private:
  gp_Ax22d pos;
  double   majorRadius;
  double   minorRadius;
};

inline gp_Ax2d gp_Elips2d::Directrix1() const
{
  double anE = Eccentricity();
  Standard_ConstructionError_Raise_if(anE <= gp::Resolution(),
                                      "gp_Elips2d::Directrix1() - zero eccentricity");
  gp_XY anOrig = pos.XDirection().XY();
  anOrig.Multiply(majorRadius / anE);
  anOrig.Add(pos.Location().XY());
  return gp_Ax2d(gp_Pnt2d(anOrig), gp_Dir2d(pos.YDirection()));
}

inline gp_Ax2d gp_Elips2d::Directrix2() const
{
  double anE = Eccentricity();
  Standard_ConstructionError_Raise_if(anE <= gp::Resolution(),
                                      "gp_Elips2d::Directrix2() - zero eccentricity");
  gp_XY anOrig = pos.XDirection().XY();
  anOrig.Multiply(-majorRadius / anE);
  anOrig.Add(pos.Location().XY());
  return gp_Ax2d(gp_Pnt2d(anOrig), gp_Dir2d(pos.YDirection()));
}

inline double gp_Elips2d::Eccentricity() const
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

inline gp_Pnt2d gp_Elips2d::Focus1() const
{
  double          aC  = sqrt(majorRadius * majorRadius - minorRadius * minorRadius);
  const gp_Pnt2d& aPP = pos.Location();
  const gp_Dir2d& aDD = pos.XDirection();
  return gp_Pnt2d(aPP.X() + aC * aDD.X(), aPP.Y() + aC * aDD.Y());
}

inline gp_Pnt2d gp_Elips2d::Focus2() const
{
  double          aC  = sqrt(majorRadius * majorRadius - minorRadius * minorRadius);
  const gp_Pnt2d& aPP = pos.Location();
  const gp_Dir2d& aDD = pos.XDirection();
  return gp_Pnt2d(aPP.X() - aC * aDD.X(), aPP.Y() - aC * aDD.Y());
}

inline void gp_Elips2d::Scale(const gp_Pnt2d& theP, const double theS)
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

inline gp_Elips2d gp_Elips2d::Scaled(const gp_Pnt2d& theP, const double theS) const
{
  gp_Elips2d anE = *this;
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

inline constexpr double gp_Elips2d::Parameter() const noexcept
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

inline gp_Elips2d gp_Elips2d::Reversed() const noexcept
{
  gp_Elips2d anE   = *this;
  gp_Dir2d   aTemp = pos.YDirection();
  aTemp.Reverse();
  anE.pos.SetAxis(gp_Ax22d(pos.Location(), pos.XDirection(), aTemp));
  return anE;
}

inline void gp_Elips2d::Transform(const gp_Trsf2d& theT)
{
  double aTSca = theT.ScaleFactor();
  if (aTSca < 0.0)
  {
    aTSca = -aTSca;
  }
  majorRadius *= aTSca;
  minorRadius *= aTSca;
  pos.Transform(theT);
}

inline gp_Elips2d gp_Elips2d::Transformed(const gp_Trsf2d& theT) const
{
  gp_Elips2d anE = *this;
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
