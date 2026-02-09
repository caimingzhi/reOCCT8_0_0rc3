#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Extrema_ExtSS.hpp>
class Geom_Surface;
class gp_Pnt;

class GeomAPI_ExtremaSurfaceSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomAPI_ExtremaSurfaceSurface();

  Standard_EXPORT GeomAPI_ExtremaSurfaceSurface(const occ::handle<Geom_Surface>& S1,
                                                const occ::handle<Geom_Surface>& S2);

  Standard_EXPORT GeomAPI_ExtremaSurfaceSurface(const occ::handle<Geom_Surface>& S1,
                                                const occ::handle<Geom_Surface>& S2,
                                                const double                     U1min,
                                                const double                     U1max,
                                                const double                     V1min,
                                                const double                     V1max,
                                                const double                     U2min,
                                                const double                     U2max,
                                                const double                     V2min,
                                                const double                     V2max);

  Standard_EXPORT void Init(const occ::handle<Geom_Surface>& S1,
                            const occ::handle<Geom_Surface>& S2);

  Standard_EXPORT void Init(const occ::handle<Geom_Surface>& S1,
                            const occ::handle<Geom_Surface>& S2,
                            const double                     U1min,
                            const double                     U1max,
                            const double                     V1min,
                            const double                     V1max,
                            const double                     U2min,
                            const double                     U2max,
                            const double                     V2min,
                            const double                     V2max);

  Standard_EXPORT int NbExtrema() const;
  Standard_EXPORT     operator int() const;

  Standard_EXPORT void Points(const int Index, gp_Pnt& P1, gp_Pnt& P2) const;

  Standard_EXPORT void Parameters(const int Index,
                                  double&   U1,
                                  double&   V1,
                                  double&   U2,
                                  double&   V2) const;

  Standard_EXPORT double Distance(const int Index) const;

  bool IsParallel() const { return myExtSS.IsParallel(); }

  Standard_EXPORT void NearestPoints(gp_Pnt& P1, gp_Pnt& P2) const;

  Standard_EXPORT void LowerDistanceParameters(double& U1,
                                               double& V1,
                                               double& U2,
                                               double& V2) const;

  Standard_EXPORT double LowerDistance() const;
  Standard_EXPORT        operator double() const;

  const Extrema_ExtSS& Extrema() const;

private:
  bool          myIsDone;
  int           myIndex;
  Extrema_ExtSS myExtSS;
};

inline const Extrema_ExtSS& GeomAPI_ExtremaSurfaceSurface::Extrema() const
{
  return myExtSS;
}
