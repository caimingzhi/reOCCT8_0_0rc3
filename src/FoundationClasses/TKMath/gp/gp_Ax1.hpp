#pragma once

#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>

class gp_Ax2;
class gp_Trsf;
class gp_Vec;

class gp_Ax1
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Ax1() noexcept
      : loc(0., 0., 0.),
        vdir(gp_Dir::D::Z)
  {
  }

  constexpr gp_Ax1(const gp_Pnt& theP, const gp_Dir& theV) noexcept
      : loc(theP),
        vdir(theV)
  {
  }

  constexpr gp_Ax1(const gp_Pnt& theP, const gp_Dir::D theDir) noexcept
      : loc(theP),
        vdir(theDir)
  {
  }

  constexpr explicit gp_Ax1(const gp_Dir::D theDir) noexcept
      : loc(0., 0., 0.),
        vdir(theDir)
  {
  }

  constexpr void SetDirection(const gp_Dir& theV) noexcept { vdir = theV; }

  constexpr void SetLocation(const gp_Pnt& theP) noexcept { loc = theP; }

  constexpr const gp_Dir& Direction() const noexcept { return vdir; }

  constexpr const gp_Pnt& Location() const noexcept { return loc; }

  Standard_EXPORT bool IsCoaxial(const gp_Ax1& Other,
                                 const double  AngularTolerance,
                                 const double  LinearTolerance) const;

  bool IsNormal(const gp_Ax1& theOther, const double theAngularTolerance) const
  {
    return vdir.IsNormal(theOther.vdir, theAngularTolerance);
  }

  bool IsOpposite(const gp_Ax1& theOther, const double theAngularTolerance) const
  {
    return vdir.IsOpposite(theOther.vdir, theAngularTolerance);
  }

  bool IsParallel(const gp_Ax1& theOther, const double theAngularTolerance) const
  {
    return vdir.IsParallel(theOther.vdir, theAngularTolerance);
  }

  double Angle(const gp_Ax1& theOther) const { return vdir.Angle(theOther.vdir); }

  constexpr void Reverse() noexcept { vdir.Reverse(); }

  [[nodiscard]] constexpr gp_Ax1 Reversed() const noexcept { return gp_Ax1(loc, vdir.Reversed()); }

  Standard_EXPORT void Mirror(const gp_Pnt& P) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Ax1 Mirrored(const gp_Pnt& P) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& A1) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Ax1 Mirrored(const gp_Ax1& A1) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2& A2) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Ax1 Mirrored(const gp_Ax2& A2) const noexcept;

  void Rotate(const gp_Ax1& theA1, const double theAngRad)
  {
    loc.Rotate(theA1, theAngRad);
    vdir.Rotate(theA1, theAngRad);
  }

  [[nodiscard]] gp_Ax1 Rotated(const gp_Ax1& theA1, const double theAngRad) const
  {
    gp_Ax1 A = *this;
    A.Rotate(theA1, theAngRad);
    return A;
  }

  constexpr void Scale(const gp_Pnt& theP, const double theS) noexcept
  {
    loc.Scale(theP, theS);
    if (theS < 0.0)
    {
      vdir.Reverse();
    }
  }

  [[nodiscard]] constexpr gp_Ax1 Scaled(const gp_Pnt& theP, const double theS) const noexcept
  {
    gp_Ax1 A1 = *this;
    A1.Scale(theP, theS);
    return A1;
  }

  void Transform(const gp_Trsf& theT)
  {
    loc.Transform(theT);
    vdir.Transform(theT);
  }

  [[nodiscard]] gp_Ax1 Transformed(const gp_Trsf& theT) const
  {
    gp_Ax1 A1 = *this;
    A1.Transform(theT);
    return A1;
  }

  constexpr void Translate(const gp_Vec& theV) noexcept { loc.Translate(theV); }

  [[nodiscard]] constexpr gp_Ax1 Translated(const gp_Vec& theV) const noexcept
  {
    gp_Ax1 A1 = *this;
    A1.loc.Translate(theV);
    return A1;
  }

  constexpr void Translate(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
  {
    loc.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Ax1 Translated(const gp_Pnt& theP1, const gp_Pnt& theP2) const noexcept
  {
    gp_Ax1 A1 = *this;
    A1.loc.Translate(theP1, theP2);
    return A1;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  Standard_EXPORT bool InitFromJson(const Standard_SStream& theSStream, int& theStreamPos);

private:
  gp_Pnt loc;
  gp_Dir vdir;
};
