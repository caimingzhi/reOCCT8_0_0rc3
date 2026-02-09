#pragma once

#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>

#include <algorithm>
#include <cmath>

class gp_Dir2d;
class gp_Trsf2d;

class Bnd_Box2d
{
public:
  DEFINE_STANDARD_ALLOC

  struct Limits
  {
    double Xmin;
    double Xmax;
    double Ymin;
    double Ymax;
  };

  constexpr Bnd_Box2d()
      : Xmin(RealLast()),
        Xmax(-RealLast()),
        Ymin(RealLast()),
        Ymax(-RealLast()),
        Gap(0.),
        Flags(VoidMask)
  {
  }

  void SetWhole() noexcept { Flags = WholeMask; }

  void SetVoid() noexcept
  {
    Xmin  = RealLast();
    Xmax  = -RealLast();
    Ymin  = RealLast();
    Ymax  = -RealLast();
    Gap   = 0.0;
    Flags = VoidMask;
  }

  void Set(const gp_Pnt2d& thePnt)
  {
    Flags = VoidMask;
    Gap   = 0.0;
    Add(thePnt);
  }

  void Set(const gp_Pnt2d& thePnt, const gp_Dir2d& theDir)
  {
    Flags = VoidMask;
    Gap   = 0.0;
    Add(thePnt, theDir);
  }

  Standard_EXPORT void Update(const double aXmin,
                              const double aYmin,
                              const double aXmax,
                              const double aYmax);

  Standard_EXPORT void Update(const double X, const double Y);

  [[nodiscard]] constexpr double GetGap() const noexcept { return Gap; }

  void SetGap(const double Tol) noexcept { Gap = std::abs(Tol); }

  void Enlarge(const double theTol) noexcept { Gap = (std::max)(Gap, std::abs(theTol)); }

  Standard_EXPORT void Get(double& aXmin, double& aYmin, double& aXmax, double& aYmax) const;

  [[nodiscard]] Standard_EXPORT Limits Get() const;

  [[nodiscard]] Standard_EXPORT double GetXMin() const;

  [[nodiscard]] Standard_EXPORT double GetXMax() const;

  [[nodiscard]] Standard_EXPORT double GetYMin() const;

  [[nodiscard]] Standard_EXPORT double GetYMax() const;

  void OpenXmin() noexcept { Flags |= XminMask; }

  void OpenXmax() noexcept { Flags |= XmaxMask; }

  void OpenYmin() noexcept { Flags |= YminMask; }

  void OpenYmax() noexcept { Flags |= YmaxMask; }

  [[nodiscard]] bool IsOpenXmin() const noexcept { return (Flags & XminMask) != 0; }

  [[nodiscard]] bool IsOpenXmax() const noexcept { return (Flags & XmaxMask) != 0; }

  [[nodiscard]] bool IsOpenYmin() const noexcept { return (Flags & YminMask) != 0; }

  [[nodiscard]] bool IsOpenYmax() const noexcept { return (Flags & YmaxMask) != 0; }

  [[nodiscard]] bool IsWhole() const noexcept { return (Flags & WholeMask) == WholeMask; }

  [[nodiscard]] bool IsVoid() const noexcept { return (Flags & VoidMask) != 0; }

  [[nodiscard]] Standard_EXPORT Bnd_Box2d Transformed(const gp_Trsf2d& T) const;

  Standard_EXPORT void Add(const Bnd_Box2d& Other);

  void Add(const gp_Pnt2d& thePnt) noexcept { Update(thePnt.X(), thePnt.Y()); }

  void Add(const gp_Pnt2d& thePnt, const gp_Dir2d& theDir) noexcept
  {
    Add(thePnt);
    Add(theDir);
  }

  Standard_EXPORT void Add(const gp_Dir2d& D);

  [[nodiscard]] Standard_EXPORT bool IsOut(const gp_Pnt2d& P) const;

  [[nodiscard]] Standard_EXPORT bool IsOut(const gp_Lin2d& theL) const;

  [[nodiscard]] Standard_EXPORT bool IsOut(const gp_Pnt2d& theP0, const gp_Pnt2d& theP1) const;

  [[nodiscard]] Standard_EXPORT bool IsOut(const Bnd_Box2d& Other) const;

  [[nodiscard]] bool IsOut(const Bnd_Box2d& theOther, const gp_Trsf2d& theTrsf) const noexcept
  {
    return IsOut(theOther.Transformed(theTrsf));
  }

  [[nodiscard]] bool IsOut(const gp_Trsf2d& T1,
                           const Bnd_Box2d& Other,
                           const gp_Trsf2d& T2) const noexcept
  {
    return Transformed(T1).IsOut(Other.Transformed(T2));
  }

  Standard_EXPORT void Dump() const;

  [[nodiscard]] double SquareExtent() const noexcept
  {
    if (IsVoid())
      return 0.0;
    const double aDx = Xmax - Xmin + Gap + Gap;
    const double aDy = Ymax - Ymin + Gap + Gap;
    return aDx * aDx + aDy * aDy;
  }

protected:
  enum MaskFlags
  {
    VoidMask  = 0x01,
    XminMask  = 0x02,
    XmaxMask  = 0x04,
    YminMask  = 0x08,
    YmaxMask  = 0x10,
    WholeMask = 0x1e
  };

private:
  double Xmin;
  double Xmax;
  double Ymin;
  double Ymax;
  double Gap;
  int    Flags;
};
