#pragma once

#include <gp_Ax22d.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_ConstructionError.hpp>

class gp_Parab2d
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Parab2d() noexcept
      : focalLength(RealLast())
  {
  }

  constexpr gp_Parab2d(const gp_Ax2d& theMirrorAxis,
                       const double   theFocalLength,
                       const bool     theSense = true)
      : pos(theMirrorAxis, theSense),
        focalLength(theFocalLength)
  {
    Standard_ConstructionError_Raise_if(theFocalLength < 0.0,
                                        "gp_Parab2d() - focal length should be >= 0");
  }

  constexpr gp_Parab2d(const gp_Ax22d& theAxes, const double theFocalLength)
      : pos(theAxes),
        focalLength(theFocalLength)
  {
    Standard_ConstructionError_Raise_if(theFocalLength < 0.0,
                                        "gp_Parab2d() - focal length should be >= 0");
  }

  Standard_EXPORT gp_Parab2d(const gp_Ax2d&  theDirectrix,
                             const gp_Pnt2d& theFocus,
                             const bool      theSense = true);

  void SetFocal(const double theFocal)
  {
    Standard_ConstructionError_Raise_if(theFocal < 0.0,
                                        "gp_Parab2d::SetFocal() - focal length should be >= 0");
    focalLength = theFocal;
  }

  constexpr void SetLocation(const gp_Pnt2d& theP) noexcept { pos.SetLocation(theP); }

  constexpr void SetMirrorAxis(const gp_Ax2d& theA) { pos.SetXAxis(theA); }

  constexpr void SetAxis(const gp_Ax22d& theA) noexcept { pos.SetAxis(theA); }

  Standard_EXPORT void Coefficients(double& theA,
                                    double& theB,
                                    double& theC,
                                    double& theD,
                                    double& theE,
                                    double& theF) const;

  gp_Ax2d Directrix() const noexcept;

  constexpr double Focal() const noexcept { return focalLength; }

  gp_Pnt2d Focus() const noexcept
  {
    return gp_Pnt2d(pos.Location().X() + focalLength * pos.XDirection().X(),
                    pos.Location().Y() + focalLength * pos.XDirection().Y());
  }

  constexpr const gp_Pnt2d& Location() const noexcept { return pos.Location(); }

  gp_Ax2d MirrorAxis() const noexcept { return pos.XAxis(); }

  constexpr const gp_Ax22d& Axis() const noexcept { return pos; }

  constexpr double Parameter() const noexcept { return 2.0 * focalLength; }

  void Reverse() noexcept
  {
    gp_Dir2d aTemp = pos.YDirection();
    aTemp.Reverse();
    pos.SetAxis(gp_Ax22d(pos.Location(), pos.XDirection(), aTemp));
  }

  [[nodiscard]] gp_Parab2d Reversed() const noexcept;

  constexpr bool IsDirect() const noexcept
  {
    return (pos.XDirection().Crossed(pos.YDirection())) >= 0.0;
  }

  Standard_EXPORT void Mirror(const gp_Pnt2d& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Parab2d Mirrored(const gp_Pnt2d& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2d& theA) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Parab2d Mirrored(const gp_Ax2d& theA) const noexcept;

  void Rotate(const gp_Pnt2d& theP, const double theAng) { pos.Rotate(theP, theAng); }

  [[nodiscard]] gp_Parab2d Rotated(const gp_Pnt2d& theP, const double theAng) const
  {
    gp_Parab2d aPrb = *this;
    aPrb.pos.Rotate(theP, theAng);
    return aPrb;
  }

  void Scale(const gp_Pnt2d& theP, const double theS);

  [[nodiscard]] gp_Parab2d Scaled(const gp_Pnt2d& theP, const double theS) const;

  void Transform(const gp_Trsf2d& theT);

  [[nodiscard]] gp_Parab2d Transformed(const gp_Trsf2d& theT) const;

  constexpr void Translate(const gp_Vec2d& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Parab2d Translated(const gp_Vec2d& theV) const noexcept
  {
    gp_Parab2d aPrb = *this;
    aPrb.pos.Translate(theV);
    return aPrb;
  }

  constexpr void Translate(const gp_Pnt2d& theP1, const gp_Pnt2d& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Parab2d Translated(const gp_Pnt2d& theP1,
                                                const gp_Pnt2d& theP2) const noexcept
  {
    gp_Parab2d aPrb = *this;
    aPrb.pos.Translate(theP1, theP2);
    return aPrb;
  }

private:
  gp_Ax22d pos;
  double   focalLength;
};

inline gp_Ax2d gp_Parab2d::Directrix() const noexcept
{
  gp_Pnt2d aP(pos.Location().X() - focalLength * pos.XDirection().X(),
              pos.Location().Y() - focalLength * pos.XDirection().Y());
  gp_Dir2d aV(pos.YDirection());
  return gp_Ax2d(aP, aV);
}

inline gp_Parab2d gp_Parab2d::Reversed() const noexcept
{
  gp_Parab2d aP    = *this;
  gp_Dir2d   aTemp = pos.YDirection();
  aTemp.Reverse();
  aP.pos.SetAxis(gp_Ax22d(pos.Location(), pos.XDirection(), aTemp));
  return aP;
}

inline void gp_Parab2d::Scale(const gp_Pnt2d& theP, const double theS)
{
  focalLength *= theS;
  if (focalLength < 0)
  {
    focalLength = -focalLength;
  }
  pos.Scale(theP, theS);
}

inline gp_Parab2d gp_Parab2d::Scaled(const gp_Pnt2d& theP, const double theS) const
{
  gp_Parab2d aPrb = *this;
  aPrb.focalLength *= theS;
  if (aPrb.focalLength < 0)
  {
    aPrb.focalLength = -aPrb.focalLength;
  }
  aPrb.pos.Scale(theP, theS);
  return aPrb;
}

inline void gp_Parab2d::Transform(const gp_Trsf2d& theT)
{
  focalLength *= theT.ScaleFactor();
  if (focalLength < 0)
  {
    focalLength = -focalLength;
  }
  pos.Transform(theT);
}

inline gp_Parab2d gp_Parab2d::Transformed(const gp_Trsf2d& theT) const
{
  gp_Parab2d aPrb = *this;
  aPrb.focalLength *= theT.ScaleFactor();
  if (aPrb.focalLength < 0)
  {
    aPrb.focalLength = -aPrb.focalLength;
  }
  aPrb.pos.Transform(theT);
  return aPrb;
}
