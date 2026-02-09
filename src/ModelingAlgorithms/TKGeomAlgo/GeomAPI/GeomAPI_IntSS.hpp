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

class GeomAPI_IntSS
{
public:
  DEFINE_STANDARD_ALLOC

  GeomAPI_IntSS();

  GeomAPI_IntSS(const occ::handle<Geom_Surface>& S1,
                const occ::handle<Geom_Surface>& S2,
                const double                     Tol);

  void Perform(const occ::handle<Geom_Surface>& S1,
               const occ::handle<Geom_Surface>& S2,
               const double                     Tol);

  bool IsDone() const;

  int NbLines() const;

  const occ::handle<Geom_Curve>& Line(const int Index) const;

private:
  GeomInt_IntSS myIntersec;
};

inline GeomAPI_IntSS::GeomAPI_IntSS() = default;

inline GeomAPI_IntSS::GeomAPI_IntSS(const occ::handle<Geom_Surface>& S1,
                                    const occ::handle<Geom_Surface>& S2,
                                    const double                     Tol)
    : myIntersec(S1, S2, Tol, true)
{
}

inline void GeomAPI_IntSS::Perform(const occ::handle<Geom_Surface>& S1,
                                   const occ::handle<Geom_Surface>& S2,
                                   const double                     Tol)
{
  myIntersec.Perform(S1, S2, Tol, true);
}

inline bool GeomAPI_IntSS::IsDone() const
{
  return myIntersec.IsDone();
}

inline int GeomAPI_IntSS::NbLines() const
{
  return myIntersec.NbLines();
}

inline const occ::handle<Geom_Curve>& GeomAPI_IntSS::Line(const int I) const
{
  return myIntersec.Line(I);
}
