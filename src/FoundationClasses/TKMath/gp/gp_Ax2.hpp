#pragma once

#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <Precision.hpp>

class gp_Trsf;
class gp_Vec;

class gp_Ax2
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Ax2() noexcept
      : vydir(gp_Dir::D::Y),
        vxdir(gp_Dir::D::X)

  {
  }

  gp_Ax2(const gp_Pnt& P, const gp_Dir& N, const gp_Dir& Vx)
      : axis(P, N),
        vydir(N),
        vxdir(N)
  {
    vxdir.CrossCross(Vx, N);
    vydir.Cross(vxdir);
  }

  constexpr gp_Ax2(const gp_Pnt& theP, const gp_Dir::D theN, const gp_Dir::D theVx) noexcept
      : axis(theP, theN),
        vydir(crossStandardDir(theN, theVx)),
        vxdir(theVx)
  {
  }

  Standard_EXPORT gp_Ax2(const gp_Pnt& P, const gp_Dir& V);

  constexpr gp_Ax2(const gp_Pnt& theP, const gp_Dir::D theV) noexcept
      : axis(theP, theV),
        vydir(getPerpendicularYDir(theV)),
        vxdir(getPerpendicularXDir(theV))
  {
  }

  constexpr explicit gp_Ax2(const gp_Dir::D theV) noexcept
      : axis(gp_Pnt(0., 0., 0.), theV),
        vydir(getPerpendicularYDir(theV)),
        vxdir(getPerpendicularXDir(theV))
  {
  }

  void SetAxis(const gp_Ax1& A1);

  void SetDirection(const gp_Dir& V);

  constexpr void SetLocation(const gp_Pnt& theP) noexcept { axis.SetLocation(theP); }

  void SetXDirection(const gp_Dir& theVx)
  {
    vxdir = axis.Direction().CrossCrossed(theVx, axis.Direction());
    vydir = axis.Direction().Crossed(vxdir);
  }

  void SetYDirection(const gp_Dir& theVy)
  {
    vxdir = theVy.Crossed(axis.Direction());
    vydir = (axis.Direction()).Crossed(vxdir);
  }

  double Angle(const gp_Ax2& theOther) const { return axis.Angle(theOther.axis); }

  constexpr const gp_Ax1& Axis() const noexcept { return axis; }

  constexpr const gp_Dir& Direction() const noexcept { return axis.Direction(); }

  constexpr const gp_Pnt& Location() const noexcept { return axis.Location(); }

  constexpr const gp_Dir& XDirection() const noexcept { return vxdir; }

  constexpr const gp_Dir& YDirection() const noexcept { return vydir; }

  bool IsCoplanar(const gp_Ax2& Other,
                  const double  LinearTolerance,
                  const double  AngularTolerance) const;

  bool IsCoplanar(const gp_Ax1& A1,
                  const double  LinearTolerance,
                  const double  AngularTolerance) const;

  Standard_EXPORT void Mirror(const gp_Pnt& P) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Ax2 Mirrored(const gp_Pnt& P) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& A1);

  [[nodiscard]] Standard_EXPORT gp_Ax2 Mirrored(const gp_Ax1& A1) const;

  Standard_EXPORT void Mirror(const gp_Ax2& A2);

  [[nodiscard]] Standard_EXPORT gp_Ax2 Mirrored(const gp_Ax2& A2) const;

  void Rotate(const gp_Ax1& theA1, const double theAng)
  {
    gp_Pnt aTemp = axis.Location();
    aTemp.Rotate(theA1, theAng);
    axis.SetLocation(aTemp);
    vxdir.Rotate(theA1, theAng);
    vydir.Rotate(theA1, theAng);
    axis.SetDirection(vxdir.Crossed(vydir));
  }

  [[nodiscard]] gp_Ax2 Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Ax2 aTemp = *this;
    aTemp.Rotate(theA1, theAng);
    return aTemp;
  }

  constexpr void Scale(const gp_Pnt& theP, const double theS) noexcept
  {
    gp_Pnt aTemp = axis.Location();
    aTemp.Scale(theP, theS);
    axis.SetLocation(aTemp);
    if (theS < 0.0)
    {
      vxdir.Reverse();
      vydir.Reverse();
    }
  }

  [[nodiscard]] constexpr gp_Ax2 Scaled(const gp_Pnt& theP, const double theS) const noexcept
  {
    gp_Ax2 aTemp = *this;
    aTemp.Scale(theP, theS);
    return aTemp;
  }

  void Transform(const gp_Trsf& theT)
  {
    gp_Pnt aTemp = axis.Location();
    aTemp.Transform(theT);
    axis.SetLocation(aTemp);
    vxdir.Transform(theT);
    vydir.Transform(theT);
    axis.SetDirection(vxdir.Crossed(vydir));
  }

  [[nodiscard]] gp_Ax2 Transformed(const gp_Trsf& theT) const
  {
    gp_Ax2 aTemp = *this;
    aTemp.Transform(theT);
    return aTemp;
  }

  constexpr void Translate(const gp_Vec& theV) noexcept { axis.Translate(theV); }

  [[nodiscard]] constexpr gp_Ax2 Translated(const gp_Vec& theV) const noexcept
  {
    gp_Ax2 aTemp = *this;
    aTemp.Translate(theV);
    return aTemp;
  }

  constexpr void Translate(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
  {
    axis.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Ax2 Translated(const gp_Pnt& theP1, const gp_Pnt& theP2) const noexcept
  {
    gp_Ax2 aTemp = *this;
    aTemp.Translate(theP1, theP2);
    return aTemp;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  Standard_EXPORT bool InitFromJson(const Standard_SStream& theSStream, int& theStreamPos);

protected:
  static constexpr gp_Dir::D getPerpendicularXDir(const gp_Dir::D theMainDir) noexcept;

  static constexpr gp_Dir::D getPerpendicularYDir(const gp_Dir::D theMainDir) noexcept;

  static constexpr gp_Dir::D crossStandardDir(const gp_Dir::D theA, const gp_Dir::D theB) noexcept;

private:
  gp_Ax1 axis;
  gp_Dir vydir;
  gp_Dir vxdir;
};

inline constexpr gp_Dir::D gp_Ax2::getPerpendicularXDir(const gp_Dir::D theMainDir) noexcept
{
  return (theMainDir == gp_Dir::D::X || theMainDir == gp_Dir::D::NX)   ? gp_Dir::D::Y
         : (theMainDir == gp_Dir::D::Y || theMainDir == gp_Dir::D::NY) ? gp_Dir::D::Z
                                                                       : gp_Dir::D::X;
}

inline constexpr gp_Dir::D gp_Ax2::getPerpendicularYDir(const gp_Dir::D theMainDir) noexcept
{
  return (theMainDir == gp_Dir::D::Z)    ? gp_Dir::D::Y
         : (theMainDir == gp_Dir::D::NZ) ? gp_Dir::D::NY
         : (theMainDir == gp_Dir::D::X)  ? gp_Dir::D::Z
         : (theMainDir == gp_Dir::D::NX) ? gp_Dir::D::NZ
         : (theMainDir == gp_Dir::D::Y)  ? gp_Dir::D::X
                                         : gp_Dir::D::NX;
}

inline constexpr gp_Dir::D gp_Ax2::crossStandardDir(const gp_Dir::D theA,
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

inline void gp_Ax2::SetAxis(const gp_Ax1& theA1)
{
  double a = theA1.Direction() * vxdir;
  if (std::abs(std::abs(a) - 1.) <= Precision::Angular())
  {
    if (a > 0.)
    {
      vxdir = vydir;
      vydir = axis.Direction();
      axis  = theA1;
    }
    else
    {
      vxdir = axis.Direction();
      axis  = theA1;
    }
  }
  else
  {
    axis  = theA1;
    vxdir = axis.Direction().CrossCrossed(vxdir, axis.Direction());
    vydir = axis.Direction().Crossed(vxdir);
  }
}

inline void gp_Ax2::SetDirection(const gp_Dir& theV)
{
  double a = theV * vxdir;
  if (std::abs(std::abs(a) - 1.) <= Precision::Angular())
  {
    if (a > 0.)
    {
      vxdir = vydir;
      vydir = axis.Direction();
      axis.SetDirection(theV);
    }
    else
    {
      vxdir = axis.Direction();
      axis.SetDirection(theV);
    }
  }
  else
  {
    axis.SetDirection(theV);
    vxdir = theV.CrossCrossed(vxdir, theV);
    vydir = theV.Crossed(vxdir);
  }
}

inline bool gp_Ax2::IsCoplanar(const gp_Ax2& theOther,
                               const double  theLinearTolerance,
                               const double  theAngularTolerance) const
{
  const gp_Dir& DD = axis.Direction();
  const gp_Pnt& PP = axis.Location();
  const gp_Pnt& OP = theOther.axis.Location();
  double        D1 =
    (DD.X() * (OP.X() - PP.X()) + DD.Y() * (OP.Y() - PP.Y()) + DD.Z() * (OP.Z() - PP.Z()));
  if (D1 < 0)
  {
    D1 = -D1;
  }
  return D1 <= theLinearTolerance && axis.IsParallel(theOther.axis, theAngularTolerance);
}

inline bool gp_Ax2::IsCoplanar(const gp_Ax1& theA,
                               const double  theLinearTolerance,
                               const double  theAngularTolerance) const
{
  const gp_Dir& DD = axis.Direction();
  const gp_Pnt& PP = axis.Location();
  const gp_Pnt& AP = theA.Location();
  double        D1 =
    (DD.X() * (AP.X() - PP.X()) + DD.Y() * (AP.Y() - PP.Y()) + DD.Z() * (AP.Z() - PP.Z()));
  if (D1 < 0)
  {
    D1 = -D1;
  }
  return D1 <= theLinearTolerance && axis.IsNormal(theA, theAngularTolerance);
}
