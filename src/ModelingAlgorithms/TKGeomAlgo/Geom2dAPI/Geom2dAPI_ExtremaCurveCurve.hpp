#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Extrema_ExtCC2d.hpp>
#include <Geom2dAdaptor_Curve.hpp>
class Geom2d_Curve;
class gp_Pnt2d;

class Geom2dAPI_ExtremaCurveCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dAPI_ExtremaCurveCurve(const occ::handle<Geom2d_Curve>& C1,
                                              const occ::handle<Geom2d_Curve>& C2,
                                              const double                     U1min,
                                              const double                     U1max,
                                              const double                     U2min,
                                              const double                     U2max);

  Standard_EXPORT int NbExtrema() const;
  Standard_EXPORT     operator int() const;

  Standard_EXPORT void Points(const int Index, gp_Pnt2d& P1, gp_Pnt2d& P2) const;

  Standard_EXPORT void Parameters(const int Index, double& U1, double& U2) const;

  Standard_EXPORT double Distance(const int Index) const;

  Standard_EXPORT void NearestPoints(gp_Pnt2d& P1, gp_Pnt2d& P2) const;

  Standard_EXPORT void LowerDistanceParameters(double& U1, double& U2) const;

  Standard_EXPORT double LowerDistance() const;
  Standard_EXPORT        operator double() const;

  const Extrema_ExtCC2d& Extrema() const;

private:
  bool                myIsDone;
  int                 myIndex;
  Extrema_ExtCC2d     myExtCC;
  Geom2dAdaptor_Curve myC1;
  Geom2dAdaptor_Curve myC2;
};

inline const Extrema_ExtCC2d& Geom2dAPI_ExtremaCurveCurve::Extrema() const
{
  return myExtCC;
}
