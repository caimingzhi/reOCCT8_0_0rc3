#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Extrema_ExtCS.hpp>
class Geom_Curve;
class Geom_Surface;
class gp_Pnt;

class GeomAPI_ExtremaCurveSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomAPI_ExtremaCurveSurface();

  Standard_EXPORT GeomAPI_ExtremaCurveSurface(const occ::handle<Geom_Curve>&   Curve,
                                              const occ::handle<Geom_Surface>& Surface);

  Standard_EXPORT GeomAPI_ExtremaCurveSurface(const occ::handle<Geom_Curve>&   Curve,
                                              const occ::handle<Geom_Surface>& Surface,
                                              const double                     Wmin,
                                              const double                     Wmax,
                                              const double                     Umin,
                                              const double                     Umax,
                                              const double                     Vmin,
                                              const double                     Vmax);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>&   Curve,
                            const occ::handle<Geom_Surface>& Surface);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>&   Curve,
                            const occ::handle<Geom_Surface>& Surface,
                            const double                     Wmin,
                            const double                     Wmax,
                            const double                     Umin,
                            const double                     Umax,
                            const double                     Vmin,
                            const double                     Vmax);

  Standard_EXPORT int NbExtrema() const;
  Standard_EXPORT     operator int() const;

  Standard_EXPORT void Points(const int Index, gp_Pnt& P1, gp_Pnt& P2) const;

  Standard_EXPORT void Parameters(const int Index, double& W, double& U, double& V) const;

  Standard_EXPORT double Distance(const int Index) const;

  bool IsParallel() const { return myExtCS.IsParallel(); }

  Standard_EXPORT void NearestPoints(gp_Pnt& PC, gp_Pnt& PS) const;

  Standard_EXPORT void LowerDistanceParameters(double& W, double& U, double& V) const;

  Standard_EXPORT double LowerDistance() const;
  Standard_EXPORT        operator double() const;

  const Extrema_ExtCS& Extrema() const;

private:
  bool          myIsDone;
  int           myIndex;
  Extrema_ExtCS myExtCS;
};

inline const Extrema_ExtCS& GeomAPI_ExtremaCurveSurface::Extrema() const
{
  return myExtCS;
}
