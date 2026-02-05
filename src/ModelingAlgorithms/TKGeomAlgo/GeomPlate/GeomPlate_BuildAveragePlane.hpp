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

//! This class computes an average inertial plane with an
//! array of points.
//! Computes the initial surface (average plane) in the cases
//! when the initial surface is not given.
class GeomPlate_BuildAveragePlane
{
public:
  DEFINE_STANDARD_ALLOC

  //! Tol is a Tolerance to make the difference between
  //! the result plane and the result line.
  //! if POption = 1 : automatic parametrisation
  //! if POption = 2 : parametrisation by eigen vectors
  //! if NOption = 1 : the average plane is the inertial plane.
  //! if NOption = 2 : the average plane is the plane of max. flux.
  Standard_EXPORT GeomPlate_BuildAveragePlane(const occ::handle<NCollection_HArray1<gp_Pnt>>& Pts,
                                              const int    NbBoundPoints,
                                              const double Tol,
                                              const int    POption,
                                              const int    NOption);

  //! Creates the plane from the "best vector"
  Standard_EXPORT GeomPlate_BuildAveragePlane(const NCollection_Sequence<gp_Vec>& Normals,
                                              const occ::handle<NCollection_HArray1<gp_Pnt>>& Pts);

  //! Return the average Plane.
  Standard_EXPORT occ::handle<Geom_Plane> Plane() const;

  //! Return a Line when 2 eigenvalues are null.
  Standard_EXPORT occ::handle<Geom_Line> Line() const;

  //! return OK if is a plane.
  Standard_EXPORT bool IsPlane() const;

  //! return OK if is a line.
  Standard_EXPORT bool IsLine() const;

  //! computes the minimal box to include all normal
  //! projection points of the initial array on the plane.
  Standard_EXPORT void MinMaxBox(double& Umin, double& Umax, double& Vmin, double& Vmax) const;

  Standard_EXPORT static bool HalfSpace(const NCollection_Sequence<gp_Vec>&  NewNormals,
                                        NCollection_Sequence<gp_Vec>&        Normals,
                                        NCollection_Sequence<GeomPlate_Aij>& Bset,
                                        const double                         LinTol,
                                        const double                         AngTol);

private:
  //! Computes a base of the average plane defined by (myG,N)
  //! using eigen vectors
  Standard_EXPORT void BasePlan(const gp_Vec& N);

  //! Defines the average plane.
  //! if NOption = 1 : the average plane is the inertial plane.
  //! if NOption = 2 : the average plane is the plane of max. flux.
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
