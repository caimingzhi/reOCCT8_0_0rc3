#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Extrema_ExtPC.hpp>
#include <GeomAdaptor_Curve.hpp>
class gp_Pnt;
class Geom_Curve;

class GeomAPI_ProjectPointOnCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomAPI_ProjectPointOnCurve();

  Standard_EXPORT GeomAPI_ProjectPointOnCurve(const gp_Pnt&                  P,
                                              const occ::handle<Geom_Curve>& Curve);

  Standard_EXPORT GeomAPI_ProjectPointOnCurve(const gp_Pnt&                  P,
                                              const occ::handle<Geom_Curve>& Curve,
                                              const double                   Umin,
                                              const double                   Usup);

  Standard_EXPORT void Init(const gp_Pnt& P, const occ::handle<Geom_Curve>& Curve);

  Standard_EXPORT void Init(const gp_Pnt&                  P,
                            const occ::handle<Geom_Curve>& Curve,
                            const double                   Umin,
                            const double                   Usup);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& Curve,
                            const double                   Umin,
                            const double                   Usup);

  Standard_EXPORT void Perform(const gp_Pnt& P);

  Standard_EXPORT int NbPoints() const;
  Standard_EXPORT     operator int() const;

  Standard_EXPORT gp_Pnt Point(const int Index) const;

  Standard_EXPORT double Parameter(const int Index) const;

  Standard_EXPORT void Parameter(const int Index, double& U) const;

  Standard_EXPORT double Distance(const int Index) const;

  Standard_EXPORT gp_Pnt NearestPoint() const;
  Standard_EXPORT        operator gp_Pnt() const;

  Standard_EXPORT double LowerDistanceParameter() const;

  Standard_EXPORT double LowerDistance() const;
  Standard_EXPORT        operator double() const;

  const Extrema_ExtPC& Extrema() const;

private:
  bool              myIsDone;
  int               myIndex;
  Extrema_ExtPC     myExtPC;
  GeomAdaptor_Curve myC;
};

inline const Extrema_ExtPC& GeomAPI_ProjectPointOnCurve::Extrema() const
{
  return myExtPC;
}
