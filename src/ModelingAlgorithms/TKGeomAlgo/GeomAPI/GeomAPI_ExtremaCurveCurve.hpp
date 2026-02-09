#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Extrema_ExtCC.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <gp_Pnt.hpp>
class Geom_Curve;

class GeomAPI_ExtremaCurveCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomAPI_ExtremaCurveCurve();

  Standard_EXPORT GeomAPI_ExtremaCurveCurve(const occ::handle<Geom_Curve>& C1,
                                            const occ::handle<Geom_Curve>& C2);

  Standard_EXPORT GeomAPI_ExtremaCurveCurve(const occ::handle<Geom_Curve>& C1,
                                            const occ::handle<Geom_Curve>& C2,
                                            const double                   U1min,
                                            const double                   U1max,
                                            const double                   U2min,
                                            const double                   U2max);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C1, const occ::handle<Geom_Curve>& C2);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C1,
                            const occ::handle<Geom_Curve>& C2,
                            const double                   U1min,
                            const double                   U1max,
                            const double                   U2min,
                            const double                   U2max);

  Standard_EXPORT int NbExtrema() const;
  Standard_EXPORT     operator int() const;

  Standard_EXPORT void Points(const int Index, gp_Pnt& P1, gp_Pnt& P2) const;

  Standard_EXPORT void Parameters(const int Index, double& U1, double& U2) const;

  Standard_EXPORT double Distance(const int Index) const;

  bool IsParallel() const { return myExtCC.IsParallel(); }

  Standard_EXPORT void NearestPoints(gp_Pnt& P1, gp_Pnt& P2) const;

  Standard_EXPORT void LowerDistanceParameters(double& U1, double& U2) const;

  Standard_EXPORT double LowerDistance() const;
  Standard_EXPORT        operator double() const;

  const Extrema_ExtCC& Extrema() const;

  Standard_EXPORT bool TotalNearestPoints(gp_Pnt& P1, gp_Pnt& P2);

  Standard_EXPORT bool TotalLowerDistanceParameters(double& U1, double& U2);

  Standard_EXPORT double TotalLowerDistance();

private:
  Standard_EXPORT void TotalPerform();

  bool              myIsDone;
  int               myIndex;
  Extrema_ExtCC     myExtCC;
  GeomAdaptor_Curve myC1;
  GeomAdaptor_Curve myC2;
  bool              myTotalExt;
  bool              myIsInfinite;
  double            myTotalDist;
  gp_Pnt            myTotalPoints[2];
  double            myTotalPars[2];
};

inline const Extrema_ExtCC& GeomAPI_ExtremaCurveCurve::Extrema() const
{
  return myExtCC;
}
