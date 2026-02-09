#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>

#include <algorithm>
#include <cmath>

class gp_Pnt;
class gp_Dir;
class gp_Trsf;
class gp_Lin;
class gp_Pln;

class Bnd_Box
{
public:
  DEFINE_STANDARD_ALLOC

  struct Limits
  {
    double Xmin;
    double Xmax;
    double Ymin;
    double Ymax;
    double Zmin;
    double Zmax;
  };

  constexpr Bnd_Box()
      : Xmin(RealLast()),
        Xmax(-RealLast()),
        Ymin(RealLast()),
        Ymax(-RealLast()),
        Zmin(RealLast()),
        Zmax(-RealLast()),
        Gap(0.0),
        Flags(VoidMask)
  {
  }

  constexpr Bnd_Box(const gp_Pnt& theMin, const gp_Pnt& theMax)
      : Xmin(theMin.X()),
        Xmax(theMax.X()),
        Ymin(theMin.Y()),
        Ymax(theMax.Y()),
        Zmin(theMin.Z()),
        Zmax(theMax.Z()),
        Gap(0.0),
        Flags(0)
  {
  }

  void SetWhole() noexcept { Flags = WholeMask; }

  void SetVoid() noexcept
  {
    Xmin  = RealLast();
    Xmax  = -RealLast();
    Ymin  = RealLast();
    Ymax  = -RealLast();
    Zmin  = RealLast();
    Zmax  = -RealLast();
    Gap   = 0.0;
    Flags = VoidMask;
  }

  Standard_EXPORT void Set(const gp_Pnt& P);

  Standard_EXPORT void Set(const gp_Pnt& P, const gp_Dir& D);

  Standard_EXPORT void Update(const double aXmin,
                              const double aYmin,
                              const double aZmin,
                              const double aXmax,
                              const double aYmax,
                              const double aZmax);

  Standard_EXPORT void Update(const double X, const double Y, const double Z);

  [[nodiscard]] constexpr double GetGap() const noexcept { return Gap; }

  void SetGap(const double Tol) noexcept { Gap = std::abs(Tol); }

  void Enlarge(const double Tol) noexcept { Gap = (std::max)(Gap, std::abs(Tol)); }

  Standard_EXPORT void Get(double& theXmin,
                           double& theYmin,
                           double& theZmin,
                           double& theXmax,
                           double& theYmax,
                           double& theZmax) const;

  [[nodiscard]] Standard_EXPORT Limits Get() const;

  [[nodiscard]] Standard_EXPORT double GetXMin() const;

  [[nodiscard]] Standard_EXPORT double GetXMax() const;

  [[nodiscard]] Standard_EXPORT double GetYMin() const;

  [[nodiscard]] Standard_EXPORT double GetYMax() const;

  [[nodiscard]] Standard_EXPORT double GetZMin() const;

  [[nodiscard]] Standard_EXPORT double GetZMax() const;

  [[nodiscard]] Standard_EXPORT gp_Pnt CornerMin() const;

  [[nodiscard]] Standard_EXPORT gp_Pnt CornerMax() const;

  void OpenXmin() noexcept { Flags |= XminMask; }

  void OpenXmax() noexcept { Flags |= XmaxMask; }

  void OpenYmin() noexcept { Flags |= YminMask; }

  void OpenYmax() noexcept { Flags |= YmaxMask; }

  void OpenZmin() noexcept { Flags |= ZminMask; }

  void OpenZmax() noexcept { Flags |= ZmaxMask; }

  [[nodiscard]] bool IsOpen() const noexcept { return (Flags & WholeMask) != 0; }

  [[nodiscard]] bool IsOpenXmin() const noexcept { return (Flags & XminMask) != 0; }

  [[nodiscard]] bool IsOpenXmax() const noexcept { return (Flags & XmaxMask) != 0; }

  [[nodiscard]] bool IsOpenYmin() const noexcept { return (Flags & YminMask) != 0; }

  [[nodiscard]] bool IsOpenYmax() const noexcept { return (Flags & YmaxMask) != 0; }

  [[nodiscard]] bool IsOpenZmin() const noexcept { return (Flags & ZminMask) != 0; }

  [[nodiscard]] bool IsOpenZmax() const noexcept { return (Flags & ZmaxMask) != 0; }

  [[nodiscard]] bool IsWhole() const noexcept { return (Flags & WholeMask) == WholeMask; }

  [[nodiscard]] bool IsVoid() const noexcept { return (Flags & VoidMask) != 0; }

  [[nodiscard]] Standard_EXPORT bool IsXThin(const double tol) const;

  [[nodiscard]] Standard_EXPORT bool IsYThin(const double tol) const;

  [[nodiscard]] Standard_EXPORT bool IsZThin(const double tol) const;

  [[nodiscard]] Standard_EXPORT bool IsThin(const double tol) const;

  [[nodiscard]] Standard_EXPORT Bnd_Box Transformed(const gp_Trsf& T) const;

  Standard_EXPORT void Add(const Bnd_Box& Other);

  Standard_EXPORT void Add(const gp_Pnt& P);

  Standard_EXPORT void Add(const gp_Pnt& P, const gp_Dir& D);

  Standard_EXPORT void Add(const gp_Dir& D);

  [[nodiscard]] Standard_EXPORT bool IsOut(const gp_Pnt& P) const;

  [[nodiscard]] Standard_EXPORT bool IsOut(const gp_Lin& L) const;

  [[nodiscard]] Standard_EXPORT bool IsOut(const gp_Pln& P) const;

  [[nodiscard]] Standard_EXPORT bool IsOut(const Bnd_Box& Other) const;

  [[nodiscard]] Standard_EXPORT bool IsOut(const Bnd_Box& Other, const gp_Trsf& T) const;

  [[nodiscard]] Standard_EXPORT bool IsOut(const gp_Trsf& T1,
                                           const Bnd_Box& Other,
                                           const gp_Trsf& T2) const;

  [[nodiscard]] Standard_EXPORT bool IsOut(const gp_Pnt& P1,
                                           const gp_Pnt& P2,
                                           const gp_Dir& D) const;

  [[nodiscard]] Standard_EXPORT double Distance(const Bnd_Box& Other) const;

  Standard_EXPORT void Dump() const;

  [[nodiscard]] double SquareExtent() const noexcept
  {
    if (IsVoid())
    {
      return 0.0;
    }

    const double aDx = Xmax - Xmin + Gap + Gap;
    const double aDy = Ymax - Ymin + Gap + Gap;
    const double aDz = Zmax - Zmin + Gap + Gap;
    return aDx * aDx + aDy * aDy + aDz * aDz;
  }

  [[nodiscard]] Bnd_Box FinitePart() const noexcept
  {
    if (!HasFinitePart())
    {
      return Bnd_Box();
    }

    Bnd_Box aBox;
    aBox.Update(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);
    aBox.SetGap(Gap);
    return aBox;
  }

  [[nodiscard]] bool HasFinitePart() const noexcept { return !IsVoid() && Xmax >= Xmin; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  Standard_EXPORT bool InitFromJson(const Standard_SStream& theSStream, int& theStreamPos);

protected:
  enum MaskFlags
  {
    VoidMask  = 0x01,
    XminMask  = 0x02,
    XmaxMask  = 0x04,
    YminMask  = 0x08,
    YmaxMask  = 0x10,
    ZminMask  = 0x20,
    ZmaxMask  = 0x40,
    WholeMask = 0x7e
  };

private:
  double Xmin;
  double Xmax;
  double Ymin;
  double Ymax;
  double Zmin;
  double Zmax;
  double Gap;
  int    Flags;
};
