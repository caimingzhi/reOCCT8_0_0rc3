#pragma once

#include <gp_Pnt2d.hpp>
#include <gp_Dir2d.hpp>

class gp_Trsf2d;
class gp_Vec2d;

class gp_Ax2d
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Ax2d() noexcept
      : loc(0., 0.)

  {
  }

  constexpr gp_Ax2d(const gp_Pnt2d& theP, const gp_Dir2d& theV) noexcept
      : loc(theP),
        vdir(theV)
  {
  }

  constexpr gp_Ax2d(const gp_Pnt2d& theP, const gp_Dir2d::D theDir) noexcept
      : loc(theP),
        vdir(theDir)
  {
  }

  constexpr explicit gp_Ax2d(const gp_Dir2d::D theDir) noexcept
      : loc(0., 0.),
        vdir(theDir)
  {
  }

  constexpr void SetLocation(const gp_Pnt2d& theP) noexcept { loc = theP; }

  constexpr void SetDirection(const gp_Dir2d& theV) noexcept { vdir = theV; }

  constexpr const gp_Pnt2d& Location() const noexcept { return loc; }

  constexpr const gp_Dir2d& Direction() const noexcept { return vdir; }

  Standard_EXPORT bool IsCoaxial(const gp_Ax2d& Other,
                                 const double   AngularTolerance,
                                 const double   LinearTolerance) const;

  bool IsNormal(const gp_Ax2d& theOther, const double theAngularTolerance) const
  {
    return vdir.IsNormal(theOther.vdir, theAngularTolerance);
  }

  bool IsOpposite(const gp_Ax2d& theOther, const double theAngularTolerance) const
  {
    return vdir.IsOpposite(theOther.vdir, theAngularTolerance);
  }

  bool IsParallel(const gp_Ax2d& theOther, const double theAngularTolerance) const
  {
    return vdir.IsParallel(theOther.vdir, theAngularTolerance);
  }

  double Angle(const gp_Ax2d& theOther) const { return vdir.Angle(theOther.vdir); }

  constexpr void Reverse() noexcept { vdir.Reverse(); }

  [[nodiscard]] constexpr gp_Ax2d Reversed() const noexcept
  {
    gp_Ax2d aTemp = *this;
    aTemp.Reverse();
    return aTemp;
  }

  Standard_EXPORT void Mirror(const gp_Pnt2d& P) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Ax2d Mirrored(const gp_Pnt2d& P) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2d& A) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Ax2d Mirrored(const gp_Ax2d& A) const noexcept;

  void Rotate(const gp_Pnt2d& theP, const double theAng)
  {
    loc.Rotate(theP, theAng);
    vdir.Rotate(theAng);
  }

  [[nodiscard]] gp_Ax2d Rotated(const gp_Pnt2d& theP, const double theAng) const
  {
    gp_Ax2d anA = *this;
    anA.Rotate(theP, theAng);
    return anA;
  }

  Standard_EXPORT void Scale(const gp_Pnt2d& P, const double S);

  [[nodiscard]] gp_Ax2d Scaled(const gp_Pnt2d& theP, const double theS) const
  {
    gp_Ax2d anA = *this;
    anA.Scale(theP, theS);
    return anA;
  }

  void Transform(const gp_Trsf2d& theT)
  {
    loc.Transform(theT);
    vdir.Transform(theT);
  }

  [[nodiscard]] gp_Ax2d Transformed(const gp_Trsf2d& theT) const
  {
    gp_Ax2d anA = *this;
    anA.Transform(theT);
    return anA;
  }

  constexpr void Translate(const gp_Vec2d& theV) noexcept { loc.Translate(theV); }

  [[nodiscard]] constexpr gp_Ax2d Translated(const gp_Vec2d& theV) const noexcept
  {
    gp_Ax2d anA = *this;
    (anA.loc).Translate(theV);
    return anA;
  }

  constexpr void Translate(const gp_Pnt2d& theP1, const gp_Pnt2d& theP2) noexcept
  {
    loc.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Ax2d Translated(const gp_Pnt2d& theP1,
                                             const gp_Pnt2d& theP2) const noexcept
  {
    gp_Ax2d anA = *this;
    (anA.loc).Translate(theP1, theP2);
    return anA;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  gp_Pnt2d loc;
  gp_Dir2d vdir;
};
