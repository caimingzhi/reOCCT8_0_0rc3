#pragma once

#include <gp_Ax1.hpp>
#include <gp_Ax3.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>

class gp_Pln
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr gp_Pln() noexcept = default;

  constexpr gp_Pln(const gp_Ax3& theA3) noexcept
      : pos(theA3)
  {
  }

  Standard_EXPORT gp_Pln(const gp_Pnt& theP, const gp_Dir& theV);

  Standard_EXPORT gp_Pln(const double theA,
                         const double theB,
                         const double theC,
                         const double theD);

  void Coefficients(double& theA, double& theB, double& theC, double& theD) const noexcept;

  void SetAxis(const gp_Ax1& theA1) { pos.SetAxis(theA1); }

  constexpr void SetLocation(const gp_Pnt& theLoc) noexcept { pos.SetLocation(theLoc); }

  constexpr void SetPosition(const gp_Ax3& theA3) noexcept { pos = theA3; }

  constexpr void UReverse() noexcept { pos.XReverse(); }

  constexpr void VReverse() noexcept { pos.YReverse(); }

  bool Direct() const { return pos.Direct(); }

  constexpr const gp_Ax1& Axis() const noexcept { return pos.Axis(); }

  constexpr const gp_Pnt& Location() const noexcept { return pos.Location(); }

  constexpr const gp_Ax3& Position() const noexcept { return pos; }

  double Distance(const gp_Pnt& theP) const noexcept;

  double Distance(const gp_Lin& theL) const noexcept;

  double Distance(const gp_Pln& theOther) const noexcept;

  double SquareDistance(const gp_Pnt& theP) const noexcept
  {
    double aD = Distance(theP);
    return aD * aD;
  }

  double SquareDistance(const gp_Lin& theL) const noexcept
  {
    double aD = Distance(theL);
    return aD * aD;
  }

  double SquareDistance(const gp_Pln& theOther) const noexcept
  {
    double aD = Distance(theOther);
    return aD * aD;
  }

  constexpr gp_Ax1 XAxis() const noexcept { return gp_Ax1(pos.Location(), pos.XDirection()); }

  constexpr gp_Ax1 YAxis() const noexcept { return gp_Ax1(pos.Location(), pos.YDirection()); }

  bool Contains(const gp_Pnt& theP, const double theLinearTolerance) const noexcept
  {
    return Distance(theP) <= theLinearTolerance;
  }

  bool Contains(const gp_Lin& theL,
                const double  theLinearTolerance,
                const double  theAngularTolerance) const noexcept
  {
    return Contains(theL.Location(), theLinearTolerance)
           && pos.Direction().IsNormal(theL.Direction(), theAngularTolerance);
  }

  Standard_EXPORT void Mirror(const gp_Pnt& theP) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Pln Mirrored(const gp_Pnt& theP) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax1& theA1) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Pln Mirrored(const gp_Ax1& theA1) const noexcept;

  Standard_EXPORT void Mirror(const gp_Ax2& theA2) noexcept;

  [[nodiscard]] Standard_EXPORT gp_Pln Mirrored(const gp_Ax2& theA2) const noexcept;

  void Rotate(const gp_Ax1& theA1, const double theAng) { pos.Rotate(theA1, theAng); }

  [[nodiscard]] gp_Pln Rotated(const gp_Ax1& theA1, const double theAng) const
  {
    gp_Pln aPl = *this;
    aPl.pos.Rotate(theA1, theAng);
    return aPl;
  }

  void Scale(const gp_Pnt& theP, const double theS) { pos.Scale(theP, theS); }

  [[nodiscard]] gp_Pln Scaled(const gp_Pnt& theP, const double theS) const
  {
    gp_Pln aPl = *this;
    aPl.pos.Scale(theP, theS);
    return aPl;
  }

  void Transform(const gp_Trsf& theT) { pos.Transform(theT); }

  [[nodiscard]] gp_Pln Transformed(const gp_Trsf& theT) const
  {
    gp_Pln aPl = *this;
    aPl.pos.Transform(theT);
    return aPl;
  }

  constexpr void Translate(const gp_Vec& theV) noexcept { pos.Translate(theV); }

  [[nodiscard]] constexpr gp_Pln Translated(const gp_Vec& theV) const noexcept
  {
    gp_Pln aPl = *this;
    aPl.pos.Translate(theV);
    return aPl;
  }

  constexpr void Translate(const gp_Pnt& theP1, const gp_Pnt& theP2) noexcept
  {
    pos.Translate(theP1, theP2);
  }

  [[nodiscard]] constexpr gp_Pln Translated(const gp_Pnt& theP1, const gp_Pnt& theP2) const noexcept
  {
    gp_Pln aPl = *this;
    aPl.pos.Translate(theP1, theP2);
    return aPl;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  gp_Ax3 pos;
};

inline void gp_Pln::Coefficients(double& theA,
                                 double& theB,
                                 double& theC,
                                 double& theD) const noexcept
{
  const gp_Dir& aDir = pos.Direction();
  if (pos.Direct())
  {
    theA = aDir.X();
    theB = aDir.Y();
    theC = aDir.Z();
  }
  else
  {
    theA = -aDir.X();
    theB = -aDir.Y();
    theC = -aDir.Z();
  }
  const gp_Pnt& aP = pos.Location();
  theD             = -(theA * aP.X() + theB * aP.Y() + theC * aP.Z());
}

inline double gp_Pln::Distance(const gp_Pnt& theP) const noexcept
{
  const gp_Pnt& aLoc = pos.Location();
  const gp_Dir& aDir = pos.Direction();
  double        aD   = (aDir.X() * (theP.X() - aLoc.X()) + aDir.Y() * (theP.Y() - aLoc.Y())
               + aDir.Z() * (theP.Z() - aLoc.Z()));
  if (aD < 0)
  {
    aD = -aD;
  }
  return aD;
}

inline double gp_Pln::Distance(const gp_Lin& theL) const noexcept
{
  double aD = 0.0;
  if ((pos.Direction()).IsNormal(theL.Direction(), gp::Resolution()))
  {
    const gp_Pnt& aP   = theL.Location();
    const gp_Pnt& aLoc = pos.Location();
    const gp_Dir& aDir = pos.Direction();
    aD                 = (aDir.X() * (aP.X() - aLoc.X()) + aDir.Y() * (aP.Y() - aLoc.Y())
          + aDir.Z() * (aP.Z() - aLoc.Z()));
    if (aD < 0)
    {
      aD = -aD;
    }
  }
  return aD;
}

inline double gp_Pln::Distance(const gp_Pln& theOther) const noexcept
{
  double aD = 0.0;
  if ((pos.Direction()).IsParallel(theOther.pos.Direction(), gp::Resolution()))
  {
    const gp_Pnt& aP   = theOther.pos.Location();
    const gp_Pnt& aLoc = pos.Location();
    const gp_Dir& aDir = pos.Direction();
    aD                 = (aDir.X() * (aP.X() - aLoc.X()) + aDir.Y() * (aP.Y() - aLoc.Y())
          + aDir.Z() * (aP.Z() - aLoc.Z()));
    if (aD < 0)
    {
      aD = -aD;
    }
  }
  return aD;
}
