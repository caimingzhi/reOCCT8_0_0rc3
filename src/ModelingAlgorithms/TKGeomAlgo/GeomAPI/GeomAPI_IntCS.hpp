#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IntCurveSurface_HInter.hpp>
#include <Standard_Integer.hpp>
class Geom_Curve;
class Geom_Surface;
class gp_Pnt;

class GeomAPI_IntCS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomAPI_IntCS();

  Standard_EXPORT GeomAPI_IntCS(const occ::handle<Geom_Curve>&   C,
                                const occ::handle<Geom_Surface>& S);

  Standard_EXPORT void Perform(const occ::handle<Geom_Curve>&   C,
                               const occ::handle<Geom_Surface>& S);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT const gp_Pnt& Point(const int Index) const;

  Standard_EXPORT void Parameters(const int Index, double& U, double& V, double& W) const;

  Standard_EXPORT int NbSegments() const;

  Standard_EXPORT occ::handle<Geom_Curve> Segment(const int Index) const;

  Standard_EXPORT void Parameters(const int Index,
                                  double&   U1,
                                  double&   V1,
                                  double&   U2,
                                  double&   V2) const;

private:
  occ::handle<Geom_Curve> myCurve;
  IntCurveSurface_HInter  myIntCS;
};
