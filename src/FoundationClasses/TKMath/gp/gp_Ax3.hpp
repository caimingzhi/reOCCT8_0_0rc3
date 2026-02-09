#pragma once

#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

class gp_Trsf;

class gp_Ax3
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Ax3() noexcept
      : vydir(gp_Dir::D::Y),
        vxdir(gp_Dir::D::X)

  {
  }

  gp_Ax3(const gp_Ax2& theA);

  gp_Ax3(const gp_Pnt& theP, const gp_Dir& theN, const gp_Dir& theVx)
      : axis(theP, theN),
        vydir(theN),
        vxdir(theN)
  {
    vxdir.CrossCross(theVx, theN);
    vydir.Cross(vxdir);
  }

  constexpr gp_Ax3(const gp_Pnt& theP, const gp_Dir::D theN, const gp_Dir::D theVx) noexcept
      : axis(theP, theN),
        vydir(crossStandardDir(theN, theVx)),
        vxdir(theVx)
  {
  }

  Standard_EXPORT gp_Ax3(const gp_Pnt& theP, const gp_Dir& theV);

  constexpr gp_Ax3(const gp_Pnt& theP, const gp_Dir::D theV) noexcept
      : axis(theP, theV),
        vydir(getPerpendicularYDir(theV)),
        vxdir(getPerpendicularXDir(theV))
  {
  }

  constexpr explicit gp_Ax3(const gp_Dir::D theV) noexcept
      : axis(gp_Pnt(0., 0., 0.), theV),
        vydir(getPerpendicularYDir(theV)),
        vxdir(getPerpendicularXDir(theV))
  {
  }

  constexpr void XReverse() noexcept { vxdir.Reverse(); }

  constexpr void YReverse() noexcept { vydir.Reverse(); }

  constexpr void ZReverse() noexcept { axis.Reverse(); }

  void SetAxis(const gp_Ax1& theA1);

  void SetDirection(const gp_Dir& theV);

  constexpr void SetLocation(const gp_Pnt& theP) noexcept { axis.SetLocation(theP); }

  void SetXDirection(const gp_Dir& theVx);

  void SetYDirection(const gp_Dir& theVy);

  double Angle(const gp_Ax3& theOther) const { return axis.Angle(theOther.axis); }

  constexpr const gp_Ax1& Axis() const noexcept { return axis; }

  gp_Ax2 Ax2() const;

  constexpr const gp_Dir& Direction() const noexcept { return axis.Direction(); }

  constexpr const gp_Pnt& Location() const noexcept { return axis.Location(); }

  constexpr const gp_Dir& XDirection() const noexcept { return vxdir; }

  constexpr const gp_Dir& YDirection() const noexcept { return vydir; }

  bool Direct() const { return (vxdir.Crossed(vydir).Dot(axis.Direction()) > 0.); }

  bool IsCoplanar(const gp_Ax3& theOther,
                  const double  theLinearTolerance,
                  const double  theAngularTolerance) const;

  bool IsCoplanar(const gp_Ax1& theA1,
                  const double  theLinearTolerance,
                  const double  theAngularTolerance) const;

  Standard_EXPORT void Mirror(const gp_Pnt& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Ax3 Mirrored(const gp_Pnt& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& theA1) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Ax3 Mirrored(const gp_Ax1& theA1) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2& theA2) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Ax3 Mirrored(const gp_Ax2& theA2) const noexcept;

  void Rotate(const gp_Ax1& theA1, const double theAng)
  {
    axis.Rotate(theA1, theAng);
    vxdir.Rotate(theA1, theAng);
    vydir.Rotate(theA1, theAng);
  }

  [[nodiscard]] gp_Ax3 Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Ax3 aTemp = *this;
    aTemp.Rotate(theA1, theAng);
    return aTemp;
  }

  void Scale(const gp_Pnt& theP, const double theS)
  {
    axis.Scale(theP, theS);
    if (theS < 0.)
    {
      vxdir.Reverse();
      vydir.Reverse();
    }
  }

  [[nodiscard]] gp_Ax3 Scaled(const gp_Pnt& theP, const double theS) const
  {
    gp_Ax3 aTemp = *this;
    aTemp.Scale(theP, theS);
    return aTemp;
  }

  void Transform(const gp_Trsf& theT)
  {
    axis.Transform(theT);
    vxdir.Transform(theT);
    vydir.Transform(theT);
  }

  [[nodiscard]] gp_Ax3 Transformed(const gp_Trsf& theT) const
  {
    gp_Ax3 aTemp = *this;
    aTemp.Transform(theT);
    return aTemp;
  }

  constexpr void Translate(const gp_Vec& theV) noexcept { axis.Translate(theV); }

  [[nodiscard]] constexpr gp_Ax3 Translated(const gp_Vec& theV) const noexcept
  {
    gp_Ax3 aTemp = *this;
    aTemp.Translate(theV);
    return aTemp;
  }

  constexpr void Translate(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
  {
    Translate(gp_Vec(theP1, theP2));
  }

  [[nodiscard]] constexpr gp_Ax3 Translated(const gp_Pnt& theP1, const gp_Pnt& theP2) const noexcept
  {
    return Translated(gp_Vec(theP1, theP2));
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  Standard_EXPORT bool InitFromJson(const Standard_SStream& theSStream, int& theStreamPos);

private:
  static constexpr gp_Dir::D getPerpendicularXDir(const gp_Dir::D theMainDir) noexcept;

  static constexpr gp_Dir::D getPerpendicularYDir(const gp_Dir::D theMainDir) noexcept;

  static constexpr gp_Dir::D crossStandardDir(const gp_Dir::D theA, const gp_Dir::D theB) noexcept;

  gp_Ax1 axis;
  gp_Dir vydir;
  gp_Dir vxdir;
};

inline constexpr gp_Dir::D gp_Ax3::getPerpendicularXDir(const gp_Dir::D theMainDir) noexcept
{
  return (theMainDir == gp_Dir::D::X || theMainDir == gp_Dir::D::NX)   ? gp_Dir::D::Y
         : (theMainDir == gp_Dir::D::Y || theMainDir == gp_Dir::D::NY) ? gp_Dir::D::Z
                                                                       : gp_Dir::D::X;
}

inline constexpr gp_Dir::D gp_Ax3::getPerpendicularYDir(const gp_Dir::D theMainDir) noexcept
{
  return (theMainDir == gp_Dir::D::Z)    ? gp_Dir::D::Y
         : (theMainDir == gp_Dir::D::NZ) ? gp_Dir::D::NY
         : (theMainDir == gp_Dir::D::X)  ? gp_Dir::D::Z
         : (theMainDir == gp_Dir::D::NX) ? gp_Dir::D::NZ
         : (theMainDir == gp_Dir::D::Y)  ? gp_Dir::D::X
                                         : gp_Dir::D::NX;
}

inline constexpr gp_Dir::D gp_Ax3::crossStandardDir(const gp_Dir::D theA,
                                                    const gp_Dir::D theB) noexcept
{

  if (theA == gp_Dir::D::X)
  {
    if (theB == gp_Dir::D::Y)
      return gp_Dir::D::Z;
    if (theB == gp_Dir::D::Z)
      return gp_Dir::D::NY;
    if (theB == gp_Dir::D::NY)
      return gp_Dir::D::NZ;
    if (theB == gp_Dir::D::NZ)
      return gp_Dir::D::Y;

    return gp_Dir::D::Z;
  }
  if (theA == gp_Dir::D::Y)
  {
    if (theB == gp_Dir::D::Z)
      return gp_Dir::D::X;
    if (theB == gp_Dir::D::X)
      return gp_Dir::D::NZ;
    if (theB == gp_Dir::D::NX)
      return gp_Dir::D::Z;
    if (theB == gp_Dir::D::NZ)
      return gp_Dir::D::NX;

    return gp_Dir::D::X;
  }
  if (theA == gp_Dir::D::Z)
  {
    if (theB == gp_Dir::D::X)
      return gp_Dir::D::Y;
    if (theB == gp_Dir::D::Y)
      return gp_Dir::D::NX;
    if (theB == gp_Dir::D::NX)
      return gp_Dir::D::NY;
    if (theB == gp_Dir::D::NY)
      return gp_Dir::D::X;

    return gp_Dir::D::Y;
  }

  if (theA == gp_Dir::D::NX)
  {
    if (theB == gp_Dir::D::Y)
      return gp_Dir::D::NZ;
    if (theB == gp_Dir::D::Z)
      return gp_Dir::D::Y;
    if (theB == gp_Dir::D::NY)
      return gp_Dir::D::Z;
    if (theB == gp_Dir::D::NZ)
      return gp_Dir::D::NY;
    return gp_Dir::D::NZ;
  }
  if (theA == gp_Dir::D::NY)
  {
    if (theB == gp_Dir::D::Z)
      return gp_Dir::D::NX;
    if (theB == gp_Dir::D::X)
      return gp_Dir::D::Z;
    if (theB == gp_Dir::D::NX)
      return gp_Dir::D::NZ;
    if (theB == gp_Dir::D::NZ)
      return gp_Dir::D::X;
    return gp_Dir::D::NX;
  }
  if (theA == gp_Dir::D::NZ)
  {
    if (theB == gp_Dir::D::X)
      return gp_Dir::D::NY;
    if (theB == gp_Dir::D::Y)
      return gp_Dir::D::X;
    if (theB == gp_Dir::D::NX)
      return gp_Dir::D::Y;
    if (theB == gp_Dir::D::NY)
      return gp_Dir::D::NX;
    return gp_Dir::D::NY;
  }
  return gp_Dir::D::Z;
}

inline gp_Ax3::gp_Ax3(const gp_Ax2& theA)
    : axis(theA.Axis()),
      vydir(theA.YDirection()),
      vxdir(theA.XDirection())
{
}

inline gp_Ax2 gp_Ax3::Ax2() const
{
  gp_Dir aZz = axis.Direction();
  if (!Direct())
  {
    aZz.Reverse();
  }
  return gp_Ax2(axis.Location(), aZz, vxdir);
}

inline void gp_Ax3::SetAxis(const gp_Ax1& theA1)
{
  axis.SetLocation(theA1.Location());
  SetDirection(theA1.Direction());
}

inline void gp_Ax3::SetDirection(const gp_Dir& theV)
{
  double aDot = theV.Dot(vxdir);
  if (1. - std::abs(aDot) <= Precision::Angular())
  {
    if (aDot > 0)
    {
      vxdir = vydir;
      vydir = axis.Direction();
    }
    else
    {
      vxdir = axis.Direction();
    }
    axis.SetDirection(theV);
  }
  else
  {
    bool direct = Direct();
    axis.SetDirection(theV);
    vxdir = theV.CrossCrossed(vxdir, theV);
    if (direct)
    {
      vydir = theV.Crossed(vxdir);
    }
    else
    {
      vydir = vxdir.Crossed(theV);
    }
  }
}

inline void gp_Ax3::SetXDirection(const gp_Dir& theVx)
{
  double aDot = theVx.Dot(axis.Direction());
  if (1. - std::abs(aDot) <= Precision::Angular())
  {
    if (aDot > 0)
    {
      axis.SetDirection(vxdir);
      vydir = -vydir;
    }
    else
    {
      axis.SetDirection(vxdir);
    }
    vxdir = theVx;
  }
  else
  {
    bool direct = Direct();
    vxdir       = axis.Direction().CrossCrossed(theVx, axis.Direction());
    if (direct)
    {
      vydir = axis.Direction().Crossed(vxdir);
    }
    else
    {
      vydir = vxdir.Crossed(axis.Direction());
    }
  }
}

inline void gp_Ax3::SetYDirection(const gp_Dir& theVy)
{
  double aDot = theVy.Dot(axis.Direction());
  if (1. - std::abs(aDot) <= Precision::Angular())
  {
    if (aDot > 0)
    {
      axis.SetDirection(vydir);
      vxdir = -vxdir;
    }
    else
    {
      axis.SetDirection(vydir);
    }
    vydir = theVy;
  }
  else
  {
    bool isDirect = Direct();
    vxdir         = theVy.Crossed(axis.Direction());
    vydir         = (axis.Direction()).Crossed(vxdir);
    if (!isDirect)
    {
      vxdir.Reverse();
    }
  }
}

inline bool gp_Ax3::IsCoplanar(const gp_Ax3& theOther,
                               const double  theLinearTolerance,
                               const double  theAngularTolerance) const
{
  gp_Vec aVec(axis.Location(), theOther.axis.Location());
  double aD1 = gp_Vec(axis.Direction()).Dot(aVec);
  if (aD1 < 0)
  {
    aD1 = -aD1;
  }
  double aD2 = gp_Vec(theOther.axis.Direction()).Dot(aVec);
  if (aD2 < 0)
  {
    aD2 = -aD2;
  }
  return (aD1 <= theLinearTolerance && aD2 <= theLinearTolerance
          && axis.IsParallel(theOther.axis, theAngularTolerance));
}

inline bool gp_Ax3::IsCoplanar(const gp_Ax1& theA1,
                               const double  theLinearTolerance,
                               const double  theAngularTolerance) const
{
  gp_Vec aVec(axis.Location(), theA1.Location());
  double aD1 = gp_Vec(axis.Direction()).Dot(aVec);
  if (aD1 < 0)
  {
    aD1 = -aD1;
  }
  double aD2 = (gp_Vec(theA1.Direction()).Crossed(aVec)).Magnitude();
  if (aD2 < 0)
  {
    aD2 = -aD2;
  }
  return (aD1 <= theLinearTolerance && aD2 <= theLinearTolerance
          && axis.IsNormal(theA1, theAngularTolerance));
}
