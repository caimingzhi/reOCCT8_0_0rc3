#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomInt_IntSS.hpp>
#include <Standard_Integer.hpp>
class StdFail_NotDone;
class Standard_OutOfRange;
class Geom_Surface;
class Geom_Curve;

//! This class implements methods for
//! computing the intersection curves between two surfaces.
//! The result is curves from Geom. The "domain" used for
//! a surface is the natural parametric domain
//! unless the surface is a RectangularTrimmedSurface
//! from Geom.
class GeomAPI_IntSS
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs an empty object. Use the
  //! function Perform for further initialization algorithm by two surfaces.
  GeomAPI_IntSS();

  //! Computes the intersection curves
  //! between the two surfaces S1 and S2. Parameter Tol defines the precision
  //! of curves computation. For most cases the value 1.0e-7 is recommended to use.
  //! Warning
  //! Use the function IsDone to verify that the intersections are successfully computed.I
  GeomAPI_IntSS(const occ::handle<Geom_Surface>& S1,
                const occ::handle<Geom_Surface>& S2,
                const double                     Tol);

  //! Initializes an algorithm with the
  //! given arguments and computes the intersection curves between the two surfaces S1 and S2.
  //! Parameter Tol defines the precision of curves computation. For most
  //! cases the value 1.0e-7 is recommended to use.
  //! Warning
  //! Use function IsDone to verify that the intersections are successfully computed.
  void Perform(const occ::handle<Geom_Surface>& S1,
               const occ::handle<Geom_Surface>& S2,
               const double                     Tol);

  //! Returns True if the intersection was successful.
  bool IsDone() const;

  //! Returns the number of computed intersection curves.
  //! Exceptions
  //! StdFail_NotDone if the computation fails.
  int NbLines() const;

  //! Returns the computed intersection curve of index Index.
  //! Exceptions
  //! StdFail_NotDone if the computation fails.
  //! Standard_OutOfRange if Index is out of range [1, NbLines] where NbLines
  //! is the number of computed intersection curves.
  const occ::handle<Geom_Curve>& Line(const int Index) const;

private:
  GeomInt_IntSS myIntersec;
};

inline GeomAPI_IntSS::GeomAPI_IntSS() = default;

//=================================================================================================

inline GeomAPI_IntSS::GeomAPI_IntSS(const occ::handle<Geom_Surface>& S1,
                                    const occ::handle<Geom_Surface>& S2,
                                    const double                     Tol)
    : myIntersec(S1, S2, Tol, true)
{
}

//=================================================================================================

inline void GeomAPI_IntSS::Perform(const occ::handle<Geom_Surface>& S1,
                                   const occ::handle<Geom_Surface>& S2,
                                   const double                     Tol)
{
  myIntersec.Perform(S1, S2, Tol, true);
}

//=================================================================================================

inline bool GeomAPI_IntSS::IsDone() const
{
  return myIntersec.IsDone();
}

//=================================================================================================

inline int GeomAPI_IntSS::NbLines() const
{
  return myIntersec.NbLines();
}

//=================================================================================================

inline const occ::handle<Geom_Curve>& GeomAPI_IntSS::Line(const int I) const
{
  return myIntersec.Line(I);
}
