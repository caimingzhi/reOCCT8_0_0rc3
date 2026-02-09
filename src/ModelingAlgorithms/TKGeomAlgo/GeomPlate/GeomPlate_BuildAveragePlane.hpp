#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Vec.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <GeomPlate_Aij.hpp>
class Geom_Plane;
class Geom_Line;

class GeomPlate_BuildAveragePlane
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomPlate_BuildAveragePlane(const occ::handle<NCollection_HArray1<gp_Pnt>>& Pts,
                                              const int    NbBoundPoints,
                                              const double Tol,
                                              const int    POption,
                                              const int    NOption);

  Standard_EXPORT GeomPlate_BuildAveragePlane(const NCollection_Sequence<gp_Vec>& Normals,
                                              const occ::handle<NCollection_HArray1<gp_Pnt>>& Pts);

  Standard_EXPORT occ::handle<Geom_Plane> Plane() const;

  Standard_EXPORT occ::handle<Geom_Line> Line() const;

  Standard_EXPORT bool IsPlane() const;

  Standard_EXPORT bool IsLine() const;

  Standard_EXPORT void MinMaxBox(double& Umin, double& Umax, double& Vmin, double& Vmax) const;

  Standard_EXPORT static bool HalfSpace(const NCollection_Sequence<gp_Vec>&  NewNormals,
                                        NCollection_Sequence<gp_Vec>&        Normals,
                                        NCollection_Sequence<GeomPlate_Aij>& Bset,
                                        const double                         LinTol,
                                        const double                         AngTol);

private:
  Standard_EXPORT void BasePlan(const gp_Vec& N);

  Standard_EXPORT gp_Vec DefPlan(const int NOption);

  occ::handle<NCollection_HArray1<gp_Pnt>> myPts;
  double                                   myUmax;
  double                                   myVmax;
  double                                   myVmin;
  double                                   myUmin;
  occ::handle<Geom_Plane>                  myPlane;
  double                                   myTol;
  occ::handle<Geom_Line>                   myLine;
  gp_Vec                                   myOX;
  gp_Vec                                   myOY;
  gp_Pnt                                   myG;
  int                                      myNbBoundPoints;
};
