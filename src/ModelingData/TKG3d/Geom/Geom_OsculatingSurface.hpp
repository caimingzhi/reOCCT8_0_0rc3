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

//! Internal helper class for Geom_OffsetSurface.
//! Detects if the surface has punctual U or V isoparametric curve
//! along on the bounds of the surface relatively to the tolerance
//! and builds the corresponding osculating surfaces.
//!
//! This is a private implementation class - not for external use.
class Geom_OsculatingSurface
{
public:
  //! Default constructor.
  Geom_OsculatingSurface();

  //! Constructor that detects punctual isoparametric curves and builds
  //! osculating surfaces.
  //! @param theBS the basis surface to analyze
  //! @param theTol tolerance for detecting punctual curves
  Geom_OsculatingSurface(const occ::handle<Geom_Surface>& theBS, double theTol);

  //! Copy constructor.
  Geom_OsculatingSurface(const Geom_OsculatingSurface& theOther);

  //! Move constructor.
  Geom_OsculatingSurface(Geom_OsculatingSurface&& theOther) noexcept;

  //! Copy assignment.
  Geom_OsculatingSurface& operator=(const Geom_OsculatingSurface& theOther);

  //! Move assignment.
  Geom_OsculatingSurface& operator=(Geom_OsculatingSurface&& theOther) noexcept;

  //! Destructor.
  ~Geom_OsculatingSurface() = default;

  //! Initialize with a surface and tolerance.
  void Init(const occ::handle<Geom_Surface>& theBS, double theTol);

  //! Returns the basis surface.
  const occ::handle<Geom_Surface>& BasisSurface() const { return myBasisSurf; }

  //! Returns the tolerance.
  double Tolerance() const { return myTol; }

  //! Returns true if any osculating surface exists.
  bool HasOscSurf() const { return myAlong[0] || myAlong[1] || myAlong[2] || myAlong[3]; }

  //! Returns true if osculating surface exists along U direction.
  bool IsAlongU() const { return myAlong[0] || myAlong[1]; }

  //! Returns true if osculating surface exists along V direction.
  bool IsAlongV() const { return myAlong[2] || myAlong[3]; }

  //! If true, theL is the local osculating surface along U at point (U,V).
  //! @param theU U parameter
  //! @param theV V parameter
  //! @param theT output flag indicating if derivative is opposite
  //! @param theL output osculating surface
  //! @return true if osculating surface was found
  bool UOsculatingSurface(double                            theU,
                          double                            theV,
                          bool&                             theT,
                          occ::handle<Geom_BSplineSurface>& theL) const;

  //! If true, theL is the local osculating surface along V at point (U,V).
  //! @param theU U parameter
  //! @param theV V parameter
  //! @param theT output flag indicating if derivative is opposite
  //! @param theL output osculating surface
  //! @return true if osculating surface was found
  bool VOsculatingSurface(double                            theU,
                          double                            theV,
                          bool&                             theT,
                          occ::handle<Geom_BSplineSurface>& theL) const;

private:
  //! Returns false if the osculating surface can't be built.
  bool buildOsculatingSurface(double                                  theParam,
                              int                                     theUKnot,
                              int                                     theVKnot,
                              const occ::handle<Geom_BSplineSurface>& theBS,
                              occ::handle<Geom_BSplineSurface>&       theL) const;

  //! Returns true if the isoparametric is quasi-punctual.
  bool isQPunctual(const occ::handle<Geom_Surface>& theS,
                   double                           theParam,
                   GeomAbs_IsoType                  theIT,
                   double                           theTolMin,
                   double                           theTolMax) const;

  //! Clear osculating flags.
  void clearOsculFlags();

private:
  occ::handle<Geom_Surface>                              myBasisSurf;
  double                                                 myTol;
  NCollection_Sequence<occ::handle<Geom_BSplineSurface>> myOsculSurf1;
  NCollection_Sequence<occ::handle<Geom_BSplineSurface>> myOsculSurf2;
  NCollection_Sequence<int>                              myKdeg;
  std::array<bool, 4>                                    myAlong;
};
