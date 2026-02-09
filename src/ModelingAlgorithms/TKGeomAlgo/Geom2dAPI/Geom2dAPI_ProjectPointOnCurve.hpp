#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Extrema_ExtPC2d.hpp>
#include <Geom2dAdaptor_Curve.hpp>
class gp_Pnt2d;
class Geom2d_Curve;

class Geom2dAPI_ProjectPointOnCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dAPI_ProjectPointOnCurve();

  Standard_EXPORT Geom2dAPI_ProjectPointOnCurve(const gp_Pnt2d&                  P,
                                                const occ::handle<Geom2d_Curve>& Curve);

  Standard_EXPORT Geom2dAPI_ProjectPointOnCurve(const gp_Pnt2d&                  P,
                                                const occ::handle<Geom2d_Curve>& Curve,
                                                const double                     Umin,
                                                const double                     Usup);

  Standard_EXPORT void Init(const gp_Pnt2d& P, const occ::handle<Geom2d_Curve>& Curve);

  Standard_EXPORT void Init(const gp_Pnt2d&                  P,
                            const occ::handle<Geom2d_Curve>& Curve,
                            const double                     Umin,
                            const double                     Usup);

  Standard_EXPORT int NbPoints() const;
  Standard_EXPORT     operator int() const;

  Standard_EXPORT gp_Pnt2d Point(const int Index) const;

  Standard_EXPORT double Parameter(const int Index) const;

  Standard_EXPORT void Parameter(const int Index, double& U) const;

  Standard_EXPORT double Distance(const int Index) const;

  Standard_EXPORT gp_Pnt2d NearestPoint() const;
  Standard_EXPORT          operator gp_Pnt2d() const;

  Standard_EXPORT double LowerDistanceParameter() const;

  Standard_EXPORT double LowerDistance() const;
  Standard_EXPORT        operator double() const;

  const Extrema_ExtPC2d& Extrema() const;

private:
  bool                myIsDone;
  int                 myIndex;
  Extrema_ExtPC2d     myExtPC;
  Geom2dAdaptor_Curve myC;
};

inline const Extrema_ExtPC2d& Geom2dAPI_ProjectPointOnCurve::Extrema() const
{
  return myExtPC;
}
