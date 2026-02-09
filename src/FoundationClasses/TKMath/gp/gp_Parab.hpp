#pragma once

#include <gp_Ax1.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <Standard_ConstructionError.hpp>

class gp_Parab
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Parab() noexcept
      : focalLength(RealLast())
  {
  }

  constexpr gp_Parab(const gp_Ax2& theA2, const double theFocal)
      : pos(theA2),
        focalLength(theFocal)
  {
    Standard_ConstructionError_Raise_if(theFocal < 0.0, "gp_Parab() - focal length should be >= 0");
  }

  gp_Parab(const gp_Ax1& theD, const gp_Pnt& theF);

  void SetAxis(const gp_Ax1& theA1) { pos.SetAxis(theA1); }

  void SetFocal(const double theFocal)
  {
    Standard_ConstructionError_Raise_if(theFocal < 0.0,
                                        "gp_Parab::SetFocal() - focal length should be >= 0");
    focalLength = theFocal;
  }

  constexpr void SetLocation(const gp_Pnt& theP) noexcept { pos.SetLocation(theP); }

  constexpr void SetPosition(const gp_Ax2& theA2) noexcept { pos = theA2; }

  constexpr const gp_Ax1& Axis() const noexcept { return pos.Axis(); }

  gp_Ax1 Directrix() const;

  constexpr double Focal() const noexcept { return focalLength; }

  gp_Pnt Focus() const;

  constexpr const gp_Pnt& Location() const noexcept { return pos.Location(); }

  constexpr double Parameter() const noexcept { return 2.0 * focalLength; }

  constexpr const gp_Ax2& Position() const noexcept { return pos; }

  constexpr gp_Ax1 XAxis() const noexcept { return gp_Ax1(pos.Location(), pos.XDirection()); }

  constexpr gp_Ax1 YAxis() const noexcept { return gp_Ax1(pos.Location(), pos.YDirection()); }

  Standard_EXPORT void Mirror(const gp_Pnt& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Parab Mirrored(const gp_Pnt& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& theA1);

  [[nodiscard]] Standard_EXPORT gp_Parab Mirrored(const gp_Ax1& theA1) const;

  Standard_EXPORT void Mirror(const gp_Ax2& theA2);

  [[nodiscard]] Standard_EXPORT gp_Parab Mirrored(const gp_Ax2& theA2) const;

  void Rotate(const gp_Ax1& theA1, const double theAng) { pos.Rotate(theA1, theAng); }

  [[nodiscard]] gp_Parab Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Parab aPrb = *this;
    aPrb.pos.Rotate(theA1, theAng);
    return aPrb;
  }

  void Scale(const gp_Pnt& theP, const double theS);

  [[nodiscard]] gp_Parab Scaled(const gp_Pnt& theP, const double theS) const;

  void Transform(const gp_Trsf& theT);

  [[nodiscard]] gp_Parab Transformed(const gp_Trsf& theT) const;

  constexpr void Translate(const gp_Vec& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Parab Translated(const gp_Vec& theV) const noexcept
  {
    gp_Parab aPrb = *this;
    aPrb.pos.Translate(theV);
    return aPrb;
  }

  constexpr void Translate(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Parab Translated(const gp_Pnt& theP1,
                                              const gp_Pnt& theP2) const noexcept
  {
    gp_Parab aPrb = *this;
    aPrb.pos.Translate(theP1, theP2);
    return aPrb;
  }

private:
  gp_Ax2 pos;
  double focalLength;
};

inline gp_Parab::gp_Parab(const gp_Ax1& theD, const gp_Pnt& theF)
{
  gp_Lin aDroite(theD);
  focalLength        = aDroite.Distance(theF) / 2.;
  gp_Ax1        anAx = aDroite.Normal(theF).Position();
  gp_Ax1        anAy = aDroite.Position();
  const gp_Dir& aDD  = anAx.Direction();
  pos                = gp_Ax2(gp_Pnt(theF.X() - focalLength * aDD.X(),
                      theF.Y() - focalLength * aDD.Y(),
                      theF.Z() - focalLength * aDD.Z()),
               anAx.Direction().Crossed(anAy.Direction()),
               anAx.Direction());
}

inline gp_Ax1 gp_Parab::Directrix() const
{
  const gp_Pnt& aPP = pos.Location();
  const gp_Dir& aDD = pos.XDirection();
  gp_Pnt        aP(aPP.X() - focalLength * aDD.X(),
            aPP.Y() - focalLength * aDD.Y(),
            aPP.Z() - focalLength * aDD.Z());
  return gp_Ax1(aP, pos.YDirection());
}

inline gp_Pnt gp_Parab::Focus() const
{
  const gp_Pnt& aPP = pos.Location();
  const gp_Dir& aDD = pos.XDirection();
  return gp_Pnt(aPP.X() + focalLength * aDD.X(),
                aPP.Y() + focalLength * aDD.Y(),
                aPP.Z() + focalLength * aDD.Z());
}

inline void gp_Parab::Scale(const gp_Pnt& theP, const double theS)
{
  focalLength *= theS;
  if (focalLength < 0)
  {
    focalLength = -focalLength;
  }
  pos.Scale(theP, theS);
}

inline gp_Parab gp_Parab::Scaled(const gp_Pnt& theP, const double theS) const
{
  gp_Parab aPrb = *this;
  aPrb.focalLength *= theS;
  if (aPrb.focalLength < 0)
  {
    aPrb.focalLength = -aPrb.focalLength;
  }
  aPrb.pos.Scale(theP, theS);
  return aPrb;
}

inline void gp_Parab::Transform(const gp_Trsf& theT)
{
  focalLength *= theT.ScaleFactor();
  if (focalLength < 0)
  {
    focalLength = -focalLength;
  }
  pos.Transform(theT);
}

inline gp_Parab gp_Parab::Transformed(const gp_Trsf& theT) const
{
  gp_Parab aPrb = *this;
  aPrb.focalLength *= theT.ScaleFactor();
  if (aPrb.focalLength < 0)
  {
    aPrb.focalLength = -aPrb.focalLength;
  }
  aPrb.pos.Transform(theT);
  return aPrb;
}
