#pragma once

#include <GeomAbs_IsoType.hpp>
#include <Geom_BSplineSurface.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <NCollection_Array1.hpp>

#include <array>

class Geom_Surface;
class Geom_BSplineSurface;

class Geom_OsculatingSurface
{
public:
  Geom_OsculatingSurface();

  Geom_OsculatingSurface(const occ::handle<Geom_Surface>& theBS, double theTol);

  Geom_OsculatingSurface(const Geom_OsculatingSurface& theOther);

  Geom_OsculatingSurface(Geom_OsculatingSurface&& theOther) noexcept;

  Geom_OsculatingSurface& operator=(const Geom_OsculatingSurface& theOther);

  Geom_OsculatingSurface& operator=(Geom_OsculatingSurface&& theOther) noexcept;

  ~Geom_OsculatingSurface() = default;

  void Init(const occ::handle<Geom_Surface>& theBS, double theTol);

  const occ::handle<Geom_Surface>& BasisSurface() const { return myBasisSurf; }

  double Tolerance() const { return myTol; }

  bool HasOscSurf() const { return myAlong[0] || myAlong[1] || myAlong[2] || myAlong[3]; }

  bool IsAlongU() const { return myAlong[0] || myAlong[1]; }

  bool IsAlongV() const { return myAlong[2] || myAlong[3]; }

  bool UOsculatingSurface(double                            theU,
                          double                            theV,
                          bool&                             theT,
                          occ::handle<Geom_BSplineSurface>& theL) const;

  bool VOsculatingSurface(double                            theU,
                          double                            theV,
                          bool&                             theT,
                          occ::handle<Geom_BSplineSurface>& theL) const;

private:
  bool buildOsculatingSurface(double                                  theParam,
                              int                                     theUKnot,
                              int                                     theVKnot,
                              const occ::handle<Geom_BSplineSurface>& theBS,
                              occ::handle<Geom_BSplineSurface>&       theL) const;

  bool isQPunctual(const occ::handle<Geom_Surface>& theS,
                   double                           theParam,
                   GeomAbs_IsoType                  theIT,
                   double                           theTolMin,
                   double                           theTolMax) const;

  void clearOsculFlags();

private:
  occ::handle<Geom_Surface>                              myBasisSurf;
  double                                                 myTol;
  NCollection_Sequence<occ::handle<Geom_BSplineSurface>> myOsculSurf1;
  NCollection_Sequence<occ::handle<Geom_BSplineSurface>> myOsculSurf2;
  NCollection_Sequence<int>                              myKdeg;
  std::array<bool, 4>                                    myAlong;
};
