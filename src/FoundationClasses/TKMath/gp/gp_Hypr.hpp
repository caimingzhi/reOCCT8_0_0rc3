#pragma once

#include <gp.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_ConstructionError.hpp>

class gp_Hypr
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Hypr() noexcept
      : majorRadius(RealLast()),
        minorRadius(RealFirst())
  {
  }

  constexpr gp_Hypr(const gp_Ax2& theA2, const double theMajorRadius, const double theMinorRadius)
      : pos(theA2),
        majorRadius(theMajorRadius),
        minorRadius(theMinorRadius)
  {
    Standard_ConstructionError_Raise_if(theMinorRadius < 0.0 || theMajorRadius < 0.0,
                                        "gp_Hypr() - invalid construction parameters");
  }

  void SetAxis(const gp_Ax1& theA1) { pos.SetAxis(theA1); }

  void SetLocation(const gp_Pnt& theP) { pos = gp_Ax2(theP, pos.Direction(), pos.XDirection()); }

  void SetMajorRadius(const double theMajorRadius)
  {
    Standard_ConstructionError_Raise_if(
      theMajorRadius < 0.0,
      "gp_Hypr::SetMajorRadius() - major radius should be greater or equal zero");
    majorRadius = theMajorRadius;
  }

  void SetMinorRadius(const double theMinorRadius)
  {
    Standard_ConstructionError_Raise_if(
      theMinorRadius < 0.0,
      "gp_Hypr::SetMinorRadius() - minor radius should be greater or equal zero");
    minorRadius = theMinorRadius;
  }

  constexpr void SetPosition(const gp_Ax2& theA2) noexcept { pos = theA2; }

  gp_Ax1 Asymptote1() const;

  gp_Ax1 Asymptote2() const;

  constexpr const gp_Ax1& Axis() const noexcept { return pos.Axis(); }

  gp_Hypr ConjugateBranch1() const
  {
    return gp_Hypr(gp_Ax2(pos.Location(), pos.Direction(), pos.YDirection()),
                   minorRadius,
                   majorRadius);
  }

  gp_Hypr ConjugateBranch2() const
  {
    gp_Dir aD = pos.YDirection();
    aD.Reverse();
    return gp_Hypr(gp_Ax2(pos.Location(), pos.Direction(), aD), minorRadius, majorRadius);
  }

  gp_Ax1 Directrix1() const;

  gp_Ax1 Directrix2() const;

  double Eccentricity() const
  {
    Standard_DomainError_Raise_if(majorRadius <= gp::Resolution(),
                                  "gp_Hypr::Eccentricity() - major radius is zero");
    return sqrt(majorRadius * majorRadius + minorRadius * minorRadius) / majorRadius;
  }

  double Focal() const noexcept
  {
    return 2.0 * sqrt(majorRadius * majorRadius + minorRadius * minorRadius);
  }

  gp_Pnt Focus1() const;

  gp_Pnt Focus2() const;

  constexpr const gp_Pnt& Location() const noexcept { return pos.Location(); }

  constexpr double MajorRadius() const noexcept { return majorRadius; }

  constexpr double MinorRadius() const noexcept { return minorRadius; }

  gp_Hypr OtherBranch() const
  {
    gp_Dir aD = pos.XDirection();
    aD.Reverse();
    return gp_Hypr(gp_Ax2(pos.Location(), pos.Direction(), aD), majorRadius, minorRadius);
  }

  double Parameter() const
  {
    Standard_DomainError_Raise_if(majorRadius <= gp::Resolution(),
                                  "gp_Hypr::Parameter() - major radius is zero");
    return (minorRadius * minorRadius) / majorRadius;
  }

  constexpr const gp_Ax2& Position() const noexcept { return pos; }

  constexpr gp_Ax1 XAxis() const noexcept { return gp_Ax1(pos.Location(), pos.XDirection()); }

  constexpr gp_Ax1 YAxis() const noexcept { return gp_Ax1(pos.Location(), pos.YDirection()); }

  Standard_EXPORT void Mirror(const gp_Pnt& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Hypr Mirrored(const gp_Pnt& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& theA1);

  [[nodiscard]] Standard_EXPORT gp_Hypr Mirrored(const gp_Ax1& theA1) const;

  Standard_EXPORT void Mirror(const gp_Ax2& theA2);

  [[nodiscard]] Standard_EXPORT gp_Hypr Mirrored(const gp_Ax2& theA2) const;

  void Rotate(const gp_Ax1& theA1, const double theAng) { pos.Rotate(theA1, theAng); }

  [[nodiscard]] gp_Hypr Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Hypr aH = *this;
    aH.pos.Rotate(theA1, theAng);
    return aH;
  }

  void Scale(const gp_Pnt& theP, const double theS);

  [[nodiscard]] gp_Hypr Scaled(const gp_Pnt& theP, const double theS) const;

  void Transform(const gp_Trsf& theT);

  [[nodiscard]] gp_Hypr Transformed(const gp_Trsf& theT) const;

  constexpr void Translate(const gp_Vec& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Hypr Translated(const gp_Vec& theV) const noexcept
  {
    gp_Hypr aH = *this;
    aH.pos.Translate(theV);
    return aH;
  }

  constexpr void Translate(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Hypr Translated(const gp_Pnt& theP1,
                                             const gp_Pnt& theP2) const noexcept
  {
    gp_Hypr aH = *this;
    aH.pos.Translate(theP1, theP2);
    return aH;
  }

private:
  gp_Ax2 pos;
  double majorRadius;
  double minorRadius;
};

inline gp_Ax1 gp_Hypr::Asymptote1() const
{
  Standard_ConstructionError_Raise_if(majorRadius <= gp::Resolution(),
                                      "gp_Hypr::Asymptote1() - major radius is zero");
  gp_Vec aV1 = gp_Vec(pos.YDirection());
  aV1.Multiply(minorRadius / majorRadius);
  gp_Vec aV = gp_Vec(pos.XDirection());
  aV.Add(aV1);
  return gp_Ax1(pos.Location(), gp_Dir(aV));
}

inline gp_Ax1 gp_Hypr::Asymptote2() const
{
  Standard_ConstructionError_Raise_if(majorRadius <= gp::Resolution(),
                                      "gp_Hypr::Asymptote1() - major radius is zero");
  gp_Vec aV1 = gp_Vec(pos.YDirection());
  aV1.Multiply(-minorRadius / majorRadius);
  gp_Vec aV = gp_Vec(pos.XDirection());
  aV.Add(aV1);
  return gp_Ax1(pos.Location(), gp_Dir(aV));
}

inline gp_Pnt gp_Hypr::Focus1() const
{
  double        aC  = sqrt(majorRadius * majorRadius + minorRadius * minorRadius);
  const gp_Pnt& aPP = pos.Location();
  const gp_Dir& aDD = pos.XDirection();
  return gp_Pnt(aPP.X() + aC * aDD.X(), aPP.Y() + aC * aDD.Y(), aPP.Z() + aC * aDD.Z());
}

inline gp_Pnt gp_Hypr::Focus2() const
{
  double        aC  = sqrt(majorRadius * majorRadius + minorRadius * minorRadius);
  const gp_Pnt& aPP = pos.Location();
  const gp_Dir& aDD = pos.XDirection();
  return gp_Pnt(aPP.X() - aC * aDD.X(), aPP.Y() - aC * aDD.Y(), aPP.Z() - aC * aDD.Z());
}

inline void gp_Hypr::Scale(const gp_Pnt& theP, const double theS)
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

inline gp_Hypr gp_Hypr::Scaled(const gp_Pnt& theP, const double theS) const
{
  gp_Hypr aH = *this;
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

inline void gp_Hypr::Transform(const gp_Trsf& theT)
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

inline gp_Hypr gp_Hypr::Transformed(const gp_Trsf& theT) const
{
  gp_Hypr aH = *this;
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

inline gp_Ax1 gp_Hypr::Directrix1() const
{
  double anE    = Eccentricity();
  gp_XYZ anOrig = pos.XDirection().XYZ();
  anOrig.Multiply(majorRadius / anE);
  anOrig.Add(pos.Location().XYZ());
  return gp_Ax1(gp_Pnt(anOrig), pos.YDirection());
}

inline gp_Ax1 gp_Hypr::Directrix2() const
{
  double anE    = Eccentricity();
  gp_XYZ anOrig = pos.XDirection().XYZ();
  anOrig.Multiply(-majorRadius / anE);
  anOrig.Add(pos.Location().XYZ());
  return gp_Ax1(gp_Pnt(anOrig), pos.YDirection());
}
