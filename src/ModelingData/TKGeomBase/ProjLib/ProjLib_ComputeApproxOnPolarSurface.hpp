#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Surface.hpp>
#include <AppParCurves_Constraint.hpp>

class Geom2d_BSplineCurve;
class Geom2d_Curve;

class ProjLib_ComputeApproxOnPolarSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ProjLib_ComputeApproxOnPolarSurface();

  Standard_EXPORT ProjLib_ComputeApproxOnPolarSurface(const occ::handle<Adaptor3d_Curve>&   C,
                                                      const occ::handle<Adaptor3d_Surface>& S,
                                                      const double Tol = 1.0e-4);

  Standard_EXPORT ProjLib_ComputeApproxOnPolarSurface(
    const occ::handle<Adaptor2d_Curve2d>& InitCurve2d,
    const occ::handle<Adaptor3d_Curve>&   C,
    const occ::handle<Adaptor3d_Surface>& S,
    const double                          Tol);

  Standard_EXPORT ProjLib_ComputeApproxOnPolarSurface(
    const occ::handle<Adaptor2d_Curve2d>& InitCurve2d,
    const occ::handle<Adaptor2d_Curve2d>& InitCurve2dBis,
    const occ::handle<Adaptor3d_Curve>&   C,
    const occ::handle<Adaptor3d_Surface>& S,
    const double                          Tol);

  Standard_EXPORT void SetDegree(const int theDegMin, const int theDegMax);

  Standard_EXPORT void SetMaxSegments(const int theMaxSegments);

  Standard_EXPORT void SetBndPnt(const AppParCurves_Constraint theBndPnt);

  Standard_EXPORT void SetMaxDist(const double theMaxDist);

  Standard_EXPORT void SetTolerance(const double theTolerance);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Curve>&   C,
                               const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Perform(
    const occ::handle<Adaptor2d_Curve2d>& InitCurve2d,
    const occ::handle<Adaptor3d_Curve>&   C,
    const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT occ::handle<Adaptor2d_Curve2d> BuildInitialCurve2d(
    const occ::handle<Adaptor3d_Curve>&   Curve,
    const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> ProjectUsingInitialCurve2d(
    const occ::handle<Adaptor3d_Curve>&   Curve,
    const occ::handle<Adaptor3d_Surface>& S,
    const occ::handle<Adaptor2d_Curve2d>& InitCurve2d);

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> BSpline() const;

  Standard_EXPORT occ::handle<Geom2d_Curve> Curve2d() const;

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT double Tolerance() const;

private:
  bool                             myProjIsDone;
  double                           myTolerance;
  occ::handle<Geom2d_BSplineCurve> myBSpline;
  occ::handle<Geom2d_Curve>        my2ndCurve;
  double                           myTolReached;
  int                              myDegMin;
  int                              myDegMax;
  int                              myMaxSegments;
  double                           myMaxDist;
  AppParCurves_Constraint          myBndPnt;
  double                           myDist;
};
